#include "RkWidget.h"
#include "RkLog.h"

RkWidget::RkWidget(RkWidget *parent)
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

const std::string& RkWidget::title() const
{
    return widgetTitle;
}


void RkWidget::show()
{
        RK_LOG_INFO("called");
}
