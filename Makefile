CC=gcc
CFLAGS=-std=-std=c99 -Wall -lncurses
SOURCES=rootshell.c
EXECUTABLE=rootshell
INSTALLDIR=/usr/local/bin

all: $(SOURCES)
	$(CC) $(SOURCES) $(CFLAGS) -o $(EXECUTABLE)
	sudo -s "id -u|xargs -I SUID chown SUID:SUID $(EXECUTABLE)&&chmod 755 $(EXECUTABLE)&&chmod +s $(EXECUTABLE)"

install:
	mkdir -p $(INSTALLDIR)
	sudo cp $(EXECUTABLE) $(INSTALLDIR)/

uninstall:
	rm $(INSTALLDIR)/$(EXECUTABLE)

run:
	exec $(EXECUTABLE)
