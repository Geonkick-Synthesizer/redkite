#include "RkWidget.h"
#include "RkWidgetImpl.h"

RkWidget::RkWidgetImpl(RkWidget *parent = nullptr)
        : parentWidget{parent}
        , platformWindow{parent ? parent->nativeWindowInfo() : nullptr}
{
}

RkWidget::RkWidgetImpl(const std::shared_ptr<RkNativeWindowInfo> &parent)
        : platformWindow{parent}
{
}

void RkWidget::RkWidgetImpl::show()
{
}

void RkWidget::RkWidgetImpl::setTitle(const std::string &title)
{
}

const std::string& RkWidget::RkWidgetImpl::title() const
{
}

std::shared_ptr<RkNativeWindowInfo> RkWidget::RkWidgetImpl::nativeWindowInfo() const
{
}

bool RkWidget::RkWidgetImpl::isClose() const
{
}

void RkWidget::RkWidgetImpl::processEvents()
{
}

RkWindowId RkWidget::RkWidgetImpl::id() const
{
}

void RkWidget::RkWidgetImpl::processEvent(const std::shared_ptr<RkEvent> &event)
{
}

RkWidget* RkWidget::RkWidgetImpl::parent()
{
}

RkWidget* RkWidget::RkWidgetImpl::child(const RkWindowId &id) const
{
}

void RkWidget::RkWidgetImpl::setSize(int x, int y)
{
}

void RkWidget::RkWidgetImpl::setSize(const std::pair<int, int> &size)
{
}

std::pair<int, int> RkWidget::RkWidgetImpl::size() const
{
}

void RkWidget::RkWidgetImpl::setWidth(int w)
{
}

int RkWidget::RkWidgetImpl::width() const
{
}

void RkWidget::RkWidgetImpl::setHeight(int h)
{
}

int RkWidget::RkWidgetImpl::height() const
{
}

int RkWidget::RkWidgetImpl::x() const
{
}

void RkWidget::RkWidgetImpl::setX(int x)
{
}

int RkWidget::RkWidgetImpl::y() const
{
}

void RkWidget::RkWidgetImpl::setY(int y)
{
}
//          void setBackgroundColor(const RkColor &color);
void RkWidget::RkWidgetImpl::setBackgroundColor(int r, int g, int b)
{
}
//void setBackgroundColor(std::tuple<int, int, int, int> &color);
//RkColor backgroundColor() const;
//d::tuple<int, int, int, int> backgroundColor() const;
