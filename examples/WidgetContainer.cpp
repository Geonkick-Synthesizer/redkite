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
#include "RkWidgetContainer.h"

/**
 * This is an exmaple of usage of RkWidgetContainer class.
 */

int main(int arc, char **argv)
{
	RkMain app(arc, argv);
	auto widget = new RkWidget(&app);
	widget->setFixedSize({400, 300});
	widget->setTitle("RkWidgetContainer example");
	widget->show();

	auto container = new RkWidgetContainer(widget, Rk::Orientation::Horizontal);
	container->setSpacing(5);
	for (int i = 0; i < 10; i++) {
		if (i == 2)
			container->addSpace(10);
		if (i == 8)
			container->addSpace(30, Rk::Alignment::AlignRight);
		auto child = new RkWidget(widget);
		child->setSize(10, 10);
		child->setBackgroundColor({255, 0, 0});
		child->show();
		if (i == 3) {
			child->setBackgroundColor({100, 0, 34});
			child->hide();
		}

		if (i > 5) {
			container->addWidget(child, Rk::Alignment::AlignRight);
			child->setBackgroundColor({0, 255, 0});
		} else {
			container->addWidget(child);
		}
	}
	auto child = new RkWidget(widget);
	child->setBackgroundColor({0, 0, 255});
	child->setPosition(0, widget->height() - 30);
	child->setSize(container->size().width(), 10);
	child->show();

	return app.exec();
}
