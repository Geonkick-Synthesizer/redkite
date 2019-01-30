#ifndef RK_WIDGET_H

#include <string>

class RkWidget {
  public:
          RkWidget(RkWidget *parent = nullptr);
          virtual ~RkWidget();
	  void show();
          void setTitle(const std::string &title);
	  const std::string& title() const;

  private:
	  std::string widgetTitle;
};

#endif // RK_WIDGET_H
