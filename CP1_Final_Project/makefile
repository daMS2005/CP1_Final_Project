exec = eva.out
sources = $(wildcard src/*.c)
objects = $(sources:.c=.o)
flags = -g

$(exec): $(objects)
    gcc $(objects) $(flags) -o $(exec)

.o: %.c include/%.h
    gcc -c $(flags) $< -o $@

install: $(exec)
    cp ./$(exec) /usr/local/bin/$(exec)

clean:
    -rm *.out
    -rm *.o
    -rm src/*.o
