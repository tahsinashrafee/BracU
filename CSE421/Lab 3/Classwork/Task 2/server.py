import socket

port = 5050  # assigning port
buffer = 16  # determining the size of buffer
termination_message = "End"  # ending msg condition
en_format = "utf-8"  # encoding format
hostname = socket.gethostname()  # retrieve the hostname
host_address = socket.gethostbyname(hostname)  # retrieve the IP Address
server_socket_address = (host_address, port)  # making the server address

server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)  # creating the server
server.bind(server_socket_address)  # binds server socket to the server address
server.listen()  # starts listening for incoming connections
print("Server is listening")

while True:
    conn, addr = server.accept()
    print("Connected to", addr)
    connected = True
    while connected:
        initial_msg = conn.recv(buffer).decode(en_format)
        print("Length of Message Received", initial_msg)
        if initial_msg:
            initial_msg = int(initial_msg)
            msg = conn.recv(initial_msg).decode(en_format)
            if msg == termination_message:
                conn.send("Terminating Connection".encode(en_format))
                connected = False
            else:
                # print(msg)
                # conn.send("Message Received Successfully".encode(en_format))
                vowels = "aeiouAEIOU"
                counter = 0
                for i in msg:
                    if i in vowels:
                        counter += 1
                if counter == 0:
                    conn.send("Not enough vowels".encode(en_format))
                elif counter <= 2:
                    conn.send("Enough Vowels I guess".encode(en_format))
                else:
                    conn.send("Too many Vowels".encode(en_format))

    conn.close()
