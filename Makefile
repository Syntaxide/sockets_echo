echo_vsock_musl: echo_server_vsock.cc
	$(CXX) -c echo_server_vsock.cc -o vsock_server.o
	musl-gcc -static vsock_server.o -o vsock_echo_musl

echo_server_vsock: echo_server_vsock.cc
	$(CXX) echo_server_vsock.cc -o echo_server_vsock

echo_server: echo_server.cc
	$(CXX) echo_server.cc -o echo_server

.PHONY: test
test: echo_server
	./echo_server 8080
