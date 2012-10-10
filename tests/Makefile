include ../Makefile.defs

MODULES = \
			apps \
			dlg \
			dump \
			filter \
			gui \
			ipc \
		  layers \
			msg \
			prefs \
			slide \
			video \
			dummy \

all:
	@for i in $(MODULES); do \
		$(ECHO) "Test $$i " && (cd $$i && make -s) && continue || exit; \
	done

clean:
	@for i in $(MODULES); do \
		$(ECHO) -n "Test $$i " && (cd $$i && make -s clean) && $(ECHO) "cleaned $(OK)" && continue || $(ECHO) "$(FAILED)" && exit; \
	done

