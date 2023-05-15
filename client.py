import socket
import re
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
    while not (password_check(password)):
        print("The password does not match the format")
        print("The format for password: at least 1 digit, 1 uppercase letter, 1 lowercase letter and 1 special char")
        password = input("Please enter the password: ")

    email = input("Please enter your email: ")
    while not (email_check(email)):
        print("The email does not match the format")
        email = input("Please enter your email: ")

    address = input("Please enter your address: ")
    while not (address_check(address)):
        print("The address does not match the format")
        print("The format for address: X, X, X")
        address = input("Please enter your address: ")

    phone_number = input("Please enter your phone number: ")
    while not (phone_number_check(phone_number)):
        print("The phone number does not match the format")
        print("The format for phone number: 0XXXXXXXX or 05XXXXXXXX")
        phone_number = input("Please enter your phone number: ")

    birthdate = input("Please enter your birthdate: ")
    while not (birthdate_check(birthdate)):
        print("The birthdate does not match the format")
        print("The format for birthdate: DD.MM.YYYY")
        birthdate = input("Please enter your birthdate: ")

    signup_request = {"username": username, "password": password, "email": email, "address": address, "phone_number": phone_number, "birthdate": birthdate}
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


def password_check(password):
    """
    the function checks if the password is valid or not
    :param password: the password to check
    :type: string
    :return: if the password is valid or not
    :rtype: bool
    """
    if(len(password) != 8):  # if the password length is 8
        return False
    elif not (re.search("[a-z]", password)):  # if the password contains lowercase letter
        return False
    elif not (re.search("[A-Z]", password)):  # if the password contains uppercase letter
        return False
    elif not (re.search("[0-9]", password)):  # if the password contains digit
        return False
    elif not (re.search("[!@#$%^&*]", password)):  # if the password contains special char
        return False
    else:
        return True


def email_check(email):
    """
    the function checks if the email is valid or not
    :param email: the email to check
    :type: string
    :return: if the email is valid or not
    :rtype: bool
    """
    regex = re.compile(r'([A-Za-z0-9]+[._-])*[A-Za-z0-9]+@[A-Za-z0-9-]+(\.[A-Z|a-z]{2,})+')  # regex pattern for email
    return bool((re.fullmatch(regex, email)))  # check if the email is valid


def address_check(address):
    """
    the function checks if the address is valid or not
    :param address: the address to check
    :type: string
    :return: if the address is valid or not
    :rtype: bool
    """
    regex = re.compile(r'([A-Za-z])*[, ]+([0-9])*[, ]+([A-Za-z]+)')
    return bool((re.fullmatch(regex, address)))


def phone_number_check(phone_number):
    """
    the function checks if the phone number is valid or not
    :param phone_number: the phone number to check
    :type: string
    :return: if the phone number is valid or not
    :rtype: bool
    """
    phone_regex_1 = re.compile(r'0+([0-9]){8}')
    phone_regex_2 = re.compile(r'05+([0-9]){8}')
    return bool((re.fullmatch(phone_regex_1, phone_number) or re.fullmatch(phone_regex_2, phone_number)))


def birthdate_check(birthdate):
    """
    the function checks if the birthdate format is valid or not
    :param birthdate: the birthdate to check
    :type: string
    :return: if the birth date format is valid or not
    :rtype: bool
    """
    regex = re.compile(r'([0-9]{1,2})\.([0-9]{1,2})\.([0-9]{4})')
    return bool((re.fullmatch(regex, birthdate)))


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
