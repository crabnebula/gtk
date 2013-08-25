CFLAGS = -g -Wall $(shell pkg-config --cflags --libs gtk+-3.0)

PROG := gtkAppWin gtkWin gtkDialog

all : $(PROG)

clean:
	@rm -v $(PROG)
