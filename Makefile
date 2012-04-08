include Makefile.defs

MODULE		= jlwuit

VERSION		= 1.0.0

EXE				= lib$(MODULE)-$(VERSION).so

CCFLAGS		+= \
						-shared \

CCFLAGS		+= \
						-Isrc/apps/$(INCDIR) \
						-Isrc/lwuit/$(INCDIR) \
						-Isrc/media/$(INCDIR) \
						-Isrc/ipc/$(INCDIR) \
						-Isrc/prefs/$(INCDIR) \
						-Isrc/usb/$(INCDIR) \
						-Isrc/util/$(INCDIR) \
						-I/usr/local/include \
						`pkg-config --cflags jlibcpp` \

LDFLAGS		= \
						-L$(LIBDIR) \
						`pkg-config --libs jlibcpp` \

DEFINES		= \

REQUIRES	= \
						jlibcpp \

SRC_APPS	= \
						appdatabase.o\
						attributes.o\
						nativeproxy.o\
						proxy.o\

SRC_LWUIT	= \
						borderlayout.o\
						capabilities.o\
						color.o\
						component.o\
						coordinatelayout.o\
						device.o\
						dialog.o\
						eventmanager.o\
						exception.o\
						flowlayout.o\
						font.o\
						graphics.o\
						gridbaglayout.o\
						gridlayout.o\
						image.o\
						implementation.o\
						layer.o\
						layersetup.o\
						layout.o\
						lookandfeel.o\
						rootcontainer.o\
						scene.o\
						screen.o\
						style.o\
						styleevent.o\
						stylelistener.o\
						transition.o\
						toast.o\
						userevent.o\
						usereventlistener.o\

SRC_MEDIA	= \
						audioconfigurationcontrol.o\
						control.o\
						mediaexception.o\
						player.o\
						playerevent.o\
						playereventlistener.o\
						playermanager.o\
						videoconfigurationcontrol.o\
						videotransformationcontrol.o\
						volumecontrol.o\

SRC_IPC		= \
						ipcclient.o\
						ipchelper.o\
						ipcserver.o\
						ipcexception.o\
						method.o\
						response.o\
						remotecalllistener.o\

SRC_PREFS	= \
						preferences.o\
						document.o\
						element.o\

SRC_USB		= \
						usbmanager.o\
						usbstatusevent.o\
						usbstatuslistener.o\

SRC_UTIL	= \
						parammapper.o\

OBJS			= \
						$(addprefix src/apps/, $(SRC_APPS)) \
						$(addprefix src/lwuit/, $(SRC_LWUIT)) \
						$(addprefix src/media/, $(SRC_MEDIA)) \
						$(addprefix src/ipc/, $(SRC_IPC)) \
						$(addprefix src/prefs/, $(SRC_PREFS)) \
						$(addprefix src/usb/, $(SRC_USB)) \
						$(addprefix src/util/, $(SRC_UTIL)) \

.PHONY: all strip tests doc install uninstall clean $(PLATFORMS)

include Makefile.native

lib: $(OBJS)
	@$(CC) $(CCFLAGS) -o $(EXE) $(OBJS)  $(LDFLAGS); $(ECHO) "generate $(EXE) ...  $(OK)" ; mkdir -p $(LIBDIR) && mv $(EXE) $(LIBDIR)

.cpp.o: $<
	@$(CC) $(CCFLAGS) -c $< -o $@ && $(ECHO) "Compiling $< ...  $(OK)" 

strip:
	@echo -e "Strip $(EXE)...  $(OK)"
	@$(STRIP) $(LIBDIR)/$(EXE)

tests:
	@cd $(TESTDIR) && make && cd .. && echo -e "Compiling $< ...  $(OK)" 

doc:
	@mkdir -p $(DOCDIR) 

install: uninstall
	@$(ECHO) "Installing resources files in $(PREFIX)/$(MODULE) $(OK)" && mkdir -p $(PREFIX)/$(MODULE)
	@install -d -o nobody -m 755 $(PREFIX)/$(MODULE)/fonts && install -o nobody -m 644 resources/fonts/* $(PREFIX)/$(MODULE)/fonts
	@install -d -o nobody -m 755 $(PREFIX)/$(MODULE)/images && install -o nobody -m 644 resources/images/* $(PREFIX)/$(MODULE)/images
	@install -d -o nobody -m 755 $(PREFIX)/$(MODULE)/sounds && install -o nobody -m 644 resources/sounds/* $(PREFIX)/$(MODULE)/sounds
	@$(ECHO) "Installing include files in $(PREFIX)/include/$(MODULE) $(OK)" && mkdir -p $(PREFIX)/include/$(MODULE)
	@install -d -o nobody -m 755 $(PREFIX)/include/$(MODULE)
	@for i in apps lwuit media ipc prefs usb util; do \
		install -d -o nobody -m 755 $(PREFIX)/include/$(MODULE)/$$i && install -o nobody -m 644 src/$$i/include/* $(PREFIX)/include/$(MODULE)/$$i ; \
	done
	@$(ECHO) "Installing $(EXE) in $(PREFIX)/lib/lib$(MODULE).so $(OK)"
	@install -d -o nobody -m 755 $(PREFIX)/lib && install -o nobody -m 644 $(LIBDIR)/$(EXE) $(PREFIX)/lib && ln -s $(PREFIX)/lib/$(EXE) $(PREFIX)/lib/lib$(MODULE).so
	@$(ECHO) "Installing $(MODULE).pc in $(PREFIX)/lib/pkgconfig $(OK)"
	@mkdir -p $(PREFIX)/lib/pkgconfig && \
		sed -e 's/@module@/$(MODULE)/g' jlwuit.pc | \
		sed -e 's/@prefix@/$(subst /,\/,$(PREFIX))/g' | \
		sed -e 's/@version@/$(VERSION)/g' | \
		sed -e 's/@cflags@/$(DEFINES)/g' | \
		sed -e 's/@requires@/$(REQUIRES)/g' | \
		sed -e 's/@libs@/$(subst /,\/,$(LDFLAGS))/g' > $(PREFIX)/lib/pkgconfig/$(MODULE).pc

uninstall:
	@rm -rf $(PREFIX)/lib/pkgconfig/$(MODULE).pc $(PREFIX)/lib/lib$(MODULE).so $(PREFIX)/lib/$(EXE) $(PREFIX)/include/$(MODULE)

clean:
	@find -iname "*.o" -exec rm {} \;;
	@find -iname "*.a" -exec rm {} \;;
	@find -iname "*.so" -exec rm {} \;;
	@find -iname "*.exe" -exec rm {} \;;
	@find -iname "*.sw*" -exec rm {} \;;
	@find -iname "*~" -exec rm {} \;;
	@cd tests && make clean && cd - &> /dev/null
	@rm -rf $(EXE) $(BINDIR) $(LIBDIR) $(DOCDIR) 2> /dev/null && echo -e "$(MODULE) clean $(OK)" 

