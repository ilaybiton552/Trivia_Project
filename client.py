import socket
import json

SERVER_IP = "127.0.0.1"
SERVER_PORT = 8826
RECV = 1024
LOGIN_REQUEST_CODE = 101
SIGNUP_REQUEST_CODE = 102

def client_socket():
    """
    Opens a client socket and talks with the server
    :return: Socket sock
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

    return sock

def login_message():
    """
    the function receives login information
    :return: the login request
    """
    username = input("Please enter your username: ")
    password = input("Please enter the password: ")
    login_request = {"username": username, "password": password}
    login_request = json.dumps(login_request)
    return login_request


def serialize_message(message, code, sock):
    """
    the function creates and sends encode message to the server
    :param message: the message to send
    :param code: the request / response code
    :param sock: the socket with server
    :return: None
    """
    data_length = len(message)
    message = code.to_bytes(1, 'little') + data_length.to_bytes(4, 'little') + message.encode('utf-8')
    sock.sendall(message)

def deserialize_message(message):
    code = message[0]
    data_length = int.from_bytes(message[1:5], "little", signed=False)
    data = message[5:-1].decode('utf-8') + '}'

def main():
    try:
        sock = client_socket()
        serialize_message(login_message(), LOGIN_REQUEST_CODE, sock)
        sock.close()
    except Exception as exc:
        print("The exception is: ", exc)
    input() # press any key to exit


if __name__ == "__main__":
    main()
