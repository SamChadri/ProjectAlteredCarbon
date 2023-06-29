comp: expr.c main.c scan.c tree.c qgen.c gen.c
	cc -o comp -g expr.c gen.c qgen.c main.c scan.c tree.c agen.c nestq.c stment.c sym.c

clean:
	rm -f comp *.o out.asm out *.s
	rm -rf *.dSYM


test: comp
	./comp input01
	cc -o out out.s
	./out

q_test: comp
	./comp input03 -q
