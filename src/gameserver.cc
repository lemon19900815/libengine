#include "gameserver.h"

#include "timehelp.h"
#include "mainloop.h"
#include "net/netcore.h"
#include "net/session_manager.h"

util::Time gtime;
util::MainLoop gloop;

// �����������˿�
constexpr int32_t kServerPort = 6666;
// ���������������
constexpr int32_t kMaxEventNum = 10000;
// ÿ֡ʱ�䶨��
constexpr uint32_t kPerFrameTime = 20;

RunApplication(GameServer);

GameServer::GameServer()
{
  stoped_ = true;
}

GameServer::~GameServer()
{
}

bool GameServer::startup(int argc, char* argv[])
{
  NOTUSED(argc);
  NOTUSED(argv);

  stoped_ = false;

  // ע����ѭ�����ȷ�ʽ�ͼ��
  gloop.registerSchema(
    kPerFrameTime, std::bind(&GameServer::schema, this));

  auto accept_proc = std::bind(&SessionManager::onAcceptSession, gSessionManagerPtr, std::placeholders::_1);
  auto close_proc = std::bind(&SessionManager::onCloseSession, gSessionManagerPtr, std::placeholders::_1);

  netcore_ = std::make_shared<NetCore>();
  if (!netcore_->initialize(kMaxEventNum, accept_proc, close_proc))
  {
    std::cerr << "initialize netcore failed." << std::endl;
    return false;
  }

  return netcore_->startup(kServerPort);
}

void GameServer::run()
{
  while (!stoped_)
  {
    gtime.update();

    // ��ѭ��
    gloop.update();

    // sleep for 10 ms
    ThreadHelper::sleep(10);
  }

  std::cout << "GameServer is closing..." << std::endl;
}

void GameServer::schema()
{
  bool active = false;
  if (gloop.frame_count() % 5 == 0)
    active = true;

  gSessionManagerPtr->update(active);
}

void GameServer::stop()
{
  stoped_ = true;
  netcore_->stop();
}
