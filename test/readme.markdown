# build and test [![Build Status](https://travis-ci.org/reqshark/sendto.svg?branch=master)](https://travis-ci.org/reqshark/sendto)

`test/index.js` file runs the tests by iterating over the required contents
within this directory.

from root directory, pipe the process to tap-spec
```js
$ node test | tap-spec
```

there are some convenience operations via make:
```bash
$ git clone https://github.com/reqshark/sendto.git && cd sendto
$ make clean && make && make check
```

these commands are respectively:
```bash
$ make clean
$ npm i
$ npm t
```
