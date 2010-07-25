
all: game

game:
	@(cd ./Game && $(MAKE))

clean:
	@(cd ./Game && $(MAKE) $@)
