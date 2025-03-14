CC=clang
override CFLAGS+=-std=c23 --target=wasm32 -nostdlib -mbulk-memory -DSERVER
override LDFLAGS+=-Wl,--no-entry

OBJ=main.o

all: clean progs.wasm

clean:
	$(RM) progs.wasm $(OBJ)

progs.wasm: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)
