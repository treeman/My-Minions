.PHONY: all clean mrproper remake

all:
	@(cd ./src && $(MAKE) $@)

debug:
	@(cd ./src && $(MAKE) $@)

remake: clean all
	@(cd ./src && $(MAKE) $@)

clean:
	@(cd ./src && $(MAKE) $@)

mrproper:
	@(cd ./src && $(MAKE) $@)

