#ifndef RK_MAIN_H
#define RK_MAIN_H

#include <Rk.h>

class RkWidget;

class RkMain {
  public:
          RkMain();
          RkMain(int argc, char **argv);
          ~RkMain();
          int exec();
          bool setTopLevelWindow(RkWidget *widget);
  private:
          RkWidget *topLevelWindow;
};

#endif // RK_MAIN_H
