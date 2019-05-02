#include "RkMain.h"
#include "RkWidget.h"
#include "RkLog.h"

int main(int arc, char **argv)
{
    RkMain app(arc, argv);

    auto widget = new RkWidget(&app);
    widget->setTitle("Hello!");
    widget->show();

    //    if (!app.setTopLevelWindow(widget)) {
    //            RK_LOG_ERROR("can't set top level window");
    //            exit(1);
    //    }

    int res = app.exec();
    return res;
}


