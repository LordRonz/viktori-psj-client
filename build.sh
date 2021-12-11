#!/usr/bin/env bash

gcc -o client.out main.c client.c serial_io.c -pthread
