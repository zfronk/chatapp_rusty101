---

# Simple TCP Chat Server in C

## Overview

This project is a basic TCP chat server written in C, designed to demonstrate fundamental network programming concepts including socket creation, binding, listening, and handling multiple clients sequentially.

Built with minimal dependencies and focusing on raw socket programming, this server runs on Linux and is intended as a learning tool or foundation for more complex network applications.

---

## Features

* Create and bind a TCP server socket on a specified port
* Listen for incoming client connections
* Accept multiple clients sequentially in a loop
* Receive messages from clients and print them to the server console
* Proper error handling and resource cleanup
* Demonstrates use of essential networking functions like `socket()`, `bind()`, `listen()`, `accept()`, `recv()`, and `close()`

---

## Requirements

* GCC or compatible C compiler
* Linux operating system (tested on Linux Mint)
* Basic understanding of C and Linux networking

---

## How to Compile

```bash
gcc -o main.exe main.c
```

---

## How to Run

```bash
./main.exe
```

By default, the server listens on port 76 (adjustable in source code).

---

## How It Works

1. The server creates a TCP socket.
2. It binds to the specified port and listens for connections.
3. When a client connects, the server accepts the connection.
4. It enters a loop to receive and display messages from the connected client.
5. If the client disconnects, the server closes the client socket and waits for new clients.

---

## Next Steps & Improvements

* Support for multiple concurrent clients (using threads or `select()`)
* Implement a proper chat protocol with message broadcasting
* Add logging and configuration file support
* Develop a client application for easier testing
* Security enhancements (input validation, encryption)

---

## License

This project is open source and free to use under the MIT License.

---

## Contact

For questions or suggestions, reach out via GitHub issues or contact me at zfronk....

---

