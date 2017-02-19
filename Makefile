all: test

test: test_cj_tbl.c cj_tbl.h fct.h
	gcc -g test_cj_tbl.c -o test
	./test

clean:
	rm test