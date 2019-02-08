#include "RkMain.h"
#include "RkWidget.h"
#include "RkLog.h"

int main(int arc, char **argv)
{
    RkMain app(arc, argv);

    // Create main window.
    RkWidget mainWindow;
    widget.setTitle("Main Window");
    widget.setSize(300, 300);

    // Create first child of a parent widget.
    RkWidget child1(&mainWindow);
    child.setSize(50, 50);
    child.setX(10);
    child.setY(10);

    // Create second child of X11 window parent.
    auto x11Paret = rk_from_x11_info(x11display, x11screenumber, x11window);
    RkWidget child2(x11Paret);
    child.setSize(50, 50);
    child.setX(80);
    child.setY(80);

    if (!app.setTopLevelWindow(&mainWindow)) {
            RK_LOG_ERROR("can't set top level window");
            exit(1);
    }

    mainWindow.show();
    int res = app.exec();
    return res;
}


