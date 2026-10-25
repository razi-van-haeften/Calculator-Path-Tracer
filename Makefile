BIN := output/bin
PPM := output/test.ppm
MAIN := main.c
DEPS := utils.c path_trace.c

.PHONY: all clean

all: $(PPM)

$(BIN): $(MAIN) $(DEPS)
	gcc -O3 -march=native -flto -ffast-math -DNDEBUG $(MAIN) $(DEPS) -o $(BIN) -lm

$(PPM): $(BIN)
	./$(BIN) > $(PPM)

clean:
	rm -f $(BIN) $(PPM)
