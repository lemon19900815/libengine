#ifndef __SESSION_INC_H__
#define __SESSION_INC_H__

class RingBuffer;

#define DEFAULT_RECV_BUFSIZE (64 * 1024)
#define DEFAULT_SEND_BUFSIZE (64 * 1024)

#include "networking.h"
#include <memory>
#include <cstring>
#include <iostream>

class Session final
{
public:
  typedef std::shared_ptr<Session> PTR;
  typedef std::weak_ptr<Session> WPTR;

public:
  Session(int fd, char* ip, int port,
    int recvbufsize = DEFAULT_RECV_BUFSIZE,
    int sendbufsize = DEFAULT_SEND_BUFSIZE);

  ~Session();

  /*
  * close session
  */
  void onClose();
  /*
  * read socket, 0-success, -1 error[close session]
  */
  int onRead();
  /*
  * write socket, 0-success, -1 error[close session]
  */
  int onWrite();

public:
  /*
  * session handle file descriptor
  */
  inline int fd() const {
    return fd_;
  }

  /*
  * session unique description
  */
  inline std::string description() const {
    char desc[128];
    snprintf(desc, sizeof(desc), "%s:%d", ip_, port_);
    return std::string(desc);
  }

private:
  // socket file descriptor
  int fd_;

  char ip_[IP_ADDRSTRLEN];
  int port_;

  RingBuffer* recvbuf_;
  RingBuffer* sendbuf_;
};

#endif // __SESSION_INC_H__
