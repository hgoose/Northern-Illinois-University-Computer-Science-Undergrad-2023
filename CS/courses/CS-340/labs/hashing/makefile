all: test_class test_file_wc

test_class: wordcount.cc test_class.cc wordcount.h
	g++ -std=c++17 -Wall -Wextra -pedantic -o test_class wordcount.cc test_class.cc

test_file_wc: wordcount.cc test_file_wc.cc wordcount.h
	g++ -std=c++17 -Wall -Wextra -pedantic -o test_file_wc wordcount.cc test_file_wc.cc

clean:
	rm test_class test_file_wc

world: clean all
