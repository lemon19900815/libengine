#include "util.h"
#include <chrono>
#include <ctime>

namespace Time
{
  /*
  * current ms time
  */
  uint64_t ms()
  {
    auto tp = std::chrono::system_clock::now();
    auto dur = tp.time_since_epoch();
    return std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();
  }

  /*
  * current unix time stamp
  */
  uint64_t now()
  {
    auto tp = std::chrono::system_clock::now();
    return std::chrono::system_clock::to_time_t(tp);
  }

  /*
  * time string format
  */
  std::string asString()
  {
    time_t t = now();
    auto ptm = std::localtime(&t);

    char buf[256];
    snprintf(buf, sizeof(buf), "%04d-%02d-%02d %02d-%02d-%02d.%03d", ptm->tm_year + 1900,
      ptm->tm_mon + 1, ptm->tm_mday, ptm->tm_hour, ptm->tm_min, ptm->tm_sec, (int)(ms() % 1000));

    return std::string(buf);
  }
}
