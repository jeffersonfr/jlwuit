include ../Makefile.defs

MODULES = \
			apps \
			dlg \
			dump \
			filter \
			http \
			gui \
			ipc \
		  layers \
			msg \
			prefs \
			slide \
			video \

all:
	@for i in $(MODULES); do \
		$(ECHO) -n "Module $$i " && (cd $$i && make -s) && $(ECHO) "$(OK)" && continue || $(ECHO) "$(FAILED)" && exit; \
	done

clean:
	@for i in $(MODULES); do \
		$(ECHO) -n "Module $$i " && (cd $$i && make -s clean) && $(ECHO) "cleaned $(OK)" && continue || $(ECHO) "$(FAILED)" && exit; \
	done

