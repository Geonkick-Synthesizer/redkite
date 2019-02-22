#include "RkMain.h"
#include "RkWidget.h"
#include "RkLog.h"

#include <vector>

int main(int arc, char **argv)
{
        RkMain app(arc, argv);

        // Create main window.
        auto mainWindow = new RkWidget;
        mainWindow->setTitle("Main Window");
	mainWindow->setPosition(180, 180);
        mainWindow->setSize(400, 500);

        int x = 10;
        int y = 10;
        RK_LOG_DEBUG("create childs");
        for (auto i = 0; i < 10; i++) {
                RK_LOG_DEBUG("create child " << i);
                auto child = new RkWidget(mainWindow);
                child->setTitle("Child[" + std::to_string(i) + "] - LEVEL 1");
                child->setPosition(x, y);
                child->setSize(60, 60);
                child->setBorderColor(0, 255, 0);
                child->show();

                auto child_l = new RkWidget(child);
                child_l->setTitle("Child[" + std::to_string(i) + "] - LEVEL 2");
                child_l->setPosition(10, 10);
                child_l->setSize(30, 30);
                child_l->setBorderColor(0, 0, 255);
                child_l->show();

                x += 65;
                if (x > 650) {
                        y += 65;
                        x = 10;
                }
        }

        mainWindow->show();
        if (!app.setTopLevelWindow(mainWindow)) {
                RK_LOG_ERROR("can't set top level window");
                exit(1);
        }

        int res = app.exec();
        return res;
}


