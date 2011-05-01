.PHONY: all clean mrproper remake

all:
	@(cd ./src && $(MAKE) $@)

debug:
	@(cd ./src && $(MAKE) $@)

remake: clean all

clean:
	@(cd ./src && $(MAKE) $@)

mrproper:
	@(cd ./src && $(MAKE) $@)

