import socket
import json

SERVER_IP = "127.0.0.1"
SERVER_PORT = 8826
RECV = 1024
LOGIN_REQUEST_CODE = 101
SIGNUP_REQUEST_CODE = 102
LOGIN = 1
SIGNUP = 2
EXIT = 0

def client_socket():
    """
    Opens a client socket
    :return: Socket sock
    """
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)  # open the socket
    server_address = (SERVER_IP, SERVER_PORT)
    sock.connect(server_address)  # connects to the server
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

def signup_message():
    """
    the function receives signup information
    :return: the signup request
    """
    username = input("Please enter your username: ")
    password = input("Please enter the password: ")
    email = input("Please enter your email: ")
    signup_request = {"username": username, "password": password, "email": email}
    signup_request = json.dumps(signup_request)
    return signup_request

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

def menu():
    """
    the function prints the menu and receives user choice
    :return: user's choice
    """
    print("What would you like to do?")
    print("1 - Login")
    print("2 - Signup")
    print("0 - Exit")
    choice = -1
    while not (0 <= choice <= 2):
        try:
            choice = int(input("Please enter your choice: "))
        except Exception as ex:
            print("Invalid input!" + str(ex))

    return choice

def action(choice, sock):
    """
    the function does the wanted action
    :param choice: user's choice of action
    :param sock: Socket sock
    :return: None
    """
    if choice is LOGIN:
        serialize_message(login_message(), LOGIN_REQUEST_CODE, sock)
    elif choice is SIGNUP:
        serialize_message(signup_message(), SIGNUP_REQUEST_CODE, sock)
    elif choice is EXIT:
        print("Goodbye!")

def main():
    try:
        sock = client_socket()
        action(menu(), sock)
        sock.close()
    except Exception as exc:
        print("The exception is: ", exc)
    input()  # press any key to exit


if __name__ == "__main__":
    main()
