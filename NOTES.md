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