import socket

def main():
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_address = ('127.0.0.1', 25565)
    client_socket.connect(server_address)

    message = "梅"
    client_socket.sendall(message.encode('utf-8'))

    response = client_socket.recv(1024)#.decode('utf-8')
    print(f"Received: {response}")

    client_socket.close()

if __name__ == "__main__":
    main()