/**
 * File name: WidgetContainer.cpp
 * Project: Redkite (A small GUI toolkit)
 *
 * Copyright (C) 2020 Iurie Nistor <http://geontime.com>
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
#include "RkContainer.h"

/**
 * This is an exmaple of usage of RkContainer class.
 */

int main(int arc, char **argv)
{
	RkMain app(arc, argv);
	auto widget = new RkWidget(&app);
	widget->setFixedSize({400, 300});
	widget->setTitle("RkContainer example");
	widget->show();

	auto container = new RkContainer(widget, Rk::Orientation::Horizontal);
        container->setSize(widget->size());
	container->setSpacing(5);
	for (int i = 0; i < 10; i++) {
                if (i == 2)
                        container->addSpace(10);
                if (i == 8)
                        container->addSpace(10, Rk::Alignment::AlignRight);

                if (i == 7) {
                        auto container1 = new RkContainer(widget, Rk::Orientation::Vertical);
                        container1->setSpacing(5);
                        container1->setSize({40, 100});
                        auto child = new RkWidget(widget);
                        child->setSize(10, 10);
                        child->setBackgroundColor({0, 255, 0});
                        child->show();
                        container1->addWidget(child);
                        child = new RkWidget(widget);
                        child->setSize(10, 10);
                        child->setBackgroundColor({0, 255, 0});
                        child->show();
                        container1->addWidget(child);
                        container->addContainer(container1, Rk::Alignment::AlignRight);
                }

		auto child = new RkWidget(widget);
                child->setSize(10, 10);
                child->setBackgroundColor({0, 0, 255});
                child->show();
                if (i == 3)
                        child->hide();

                if (i > 5)
                        container->addWidget(child, Rk::Alignment::AlignRight);
                else
                        container->addWidget(child);
	}

	return app.exec();
}
