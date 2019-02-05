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
    : privateWidget(parent ? std::make_unique<RkWidgetXWin>(parent->nativeWindow()) : std::make_unique<RkWidgetXWin>())
#endif
{
        if (!privateWidget->init()) {
                RK_LOG_ERROR("can't init private widget");
        }
}

RkWidget::RkWidget(RkNativeWindow parent)
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

void RkWidget::pocessEvents()
{
        privateWidget->processEvents();
}

void RkWidget::closeEvent(std::shared_ptr<RkCloseEvent> &event)
{
        RK_UNUSED(event);
}

void RkWidget::keyPressEvent(std::shared_ptr<RkKeyEvent> &event)
{
        RK_UNUSED(event);
}

void RkWidget::keyReleaseEvent(std::shared_ptr<RkKeyEvent> &event)
{
        RK_UNUSED(event);
}

void RkWidget::paintEvent(std::shared_ptr<RkPainEvent> &event)
{
        RK_UNUSED(event);
}

void RkWidget::mousePressEvent(std::shared_ptr<RkMouseEvent> &event)
{
        RK_UNUSED(event);
}

void RkWidget::mouseReleaseEvent(std::shared_ptr<RkMouseEvent> &event)
{
        RK_UNUSED(event);
}

void RkWidget::mouseDoubleClickEvent(std::shared_ptr<RkMouseEvent> &event)
{
        RK_UNUSED(event);
}

void RkWidget::mouseMoveEvent(std::shared_ptr<RkMouseEvent> &event)
{
        RK_UNUSED(event);
}

void RkWidget::paintEvent(std::shared_ptr<RkPainEvent> &event)
{
        RK_UNUSED(event);
}

void RkWidget::wheelEvent(std::shared_ptr<RkPainEvent> &event)
{
        RK_UNUSED(event);
}

void RkWidget::resizeEvent(std::shared_ptr<RkResizeEvent> &event)
{
        RK_UNUSED(event);
}

void RkWidget::showEvent(std::shared_ptr<RkShowEvent> &event)
{
        RK_UNUSED(event);
}

void RkWidget::hideEvent(std::shared_ptr<RkHideEvent> &event)
{
        RK_UNUSED(event);
}
