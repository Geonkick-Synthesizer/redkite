#ifndef RK_WIDGET_H
#define RK_WIDGET_H

#include <Rk.h>

#include <string>

class RkWidget {
  public:
#ifdef RK_OS_WIN
          using RkNativeWindow = HWND;
#elif RK_OS_MAC
          using RkNativeWindow = NSWindow;
#else
          using RkNativeWindow = Window;
#endif

          RkWidget(RkWidget *parent = nullptr);
          virtual ~RkWidget();
	  void show();
          void setTitle(const std::string &title);
	  const std::string& title() const;
          RkNativeWindow nativeWindows();

  private:

/**
 * Private implementations for platforms.
 * Not to be exposed to users.
 * This also provides ABI compatibility.
 */
#ifdef RK_OS_WIN
	  class RkWidgetXWin;
	  std::unique_ptr<RkWidgetWin> privateWidget;
#elif RK_OS_MAC
	  class RkWidgetMac;
	  std::unique_ptr<RkWidgetMac> privateWidget;
#else
          class RkWidgetXWin;
	  std::unique_ptr<RkWidgetXWin> privateWidget;
#endif
};

#endif // RK_WIDGET_H
