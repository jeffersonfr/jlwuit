include ../Makefile.defs

MODULES = \
			dlg \
		  gui \
			ipc \
		  layers \
			msg \
			prefs \
		  robots \

all:
	@for i in $(MODULES); do \
		$(ECHO) -n "Module $$i " && (cd $$i && make -s) && $(ECHO) "$(OK)" && continue || $(ECHO) "$(FAILED)" && exit; \
	done

clean:
	@for i in $(MODULES); do \
		$(ECHO) -n "Module $$i " && (cd $$i && make -s clean) && $(ECHO) "cleaned $(OK)" && continue || $(ECHO) "$(FAILED)" && exit; \
	done

