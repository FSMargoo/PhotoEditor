#pragma once

#include "pe.ui.hpp"
#include "pe.app.uilib.hpp"

namespace PDotE
{
	namespace AppMessageBox
	{
		class InfoMessage
		{
		private:
			bool cancel_clicked = false;
			bool yes_clicked    = false;

		public:
			void CancelOnClicked()
			{
				cancel_clicked = true;
			}
			void YesOnClicked()
			{
				yes_clicked = true;
			}

		public:
			int InfoMessageBox(UI::Object* parent, std::wstring title, std::wstring text)
			{
				auto  label = new UI::MaskLabel(parent->GetWidth(), parent->GetHeight(), 89, parent);
				auto  background_radius = new UI::RadiusLabel(400, 206, 16, false, label);

				IMAGE message_image = GetIcon(L"message");

				auto  message_icon = new UI::ImageLabel(17, 17, &message_image, false, background_radius);

				auto font = GetFont(MEDIUM);
				font.lfHeight = 23;
				settextstyle(&font);

				auto  notice_title =
					new UI::TextLabel(textwidth(title.c_str()), textheight(title.c_str()), background_radius);

				font = GetFont(MEDIUM);
				font.lfHeight = 17;
				settextstyle(&font);
				auto  notice_text =
					new UI::TextLabel(textwidth(text.c_str()), textheight(text.c_str()), background_radius);

				auto  cancel_button =
					new UI::Button(28, 16, false, background_radius);
				auto  yes_button =
					new UI::Button(83, 36, false, background_radius);

				background_radius->Move(parent->GetWidth() / 2 - 200, parent->GetHeight() / 2 - 103);

				message_icon->Move(33, 36);
				notice_title->Move(31, 62);
				notice_text->Move(31, 96);

				notice_title->SetPlaneText(title);
				notice_text->SetPlaneText(text);

				notice_title->SetTextStyle(GetFont(MEDIUM));
				notice_title->SetTextHeight(23);

				notice_text->SetTextStyle(GetFont(MEDIUM));
				notice_text->SetTextHeight(17);

				notice_title->SetTextColor(RGB(15, 147, 243));
				notice_text->SetTextColor(RGB(0, 0, 0));

				cancel_button->SetNormalFillColor(WHITE);
				cancel_button->SetCoverdFillColor(WHITE);
				cancel_button->SetPushedFillColor(WHITE);

				cancel_button->SetNormalLineColor(WHITE);
				cancel_button->SetCoverdLineColor(WHITE);
				cancel_button->SetPushedLineColor(WHITE);

				cancel_button->SetNormalTextColor(RGB(126, 126, 126));
				cancel_button->SetCoverdTextColor(RGB(15, 174, 243));
				cancel_button->SetPushedTextColor(RGB(15, 184, 243));

				cancel_button->SetFontStyle(GetFont(MEDIUM));
				cancel_button->SetTextHeight(14);
				cancel_button->SetPlaneText(L"取消");

				cancel_button->Move(35, 157);

				cancel_button->mouseOnClicked = std::bind(&InfoMessage::CancelOnClicked, this);

				yes_button->SetFontStyle(GetFont(MEDIUM));
				yes_button->SetTextHeight(14);
				yes_button->SetBorder(18);
				yes_button->SetPlaneText(L"确认");

				yes_button->Move(292, 148);

				yes_button->mouseOnClicked = std::bind(&InfoMessage::YesOnClicked, this);

				label->Show();
				label->ShowOffChild();

				ExMessage message;

				while (true)
				{
					while (peekmessage(&message))
					{
						if (parent->ProcessMessage(message) == true)
						{
							if (cancel_clicked == true)
							{
								label->SetParent(nullptr);

								return 0;
							}
							if (yes_clicked == true)
							{
								label->SetParent(nullptr);

								return 1;
							}
						}
					}

					Sleep(1);
				}

				return -1;
			}
			int operator()(UI::Object* parent, std::wstring title, std::wstring text)
			{
				return InfoMessageBox(parent, title, text);
			}
		};
		class AssertMessage
		{
		private:
			bool cancel_clicked = false;
			bool yes_clicked = false;

		public:
			void CancelOnClicked()
			{
				cancel_clicked = true;
			}
			void YesOnClicked()
			{
				yes_clicked = true;
			}

		public:
			int AssertMessageBox(UI::Object* parent, std::wstring title, std::wstring text)
			{
				auto  label = new UI::MaskLabel(parent->GetWidth(), parent->GetHeight(), 89, parent);
				auto  background_radius = new UI::RadiusLabel(400, 206, 16, false, label);

				IMAGE message_image = GetIcon(L"warning");

				auto  message_icon = new UI::ImageLabel(20, 20, &message_image, false, background_radius);

				auto font = GetFont(MEDIUM);
				font.lfHeight = 23;
				settextstyle(&font);

				auto  notice_title =
					new UI::TextLabel(textwidth(title.c_str()), textheight(title.c_str()), background_radius);

				font = GetFont(MEDIUM);
				font.lfHeight = 17;
				settextstyle(&font);
				auto  notice_text =
					new UI::TextLabel(textwidth(text.c_str()), textheight(text.c_str()), background_radius);

				auto  cancel_button =
					new UI::Button(28, 16, false, background_radius);
				auto  yes_button =
					new UI::Button(83, 36, false, background_radius);

				background_radius->Move(parent->GetWidth() / 2 - 200, parent->GetHeight() / 2 - 103);

				message_icon->Move(31, 33);
				notice_title->Move(31, 62);
				notice_text->Move(31, 96);

				notice_title->SetPlaneText(title);
				notice_text->SetPlaneText(text);

				notice_title->SetTextStyle(GetFont(MEDIUM));
				notice_title->SetTextHeight(23);

				notice_text->SetTextStyle(GetFont(MEDIUM));
				notice_text->SetTextHeight(17);

				notice_title->SetTextColor(RGB(255, 58, 90));
				notice_text->SetTextColor(RGB(0, 0, 0));

				cancel_button->SetNormalFillColor(WHITE);
				cancel_button->SetCoverdFillColor(WHITE);
				cancel_button->SetPushedFillColor(WHITE);

				cancel_button->SetNormalLineColor(WHITE);
				cancel_button->SetCoverdLineColor(WHITE);
				cancel_button->SetPushedLineColor(WHITE);

				cancel_button->SetNormalTextColor(RGB(126, 126, 126));
				cancel_button->SetCoverdTextColor(RGB(255, 100, 125));
				cancel_button->SetPushedTextColor(RGB(255, 90, 125));

				cancel_button->SetFontStyle(GetFont(MEDIUM));
				cancel_button->SetTextHeight(14);
				cancel_button->SetPlaneText(L"取消");

				cancel_button->Move(35, 157);

				cancel_button->mouseOnClicked = std::bind(&AssertMessage::CancelOnClicked, this);

				yes_button->SetFontStyle(GetFont(MEDIUM));
				yes_button->SetTextHeight(14);
				yes_button->SetBorder(18);
				yes_button->SetPlaneText(L"确认");

				yes_button->Move(292, 148);

				yes_button->mouseOnClicked = std::bind(&AssertMessage::YesOnClicked, this);

				yes_button->SetCoverdFillColor(RGB(255, 100, 125));
				yes_button->SetCoverdLineColor(RGB(255, 100, 125));
				yes_button->SetPushedLineColor(RGB(255, 90, 125));
				yes_button->SetPushedFillColor(RGB(255, 90, 125));

				label->Show();
				label->ShowOffChild();

				ExMessage message;

				while (true)
				{
					while (peekmessage(&message))
					{
						if (label->ProcessMessage(message) == true)
						{
							if (cancel_clicked == true)
							{
								label->SetParent(nullptr);

								return 0;
							}
							if (yes_clicked == true)
							{
								label->SetParent(nullptr);

								return 1;
							}
						}
					}

					Sleep(20);
				}

				return -1;
			}
			int operator()(UI::Object* parent, std::wstring title, std::wstring text)
			{
				return AssertMessageBox(parent, title, text);
			}
		};
	}
}