#ifndef RK_MAIN_H
#define RK_MAIN_H

#include "Rk.h"

class RkWidget;

class RkMain {
  public:
          RkMain();
          RkMain(int argc, char **argv);
          ~RkMain();
          int exec();
          bool setTopLevelWindow(RkWidget *widget);
  private:

/**
 * Private implementations for platforms.
 * Not to be exposed to users.
 * This also provides ABI compatibility.
 */
#ifdef RK_OS_WIN
	  RK_PRIVATE_IMPL(RkMainWin, privateMain);
#elif RK_OS_MAC
	  RK_PRIVATE_IMPL(RkMainMac, privateMain);
#else
	  RK_PRIVATE_IMPL(RkMainXWin, privateMain);
#endif

          RkWidget *topLevelWindow;
};

#endif // RK_MAIN_H
