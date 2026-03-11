all: 07-01-background.gb 07-02-background-broken.gb 07-03-background-fixed.gb

%.o: %.asm
	rgbasm -Werror -Weverything -o $@ $^

%.gb: %.o main.o
	rgblink --dmg --tiny --map $*.map --sym $*.sym -o $@ $^
	rgbfix --title $* --pad-value 0 --validate $@

clean:
	rm -f *.o *.gb *.map *.sym
