#!/usr/bin/env python3

import argparse
import concurrent.futures
import logging
import socket
import threading
from secrets import choice
from typing import Any


def get_args() -> dict[str, Any]:
    parser = argparse.ArgumentParser(description="Dummy Client")
    parser.add_argument("-p", default=3069, type=int, help="Server Port")
    parser.add_argument("-a", default="127.0.0.1", type=str, help="Server IP")
    parser.add_argument("-t", default=5, type=int, help="Thread count")

    return vars(parser.parse_args())


def client_thread(args: dict[str, Any]) -> None:
    ADDR: str = args["addr"]
    PORT: int = args["port"]
    NAME: int = args["name"]
    event: threading.Event = args["event"]
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.connect((ADDR, PORT))
        while True:
            payload = f"{choice(range(1, 101))} {choice(range(1, 101))} {choice(range(1, 101))}\n"
            s.sendall(bytes(payload, "utf-8"))
            data = s.recv(1024)
            if not data:
                break
            logging.info("Thread %s, Received %s", NAME, repr(data))
            event.wait(choice(range(1, 7)))


def main() -> None:
    fmt = "%(asctime)s: %(message)s"
    logging.basicConfig(format=fmt, level=logging.INFO, datefmt="%H:%M:%S")

    args = get_args()
    event = threading.Event()
    thread_count = max(min(50, args["t"]), 1)
    addr: str = args["a"]
    port: int = max(min(args["p"], 65535), 1)

    try:
        socket.inet_aton(addr)
    except socket.error:
        addr = "127.0.0.1"

    cft = concurrent.futures.ThreadPoolExecutor
    with cft(max_workers=thread_count) as executor:
        executor.map(
            client_thread,
            (
                {
                    "addr": addr,
                    "port": port,
                    "name": i,
                    "event": event,
                }
                for i in range(thread_count)
            ),
        )


if __name__ == "__main__":
    main()
