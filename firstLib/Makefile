build:
	g++ -o libProst.so -shared -fPIC functions.cpp
	g++ main.cpp -L. -lProst -o output
	export LD_LIBRARY_PATH=.
clean:
	rm -rf libProst.so output