BIN := output/bin
PPM := output/test.ppm
MAIN := main.c
DEPS := utils.c path_trace.c

.PHONY: all clean

all: $(PPM)

$(BIN): $(MAIN) $(DEPS)
	clang $(MAIN) $(DEPS) -o $(BIN)

$(PPM): $(BIN)
	./$(BIN) > $(PPM)

clean:
	rm -f $(BIN) $(PPM)
