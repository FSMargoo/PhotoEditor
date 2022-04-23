#pragma once

#include "pe.ui.object.hpp"

namespace PDotE
{
	namespace UI
	{
		class RadiusLabel : public Object
		{
		private:
			bool shadow = false;

			int radius;

			COLORREF _line_color = WHITE;
			COLORREF _background_color;

		public:
			RadiusLabel(int nwidth, int nheight, int nradius = 4, bool nshadow = false, Object* nparent = nullptr)
			{
				width = nwidth;
				height = nheight;

				shadow = nshadow;

				parent = nparent;

				radius = nradius;

				if (shadow == true)
				{
					width += 120;
					height += 120;

					x -= 60;
					y -= 60;
				}

				SetParent(parent);

				CreateRoundRectangleMask(width, height, radius);

				_background_color = WHITE;
			}

			void Draw()
			{
				setfillcolor(_background_color);
				setlinecolor(_line_color);

				if (shadow == false)
				{
					drawLinedRoundedRectangle(0, 0, width, height, radius, 2);
				}
				else
				{
					drawRoundedRectangleShadow(0, 0, width - 60, height - 60, radius + 2);

					drawLinedRoundedRectangle(30, 30, width - 120, height - 120, radius);
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

				CreateRoundRectangleMask(width, height, radius);
			}

		public:
			void SetRadius(int nradius)
			{
				radius = nradius;

				PDraw();
			}
			void SetShadow(bool nshadow)
			{
				shadow = nshadow;

				if (shadow == true)
				{
					width  += 120;
					height += 120;

					x -= 60;
					y -= 60;
				}
				else
				{
					width  -= 120;
					height -= 120;

					x += 60;
					y += 30;
				}

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