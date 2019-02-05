#include "RkMainXWin.h"

RkMain::RkMainWin::RkMainXWin()
{
  
}

RkMain::RkMainWin::~RkMainXWin()
{
  
}

void RkMain::setTopLevelWindow(RkWidget* widget)
{
      topLevelWindow = widget;
}

RkWidget* RkMain::topLevelWindow(void)
{
      return topLevelWindow;
}

int RkMain::RkMainWin::exec()
{
        if (!topLevelWindow) {
                RK_LOG_ERROR("top window not defined");
		return 1;
	}

        for (; !isQuit(); )
	        topLevelWindow->processEvents();
	
        return exitStatus();
}
