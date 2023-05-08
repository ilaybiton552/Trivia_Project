import socket

SERVER_IP = "127.0.0.1"
SERVER_PORT = 8826
SERVER_MESSAGE = "Hello"
RECV = 1024


def client_socket():
    """
    Opens a client socket and talks with the server
    :return: None
    """
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_address = (SERVER_IP, SERVER_PORT)
    sock.connect(server_address)
    server_msg = sock.recv(RECV)
    server_msg = server_msg
    print("Server message: ", server_msg.decode())
    sock.sendall(SERVER_MESSAGE.encode())
    sock.close()


def main():
    client_socket()
    input() # press any key to exit


if __name__ == "__main__":
    main()
