#ifndef __SERVER_APPLICATION_INC_H__
#define __SERVER_APPLICATION_INC_H__

#include <stdio.h>
#include <stdlib.h>

class ServerApplication
{
public:
  ServerApplication();
  virtual ~ServerApplication();

  virtual bool startup(int argc, char* argv[]);
  virtual void run();
  virtual void stop();
};

#define RunApplication(ServerApplication) \
int main(int argc, char* argv[]) {\
  ServerApplication app; \
  if(app.startup(argc, argv)) { \
    app.run(); \
  } else { \
    printf("Server Application Startup Failed.\n");\
    exit(1); \
  }\
  app.stop(); \
}

#endif // __SERVER_APPLICATION_INC_H__
