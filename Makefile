C_FLAGS := -std=c11
LD_FLAGS := -lm -lcairo
INCLUDES := -Iinclude

SOURCES := $(shell find src -name "*.c")
OBJECTS := $(SOURCES:src/%.c=build/%.o)
DEPS    := $(OBJECTS:.o=.d)

debug:   export CFLAGS := $(C_FLAGS) -g -Og -DDEBUG
release: export CFLAGS := $(C_FLAGS) -O3 -DNDEBUG

.PHONY: debug
debug: dirs
	$(MAKE) all --no-print-directory

.PHONY: release
release: dirs
	$(MAKE) all --no-print-directory

.PHONY: dirs
dirs:
	mkdir -p bin

.PHONY: clean
clean:
	rm -f hexes
	rm -rf bin
	rm -rf build

.PHONY: all
all: hexes

include $(DEPS)

hexes: bin/hexes
	ln -sf $< $@

bin/hexes: $(OBJECTS)
	gcc $(LD_FLAGS) -o $@ $^ 

build/%.d: src/%.c
	mkdir -p $(dir $@)
	./depend.sh $(shell dirname $@) $(CFLAGS) $(INCLUDES) $< > $@

build/%.o: src/%.c
	gcc $(CFLAGS) $(INCLUDES) -o $@ -c $<
