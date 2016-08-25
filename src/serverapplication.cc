#include "serverapplication.h"

#include <stdio.h>
#include <stdlib.h>

//RunApplication(ServerApplication);

ServerApplication::ServerApplication()
{

}

ServerApplication::~ServerApplication()
{

}

bool ServerApplication::startup(int argc, char* argv[])
{
  printf("server application startup.\n");
  return true;
}

void ServerApplication::run()
{
  printf("server application is running.\n");
}

void ServerApplication::stop()
{
  printf("server application stoped.\n");

#ifdef _WIN32
  system("pause");
#endif
}
