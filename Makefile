CC=gcc

CFLAGS=-O3

LIBS=-lusb-1.0

all: alienfx-cli

uninstall:
	rm /usr/local/bin/alienfx-cli

install: copy setuid

setuid:
	chmod +s /usr/local/bin/alienfx-cli
copy:
	cp alienfx-cli /usr/local/bin/	

alienfx-cli: alienfx-usb.o alienfx-cli.o
	$(CC) $(CFLAGS) alienfx-usb.o alienfx-cli.o  $(LIBS) -o alienfx-cli
	
alienfx-cli.o: alienfx-cli.c
	$(CC) $(CFLAGS) -c alienfx-cli.c

alienfx-usb.o: alienfx-usb.c
	$(CC) $(CFLAGS) -c alienfx-usb.c

clean:
	rm -rf *.o alienfx-cli
