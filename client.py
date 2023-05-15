import socket
import re

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
    if (re.fullmatch(regex, email)):  # check if the email is valid
        return True
    else:
        return False

def address_check(address):
    """
    the function checks if the address is valid or not
    :param address: the address to check
    :type: string
    :return: if the address is valid or not
    :rtype: bool
    """
    regex = re.compile(r'([A-Za-z])*[, ]+([0-9])*[, ]+([A-Za-z]+)')
    if (re.fullmatch(regex, address)):
        return True
    else:
        return False

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
    if(re.fullmatch(phone_regex_1, phone_number) or re.fullmatch(phone_regex_2, phone_number)):
        return True
    else:
        return False

def birth_date_check(birth_date):
    """
    the function checks if the birth date format is valid or not
    :param birth_date: the birth date to check
    :type: string
    :return: if the birth date format is valid or not
    :rtype: bool
    """
    regex = re.compile(r'([0-9]{1,2})\.([0-9]{1,2})\.([0-9]{4})')
    if(re.fullmatch(regex, birth_date)):
        return True
    else:
        return False

def main():
    try:
        while True:
            print(birth_date_check(input("Enter birth date: ")))
    except Exception as exc:
        print("The exception is: ", exc)
    input() # press any key to exit


if __name__ == "__main__":
    main()
