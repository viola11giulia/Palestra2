CC = gcc
CFLAGS = -Wall -Iinclude
SRC = src
OBJ = obj
BIN = gvfit

SOURCES = $(wildcard $(SRC)/*.c)
OBJECTS = $(SOURCES:$(SRC)/%.c=$(OBJ)/%.o)

$(BIN): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJ)/%.o: $(SRC)/%.c
	mkdir -p $(OBJ)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ) $(BIN)


test_prenota:
	gcc -Iinclude test/test_prenota_lezione.c src/lezione.c -o test_prenota
	./test_prenota


test_abbonamento:
	gcc -Iinclude test/test_abbonamento.c src/abbonamento.c src/cliente.c -o test_abbonamento
	./test_abbonamento


test_report:
	gcc -Iinclude test/test_report.c src/report.c src/lezione.c -o test_report
	./test_report
