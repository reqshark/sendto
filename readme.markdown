# sendto

unix datagrams on osx have system output buffer limits of 2048 bytes.

this module performs a posix `sendto()` but first sets socket option `SO_SNDBUF`, raising the output limit size up to the size of whatever node buffer you pass.
