#include "RkMain.h"
#include "RkLog.h"
#include "RkWidget.h"

RkMain::RkMain()
        : topLevelWindow(nullptr)
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
        topLevelWindow = widget;
        return true;
}

int RkMain::exec()
{
        if (!topLevelWindow) {
                RK_LOG_ERROR("top level window is not set");
                return 1;
        }

        // Move this to platfroms impl.
        Display* d = topLevelWindow->display();
        XEvent event;
        for (;;) {
                XNextEvent(d, &event);
                if (event.type == KeyPress)
                        break;
        }
        return 0;
}
