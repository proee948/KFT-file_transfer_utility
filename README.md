# TCP File Transfer utility

A minimalist file streaming linux exclusive utility for transferring files over local network.
still in progress.

# issues

there is a issue where `stat` structure is platform specific in size and thus incompatible with other distros,
to fix this a custom structure equivalent of stat needs to be defined,populated and passed over socket.
this is to be done using `__packed__` compiler attribute.
testing done on usage of program between x86_64 fedora pc sending to aarch64 raspberry pi terminates with segfault,above
explanation is the most likely cause.
[] check once fixed.
