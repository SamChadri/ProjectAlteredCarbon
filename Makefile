comp: expr.c main.c scan.c tree.c qgen.c gen.c
	cc -o comp -g expr.c gen.c qgen.c main.c scan.c tree.c

clean:
	rm -f comp *.o:
	rm out.asm
	rm -rf *.dSYM