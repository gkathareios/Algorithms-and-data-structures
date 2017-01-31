all: red_black_tree_test segment_tree_test

red_black_tree_test: red_black_tree_test.cc red_black_tree.cc red_black_tree.h
	g++ -std=c++11 red_black_tree_test.cc red_black_tree.cc -o red_black_tree_test

segment_tree_test: segment_tree_test.cc segment_tree.cc segment_tree.h
	g++ -std=c++11 segment_tree_test.cc segment_tree.cc -o segment_tree_test

clean:
	rm -f segment_tree_test red_black_tree_test