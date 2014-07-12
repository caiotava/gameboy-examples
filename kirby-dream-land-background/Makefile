CC	= C:\gbdk\bin\lcc.exe
CFLAGS	= -Wa-l -Wl-m -Wl-j
LDFLAGS	=
BIN	= background.gb

$(BIN)	: main.o bgTiles.o bgMaps.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(BIN) $^

main.o	: main.c
	$(CC) $(CFLAGS) -c -o main.o main.c

bgTile.o: bgTile.c
	$(CC) $(CFLAGS) -c -o bgTile.o bgTile.c

bgMaps.o: bgMaps.c
	$(CC) $(CFLAGS) -c -o bgMaps.o bgMaps.c

clean	:
	rm -f *.o *.gbc *.lst *.map

