
class RkWidget::RkWidgetImpl {
 public:
        explicit RkWidgetImpl(RkWidget *parent = nullptr);
        explicit RkWidgetImpl(const std::shared_ptr<RkNativeWindowInfo> &parent);
        RkWidgetImpl(const RkWidget &other) = delete;
        RkWidgetImpl& operator=(const RkWidgetImpl &other) = delete;
        RkWidgetImpl(RkWidgetImpl &&other) = delete;
        RkWidgetImpl& operator=(RkWidgetImpl &&other) = delete;

        void show();
        void setTitle(const std::string &title);
        const std::string& title() const;
        std::shared_ptr<RkNativeWindowInfo> nativeWindowInfo() const;
        bool isClose() const;
        void processEvents();
        RkWindowId id() const;
        void processEvent(const std::shared_ptr<RkEvent> &event);
        RkWidget* parent();
        RkWidget* child(const RkWindowId &id) const;

        void setSize(int x, int y);
        void setSize(const std::pair<int, int> &size);
        std::pair<int, int> size() const;
        void setWidth(int w);
        int width() const;
        void setHeight(int h);
        int height() const;
        int x() const;
        void setX(int x);
        int y() const;
        void setY(int y);
        //          void setBackgroundColor(const RkColor &color);
        void setBackgroundColor(int r, int g, int b);
        //void setBackgroundColor(std::tuple<int, int, int, int> &color);
        //RkColor backgroundColor() const;
        //        std::tuple<int, int, int, int> backgroundColor() const;

 private:
        RkWidget *parentWidget;
#ifdef RK_WIN_OS
        std::unique_ptr<RkWidgetWin> platformWindow;
#elif
        std::unique_ptr<RkWidgetMac> platformWindow;
#else
        std::unique_ptr<RkWidgetXWin> platformWindow;
#endif
        std::string widgetTitle;
        std::list<RkWidget*> widgetChildren;
};
