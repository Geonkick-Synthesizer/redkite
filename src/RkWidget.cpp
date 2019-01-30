#include "RkWidget.h"
#include "RkLog.h"

RkWidget::RkWidget(RkWidget *parent = nullptr)
{
       RK_UNUSED(parent);
       RK_LOG_INFO("called");
}

RkWidget::~RkWidget()
{
}

void RkWidget::setTitle(const std::string &title)
{
    widgetTitle = title;
}

std::string& RkWidget::title() const
{
    return widgetTitle;
}


void RkWidget::show()
{
        RK_LOG_INFO("called");
}
