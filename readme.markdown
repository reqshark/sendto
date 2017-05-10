# sendto
[![Build Status](https://travis-ci.org/reqshark/sendto.svg?branch=master)](https://travis-ci.org/reqshark/sendto)

unix datagrams on osx have system send buffer limits of `2048` bytes.

this module performs a posix `sendto()` but first sets socket option `SO_SNDBUF`, raising the send limit size up to the size of whatever node buffer you pass.

```bash
npm i sendto
node -e "require('sendto')('/tmp/a', Buffer('hello'))"
```

### sendto(*string*, *buffer*)

pass a unix datagram socket path and then the buffer, something like:

```js
const sendto = require('sendto')
const str = 'some buffer bigger than this'
sendto('/tmp/mysocketpath', Buffer(str) )
```

*special note on `sendto(str, Buffer)`. there are two ways to interrupt or force node process to exit:*

* not giving node buffer

* to an addressable sockname on `recv` side (bind the `recv()` first before `sendto()`)

#### my ideas on that:

implicit coercion seems to be preferred by JavaScript over type checking, i.e. convert input to a buffer for the user. And where there's no socket address, we should probably back-off and retry to send later. Or emit JavaScript error event about the missing addressable path. Probably overkill to do a JS error, since the native `perror()` call already does some descriptive noise about it, though less catchable in JS
