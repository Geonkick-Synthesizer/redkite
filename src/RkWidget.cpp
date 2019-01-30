#include "RkWidget.h"

RkWidget::RkWidget(RkWidget *parent = nullptr)
{
       RK_UNUSED(parent);
}

virtual ~RkWidget()
{
}

int RkWidget::setTitle(const std::string &title)
{
    widgetTitle = title;
}

std::string& RkWidget::title() const
{
    return widgetTitle;
}


void RkWidget::show()
{
}
