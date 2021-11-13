compiler = g++
gdb_flag = -g

test: test.cpp link_list.o
	# $(compiler) $(gdb_flag) -E test.cpp -o test.i
	# $(compiler) $(gdb_flag) -S test.i -o test.s
	# $(compiler) $(gdb_flag) -c test.s -o test.o
	$(compiler) $(gdb_flag) test.cpp link_list.o -o test

link_list.o: link_list.cpp
	# $(compiler) $(gdb_flag) -E link_list.cpp -o link_list.i
	# $(compiler) $(gdb_flag) -S link_list.i -o link_list.s
	$(compiler) $(gdb_flag) -c link_list.cpp -o link_list.o

clean:
	rm -rf *.i *.s *.o test
