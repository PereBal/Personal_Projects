import socket
from multiprocessing import Process

HOST = '127.0.0.1'
PORT = 55555

def init_socket():
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.connect((HOST, PORT))
    return sock

def listen_thread(sock, data):
    try:
        while data != "exit":
            print (data)
            data = sock.recv(1024).decode()
    except KeyboardInterrupt:
        return

if __name__ == '__main__':
    waiting = False
    sock = init_socket()
    try: 
        print(sock.recv(128).decode())
        data = input()
        sock.send(bytes(data, 'UTF-8'))
        data = sock.recv(1024).decode()

        t = Process(target=listen_thread, args=(sock, data))
        t.start()

        data = input()
        while data != "exit":
            sock.send(bytes(data, 'UTF-8'))
            data = input()

        sock.send(bytes("exit", 'UTF-8'))

        waiting = True

        t.join()

    except KeyboardInterrupt:
        if not waiting:
            sock.send(bytes("exit", 'UTF-8'))

    sock.close()
