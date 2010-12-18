.PHONY: all clean mrproper remake

all:
	@(cd ./Game && $(MAKE) $@)

remake: clean all
	@(cd ./Game && $(MAKE) $@)

clean:
	@(cd ./Game && $(MAKE) $@)

mrproper:
	@(cd ./Game && $(MAKE) $@)

