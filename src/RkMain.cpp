#include "RkMain.h"
#include "RkLog.h"
#include "RkWidget.h"

RkMain::RkMain()
#ifdef RK_WIN_OS
  : privateMain(std::make_unique<RkMainWin>())
#elif RK_MAC_OS
  : privateMain(std::make_unique<RkMainMac>())
#else
  : privateMain(std::make_unique<RkMainXWin>())
#endif
  , topLevelWindow(nullptr)
{
        RK_LOG_INFO("called");
}

RkMain::RkMain(int argc, char **argv)
        : topLevelWindow(nullptr)
{
       RK_UNUSED(argc);
       RK_UNUSED(argv);
       RK_LOG_INFO("called");
}

RkMain::~RkMain()
{
}

bool RkMain::setTopLevelWindow(RkWidget *widget)
{
        if (topLevelWindow) {
                RK_LOG_ERROR("top level window is already set");
                return false;
        }
	privateMain->setTopLevelWindow(topLevelWindow);
        return true;
}

int RkMain::exec()
{
        if (!topLevelWindow) {
                RK_LOG_ERROR("top level window is not set");
                return 1;
        }

	return privateMain->exec();
}
