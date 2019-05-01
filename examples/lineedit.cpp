/**
 * File name: painter.cpp
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
#include "RkLog.h"
#include "RkLineEdit.h"

class  LineEditExample: public RkWidget {
  public:
        LineEditExample(const std::shared_ptr<RkEventQueue> &q, RkWidget *parent = nullptr)
                : RkWidget(parent)
        {
                setEventQueue(q.get());
                auto lineEdit = new RkLineEdit(this);
                //                lineEdit->setBackgroundColor(80, 80, 80);
                lineEdit->setSize(150, 25);
                RK_ACT_BIND(lineEdit, textEdited, RK_ACT_ARGS(const std::string &text), this, onUpdateText(text));
                lineEdit->show();
        }

  protected:
        void onUpdateText(const std::string &text)
        {
                RK_LOG_INFO("text:" << text);
        }
};

int main(int arc, char **argv)
{
    RkMain app(arc, argv);

    auto widget = new LineEditExample(app.eventQueue());
    widget->setTitle("Line Edit Example");
    widget->setSize(350, 350);
    widget->show();

    if (!app.setTopLevelWindow(widget)) {
            RK_LOG_ERROR("can't set top level window");
            exit(1);
    }

    return app.exec();
}
