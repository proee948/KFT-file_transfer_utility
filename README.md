# File Path Saver & TCP File Transfer

A minimal drag-and-drop local network file transfer tool.

# scope

linux x86_64 only

## Components

A PyQt6 GUI captures a dropped file's path, and a C client/server pair transfers that file over a raw TCP socket using zero copy methods like `sendfile()`.
- **`gui.py`** — PyQt6 drop zone. Dropping a file extracts its absolute path
- **`main.h`** — common header.
- **`host.c`** — majority of sending and handling logic.
- **`receiver.c`** — exactly that, a receiver meant for target.

## Build

```bash
gcc receiver.c -o receiver 
gcc -DRECEIVER_IP=\"<receiver-ip>\" -o host host.c
```

`RECEIVER_IP` must be defined at compile time for `host.c`; it defaults to a placeholder string(garbage string) if omitted.

## Usage

1. Start the receiver on the target machine:
```bash
   ./receiver
```
2. Run the GUI on the sending machine and drag a file onto the window.
3. Run the host binary to send the file:
```bash
   ./host
```
4. The received file is written to the receiver's working directory using the original name and extension.

## Requirements

- Python 3 with PyQt6 (`pip install PyQt6`)
- GCC / POSIX environment (uses `sys/socket.h`, `sys/sendfile.h`, `arpa/inet.h`)

## Notes

- Port `4444` is hardcoded on both ends.
- `receiver` handles one connection per run and exits after the transfer completes.
- x86_64 to x86_64 works with no issues (tested by sending files between two x86_64 linux distro PCs)
- receiver loops until SIGINT , ctrl+c

# issues

there is a issue where `stat` structure is platform specific in size and thus non usable on diff architectures,
to fix this a custom structure equivalent of stat needs to be defined,populated and passed over socket.
this is to be done using `__packed__` compiler attribute.
testing done on usage of program between x86_64 fedora pc sending to aarch64 raspberry pi terminates with segfault,above
explanation is the most likely cause.

- [] check once fixed.
there are many ways to improve and automate this tool, maybe one day.

