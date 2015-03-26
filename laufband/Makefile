default:
	gcc main.cpp -o testIt -lwiringPi

test:
	gcc server.cpp -o testServer -lmicrohttpd -lstdc++ -DUSE_STL -lwiringPi
#	clang++ server.cpp -o testServer -lmicrohttpd -std=c++11 -stdlib=libc++ -Wall

clean:
	rm -rf testIt testServer *~
    
