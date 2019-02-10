#ifndef RK_COLOR_H
#define RK_COLOR_H

class RkColor {
 public:
        explicit RkColor(const RkColor &color);
        //        explicit RkColor(const QString &color);
        explicit RkColor(int r, int g, int b, int a = 255);
        explicit RkColor(std::tuple<int, int, int, int> &color);
        virtual RkColor();
};

#endif // RK_COLOR_H
