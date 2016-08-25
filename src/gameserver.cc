#include "gameserver.h"

#include "util.h"
#include "netcore.h"

RunApplication(GameServer);

GameServer::GameServer()
{
  netcore_ = std::make_shared<NetCore>();
}

GameServer::~GameServer()
{

}

bool GameServer::startup(int argc, char* argv[])
{
  NOTUSED(argc);
  NOTUSED(argv);

#define SERVER_PORT 6666
#define MAX_EVENTS 10000

  if (netcore_->initialize(MAX_EVENTS)) {
    return netcore_->startup(SERVER_PORT);
  }

  return false;
}

void GameServer::run()
{
  uint64_t current;
  uint64_t last = Time::ms();

// server main loop frame times per second defeine
#define SERVER_FRAME 20

// server per main loop cost milli second define
#define FRAME_TIME 50

  int32_t frame = 0;

  while (1)
  {
    current = Time::ms();
    uint64_t elapsed = current - last;
    if (elapsed >= FRAME_TIME)
    {
      // do main logic
      if (frame % 100 == 0) {
        printf("in main loop\n");
      }

      ++frame;
      last = current;
    }

    // sleep for 10 ms
    ThreadHelper::sleep(10);
  }
}

void GameServer::stop()
{
  netcore_->stop();
}
