proxy server
avin chadee - kaimin huang
	
The following folders contain an example of a proxy server, to run the server type:

cd proxy-server
make clean
make
./run-server 12345

This will start a server on port 12345, with all log output going to:

./proxy-server/logs/proxy.log

- The test folder contains useful provided tests and generated scripts
- The client folder conatins an early client prototype for testing