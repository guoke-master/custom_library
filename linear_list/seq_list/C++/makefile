compiler = g++
gdb_flag = -g

test: test.cpp seq_list.o
	# $(compiler) $(gdb_flag) -E test.cpp -o test.i
	# $(compiler) $(gdb_flag) -S test.i -o test.s
	# $(compiler) $(gdb_flag) -c test.s -o test.o
	$(compiler) $(gdb_flag) test.cpp seq_list.o -o test

seq_list.o: seq_list.cpp
	# $(compiler) $(gdb_flag) -E seq_list.c -o seq_list.i
	# $(compiler) $(gdb_flag) -S seq_list.i -o seq_list.s
	$(compiler) $(gdb_flag) -c seq_list.cpp -o seq_list.o

clean:
	rm -rf *.i *.s *.o test
