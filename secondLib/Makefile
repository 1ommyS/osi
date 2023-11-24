build:
	g++ -o libTer.so -shared -fPIC Ter.cpp
	g++ -o libBin.so -shared -fPIC Bin.cpp
	g++ main.cpp -o output
clean:
	rm -rf libBin.so libTer.so output