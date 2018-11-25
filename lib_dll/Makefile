all: lib dll test

lib: ECHO
	make -C $@
dll: ECHO 
	make -C $@
test: ECHO 
	make -C $@

ECHO:
	@echo lib dll test

remove:
	@make remove -C lib
	@make remove -C dll
	@rm run -f
