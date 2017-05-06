# sendto

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
