all: 08-01-input.gb

%.o: %.asm
	rgbasm -Werror -Weverything -o $@ $^

%.gb: %.o main.o
	rgblink --dmg --tiny --map $*.map --sym $*.sym -o $@ $^
	rgbfix --title $* --pad-value 0 --validate $@

clean:
	rm -f *.o *.gb *.map *.sym
