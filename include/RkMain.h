#ifndef RK_MAIN_H
#define RK_MAIN_H

#include <Rk.h>

class RkMain {
  public:
          RkMain();
          RkMain(int argc, char **argv);
          ~RkMain();
          int exec();
};

#endif // RK_MAIN_H
