import socket

SERVER_IP = "127.0.0.1"
SERVER_PORT = 8826
RECV = 1024


def client_socket():
    """
    Opens a client socket and talks with the server
    :return: None
    """
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_address = (SERVER_IP, SERVER_PORT)
    sock.connect(server_address)

    server_msg = sock.recv(RECV).decode()
    print("Server message: ", server_msg)

    client_msg = input("Enter the message for the server: ")
    print(client_msg)
    if (client_msg == "Hello"):
        sock.sendall(client_msg.encode())
    sock.close()


def main():
    try:
        client_socket()
    except Exception as exc:
        print("The exception is: ", exc)
    input() # press any key to exit


if __name__ == "__main__":
    main()
