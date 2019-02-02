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
#ifdef RK_WIN_OS
  : privateWidget(std::make_unique<RkWidgetWin>(parent))
#elif RK_MAC_OS
  : privateWidget(std::make_unique<RkWidgetMac>(parent))
#else
  : privateWidget(std::make_unique<RkWidgetXWin>(parent))
#endif
{
        if (!privateWidget->init()) {
                RK_LOG_ERROR("can't init private widget");
        }
}

RkWidget::~RkWidget()
{
}

void RkWidget::setTitle(const std::string &title)
{
        privateWidget->setTitle(title);
        widgetTitle = title;
}

const std::string& RkWidget::title() const
{
        return widgetTitle;
}


void RkWidget::show()
{
        privateWidget->show();
}

RkWidget::RkNativeWindow RkWidget::nativeWindow()
{
        return privateWidget->getWindow();
}

Display* RkWidget::display()
{
        return privateWidget->display();
}
