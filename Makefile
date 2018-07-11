CC=clang
CFLAGS=-Wall -lncurses
SOURCES=rootshell.c
EXECUTABLE=rootshell
INSTALLDIR=/usr/local/bin

.PHONY:all install uninstall clean run

all: $(EXECUTABLE)
	$(shell id -u|xargs -I SUID chown SUID:SUID $(EXECUTABLE) \
	&&chmod 755 $(EXECUTABLE)&&chmod +s $(EXECUTABLE))

$(EXECUTABLE):$(SOURCES)
	@check_user="$(shell whoami)"; \
	if [ $$check_user != "root" ]; then \
	    echo "Require sudo or root for +s, Please try again with Privilege"; \
			exit 1; \
	fi;
	$(CC) $(SOURCES) $(CFLAGS) -o $(EXECUTABLE)

install:
	mkdir -p $(INSTALLDIR)
	sudo cp $(EXECUTABLE) $(INSTALLDIR)/

uninstall:
	sudo rm $(INSTALLDIR)/$(EXECUTABLE)

clean:
	sudo rm $(EXECUTABLE)

run:
	exec $(EXECUTABLE)
