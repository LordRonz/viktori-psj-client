#!/usr/bin/env python3

import logging
import socket
import concurrent.futures
import time
from secrets import choice

def client_thread(name):
    HOST = '127.0.0.1'
    PORT = 3069
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.connect((HOST, PORT))
        while True:
            payload = f'{choice((0, 1))} {choice(range(1, 101))} {choice(range(1, 101))}\n'
            s.sendall(bytes(payload, 'utf-8'))
            data = s.recv(1024)
            if not data:
                return
            logging.info('Thread %s, Received %s', name, repr(data))
            time.sleep(3)

def main():
    fmt = '%(asctime)s: %(message)s'
    logging.basicConfig(format=fmt, level=logging.INFO,
                        datefmt='%H:%M:%S')
    with concurrent.futures.ThreadPoolExecutor(max_workers=5) as executor:
        executor.map(client_thread, range(5))

if __name__ == '__main__':
    main()
