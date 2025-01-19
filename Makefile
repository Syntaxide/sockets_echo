.PHONY: test
test: echo_server
	./echo_server 8080

echo_server: echo_server.cc
	$(CXX) echo_server.cc -o echo_server
