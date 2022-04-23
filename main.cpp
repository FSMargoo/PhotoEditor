#include "pe.application.hpp"
#include "pe.app.messagebox.hpp"
#include "pe.app.mainui.hpp"
#include "pe.ui.colorselector.hpp"

int main()
{
	PDotE::UI::XmlWidget* widget = new PDotE::UI::XmlWidget(1476, 872);

	widget->Show();

	PDotE::AppStart::Start start(widget);

	start.InitStartUI(widget);

	return widget->exec();
}