import socket
import random

def random_chinese_string(length):
    # 中文字符的 Unicode 编码范围
    ranges = [
        (0x4E00, 0x9FFF),  # 基本汉字
        (0x3400, 0x4DBF),  # 扩展 A
        (0x20000, 0x2A6DF)  # 扩展 B
    ]
    
    result = []
    for _ in range(length):
        # 随机选择一个范围
        chosen_range = random.choice(ranges)
        # 随机选择一个字符
        char_code = random.randint(chosen_range[0], chosen_range[1])
        # 将字符代码转换为字符
        result.append(chr(char_code))
    
    return ''.join(result)


def main():
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_address = ('127.0.0.1', 25565)
    client_socket.connect(server_address)

    while(1):
        msg = input("> ")
        client_socket.sendall(msg.encode('utf-8'))

        response = client_socket.recv(1024)#.decode('utf-8')
        print(f"Received: {response}")
        print(response.decode('utf-8'))

    client_socket.close()

if __name__ == "__main__":
    main()