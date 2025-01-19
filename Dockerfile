FROM alpine:latest

COPY ./vsock_echo_musl /bin/vsock_echo_musl

CMD ["/bin/vsock_echo_musl"]
