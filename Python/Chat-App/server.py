import socket
from multiprocessing import Process, Manager

HOST = ''
PORT = 55555

def init_socket():
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.bind((HOST, PORT))
    sock.listen(10)
    return sock

def user_process(conn, user, lock):
    try:
        conn.sendall(b'Please, tell us your name (type exit to leave): ')
        user = conn.recv(1024).decode()
        if user != "exit":
            
            lock.acquire()
            users[user] = conn
            lock.release()
            
            conn.sendall(bytes("Welcome '" + user + "', there are " + str((len(users) - 1))+ " users (besides you) on the system", 'UTF-8')) 
            data = conn.recv(1024).decode()
            print(user + " says: " + data)
            while data != 'exit':

                for key, sock in users.items():
                    if key != user:
                        sock.sendall(bytes(user + " says: " + data, 'UTF-8'))
                data = conn.recv(1024).decode()
                print(user + " says: " + data)

            conn.sendall(b'exit')
            lock.acquire()
            del users[user]
            lock.release()
            conn.close()

    except KeyboardInterrupt:
        conn.sendall(b'exit')
        conn.close()
        return

def listen_process(sock, users, lock):
    try:
        while True:
            conn, addr = sock.accept()
            p = Process(target = user_process, args=(conn, users, lock))
            p.start()
    except KeyboardInterrupt:
        return

if __name__ == '__main__':
    users = Manager().dict()
    lock = Manager().Lock()

    sock = init_socket()
    listen_process(sock, users, lock)

    sock.close()
