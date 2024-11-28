import socket
port = 5050     # assigning port
buffer = 16     # determining the size of buffer
termination_message = "End"     # ending msg condition
en_format = "utf-8"     # encoding format
hostname = socket.gethostname()     # retrieve the hostname
host_address = socket.gethostbyname(hostname)   # retrieve the IP Address
server_socket_address = (host_address, port)    # making the server address

server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)      # creating the server
server.bind(server_socket_address)  # binds server socket to the server address
server.listen()     # starts listening for incoming connections
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
                tk = 0
                msg = int(msg)
                if msg <= 40:
                    tk = msg * 200
                else:
                    tk = 8000 + (msg - 40) * 300
                conn.send(f'Salary = {tk}'.encode(en_format))

    conn.close()
