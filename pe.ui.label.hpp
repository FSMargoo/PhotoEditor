#pragma once

#include "pe.ui.object.hpp"

namespace PDotE
{
	namespace UI
	{
		class FlatLabel : public Object
		{
		private:
			bool shadow = false;

			COLORREF _line_color = WHITE;
			COLORREF _background_color;

		public:
			FlatLabel(int nwidth, int nheight, bool nshadow = false, Object* nparent = nullptr)
			{
				width = nwidth;
				height = nheight;

				shadow = nshadow;

				parent = nparent;

				if (shadow == true)
				{
					width += 20;
					height += 20;

					x -= 10;
					y -= 10;
				}

				SetParent(parent);

				CreateRectangleMask(width, height);

				_background_color = WHITE;
			}

			void Draw()
			{
				setfillcolor(_background_color);
				setlinecolor(_line_color);

				if (shadow == false)
				{
					fillrectangle(0, 0, width, height);
				}
				else
				{
					drawRectangleShadow(0, 0, width - 20, height - 20);

					fillrectangle(10, 10, width - 30, height - 30);
				}
			}

			void Move(int nx, int ny)
			{
				x = nx;
				y = ny;

				if (shadow == true)
				{
					x -= 30;
					y -= 30;
				}

				PDraw();
			}

			void Resize(int nwidth, int nheight)
			{
				if (shadow == false)
				{
					width = nwidth;
					height = nheight;
				}
				else
				{
					width = nwidth;
					height = nheight;

					width += 30;
					height += 30;
				}

				PDraw();

				CreateRectangleMask(width, height);
			}

		public:
			void SetShadow(bool nshadow)
			{
				shadow = nshadow;

				width += 60;
				height += 60;

				x -= 30;
				y -= 30;

				PDraw();
			}
			void SetBackgroundColor(COLORREF color)
			{
				_background_color = color;

				PDraw();
			}
			void SetLineColor(COLORREF color)
			{
				_line_color = color;

				PDraw();
			}
		};
	}
}