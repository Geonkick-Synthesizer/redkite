#include "RkMain.h"
#include "RkWidget.h"
#include "RkLog.h"

/**
 * Demonstration how multiple toolkit states
 * can & must live in the sample process.
 */

#include <thread>

static int func1()
{
    RkMain app;

    RkWidget widget;
    widget.setTitle("Hello First!");
    widget.show();

    if (!app.setTopLevelWindow(&widget)) {
            RK_LOG_ERROR("first: can't set top level window");
            exit(1);
    }

    return app.exec();
}

static int func2()
{
    RkMain app;

    RkWidget widget;
    widget.setTitle("Hello Second!");
    widget.show();

    if (!app.setTopLevelWindow(&widget)) {
            RK_LOG_ERROR("second: can't set top level window");
            exit(1);
    }

    return app.exec();
}


int main(int arc, char **argv)
{
    std::thread first (func1);
    std::thread second (func2);

    std::cout << "\n NOTE: Widgets are put one over another\n "
              << "because there is a need to set different origins. \n"
              << "Just drag and you'll see the second one. \n"
              << "Press any key on active window to close it.\n"
              << "Close button still not work correctly." << std::endl;
    first.join();
    second.join();

    return 0;
}


