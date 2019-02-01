#include "RkLog.h"
#include "RkWidget.h"
#ifdef RK_WIN_OS
#include "RkWidgetWin.h"
#elif RK_MAC_OS
#include "RkWidgetMac.h"
#else
#include "RkWidgetXWin.h"
#endif

RkWidget::RkWidget(RkWidget *parent)
#ifdef RK_WIN_API
  : privateWidget(std::make_unique<RkWidgetWin>(parent))
#elif RK_WIN_MAC
  : privateWidget(std::make_unique<RkWidgetMac>(parent))
#else
  : privateWidget(std::make_unique<RkWidgetXWin>(parent))
{
       RK_LOG_INFO("called");
}

RkWidget::~RkWidget()
{
}

void RkWidget::setTitle(const std::string &title)
{
        privateWidget->setTitle(title);
}

const std::string& RkWidget::title() const
{
        return privateWidget->title();
}


void RkWidget::show()
{
        privateWidget->show();
}
