# DualDynamics-ClientServer
An elegant and modular implementation of both client and server-side protocols for efficient data communication. Crafted with modern best practices, this repository offers comprehensive examples and documentation for enthusiasts and professionals alike to understand and deploy client-server interactions.


# Client-Server State Machine Implementation

This repository offers a detailed understanding of the client-server state machine using the socket API. Learn how functions like `socket()`, `bind()`, `listen()`, `accept()`, `connect()`, `send()`, and `recv()` interplay to establish and manage connections.

## Table of Contents

1. [Server State Machine](#server-state-machine)
2. [Client State Machine](#client-state-machine)
3. [Key Concepts](#key-concepts)

## Server State Machine

### 1. Create Socket (`socket()` call)

The server initiates the communication process by creating a socket, which serves as the endpoint for sending or receiving data.

### 2. Bind Socket (`bind()` call)

The `bind()` function associates the socket with a specific IP address and port number, preparing it to listen for incoming connections on that address.

### 3. Listen (`listen()` call)

After binding, the server listens for incoming client connections using the `listen()` function. This sets the server socket in a listening state, specifying the length of the queue for incoming connection requests.

### 4. Accept Connection (`accept()` call)

The server waits for client connections using the `accept()` function. This function is typically blocking, meaning it waits until a client connects. Upon a connection, it returns a new socket specifically for that client.

### 5. Receive & Send Data (`recv()` & `send()` calls)

With the connection established, the server can exchange data with the client using the `recv()` and `send()` functions.

## Client State Machine

### 1. Create Socket (`socket()` call)

The client also starts by creating a socket, enabling it to initiate communication with the server.

### 2. Connect to Server (`connect()` call)

The client connects to a listening server using the `connect()` function. It requires the IP address and port number of the server to establish this connection.

### 3. Send & Receive Data (`send()` & `recv()` calls)

Once the connection is made, the client and server can exchange data using the `send()` and `recv()` functions.

## Key Concepts

### Why is `accept()` blocking?

The `accept()` function is designed to block so that the server can efficiently wait for incoming connections without constant polling. For non-blocking behavior, consider setting the socket to non-blocking mode or using `select()` or `epoll()` mechanisms.

### Role of `connect()`

The `connect()` function enables the client to initiate a connection to a listening server by providing the server's IP and port. If the server isn't active or there are network issues, this call will fail.

---

# Integer Accumulator Server

This repository houses a client-server application where the client sends integer values to the server. The server accumulates these values. When the client sends a value of `0`, the server completes the accumulation and sends the final result back to the client.

## Table of Contents

1. [Problem Statement](#problem-statement)


## Problem Statement

### Objective:

Develop a client and server application with the following characteristics:

1. **Client**:
    * The client can send multiple integer values to the server.
    * Once the client sends a value of `0`, it indicates the end of the input sequence.
    
2. **Server**:
    * The server continuously listens for incoming integer values from the client.
    * It accumulates the values sent by the client.
    * When the server receives a value of `0`, it concludes the accumulation process and sends the final sum back to the client.

### Constraints:

- The client must be able to send a sequence of integer values in succession.
- The server must maintain a live connection with the client until the value `0` is received, post which it should send back the final result.
- Error handling mechanisms should be in place to manage potential connection drops or invalid inputs.

# UNIX Domain Sockets in Linux: `sockaddr_un`

In Linux, the `sockaddr_un` structure is crucial for UNIX domain sockets, a method of inter-process communication on the same machine. This structure is defined in the `<sys/un.h>` header file.

## Structure Definition

The typical definition of this structure is as follows:

```c
struct sockaddr_un {
    sa_family_t sun_family;     /* AF_UNIX */
    char        sun_path[108];  /* pathname */
};
```

## Key Components

- **sun_family**: This always contains the value `AF_UNIX`.
- **sun_path**: This is a character array capturing the pathname. Notably, if it begins with a null byte, it represents an abstract path.

## Integration in C/C++ Programs

For developers working on a Linux machine, the `<sys/un.h>` header should be readily available. To utilize the `sockaddr_un` structure in your C or C++ application, include the header as:

```c
#include <sys/un.h>
```
## Locating the Header
To verify the presence of this header or to inspect its content:

Navigate to its usual directory:
bash
```C
/usr/include/sys/
```

Use a text editor or a terminal tool such as cat to display its content:

```bash
cat /usr/include/sys/un.h
```

Reading through the un.h file will provide a comprehensive view of `sockaddr_un`, along with any associated macros or functions.

```
cat /usr/include/bits/socket_type.h
```

![](/images/Screenshot%20from%202023-08-16%2018-58-48.png)

```bash
cat /usr/include/bits/types/struct_osockaddr.h
```

```C
#ifndef __osockaddr_defined
#define __osockaddr_defined 1

/* This is the 4.3 BSD `struct sockaddr' format, which is used as wire
   format in the grotty old 4.3 `talk' protocol.  */
struct osockaddr
{
  unsigned short int sa_family;
  unsigned char sa_data[14];
};

#endif

```

------------------

# bind() Function in Socket Programming

The `bind()` function is used in socket programming to associate a socket with a specific address. In essence, it "binds" a socket to a particular endpoint.

In this way servers dictates to the operating system the criteria for receiving the data.

Here , bind system call is telling the OS , if there is a packet from the mentioned address it should be sent to this server ,which has this address.

## Function Signature

In C, the function signature for `bind()` is:

```c
int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
```

## Parameters

- **sockfd**: This is the socket file descriptor, returned by the `socket()` function.
- **addr**: A pointer to a structure representing the address to which the socket should be bound. The structure depends on the address family:
  * IPv4 (`AF_INET`): `struct sockaddr_in`
  * IPv6 (`AF_INET6`): `struct sockaddr_in6`
  * UNIX domain sockets (`AF_UNIX`): `struct sockaddr_un`
- **addrlen**: Length in bytes of the address structure.

## Return Value

- **Success**: Returns `0`.
- **Failure**: Returns `-1` and sets `errno`.

## Common Uses

1. **TCP Servers**: Use `bind()` to specify the port and IP address for incoming connections.
2. **UDP**: Use `bind()` to specify the local endpoint for UDP datagrams.

## AF_UNIX Example

```c
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>

int main() {
    int sockfd;
    struct sockaddr_un server_addr;
    const char* SOCKET_PATH = "/tmp/mysocket";

    sockfd = socket(AF_UNIX, SOCK_STREAM, 0); // UNIX domain socket

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sun_family = AF_UNIX; 
    strncpy(server_addr.sun_path, SOCKET_PATH, sizeof(server_addr.sun_path) - 1); 

    if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind failed");
        return 1;
    }

    printf("Bound to UNIX domain socket %s\n", SOCKET_PATH);
    return 0;
}
```

This binds the UNIX domain socket to the local filesystem path `/tmp/mysocket`.


--------------------

# Understanding Socket Address Structures in C

In the realm of socket programming in C, several address structures are vital for managing different types of network communications. This document explores these structures, explaining their importance and differences.

## Table of Contents

- [The Importance of Socket Address Structures](#the-importance-of-socket-address-structures)
- [Comparison of Key Structures](#comparison-of-key-structures)
  - [`struct sockaddr`](#struct-sockaddr)
  - [`struct sockaddr_un`](#struct-sockaddr_un)
  - [`struct sockaddr_in`](#struct-sockaddr_in)
  - [`struct sockaddr_in6`](#struct-sockaddr_in6)

## The Importance of Socket Address Structures

Socket address structures are foundational in C socket programming. They provide:

1. **Flexibility**: The structures accommodate various address families, such as IPv4, IPv6, and UNIX domain sockets.
2. **Uniformity**: Socket functions like `bind()`, `connect()`, and `accept()` use these structures, ensuring consistency across different socket types.
3. **Extensibility**: New structures can be introduced for emerging protocols or standards without altering existing function signatures.

## Comparison of Key Structures

### `struct sockaddr`

This is a generic structure meant to be a placeholder for family-specific structures. It's used for type uniformity in socket function signatures.

```c
struct sockaddr {
    sa_family_t sa_family;  // Address family
    char        sa_data[14]; // Protocol-specific address
};
```

### `struct sockaddr_un`

This structure is specific to UNIX domain sockets, which facilitate inter-process communication on the same machine.

```c
struct sockaddr_un {
    sa_family_t sun_family;  // Address family (should be AF_UNIX)
    char        sun_path[108]; // Null-terminated pathname
};
```

### `struct sockaddr_in`

Tailored for IPv4 communication, this structure carries information like the IP address and port.

```c
struct sockaddr_in {
    sa_family_t    sin_family;  // Address family (should be AF_INET)
    in_port_t      sin_port;    // Port number
    struct in_addr sin_addr;    // IPv4 address
};
```

### `struct sockaddr_in6`

Designed for IPv6, this structure can carry more extensive address data compared to its IPv4 counterpart.

```c
struct sockaddr_in6 {
    sa_family_t     sin6_family;   // Address family (should be AF_INET6)
    in_port_t       sin6_port;     // Port number
    uint32_t        sin6_flowinfo; // Flow information
    struct in6_addr sin6_addr;     // IPv6 address
    uint32_t        sin6_scope_id; // Scope ID
};
```

In many socket functions, you'll often cast a pointer of a specific structure (like `struct sockaddr_in *`) to a more generic one (`struct sockaddr *`) to maintain function signature consistency.

-------------------------

# Understanding `bind` function in Socket Programming

In socket programming in C, the `bind` function plays an integral role by associating a socket with a specific address and port number. This document explains the nuances of passing address structures to the `bind` function.

## Table of Contents
- [Introduction to `bind`](#introduction-to-bind)
- [The Role of Pointers in `bind`](#the-role-of-pointers-in-bind)
- [Example with `struct sockaddr_un`](#example-with-struct-sockaddr_un)

## Introduction to `bind`

The `bind` function is primarily used to bind a socket to a specific address and port number. The signature of this function looks like this:

```c
int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
```

Here, `addr` is a pointer to the address structure, and `addrlen` is its size.

## The Role of Pointers in `bind`

For many C functions, especially those related to sockets, pointers are preferred over the structures themselves. This is due to various reasons including efficiency (avoiding copying data) and flexibility in handling different types of address structures.

Passing `name` directly would result in a compiler error due to a type mismatch. However, by using the `&` operator, you can pass the address of the structure (i.e., a pointer), which aligns with the expected argument type of the function.

## Example with `struct sockaddr_un`

Consider the following code snippet:

```c
struct sockaddr_un name;
ret = bind(connection_socket, (const struct sockaddr *)&name, sizeof(struct sockaddr_un));
```

Here, the `struct sockaddr_un name;` line declares a variable `name` of type `struct sockaddr_un`. However, when we call the `bind` function, it expects a pointer to a `struct sockaddr`. Hence, we use `(const struct sockaddr *)&name` to pass a pointer to `name` and then cast it to the expected type.

Always remember, in C, when you have a struct, using the `&` operator in front of it returns a pointer to that struct. 

---

For those diving into socket programming, understanding these intricacies is essential for effectively working with different socket functions and address structures.

----

# Understanding the `listen` Function in Socket Programming

In the domain of socket programming, especially when dealing with TCP-based communications, the `listen` function holds a significant role. This document elaborates on the purpose and usage of this function.

## Table of Contents

- [Function Definition](#function-definition)
- [Purpose of `listen`](#purpose-of-listen)
- [Usage and Examples](#usage-and-examples)

## Function Definition

The `listen` function is defined as:

```c
int listen(int sockfd, int backlog);
```

- `sockfd`: The socket file descriptor obtained from the `socket()` function.
- `backlog`: The number of connections that the system can queue for this socket while waiting for the server to accept them.

Return Value:
- On success, it returns `0`.
- On failure, `-1` is returned, and the global variable `errno` is set to indicate the error.

## Purpose of `listen`

The primary purpose of `listen` is to mark a socket as a passive socket, i.e., a socket that will be used to accept incoming connection requests using the `accept` function.

The `backlog` parameter specifies the maximum length for the queue of pending connections. If a connection request arrives and the queue is full, the client may receive an error with an indication of `ECONNREFUSED`.

## Usage and Examples

Consider you have a TCP server socket and you want to listen for incoming connections:

```c
int server_socket = socket(AF_INET, SOCK_STREAM, 0);

// ... (binding the socket to an address happens here)

if (listen(server_socket, 5) < 0) {
    perror("Error on listen");
    exit(EXIT_FAILURE);
}
```

In this example, the server socket is marked as a listening socket, ready to accept incoming connection requests. The queue for this socket can hold up to `5` pending connections.

---

# Understanding the `accept` Function in Socket Programming

For those delving into the world of socket programming, particularly with TCP-based servers, understanding the `accept` function is crucial. This document provides a comprehensive overview of this system call and its significance.

## Table of Contents

- [Function Definition](#function-definition)
- [Purpose of `accept`](#purpose-of-accept)
- [Usage and Examples](#usage-and-examples)
- [Common Pitfalls and Notes](#common-pitfalls-and-notes)

## Function Definition

The `accept` system call is defined as:

```c
int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
```

- `sockfd`: The socket file descriptor, typically the one returned from the `socket()` function and has been set up to listen via the `listen()` call.
- `addr`: A pointer to a `struct sockaddr` that will be filled with the address information of the connecting peer.
- `addrlen`: A value-result argument. Initially, it should be set to the size of `addr`. On return, it will contain the actual length (in bytes) of the address returned.

Return Value:
- On success, it returns a new socket file descriptor for the accepted connection. This new descriptor should be used for all subsequent communication with this client.
- On failure, `-1` is returned, and the global variable `errno` is set to indicate the error.

## Purpose of `accept`

The primary role of `accept` is to extract the first connection on the queue of pending connections, create a new socket with a new file descriptor, and return it. This new socket is what the server uses to communicate with the client.

## Usage and Examples

Consider you have a TCP server socket set up and listening:

```c
int server_socket = socket(AF_INET, SOCK_STREAM, 0);
struct sockaddr_in client_addr;
socklen_t client_addr_len = sizeof(client_addr);

// ... (binding and listening on the socket)

int client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_addr_len);
if (client_socket < 0) {
    perror("Error on accept");
    exit(EXIT_FAILURE);
}
```

Here, the server waits for a client connection and, once established, the `client_socket` can be used to communicate with the client.

## Common Pitfalls and Notes

- The `accept` function is blocking by default. If no pending connections are present on the queue, it will wait until one arrives. For non-blocking behavior, you'll need to look into setting socket options or using mechanisms like `select`, `poll`, or `epoll`.

---

# Understanding the Use of `NULL` in `accept()`

In socket programming, one may come across the `accept` function being used in various ways. This document delves into why you might encounter the use of `NULL` in an `accept()` call and what it signifies.

## Function Signature

The `accept` function is defined as:

```c
int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
```

A specific use case one might observe is:

```c
data_socket = accept(connection_socket, NULL, NULL);
```

## Why Use `NULL`?

When `NULL` is used for the `addr` and `addrlen` arguments in the `accept` function, it indicates certain intentions:

### 1. Not Needing Client Information

By passing `NULL`, the server indicates that it does not need to know the address of the connecting client. This approach is common for simple server applications where the identity or address of the client is not required for the server's behavior.

### 2. Simplifying Code

For rudimentary server applications or when demonstrating basic socket programming concepts, omitting unnecessary details can be beneficial. Using `NULL` negates the need to define address structures or handle address lengths, leading to more straightforward code.

### 3. Avoiding Manual Memory Management

Avoiding the definition and management of address structures by passing `NULL` sidesteps potential errors related to memory management. This can be particularly useful in preventing oversights in beginner or demonstration code.

## Conclusion

While using `NULL` in the `accept()` function simplifies certain aspects, there are scenarios, especially in production or complex applications, where knowing the client's address is essential for tasks like logging, access control, or client-specific responses. In these situations, valid pointers for the `addr` and `addrlen` arguments would be provided, allowing `accept` to populate them with the connecting client's address details.

---

# The `read()` System Call in Client-Server Communication

The `read()` system call is a fundamental function in Unix-like operating systems for reading data from file descriptors. In the context of client-server communication, this syscall is commonly used to read data sent over a socket.

## Function Signature

The `read()` function is defined as:

```c
ssize_t read(int fd, void *buf, size_t count);
```

Where:
- `fd` is the file descriptor from which to read.
- `buf` is the buffer to read the data into.
- `count` is the number of bytes to read.

## Return Value

- On success, the number of bytes read is returned (this might be less than the `count` if fewer bytes are available).
- On error, -1 is returned, and `errno` is set to indicate the cause.
- When `read()` encounters the end of the file, it returns 0.

## Use in Client-Server Communication

When dealing with sockets in client-server models:

1. The `fd` would typically be the socket descriptor.
2. The data read would be the data sent by the client or server over the network.

### Important Notes:

- If the other end of the socket is closed and there's no more data to read, `read()` returns 0. In the context of sockets, this usually indicates that the client has closed the connection.
  
- It's essential to handle partial reads. Network communications can be unpredictable, so it's common to use `read()` in a loop until all expected data is received, or an error or end-of-file condition is encountered.

## Example in a Server Context:

Reading from a client's socket might look something like this:

```c
char buffer[256];
ssize_t bytesRead;

bytesRead = read(clientSocket, buffer, sizeof(buffer)-1);
if (bytesRead < 0) {
    perror("Error reading from client socket");
}
```

In this example, the server attempts to read up to 255 bytes from `clientSocket` into `buffer`.

---

To ensure proper functioning in your client-server applications, always handle the return values and potential errors from `read()` appropriately, and be prepared to manage partial reads or interruptions.

---
# `write()` System Call: An Overview

The `write()` system call is an essential function in the realm of Unix and Linux systems, especially when dealing with inter-process and client-server communications.

## **Definition**

The primary purpose of the `write()` syscall is to transfer data from a specified buffer to a provided file descriptor. This function is especially useful when transmitting data over network sockets in client-server architectures.

### **Function Signature**

```c
ssize_t write(int fd, const void *buf, size_t count);
```


- `fd`: This represents a descriptor, often a socket descriptor in the context of network communications. It dictates where the data will be written.
- `buf`: This is a pointer pointing to the buffer from where the data will be sourced.
- `count`: This number dictates the byte size of the data to be written from the buffer.

### Return Value

On successful execution, `write()` will return the actual number of bytes written. Should there be an error, the function will return -1, with the global variable `errno` indicating the error type.

## Role in Client-Server Communication

In the context of client-server dynamics:

- **Server-side**: The server employs `write()` to relay responses or relevant data once it processes requests from the client.
- **Client-side**: `write()` is leveraged by the client to send its requests or data to the server.

It's worth noting that `write()` might not dispatch all bytes in a singular call. Therefore, it's common to use loops to ensure the entire data packet is sent. 

### Example Usage

Consider a scenario where a client wishes to send a message, "Hello Server!", to the server:

```C
char *message = "Hello Server!";
ssize_t bytes_sent;
size_t total_bytes = strlen(message);

bytes_sent = write(socket_fd, message, total_bytes);

if (bytes_sent < 0) {
perror("Error in sending message");
}

```

In this scenario, the client aims to send a message to the server. Incorporating error-checking mechanisms is essential to catch and manage potential transmission issues.

## Conclusion

In the vast domain of client-server applications, it's imperative to understand the intricacies of the `write()` system call. Properly using and handling this syscall can significantly boost the efficacy and speed of networked applications.

----

# Extra Bonus 

# C Library Functions  Overview

Delving into the memory and string operations of the C programming language, we encounter essential functions such as `memset`, `memcpy`, and `strcpy`. This guide provides an insight into their usage and importance.

## `memset`

### Description
`memset` is used for filling a block of memory with a particular value. Commonly, this function initializes arrays or memory regions to a default value.

### Signature
```c
void* memset(void* ptr, int value, size_t num);
```
**Parameters:**
- `ptr`: Pointer to memory location.
- `value`: Value to fill the memory block with.
- `num`: Number of bytes to be set.

**Example**:

To initialize the first ten characters of a string to 'A':

```c
char str[50];
memset(str, 'A', 10);
```

## `memcpy`

### Description
`memcpy` copies memory areas. It's perfect for copying blocks of memory from one location to another.

### Signature
```c
void* memcpy(void* dest, const void* src, size_t num);
```
**Parameters:**
- `dest`: Destination pointer.
- `src`: Source pointer.
- `num`: Number of bytes to copy.

**Example**:

Copying a string from `src` to `dest`:

```c
char src[50] = "sourceString";
char dest[50];
memcpy(dest, src, strlen(src)+1);
```

## `strcpy`

### Description
`strcpy` copies the C-string pointed by `src` (including the null character) to the destination array pointed to by `dest`.

### Signature
```c
char* strcpy(char* dest, const char* src);
```
**Parameters:**
- `dest`: Destination pointer.
- `src`: Source string.

**Example**:

Copying a string "Hello World" from `src` to `dest`:

```c
char src[40] = "Hello World";
char dest[40];
strcpy(dest, src);
```

## Conclusion

Memory and string management is pivotal in C programming. Using functions like `memset`, `memcpy`, and `strcpy`, one can efficiently handle data, making operations streamlined and more intuitive.



## Result

![](./images/Screenshot%20from%202023-08-16%2021-06-16.png)

