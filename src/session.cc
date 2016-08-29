#include "session.h"
#include "ringbuffer.h"
#include "networking.h"
#include "util.h"

#include <iostream>
#include <algorithm>

Session::Session(int fd, char* ip, int port,
  int recvbufsize, int sendbufsize)
{
  fd_ = fd;
  port_ = port;
  SAFE_COPY(ip_, ip, sizeof(ip_));
  recvbuf_ = new RingBuffer(recvbufsize);
  sendbuf_ = new RingBuffer(sendbufsize);
}

Session::~Session()
{
  onClose();
}

void Session::onClose()
{
  if (fd_ != -1) {
    SAFE_DELETE(recvbuf_);
    SAFE_DELETE(sendbuf_);

    network::anetClose(fd_);
    fd_ = -1;
  }
}

int Session::onRead()
{
  int len;
  char buf[8192]; // 8k

  unsigned int availablebuflen = recvbuf_->available();
  if (availablebuflen == 0)
    return 0;

  len = network::anetRead2(fd_, buf, std::min<unsigned int>(sizeof(buf), availablebuflen));
  if (len < 0) return -1; // read on fd error

  recvbuf_->__kfifo_put(buf, len);

  return 0;
}

int Session::onWrite()
{
  int len;
  char buf[8192]; // 8k

  unsigned int used = sendbuf_->used();
  if (used == 0)
    return 0;

  if (used > sizeof(buf))
    used = sizeof(buf);

  sendbuf_->__peek(buf, used);

  len = network::anetWrite2(fd_, buf, used);
  if (len < 0) return -1; // write on fd error

  sendbuf_->__seekread(len);

  return 0;
}
