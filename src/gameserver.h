#ifndef __GAME_SERVER_INC_H__
#define __GAME_SERVER_INC_H__

#include "serverapplication.h"
#include <memory>

class NetCore;

class GameServer : public ServerApplication
{
public:
  GameServer();
  ~GameServer() override;

  bool startup(int argc, char* argv[]) override;
  void run() override;
  void stop() override;

private:
  std::shared_ptr<NetCore> netcore_;
};

#endif // __GAME_SERVER_INC_H__
