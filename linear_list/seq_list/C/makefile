compiler = gcc
gdb_flag = -g

test: test.c seq_list.o
	# $(compiler) $(gdb_flag) -E test.c -o test.i
	# $(compiler) $(gdb_flag) -S test.i -o test.s
	# $(compiler) $(gdb_flag) -c test.s -o test.o
	$(compiler) $(gdb_flag) test.c seq_list.o -o test

seq_list.o: seq_list.c
	# $(compiler) $(gdb_flag) -E seq_list.c -o seq_list.i
	# $(compiler) $(gdb_flag) -S seq_list.i -o seq_list.s
	$(compiler) $(gdb_flag) -c seq_list.c -o seq_list.o

clean:
	rm -rf *.i *.s *.o test
