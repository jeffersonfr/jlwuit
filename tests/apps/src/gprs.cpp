#include "gprs.h"
#include "jkeyboard.h"
#include "jmessagedialogbox.h"
#include "jsocket.h"
#include "jdebug.h"

#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void sigquit(int)
{
	*(volatile char *)NULL;
}

static bool perfil_compare(const GPRSDB::perfil_t &a, const GPRSDB::perfil_t &b) 
{
	if (strcmp(a.name.c_str(), b.name.c_str()) < 0) {
		return true;
	}

	return false;
}

GPRSDB::GPRSDB(std::string file)
{
	_file = file;
}

GPRSDB::~GPRSDB()
{
}

bool GPRSDB::Load()
{
	XmlDocument doc(_file.c_str());

	if (!doc.LoadFile()) {
		return false;
	}

	XmlElement *psg;

	// parser servern node
	psg = doc.RootElement()->FirstChildElement();

	do {
		std::string name,
			login,
			password,
			phone,
			apn;

		if (psg == NULL || strcmp(psg->Value(), "perfil") != 0) {
			break;
		}

		if (psg->Attribute("name") != NULL) {
			name = psg->Attribute("name");
		}

		if (psg->Attribute("login") != NULL) {
			login = psg->Attribute("login");
		}

		if (psg->Attribute("password") != NULL) {
			password = psg->Attribute("password");
		}

		if (psg->Attribute("phone") != NULL) {
			phone = psg->Attribute("phone");
		}

		if (psg->Attribute("apn") != NULL) {
			apn = psg->Attribute("apn");
		}

		if (name != "") {
			struct perfil_t t;

			t.name = name;
			t.login = login;
			t.password = password;
			t.phone = phone;
			t.apn = apn;

			perfis.push_back(t);
		}
	} while ((psg = psg->NextSiblingElement("perfil")) != NULL);

	std::sort(perfis.begin(), perfis.end(), perfil_compare);

	return true;
}

int GPRSDB::GetCapacity()
{
	return 10;
}

int GPRSDB::GetSize()
{
	return perfis.size();
}

struct GPRSDB::perfil_t * GPRSDB::Get(int i)
{
	if (i < 0 || i >= GetSize()) {
		return NULL;
	}

	return &perfis[i];
}

void GPRSDB::Remove(int i)
{
	if (i < 0 || i >= GetSize()) {
		return;
	}

	perfis.erase(perfis.begin()+i);

	std::sort(perfis.begin(), perfis.end(), perfil_compare);
}

bool GPRSDB::IsFull()
{
	return (GetSize() >= GetCapacity());
}

bool GPRSDB::IsEmpty()
{
	return (GetSize() == 0);
}

bool GPRSDB::Add(struct GPRSDB::perfil_t * p)
{
	if (IsFull() == true) {
		return false;
	}

	struct perfil_t t;

	t.name = p->name;
	t.login = p->login;
	t.password = p->password;
	t.phone = p->phone;
	t.apn = p->apn;

	perfis.push_back(t);

	std::sort(perfis.begin(), perfis.end(), perfil_compare);

	return true;
}

bool GPRSDB::Update(int i, struct GPRSDB::perfil_t * p)
{
	if (i < 0 || i >= GetSize()) {
		return false;
	}

	struct perfil_t t = perfis[i];

	perfis[i].name = p->name;
	perfis[i].login = p->login;
	perfis[i].password = p->password;
	perfis[i].phone = p->phone;
	perfis[i].apn = p->apn;

	std::sort(perfis.begin(), perfis.end(), perfil_compare);

	return false;
}

int GPRSDB::Find(struct GPRSDB::perfil_t * p)
{
	for (int i=0; i<(int)perfis.size(); i++) {
		struct perfil_t t = perfis[i];

		if (t.name == p->name &&
				t.login == p->login && 
				t.password == p->password && 
				t.phone == p->phone && 
				t.apn == p->apn) {
			return i;
		}
	}

	return -1;
}

bool GPRSDB::Save()
{
	std::ostringstream o;

	o << "<modem>" << std::endl;

	for (int i=0; i<(int)perfis.size(); i++) {
		struct perfil_t t = perfis[i];

		o << "<perfil name=\"" << t.name 
			<< "\" login=\"" << t.login 
			<< "\" password=\"" << t.password
			<< "\" phone=\"" << t.phone
			<< "\" apn=\"" << t.apn << "\" />" << std::endl;
	}

	o << "</modem>" << std::endl;

	XmlDocument doc;

	doc.Parse(o.str().c_str());

	if (doc.Error()) {
		return false;
	}

	doc.SaveFile(_file.c_str());

	return true;
}

void GPRSDB::RemoveAll()
{
	perfis.clear();
}

ModemRequest::ModemRequest()
{
	_alive = false;
	_signal = 0;
	_type = -1;
	_state_index = 0;
	_state = Request_Offline; 
	_buffer =(char *)malloc( 256 *sizeof(char));                                                                                               

	_fd = open("/dev/ttyUSB1", O_RDWR | O_NONBLOCK | O_NDELAY |  O_NOCTTY);

	if (_fd < 0) {
		_fd = -1;
	}

}

ModemRequest::~ModemRequest()
{
	if (_fd > 0) {
		close(_fd);
	}
}


int ModemRequest::GetSignal()
{
	return _signal;
}

bool ModemRequest::GetStatus()
{
	JDEBUG(JINFO, "status");

	FILE *fp;

	if (!(fp=fopen("/proc/sys/net/ipv4/conf/ppp0/tag", "r" ))){
		return false;
	}

	fclose(fp);

	return true;
}


int ModemRequest::GetNetworkType()
{
	// jthread::AutoLock lock(&_mutex);
	return _type;
}

modem_request_t ModemRequest::GetState()
{

	if (!GetStatus()){
		_state = Request_Offline;
	}
	return _state;
}


void ModemRequest::SetState(modem_request_t state)
{
	if (state == Request_Waiting){
		waiting_time = time(NULL);
	}
	_state = state;
}


bool ModemRequest::isConnectionTimeout(){
	if (_state == Request_Waiting){
		double d;
		d = difftime( time(NULL), waiting_time);
		if ( d > 20.0 )
			return true;
	}
	return false;
}


int ModemRequest::GetStateIdentifier()
{
	return _state_index;
}

void ModemRequest::GetCarrier()
{
	JDEBUG(JINFO, "carrier");

	int bytes;
	unsigned int SecondsPast, 
							 SpeedUp, 
							 SpeedDown, 
							 TX, 
							 RX;
	char *byte_signal,
			 *byte_mode;

	bytes = read(_fd, _buffer, 255);
	_buffer2=strchr(_buffer,'^');
	_buffer[bytes]=0x00;

	if (_buffer2){
		strcpy(_buffer, _buffer2);
		if (_buffer[0] == '^'){
			switch (_buffer[1]) {
				case 'B': 
					break;
				case 'M':
					byte_mode = _buffer+8;
					if (byte_mode[0] == '4'){
						_type = 1;
						_state = Request_Online;
						_state_index++;
					}
					if (byte_mode[0] == '5'){
						_type = 2;
						_state = Request_Online;
						_state_index++;
					}
					break;
				case 'D': 
					sscanf(_buffer+11,"%X,%X,%X,%X,%X", &SecondsPast,&SpeedUp,&SpeedDown,&TX,&RX);
					if (SecondsPast > 1){
						_alive = true;
						_state = Request_Online;
						_state_index++;
					}
					break;
				case 'R': 
					byte_signal = _buffer + 6;
					_signal = atoi((const char *)byte_signal[0]); 
					_state_index++;
					break;
			}
		}
	}
}

void ModemRequest::Stop()
{
	_alive = false;
}

ModemConnectionConfiguration::ModemConnectionConfiguration(GPRSDB *db, int x, int y):
	jgui::Frame("Configuracao GPRS", x, y, 850, 520)
{
	jgui::jinsets_t insets = GetInsets();

	_state = 0;

	_db = db;
	_frame = NULL;

	int fwidth = 250,
			fheight = 40;

	{
		lnome = new jgui::Label("Nome", insets.left, insets.top, fwidth, fheight);
		llogin = new jgui::Label("Login", insets.left, lnome->GetY()+lnome->GetHeight()+10, fwidth, fheight);
		lsenha = new jgui::Label("Senha", insets.left, llogin->GetY()+llogin->GetHeight()+10, fwidth, fheight);
		ltelefone = new jgui::Label("Telefone", insets.left, lsenha->GetY()+lsenha->GetHeight()+10, fwidth, fheight);
		lapn = new jgui::Label("APN", insets.left, ltelefone->GetY()+ltelefone->GetHeight()+10, fwidth, fheight);

		rnome = new jgui::TextField(insets.left+fwidth+10, insets.top, _size.width-insets.left-insets.right-fwidth-10, fheight);
		rlogin = new jgui::TextField(insets.left+fwidth+10, lnome->GetY()+lnome->GetHeight()+10, _size.width-insets.left-insets.right-fwidth-10, fheight);
		rsenha = new jgui::TextField(insets.left+fwidth+10, llogin->GetY()+llogin->GetHeight()+10, _size.width-insets.left-insets.right-fwidth-10, fheight);
		rtelefone = new jgui::TextField(insets.left+fwidth+10, lsenha->GetY()+lsenha->GetHeight()+10, _size.width-insets.left-insets.right-fwidth-10, fheight);
		rapn = new jgui::TextField(insets.left+fwidth+10, ltelefone->GetY()+ltelefone->GetHeight()+10, _size.width-insets.left-insets.right-fwidth-10, fheight);
	}

	rnome->SetCaretVisible(false);
	rlogin->SetCaretVisible(false);
	rsenha->SetCaretVisible(false);
	rtelefone->SetCaretVisible(false);
	rapn->SetCaretVisible(false);

	rnome->SetNextComponentFocus(NULL, NULL, NULL, rlogin);
	rlogin->SetNextComponentFocus(NULL, NULL, rnome, rsenha);
	rsenha->SetNextComponentFocus(NULL, NULL, rlogin, rtelefone);
	rtelefone->SetNextComponentFocus(NULL, NULL, rsenha, rapn);
	rapn->SetNextComponentFocus(NULL, NULL, rtelefone, NULL);

	Add(lnome);
	Add(llogin);
	Add(lsenha);
	Add(ltelefone);
	Add(lapn);
	Add(rnome);
	Add(rlogin);
	Add(rsenha);
	Add(rtelefone);
	Add(rapn);

	rnome->RequestFocus();

	AddSubtitle("icons/blue_icon.png", "Adicionar");

	Pack();
}

ModemConnectionConfiguration::ModemConnectionConfiguration(GPRSDB *db, int index, int x, int y):
	jgui::Frame("Configuracao GPRS", x, y, 850, 520)
{
	jgui::jinsets_t insets = GetInsets();

	_state = 1;
	_index = index;

	_db = db;
	_frame = NULL;

	int fwidth = 250,
			fheight = 40;

	{
		lnome = new jgui::Label("Nome", insets.left, insets.top, fwidth, fheight);
		llogin = new jgui::Label("Login", insets.left, lnome->GetY()+lnome->GetHeight()+10, fwidth, fheight);
		lsenha = new jgui::Label("Senha", insets.left, llogin->GetY()+llogin->GetHeight()+10, fwidth, fheight);
		ltelefone = new jgui::Label("Telefone", insets.left, lsenha->GetY()+lsenha->GetHeight()+10, fwidth, fheight);
		lapn = new jgui::Label("APN", insets.left, ltelefone->GetY()+ltelefone->GetHeight()+10, fwidth, fheight);

		rnome = new jgui::TextField(insets.left+fwidth+10, insets.top, _size.width-insets.left-insets.right-fwidth-10, fheight);
		rlogin = new jgui::TextField(insets.left+fwidth+10, lnome->GetY()+lnome->GetHeight()+10, _size.width-insets.left-insets.right-fwidth-10, fheight);
		rsenha = new jgui::TextField(insets.left+fwidth+10, llogin->GetY()+llogin->GetHeight()+10, _size.width-insets.left-insets.right-fwidth-10, fheight);
		rtelefone = new jgui::TextField(insets.left+fwidth+10, lsenha->GetY()+lsenha->GetHeight()+10, _size.width-insets.left-insets.right-fwidth-10, fheight);
		rapn = new jgui::TextField(insets.left+fwidth+10, ltelefone->GetY()+ltelefone->GetHeight()+10, _size.width-insets.left-insets.right-fwidth-10, fheight);

		rnome->SetCaretVisible(false);
		rlogin->SetCaretVisible(false);
		rsenha->SetCaretVisible(false);
		rtelefone->SetCaretVisible(false);
		rapn->SetCaretVisible(false);
	}

	if (_db->GetSize() > 0) {
		struct GPRSDB::perfil_t *t = _db->Get(_index);

		rnome->Insert(t->name);
		rlogin->Insert(t->login);
		rsenha->Insert(t->password);
		rtelefone->Insert(t->phone);
		rapn->Insert(t->apn);
	}

	rnome->SetNextComponentFocus(NULL, NULL, NULL, rlogin);
	rlogin->SetNextComponentFocus(NULL, NULL, rnome, rsenha);
	rsenha->SetNextComponentFocus(NULL, NULL, rlogin, rtelefone);
	rtelefone->SetNextComponentFocus(NULL, NULL, rsenha, rapn);
	rapn->SetNextComponentFocus(NULL, NULL, rtelefone, NULL);

	Add(lnome);
	Add(llogin);
	Add(lsenha);
	Add(ltelefone);
	Add(lapn);
	Add(rnome);
	Add(rlogin);
	Add(rsenha);
	Add(rtelefone);
	Add(rapn);

	rnome->RequestFocus();

	AddSubtitle("icons/blue_icon.png", "Confirmar");
	AddSubtitle("icons/yellow_icon.png", "Remover");

	Pack();
}

ModemConnectionConfiguration::~ModemConnectionConfiguration()
{
	jthread::AutoLock lock(&_mutex);

	delete lnome;
	delete llogin;
	delete lsenha;
	delete ltelefone;
	delete lapn;
	delete rnome;
	delete rlogin;
	delete rsenha;
	delete rtelefone;
	delete rapn;
}

void ModemConnectionConfiguration::KeyboardPressed(jgui::KeyEvent *event)
{
	Component *owner = GetFocusOwner();
	
	if (owner == rtelefone) {
		int code = event->GetKeyCode();

		if (code >= '0' && code <= '9') {
			owner->ProcessEvent(event);
		}
	} else {
		owner->ProcessEvent(event);
	}
}

bool ModemConnectionConfiguration::ProcessEvent(jgui::KeyEvent *event)
{
	jthread::AutoLock lock(&_mutex);

	if (event->GetType() != jgui::JKT_PRESSED) {
		return false;
	}

	if (event->GetSymbol() == jgui::JKS_YELLOW || event->GetSymbol() == jgui::JKS_F3) {
		if (_state == 1) {
			_db->Remove(_index);
			_db->Save();

			_frame = new jgui::MessageDialogBox("Aviso", "GPRS removido com sucesso", _location.x-50, _location.y+_size.height+10);

			_frame->SetLocation((1920-_frame->GetWidth())/2, (1080-_frame->GetHeight())/2);
			_frame->Show();

			delete _frame;
			_frame = NULL;

			Hide();	
			_frame_sem.Notify();
		}
	} else if (event->GetSymbol() == jgui::JKS_BLUE || event->GetSymbol() == jgui::JKS_F4) {
		struct GPRSDB::perfil_t t;

		t.name = rnome->GetText();
		t.login = rlogin->GetText();
		t.password = rsenha->GetText();
		t.phone = rtelefone->GetText();
		t.apn = rapn->GetText();

		if (t.name == "" || t.login == "" || t.password == "") {
			_frame = new jgui::MessageDialogBox("Aviso", "Informe os campos nome, login e senha", _location.x-50, _location.y+_size.height+10);

			_frame->SetLocation((1920-_frame->GetWidth())/2, (1080-_frame->GetHeight())/2);
			_frame->Show();

			delete _frame;
			_frame = NULL;
		} else {
			if (_state == 0) {
				if (_db->Add(&t) == false) {
					_frame = new jgui::MessageDialogBox("Aviso", "Registro cheio.", _location.x-50, _location.y+_size.height+10);

					_frame->SetLocation((1920-_frame->GetWidth())/2, (1080-_frame->GetHeight())/2);
					_frame->Show();

					delete _frame;
					_frame = NULL;
				} else {
					_frame = new jgui::MessageDialogBox("Aviso", "Novo perfil adicionado.", _location.x-50, _location.y+_size.height+10);

					_frame->SetLocation((1920-_frame->GetWidth())/2, (1080-_frame->GetHeight())/2);
					_frame->Show();

					delete _frame;
					_frame = NULL;
				}
			} else {
				_db->Update(_index, &t);
			}

			Hide();
			_frame_sem.Notify();
		}
	} else if (event->GetSymbol() == jgui::JKS_ENTER) {
		if (GetFocusOwner() != NULL) {
			jgui::TextField *f = (jgui::TextField *)GetFocusOwner();

			std::string tmp = f->GetText();

			if (GetFocusOwner() == rtelefone) {
				_frame = new jgui::Keyboard(_location.x+_size.width+20, _location.y, jgui::JKB_NUMERIC, false);
			} else {
				_frame = new jgui::Keyboard(_location.x+_size.width+20, _location.y, jgui::JKB_ALPHA_NUMERIC, false);
			}

			((jgui::Keyboard *)_frame)->SetTextSize(20);
			((jgui::Keyboard *)_frame)->SetText(f->GetText());
			((jgui::Keyboard *)_frame)->RegisterKeyboardListener(this);

			((jgui::Keyboard *)_frame)->Show();

			if (((jgui::Keyboard *)_frame)->GetLastKeyCode() != jgui::JKS_BLUE && ((jgui::Keyboard *)_frame)->GetLastKeyCode() != jgui::JKS_F4) {
				f->SetText(tmp);
			}

			delete _frame;
			_frame = NULL;
		}
	}

	return true;
}

ModemConnectionUpdate::ModemConnectionUpdate(ModemConnection *modem):
	jthread::Thread(jthread::JTT_JOINABLE)
{
	_modem = modem;

	_request = new ModemRequest();
}

ModemConnectionUpdate::~ModemConnectionUpdate()
{
	delete _request;
}

void ModemConnectionUpdate::Run()
{
	_alive = true;

	int old_state = 0, 
			new_state = 0;

	while (_alive == true) {
		if (_request->isConnectionTimeout()){
			_modem->SetStatus("Desconectado");
			PPPConnection::GetInstance()->Close();
		}

		_request->GetCarrier();

		new_state = _request->GetStateIdentifier();

		if (new_state > old_state) {
			int s = _request->GetSignal();

			if (s >= 0) {
				_modem->SetSignal(s);
			} else {
				_modem->SetSignal(0);
			}

			if (_request->GetState() == Request_Offline) {
				_modem->SetStatus("Desconectado");
				_modem->SetNetworkType("");
			} else if (_request->GetState() == Request_Online) {
				int id = _request->GetNetworkType();
				_modem->SetStatus("Conectado");
				if (id == 1) {
					_modem->SetNetworkType("GSM");
				} else if (id == 2) {
					_modem->SetNetworkType("3G");
				}
				_alive = false;
			} else if (_request->GetState() == Request_Waiting) {
				_modem->SetStatus("Conectando...");
			}
		}

		old_state = new_state;

		sleep(1);
	}
}

void ModemConnectionUpdate::Stop()
{
	_alive = false;
	_request->Stop();
}

ModemConnectionUpdate *update = NULL;

PPPConnection *PPPConnection::_instance = NULL;

PPPConnection::PPPConnection()
{
	_pid = -1;
}

PPPConnection::~PPPConnection()
{
}

PPPConnection * PPPConnection::GetInstance()
{
	if (_instance == NULL) {
		_instance = new PPPConnection();
	}

	return _instance;
}

int PPPConnection::GetPID()
{
	return _pid;
}

void PPPConnection::SetPID(int pid)
{
	_pid = pid;
}

void PPPConnection::Close()
{
	int status;
	pid_t p;

	if (_pid > 0){
		p = waitpid(_pid, &status, WNOHANG);

		if ((WIFEXITED(status) || WIFSIGNALED(status) || WIFSTOPPED(status)) == 0) {
			kill(_pid, SIGKILL);
			_pid = -1;
		}
	}
}

ModemConnection::ModemConnection(int x, int y):
	jgui::Frame("Conexao com Internet", x, y, 850, 720)
{
	jgui::jinsets_t insets = GetInsets();

	_frame = NULL;

	_db = new GPRSDB("./config/modem.xml");

	_db->Load();

	int fheight = 40;

	{
		lperfil = new jgui::Label("GPRS", insets.left, insets.top, _size.width-insets.left-insets.right, fheight);
		rstatus = new jgui::Label("Desconectado", _size.width-insets.right-500, insets.top, 500, fheight);
		list = new jgui::ListBox(insets.left, lperfil->GetY()+lperfil->GetHeight()+10, _size.width-insets.left-insets.right, 205);
		loperadora = new jgui::Label("<unknown>", insets.left, list->GetY()+list->GetHeight()+15, 500, fheight);
		_signal = new InfoSignal(_size.width-insets.right-150, list->GetY()+list->GetHeight()+10, 150, 60);
	}

	jgui::Color c = GetBackgroundColor();

	loperadora->SetBackgroundVisible(false);
	loperadora->SetHorizontalAlign(jgui::JHA_LEFT);
	loperadora->SetBorder(jgui::JCB_EMPTY);

	lperfil->SetBackgroundVisible(false);
	lperfil->SetBorder(jgui::JCB_EMPTY);

	rstatus->SetBackgroundVisible(false);
	rstatus->SetHorizontalAlign(jgui::JHA_RIGHT);
	rstatus->SetBorder(jgui::JCB_EMPTY);

	_signal->SetBackgroundColor(c);

	if (_db->GetSize() > 0) {
		loperadora->SetText(_db->Get(0)->name);
	}

	for (int i=0; i<_db->GetSize(); i++) {
		list->AddTextItem(_db->Get(i)->name);
	}

	Add(_signal);
	Add(lperfil);
	Add(list);
	Add(loperadora);
	Add(rstatus);

	list->RequestFocus();

	AddSubtitle("icons/blue_icon.png", "Conectar");
	AddSubtitle("icons/yellow_icon.png", "Adicionar");
	AddSubtitle("icons/green_icon.png", "Editar");

	update = new ModemConnectionUpdate(this);

	update->Start();

	Pack();
}

ModemConnection::~ModemConnection()
{
	/*
	int pid = PPPConnection::GetInstance()->GetPID();

	if (pid != -1) {
		kill(pid, SIGQUIT);

		PPPConnection::GetInstance()->SetPID(-1);

		sleep(1);
	}
	*/

	update->Stop();
	update->WaitThread();

	if (_frame != NULL) {
		_frame->Release();
	}

	jthread::AutoLock lock(&_mutex);

	_db->Save();

	delete _db;
	delete _signal;
	delete lperfil;
	delete list;
	delete loperadora;
	delete rstatus;
}

void ModemConnection::SetSignal(int s)
{
	_signal->SetSignal(s);
	_signal->Repaint();
}

void ModemConnection::SetNetworkType(std::string s)
{
	std::string o;

	if (_db->GetSize() > 0) {
		o = _db->Get(list->GetCurrentIndex())->name;

		if (s != "") {
			o = o + " [" + s + "]";
		}
	} else {
		o = "<unknown>";
	}

	loperadora->SetText(o);
}

void ModemConnection::SetStatus(std::string s)
{
	rstatus->SetText(s);
}

bool ModemConnection::ProcessEvent(jgui::KeyEvent *event)
{
	jthread::AutoLock lock(&_mutex);

	if (event->GetType() != jgui::JKT_PRESSED) {
		return false;
	}

	if (event->GetSymbol() == jgui::JKS_BLUE || event->GetSymbol() == jgui::JKS_F4) {
		if (list->GetItemsSize() == 0) {
			_frame = new jgui::MessageDialogBox("Aviso", "Nenhum perfil selecionado", _location.x-50, _location.y+_size.height+10);

			_frame->SetLocation((1920-_frame->GetWidth())/2, (1080-_frame->GetHeight())/2);
			_frame->Show();

			delete _frame;
			_frame = NULL;

			return false;
		} else {
			if (_db->GetSize() > 0) {
				loperadora->SetText(_db->Get(list->GetCurrentIndex())->name);
			}
		}

		// rstatus->SetText("Reinicializando o servico ...");
		int pid = PPPConnection::GetInstance()->GetPID();

		if (pid != -1) {
			kill(pid, SIGQUIT);

			PPPConnection::GetInstance()->SetPID(-1);

			sleep(1);
		}

		update->Stop();
		update->WaitThread();

		rstatus->SetText("Conectando ...");

		struct GPRSDB::perfil_t *perfil = _db->Get(list->GetCurrentIndex());

		// gerando arquivos
		int p = open("/tmp/m.ppp", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);

		if (p > 0) {
			std::ostringstream o;

			o << "/dev/ttyUSB0" << "\n"
				<< "460800" << "\n"
				<< "noipdefault" << "\n"
				<< "defaultroute" << "\n"
				<< "persist" << "\n"
				<< "debug" << "\n"
				<< "noauth" << "\n"
				<< "nodetach" << "\n"
				<< "usepeerdns" << "\n"
				<< "novj" << "\n"
				<< "novjccomp" << "\n"
				<< "nopcomp" << "\n"
				<< "nodeflate" << "\n"
				// << "user claro\n"
				// << "password claro\n"
				<< "user " << perfil->login << "\n"
				<< "password " << perfil->password << "\n"
				<< "connect \"/usr/bin/chat -vf /tmp/m.chat.ppp\"" << "\n"
				<< std::flush;

			write(p, o.str().c_str(), o.str().size());

			close(p);
		}

		int c = open("/tmp/m.chat.ppp", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);

		if (c > 0) {
			std::ostringstream o;

			o << "TIMEOUT 30" << "\n"
				<< "ABORT BUSY" << "\n"
				<< "ABORT 'NO CARRIER'" << "\n"
				<< "ABORT VOICE" << "\n"
				<< "ABORT 'NO DIALTONE'" << "\n"
				<< "ABORT 'NO DIAL TONE'" << "\n"
				<< "ABORT 'NO ANSWER'" << "\n"
				<< "ABORT DELAYED" << "\n"
				<< "\"\" ATZ" << "\n"
				<< "OK ATQ0V1E1S0=0&C1&D2" << "\n"
				// << "OK " << "ATDT*99***1#" << "\n"
				<< "OK ATDT" << perfil->phone << "\n"
				<< "CONNECT \"\"" << "\n"
				<< std::flush;

			write(c, o.str().c_str(), o.str().size());

			close(c);
		}

		update->_request->SetState(Request_Waiting);

		switch (pid = fork()) {
			case -1: 
				break;
			case 0:
				{
					char *args[] = {(char *)"/usr/bin/pppd", (char *)"file", (char *)"/tmp/m.ppp", (char *)NULL};

					// signal(SIGQUIT, sigquit);
					// unshare(CLONE_FILES | CLONE_FS | CLONE_NEWNS);

					execve(args[0], args, NULL);

					exit(0);
				}
			default:
				PPPConnection::GetInstance()->SetPID(pid);

				sleep(32);

				/* WARN:: codigo comentado sem explicacao
					 if (get_stats() == false) {
					 int status;
					 pid_t p;

					 p = waitpid(pid, &status, WNOHANG);

					 if ((WIFEXITED(status) || WIFSIGNALED(status) || WIFSTOPPED(status)) == 0) {

					 kill(pid, SIGKILL);
					 }
					 }
					 */

				update->Start();
		}
	} else if (event->GetSymbol() == jgui::JKS_YELLOW || event->GetSymbol() == jgui::JKS_F3) {
		// window->SetOpacity(window, 0x00);

		_frame = new ModemConnectionConfiguration(_db, _location.x, _location.y);

		_frame->Show();

		if (((jgui::Keyboard *)_frame)->GetLastKeyCode() == jgui::JKS_BLUE || ((jgui::Keyboard *)_frame)->GetLastKeyCode() == jgui::JKS_F4) {
			list->RemoveItems();

			for (int i=0; i<_db->GetSize(); i++) {
				struct GPRSDB::perfil_t *t = _db->Get(i);

				list->AddTextItem(t->name);
			}

			list->Repaint();
		}

		delete _frame;
		_frame = NULL;

		// window->SetOpacity(window, 0xff);
	} else if (event->GetSymbol() == jgui::JKS_GREEN || event->GetSymbol() == jgui::JKS_F2) {
		if (_db->GetSize() == 0) {
			_frame = new jgui::MessageDialogBox("Aviso", "Nenhum perfil selecionado", _location.x-50, _location.y+_size.height+10);

			_frame->SetLocation((1920-_frame->GetWidth())/2, (1080-_frame->GetHeight())/2);
			_frame->Show();

			delete _frame;
			_frame = NULL;
		} else {
			// window->SetOpacity(window, 0x00);

			_frame = new ModemConnectionConfiguration(_db, list->GetCurrentIndex(), _location.x, _location.y);

			_frame->Show();

			if (((jgui::Keyboard *)_frame)->GetLastKeyCode() == jgui::JKS_BLUE || ((jgui::Keyboard *)_frame)->GetLastKeyCode() == jgui::JKS_F4) {
				list->RemoveItems();

				for (int i=0; i<_db->GetSize(); i++) {
					struct GPRSDB::perfil_t *t = _db->Get(i);

					list->AddTextItem(t->name);
				}

				list->Repaint();
			}

			delete _frame;
			_frame = NULL;

			// window->SetOpacity(window, 0xff);
		}
	}

	return true;
}

