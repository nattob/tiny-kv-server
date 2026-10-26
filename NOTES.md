This is a learning project to practice modern C++ and Linux systems programming by building a small, low-latency key-value server step by step. Each entry logs what I built, what I learned, and what I measured.

## Step 1 - Boiler Plate


**Date:** 2026-10-20   

**Commit:** 'boiler plate'
#### What
Added project structure that includes kvserver, kvbench, kvtop, and a core shared library and tests.
#### Why
**kvserver** - the key-value server \
**kvbench** - The client to create load and measure latency \
**kvtop** - live stats viewer (terminal UI) \
**tests** - unit tests \
**core** - shared logic that can be unit tested 


**Commit:** 'add uniquefd class'
#### What
Add UniqueFd class
#### Why
Proper RAII for linux fds. The tiny-kv-server will be creating fds and the ownership needs to be clear.

- explicit UniqueFd( int fd ) is important here so that fd isn't turned into a UniqueFd by accident, esentially creating a second owner of the same fd number. /
- follow the rule of three

**Commit:** 'listener socket ad error checking'
#### What
Add some error catching. And the ability to create a listening socket
#### Why
- using a template for sys::check() because not all syscalls return the same type. 
- use sys::check() when making a syscall to package errno as an error
- TCP: (SOCK_STREAM)
    - if a packet is lost, the kernel notices and it gets resent
    - bytes arrive in the same order they were sent in
    - connection explicitly setup and closed on both ends
    - if the server is being slow, the kernel will tell the client to slow in order to not buffer overflow
- UDP (SOCK_DGRAM) is another network option, often used in games and market data feeds, because it is faster, butwith out any of the guarentees of TCP
- a listening socket's job is to wait on a port for new clients
- a connection socket (one per client) gets put in a queue on the listening socket and will give you a new fd where you can read client commands and write replies back to it.
