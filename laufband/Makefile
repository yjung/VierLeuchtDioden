default:
	gcc main.cpp -o testIt -lwiringPi

test:
	gcc server.cpp -o testServer -lmicrohttpd -lstdc++ -DUSE_STL -lwiringPi

clean:
	rm -rf testIt testServer *~
    
