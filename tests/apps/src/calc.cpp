/***************************************************************************
 *   Copyright (C) 2005 by Jeff Ferr                                       *
 *   root@sat                                                              *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#include "calc.h"
#include "lookandfeel.h"

#include <string.h>
#include <math.h>

#define BUTTON_GAPX		8
#define BUTTON_GAPY		8
#define BUTTON_WIDTH	90
#define BUTTON_HEIGHT	80

#define MARGIN_LEFT		BUTTON_GAPX
#define MARGIN_RIGHT	BUTTON_GAPY
#define MARGIN_TOP		BUTTON_GAPY+BUTTON_HEIGHT+BUTTON_GAPY
#define MARGIN_BOTTOM	BUTTON_GAPY

std::string buttons[] = { 
	"7", "8", "9", "/", "C",
	"4", "5", "6", "x", "raiz",
	"1", "2", "3", "-", "del",
	"0", ".", "%", "+", "=",
};

Calc::Calc(int x, int y):
 	jlwuit::Scene(x, y, 0, 0)
{
	_number0 = "";
	_number1 = "";
	_operation = "";
	_state = 1;
	_index = 0;
	
	SetSize(MARGIN_LEFT+MARGIN_RIGHT+5*(BUTTON_WIDTH+BUTTON_GAPX)-BUTTON_GAPX, MARGIN_TOP+MARGIN_BOTTOM+4*(BUTTON_HEIGHT+BUTTON_GAPY)-BUTTON_GAPY);
}

Calc::~Calc() 
{
	jthread::AutoLock lock(&_mutex);
}

void Calc::Process(std::string type)
{
	std::string button = buttons[_index];

	if (type == ".") {
		if (_state == 2 || _state == 5) {
			if (_number0.size() < 9) {
				if (strchr(_number0.c_str(), '.') == NULL) {
					_number0 += ".";
				}
			}
		} else if (_state == 4) {
			if (_number1.size() < 9) {
				if (strchr(_number1.c_str(), '.') == NULL) {
					_number1 += ".";
				}
			}
		}
	} else if (type == "0" ||
			type == "1" ||
			type == "2" ||
			type == "3" ||
			type == "4" ||
			type == "5" ||
			type == "6" ||
			type == "7" ||
			type == "8" ||
			type == "9") {
		if (_state == 1 || _state == 2 || _state == 5 || _state == 7 || _state == 8) {
			if (_state == 1 || _state == 5 || _state == 7) {
				_number0 = button;
			} else {
				if (_number0.size() < 9 && (_number0 != "0" || button != "0")) {
					if (_number0 == "0") {
						_number0 = button;
					} else {
						_number0 += button;
					}
				}
			}

			_state = 2;
		} else if (_state == 3 || _state == 4 || _state == 6) {
			if (_state == 3 || _state == 6) {
				_number1 = button;
			} else {
				if (_number1.size() < 9 && (_number1 != "0" || button != "0")) {
					if (_number1 == "0") {
						_number1 = button;
					} else {
						_number1 += button;
					}
				}
			}

			_state = 4;
		}
	} else if (type == "+" ||
			type == "-" ||
			type == "x" ||
			type == "/") {
		if (_state == 1) {
			if (type == "-") {
				_state = 8;
				_number0 = "-";
			}
		} else if (_state == 2) {
			_state = 3;
			_operation = type;
		} else if (_state == 3) {
			_state = 3;
			_operation = type;
		} else if (_state == 5) {
			_state = 6;
			_operation = type;
		} else if (_state == 6) {
			_state = 6;
			_operation = type;
		} else if (_state == 7) {
			_state = 3;
			_operation = type;
		} else if (_state == 4) {
			Process("=");

			_operation = type;
			_state = 3;
		}

		if (_state == 3 || _state == 6) {
			_operation = button;
		}
	} else if (type == "raiz") {
		if (_state == 2 || _state == 3 || _state == 4 || _state == 5 || _state == 6 || _state == 7) {
			if (_state == 4) {
				_number0 = _number1;
			}

			_state = 7;

			double a1 = atof(_number0.c_str());
			char *i1,
					 tmp[255];

			if (a1 < 0) {
				_state = 255;
				_text = "Erro";

				return;
			}

			a1 = sqrt(a1);

			if ((a1-(int)a1) > 0.0) {
				if (a1 >= 100000000) {
					sprintf(tmp, "%g", a1);
				} else {
					sprintf(tmp, "%f", a1);
				}
			} else {
				sprintf(tmp, "%d", (int)a1);
			}

			// INFO:: tirar zeros a direitaa
			std::string zeros = tmp;

			if (strchr(tmp, '.') != NULL) {
				while (zeros.size() > 1 && (i1 = (char *)strrchr(zeros.c_str(), '0')) != NULL) {
					int d1 = (int)(i1-zeros.c_str());

					if (d1 == (int)(zeros.size()-1)) {
						zeros = zeros.substr(0, zeros.size()-1);
					} else {
						break;
					}
				}

				if (zeros.size() > 1 && zeros[zeros.size()-1] == '.') {
					zeros = zeros.substr(0, zeros.size()-1);
				}
			}

			_number0 = zeros;
		}
	} else if (type == "=") {
		if (_state == 4) {
			_state = 5;

			double a1 = atof(_number0.c_str()),
						 a2 = atof(_number1.c_str());
			char *i1,
					 tmp[255];

			if (_operation == "/") {
				if (a2 == 0) {
					_state = 255;

					_text = "Erro";
				} else {
					a1 /= a2;
				}
			} else if (_operation == "x") {
				a1 *= a2;
			} else if (_operation == "+") {
				a1 += a2;
			} else if (_operation == "-") {
				a1 -= a2;
			}

			if ((a1-(int)a1) > 0.0) {
				if (a1 >= 100000000) {
					sprintf(tmp, "%g", a1);
				} else {
					sprintf(tmp, "%f", a1);
				}
			} else {
				sprintf(tmp, "%d", (int)a1);
			}

			// INFO:: tirar zeros a direitaa
			std::string zeros = tmp;

			if (strchr(tmp, '.') != NULL) {
				while (zeros.size() > 1 && (i1 = (char *)strrchr(zeros.c_str(), '0')) != NULL) {
					int d1 = (int)(i1-zeros.c_str());

					if (d1 == (int)(zeros.size()-1)) {
						zeros = zeros.substr(0, zeros.size()-1);
					} else {
						break;
					}
				}

				if (zeros.size() > 1 && zeros[zeros.size()-1] == '.') {
					zeros = zeros.substr(0, zeros.size()-1);
				}
			}

			_number0 = zeros;
		}
	} else if (type == "%") {
		if (_state == 4) {
			_state = 5;

			double a1 = atof(_number0.c_str()),
						 a2 = atof(_number1.c_str());
			char *i1,
					 tmp[255];

			a2 = a1*(a2/100.0);

			if (_operation == "/") {
				if (a2 == 0) {
					_state = 255;

					_text = "Erro";
				} else {
					a1 /= a2;
				}
			} else if (_operation == "x") {
				a1 *= a2;
			} else if (_operation == "+") {
				a1 += a2;
			} else if (_operation == "-") {
				a1 -= a2;
			}

			if ((a1-(int)a1) > 0.0) {
				if (a1 >= 100000000) {
					sprintf(tmp, "%g", a1);
				} else {
					sprintf(tmp, "%f", a1);
				}
			} else {
				sprintf(tmp, "%d", (int)a1);
			}

			// INFO:: tirar zeros a direitaa
			std::string zeros = tmp;

			if (strchr(tmp, '.') != NULL) {
				while (zeros.size() > 1 && (i1 = (char *)strrchr(zeros.c_str(), '0')) != NULL) {
					int d1 = (int)(i1-zeros.c_str());

					if (d1 == (int)(zeros.size()-1)) {
						zeros = zeros.substr(0, zeros.size()-1);
					} else {
						break;
					}
				}

				if (zeros.size() > 1 && zeros[zeros.size()-1] == '.') {
					zeros = zeros.substr(0, zeros.size()-1);
				}
			}

			_number0 = zeros;
		}
	} else if (type == "C") {
		_number0 = "";
		_number1 = "";
		_operation = "";
		_state = 1;
	} else if (type == "del") {
		if (_state == 2 || _state == 5 || _state == 7) {
			_number0 = _number0.substr(0, _number0.size()-1);

			if (_number0 == "") {
				_number0 = "0";
			}
		} else if (_state == 4) {
			_number1 = _number1.substr(0, _number1.size()-1);

			if (_number1 == "") {
				_number1 = "0";
			}
		}
	}
}

bool Calc::OnKeyDown(jlwuit::UserEvent *event)
{
	jthread::AutoLock lock(&_mutex);

	std::string num = "";

	if (event->GetKeySymbol() == jlwuit::LKS_CURSOR_LEFT) {
		int mod = (_index % 5);

		if (mod > 0) {
			_index = _index - 1;
		}
	} else if (event->GetKeySymbol() == jlwuit::LKS_CURSOR_RIGHT) {
		int mod = (_index % 5);

		if (mod < 5-1) {
			_index = _index + 1;
		}
	} else if (event->GetKeySymbol() == jlwuit::LKS_CURSOR_UP) {
		int mod = (_index / 5);

		if (mod > 0) {
			_index = _index - 1*5;
		}
	} else if (event->GetKeySymbol() == jlwuit::LKS_CURSOR_DOWN) {
		int mod = (_index / 5);

		if (mod < 4-1) {
			_index = _index + 1*5;
		}
	} else if (event->GetKeySymbol() == jlwuit::LKS_ENTER) {
		Process(buttons[_index]);

		if (_state == 1) {
			_text = "";
		} else if (_state == 2 || _state == 3 || _state == 5 || _state == 7) {
			char *tmp = strdup(_number0.c_str()),
					 *i1;

			if (strlen(tmp) > 9) {
				i1 = strchr(tmp, '.');

				if (i1 != NULL) {
					int d1 = (int)(i1-tmp);

					if (d1 < 9) {
						tmp[9] = '\0';

						_number0 = tmp;
						_text = _number0;
					} else {
						_state = 255;
						_text = "Erro";
					}
				} else {
					_state = 255;
					_text = "Erro";
				}
			} else {
				_text = _number0;
			}

			if (_state == 3) {
				if (_operation == "+") {
					_operation = "+";
				} else if (_operation == "-") {
					_operation = "-";
				} else if (_operation == "x") {
					_operation = "x";
				} else if (_operation == "/") {
					_operation = "/";
				}
			}

			delete tmp;
		} else if (_state == 4) {
			char *tmp = strdup(_number1.c_str());

			if (strlen(tmp) > 9) {
				char *i1 = strchr(tmp, '.');

				if (i1 != NULL) {
					int d1 = (int)(i1-tmp);

					if (d1 < 9) {
						tmp[9] = '\0';

						_number1 = tmp;
						_text = _number1;
					} else {
						_state = 255;
						_text = "Erro";
					}
				} else {
					_state = 255;
					_text = "Erro";
				}
			} else {
				_text = _number1;
			}

			delete tmp;
		}
	} else if (event->GetKeySymbol() == jlwuit::LKS_1) {
		num = "1";
	} else if (event->GetKeySymbol() == jlwuit::LKS_2) {
		num = "2";
	} else if (event->GetKeySymbol() == jlwuit::LKS_3) {
		num = "3";
	} else if (event->GetKeySymbol() == jlwuit::LKS_4) {
		num = "4";
	} else if (event->GetKeySymbol() == jlwuit::LKS_5) {
		num = "5";
	} else if (event->GetKeySymbol() == jlwuit::LKS_6) {
		num = "6";
	} else if (event->GetKeySymbol() == jlwuit::LKS_7) {
		num = "7";
	} else if (event->GetKeySymbol() == jlwuit::LKS_8) {
		num = "8";
	} else if (event->GetKeySymbol() == jlwuit::LKS_9) {
		num = "9";
	} else if (event->GetKeySymbol() == jlwuit::LKS_0) {
		num = "0";
	}

	if (num != "") {
		if (_state == 1 || _state == 2 || _state == 5 || _state == 7 || _state == 8) {
			if (_state == 1 || _state == 5 || _state == 7) {
				_number0 = num;
			} else {
				if (_number0.size() < 9 && (_number0 != "0" || num != "0")) {
					if (_number0 == "0") {
						_number0 = num;
					} else {
						_number0 += num;
					}
				}
			}

			_state = 2;
		} else if (_state == 3 || _state == 4 || _state == 6) {
			if (_state == 3 || _state == 6) {
				_number1 = num;
			} else {
				if (_number1.size() < 9 && (_number1 != "0" || num != "0")) {
					if (_number1 == "0") {
						_number1 = num;
					} else {
						_number1 += num;
					}
				}
			}

			_state = 4;
		}
	}

	if (_state == 1) {
		_text = "";
	} else if (_state == 2 || _state == 3 || _state == 5 || _state == 7) {
		char *tmp = strdup(_number0.c_str()),
				 *i1;

		if (strlen(tmp) > 9) {
			i1 = strchr(tmp, '.');

			if (i1 != NULL) {
				int d1 = (int)(i1-tmp);

				if (d1 < 9) {
					tmp[9] = '\0';

					_number0 = tmp;
					_text = _number0;
				} else {
					_state = 255;
					_text = "Erro";
				}
			} else {
				_state = 255;
				_text = "Erro";
			}
		} else {
			_text = _number0;
		}

		if (_state == 3) {
			if (_operation == "+") {
				_operation = "+";
			} else if (_operation == "-") {
				_operation = "-";
			} else if (_operation == "x") {
				_operation = "x";
			} else if (_operation == "/") {
				_operation = "/";
			}
		}

		delete tmp;
	} else if (_state == 4) {
		char *tmp = strdup(_number1.c_str());

		if (strlen(tmp) > 9) {
			char *i1 = strchr(tmp, '.');

			if (i1 != NULL) {
				int d1 = (int)(i1-tmp);

				if (d1 < 9) {
					tmp[9] = '\0';

					_number1 = tmp;
					_text = _number1;
				} else {
					_state = 255;
					_text = "Erro";
				}
			} else {
				_state = 255;
				_text = "Erro";
			}
		} else {
			_text = _number1;
		}

		delete tmp;
	}

	Repaint();

	return true;
}

void Calc::Paint(jlwuit::Graphics *g)
{
	jlwuit::LookAndFeel *laf = jlwuit::LookAndFeel::GetInstance();
	jlwuit::lwuit_region_t bounds = GetBounds();

	laf->DrawBox(g, NULL, bounds.x, bounds.y, bounds.width, bounds.height);
	laf->DrawBox(g, NULL, bounds.x+MARGIN_LEFT, bounds.y+BUTTON_GAPY, 5*(BUTTON_WIDTH+BUTTON_GAPX)-BUTTON_GAPX, BUTTON_HEIGHT);

	if (_operation != "") {
		laf->DrawText(g, NULL, "medium", _operation, bounds.x+MARGIN_LEFT+BUTTON_GAPX, bounds.y+BUTTON_GAPY, 5*(BUTTON_WIDTH+BUTTON_GAPX)-3*BUTTON_GAPX, BUTTON_HEIGHT, jlwuit::LHA_LEFT);
	}

	laf->DrawText(g, NULL, "medium", _text, bounds.x+MARGIN_LEFT+BUTTON_GAPX, bounds.y+BUTTON_GAPY, 5*(BUTTON_WIDTH+BUTTON_GAPX)-3*BUTTON_GAPX, BUTTON_HEIGHT, jlwuit::LHA_RIGHT);

	for (int i=0; i<20; i++) {
		int x = i%5,
				y = i/5;

		laf->DrawBox(g, NULL, bounds.x+MARGIN_LEFT+x*(BUTTON_WIDTH+BUTTON_GAPX), bounds.y+MARGIN_TOP+y*(BUTTON_HEIGHT+BUTTON_GAPY), BUTTON_WIDTH, BUTTON_HEIGHT);

		if (i == _index) {
			laf->SetType(jlwuit::LST_FOCUS);
			laf->DrawBorder(g, NULL, bounds.x+MARGIN_LEFT+x*(BUTTON_WIDTH+BUTTON_GAPX), bounds.y+MARGIN_TOP+y*(BUTTON_HEIGHT+BUTTON_GAPY), BUTTON_WIDTH, BUTTON_HEIGHT);
			laf->SetType(jlwuit::LST_NORMAL);
		}
	
		laf->DrawText(g, NULL, "medium", buttons[i], bounds.x+MARGIN_LEFT+x*(BUTTON_WIDTH+BUTTON_GAPX), bounds.y+MARGIN_TOP+y*(BUTTON_HEIGHT+BUTTON_GAPY), BUTTON_WIDTH, BUTTON_HEIGHT);
	}

}
