#ifndef __NET_CORE_INC_H__
#define __NET_CORE_INC_H__

struct aeEventLoop;

#include "session.h"
#include "runable.h"
#include "threadhelper.h"

#include <mutex>

class NetCore : public IRunable, public std::enable_shared_from_this<NetCore>
{
public:
  NetCore();
  virtual ~NetCore();

  /*
  * initialize event module
  */
  bool initialize(int maxeventsize);

  /*
  * start network thread work
  */
  bool startup(int port);

  /*
  * stop network thread work
  */
  void stop();

  // thread function
  void run(void* arg) override;

private:
  /*
   * accept client session
   */
  virtual void onAccept(Session::PTR session);

  /*
  * close client session
  */
  virtual void onClose(Session::PTR session);

private:
  aeEventLoop* ae_;
  ThreadHelper::PTR thread_helper_;

  std::mutex mutex_;
  Session::WPTR* sessions_;
};

#endif // __NET_CORE_INC_H__
