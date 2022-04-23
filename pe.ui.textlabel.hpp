#pragma once

#include "pe.ui.object.hpp"

#include <string>

namespace PDotE
{
	namespace UI
	{
		class TextLabel : public Object
		{
		private:
			COLORREF font_color;

			std::wstring plane_text;

			bool text_center = false;

		public:
			TextLabel(int nwidth, int nheight, Object* nparent = nullptr)
			{
				width  = nwidth;
				height = nheight;

				SetParent(nparent);

				CreateRectangleMask(width, height);

				gettextstyle(&_font);

				font_color = gettextcolor();
			}

			void Draw()
			{
				setbkmode(TRANSPARENT);
				
				settextstyle(&_font);

				int text_x;

				if (text_center == false)
				{
					text_x = 0;
				}
				else
				{
					text_x = width / 2 - textwidth(plane_text.c_str()) / 2;
				}

				int text_y = height / 2 - textheight(plane_text.c_str()) / 2;

				settextcolor(font_color);

				outtextxy(text_x, text_y, plane_text.c_str());
			}

		public:
			void SetTextStyle(LOGFONT nfont)
			{
				_font = nfont;

				PDraw();
			}
			void SetPlaneText(std::wstring text)
			{
				plane_text = text;

				PDraw();
			}
			void SetTextColor(COLORREF color)
			{
				font_color = color;

				PDraw();
			}

			void SetTextCenter(bool center)
			{
				text_center = center;

				PDraw();
			}
		};
	}
}