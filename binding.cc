
/*
  Copyright (c) 2017 Bent Cardan

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"),
  to deal in the Software without restriction, including without limitation
  the rights to use, copy, modify, merge, publish, distribute, sublicense,
  and/or sell copies of the Software, and to permit persons to whom
  the Software is furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included
  in all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
  THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
  IN THE SOFTWARE.
*/

#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <errno.h>

#include "nan.h"
#include "ref.h"

using v8::FunctionTemplate;
using v8::Number;
using v8::String;

using Nan::HandleScope;
using Nan::Set;
using Nan::New;

static int fd, sz;
static struct sockaddr_un addr;

NAN_METHOD(up){

  /* open unix datagram socket for node.js */
  if ( (fd = socket(AF_UNIX, SOCK_DGRAM, 0)) == -1)
    perror("socket error");

  /* start send buffer limit at zero  */
  sz = 0;
}


NAN_METHOD(sendto){
  String::Utf8Value path(info[0]);
  char *sockname = *path;

  /* compare buffer to send buf limit. increase accordingly */
  int opt = node::Buffer::Length(info[1]);
  if (opt > sz) {
    if (setsockopt(fd, SOL_SOCKET, SO_SNDBUF, &opt, sizeof (opt)) < 0)
      perror("SO_SNDBUF setsockopt()");

    /* store new limit */
    sz = opt;
  }

  memset(&addr, 0, sizeof(addr));
  addr.sun_family = AF_UNIX;
  strcpy(addr.sun_path, sockname);

  int tx, rtry = 1, backoff = 250; // start backoff wait at quarter millisecond
  do {
    tx = sendto(
      fd,
      node::Buffer::Data(info[1]),
      opt,
      0,
      (struct sockaddr *)&addr,
      sizeof(struct sockaddr_un)
    );

    if (tx == -1) {
      if (rtry++ > 100)
        perror("retrying sendto(). recv() is slow to read");
      usleep(backoff * rtry);
    }


  } while( tx < 0 );

  info.GetReturnValue().Set(New<Number>(opt));
}

#define EXPORT_METHOD(C, S)                                                    \
  Set(C, New(#S).ToLocalChecked(),                                             \
    Nan::GetFunction(New<FunctionTemplate>(S)).ToLocalChecked());

NAN_MODULE_INIT(Init) {
  HandleScope scope;

  EXPORT_METHOD(target, sendto);
  EXPORT_METHOD(target, up);

}

NODE_MODULE(sendto, Init)
