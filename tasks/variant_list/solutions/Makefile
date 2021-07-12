.PHONY: test clean

test: variant_list_test.out
	./variant_list_test.out

variant_list_test.out: variant_list_test.o variant_list.o
	$(CC) -o variant_list_test.out variant_list_test.o variant_list.o $(CFLAGS)

variant_list.o: variant_list.c variant_list.h
	$(CC) -o variant_list.o -c variant_list.c $(CFLAGS)

variant_list_test.o: variant_list_test.c variant_list.h
	$(CC) -o variant_list_test.o -c variant_list_test.c $(CFLAGS)

clean:
	rm -f *.o
	rm -f *.out
