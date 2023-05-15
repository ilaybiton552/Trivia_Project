import socket
import json

SERVER_IP = "127.0.0.1"
SERVER_PORT = 8826
RECV = 1024
LOGIN_REQUEST_CODE = 101
SIGNUP_REQUEST_CODE = 102
DISCONNECT_REQUEST_CODE = 0
LOGIN = 1
SIGNUP = 2
EXIT = 0
CUSTOM_MESSAGE = 3


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
    message = code.to_bytes(1, 'big') + data_length.to_bytes(4, 'big') + message.encode()
    sock.sendall(message)


def deserialize_message(message):
    """
    the function deserialize the message from the server
    :param message: the message that the server sends
    :return: None
    """
    code = message[0]
    data_length = int.from_bytes(message[1:5], "big", signed=False)
    data = message[5:-1].decode('utf-8') + '}'

    print("Server's response: ")
    print("Message code: " + str(code))
    print("Data length: " + str(data_length))
    print("Message content: " + data)


def custom_message():
    """
    The function gets a custom message from the client
    :return: tuple, the data and the code of the message
    """
    code = int(input("Enter the code of the message: "))
    data = input("Enter the data of the message: ")
    return data, code

def menu():
    """
    the function prints the menu and receives user choice
    :return: user's choice
    """
    print("What would you like to do?")
    print("0 - Exit")
    print("1 - Login")
    print("2 - Signup")
    print("3 - Custom message")
    choice = -1
    while not (0 <= choice <= 3):
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
        serialize_message("disconnect", DISCONNECT_REQUEST_CODE, sock)
    elif choice is CUSTOM_MESSAGE:
        data, code = custom_message()
        serialize_message(data, code, sock)


def main():
    try:
        sock = client_socket()
        user_choice = menu()
        while (user_choice != EXIT):
            action(user_choice, sock)
            deserialize_message(sock.recv(RECV))
            user_choice = menu()
        action(user_choice, sock)
        sock.close()
    except Exception as exc:
        print("The exception is: ", exc)
    input()  # press any key to exit


if __name__ == "__main__":
    main()
