mainloop:date ls cat mkdir rm
	gcc -o mainloop mainloop.c
	./mainloop
date:
	gcc -o date date.c
ls:
	gcc -o ls ls.c
cat:
	gcc -o cat cat.c
mkdir:
	gcc -o mkdir mkdir.c
rm:
	gcc -o rm rm.c
clean:
	rm -rf *ls *mkdir *rm *date *cat *mainloop
