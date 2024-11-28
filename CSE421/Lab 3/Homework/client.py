import socket

port = 5050
buffer = 16
termination_message = "End"
en_format = "utf-8"
hostname = socket.gethostname()
host_address = socket.gethostbyname(hostname)
server_socket_address = (host_address, port)

client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)  # Change this line
client.connect(server_socket_address)


def send_message(msg):
    msg = msg.encode(en_format)
    msg_length = len(msg)
    msg_length = str(msg_length).encode(en_format)
    msg_length += b" " * (buffer - len(msg_length))
    client.send(msg_length)
    client.send(msg)
    print(client.recv(2048).decode(en_format))


# send_message("The IP Address of the client is " + host_address + " and Hostname is " + hostname)
# send_message(termination_message)
while True:
    msg = input("Enter hours worked: ")
    if msg.lower() == "done":
        send_message(termination_message)
        break
    else:
        send_message(msg)
