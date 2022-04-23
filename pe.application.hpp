#pragma once

#include "pe.app.start.hpp"

namespace PDotE
{
	class Application
	{
	private:
		UI::XmlWidget* widget;

	public:
		Application()
		{
			widget = new UI::XmlWidget(1476, 872);

			widget->Show();

			AppStart::Start start(widget);

			start.InitStartUI(widget);
		}

		int exec()
		{
			return widget->exec();
		}

	public:

	};
}