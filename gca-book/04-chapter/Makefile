all: 04-01-sample.gb

%.o: %.asm
	rgbasm -Werror -Weverything -o $@ $^

%.gb: 04-01-sample.o main.o
	rgblink --dmg --tiny --map $*.map --sym $*.sym -o $@ $^
	rgbfix --title $* --pad-value 0 --validate $@

clean:
	rm -f *.o *.gb *.map *.sym
