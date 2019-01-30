#include "RkMain.h"
#include "RkWidget.h"

int main(int arc, char **argv)
{
    RkMain app(arc, argv);

    RkWidget widget;
    widget.setTitle("Hello!");
    widget.show();

    int res = app.exec();
    return res;
}


