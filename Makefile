run:deepanshu2021249
	./deepanshu2021249
deepanshu2021249:loadfile.o
	gcc -m64 -no-pie loadfile.o -o deepanshu2021249
loadfile.o:deepanshu2021249.asm
	yasm -f elf64 -o loadfile.o deepanshu2021249.asm
clean:
	rm -rf *.o *deepanshu2021249
