f      = 1
n      = 0616015
TARGET = scanner
OBJECT = lex.yy.c
CC     = gcc
CFLAGS = -Wall -Wextra -pedantic -g3
LEX    = flex
LIBS   = -lfl

all: $(TARGET)

$(TARGET):
	g++ $(n)_hw2-$(f).cpp -o $(f).out

.PHONY: test

test: $(TARGET)
	./test.sh $(f)

.PHONY: clean

clean:
	$(RM) -f $(TARGET) $(OBJECT)
