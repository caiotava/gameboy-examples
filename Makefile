CC	= C:\gbdk\bin\lcc.exe
CFLAGS	= -Wa-l -Wl-m -Wl-j
LDFLAGS	= -Wl-yt0x01 -Wl-yo4 -Wl-yp0x143=0x80
BIN	= slideScrolling.gbc

$(BIN)	: main.o bank2.o bank3.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(BIN) $^

main.o	: main.c
	$(CC) $(CFLAGS) -c -o main.o main.c

bank2.o	: bank2.c
	$(CC) $(CFLAGS) -Wf-bo2 -c -o bank2.o bank2.c

bank3.o	: bank3.c
	$(CC) $(CFLAGS) -Wf-bo3 -c -o bank3.o bank3.c

clean	:
	rm -f *.o *.gbc *.lst *.map
