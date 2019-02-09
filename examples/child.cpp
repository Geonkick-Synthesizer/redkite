#include "RkMain.h"
#include "RkWidget.h"
#include "RkLog.h"

#include <vector>

int main(int arc, char **argv)
{
    RkMain app(arc, argv);

    // Create main window.
    RkWidget mainWindow;
    mainWindow.setTitle("Main Window");
    mainWindow.setSize(750, 600);

    int x = 10;
    int y = 10;
    RK_LOG_DEBUG("create childs");
    for (auto i = 0; i < 99; i++) {
            RK_LOG_DEBUG("create child " << i);
            auto child = new RkWidget(&mainWindow);
            child->setTitle("Child-" + std::to_string(i) + " - level0");
            child->setX(x);
            child->setY(y);
            child->setSize(50, 50);
            child->show();

            auto child_l = new RkWidget(child);
            child_l->setTitle("Child " + std::to_string(i) + " -Level1");
            child_l->setX(5);
            child_l->setY(5);
            child_l->setSize(20, 20);
            child_l->show();

            x += 60;
            if (x > 650) {
                    y += 60;
                    x = 10;
            }
    }

    if (!app.setTopLevelWindow(&mainWindow)) {
            RK_LOG_ERROR("can't set top level window");
            exit(1);
    }

    mainWindow.show();
    int res = app.exec();
    return res;
}


