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

    auto widget = new RkWidget(&app);
    widget->setTitle("Hello First!");
    widget->setX(10);
    widget->setY(10);
    widget->setSize(250, 250);
    widget->show();

    return app.exec();
}

static int func2()
{
    RkMain app;

    auto widget = new RkWidget(&app);
    widget->setTitle("Hello Second!");
    widget->setX(100);
    widget->setY(100);
    widget->setSize(300, 400);
    widget->show();

    return app.exec();
}


int main(int arc, char **argv)
{
    std::thread first (func1);
    std::thread second (func2);

    first.join();
    second.join();

    return 0;
}
