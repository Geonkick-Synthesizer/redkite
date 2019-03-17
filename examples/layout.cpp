/**
 * File name: layout.cpp
 * Project: Redkite (A small GUI toolkit)
 *
 * Copyright (C) 2019 Iurie Nistor <http://quamplex.com>
 *
 * This file is part of Redkite.
 *
 * Redkite is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#include "RkMain.h"
#include "RkWidget.h"
#include "RkVLayout.h"

class LayoutExample : public RkWidget {
  public:
        LayoutExample()
        {
                auto layout = new RkBoxLayout(this, RkLayout::Type::Vertical);
                layout->setPadding(3);
                for (auto i = 0; i < 4; i++) {
                        auto widget = new RkWidget(this);
                        widget->setTitle("Widget" + std::to_string(i + 1));
                        widget->setBackgroundColor(255, 255 - i * 25, 255);
                        widget->show();
                        layout->addWidget(widget);
                }
        }
};

int main(int arc, char **argv)
{
    RkMain app(arc, argv);

    // Create main window.
    auto layoutWidget = new LayoutExample;
    layoutWidget->setTitle("Layout Example");
    layoutWidget->setSize(350, 250);
    layoutWidget->show();

    if (!app.setTopLevelWindow(layoutWidget)) {
            RK_LOG_ERROR("can't set top level window");
            exit(1);
    }

    return app.exec();
}

