#pragma once

#include "pe.ui.object.h"

#include <string>

namespace PDotE
{
	namespace UI
	{
		class Button : public Object
		{
		private:
			bool shadow = false;

			std::wstring plane_text;

			int text_x = 0;
			int text_y = 0;

			IMAGE icon_image;

		private:
			COLORREF normal_line_color = WHITE;
			COLORREF normal_fill_color = WHITE;
			COLORREF normal_text_color = RGB(128, 128, 128);

			COLORREF coverd_line_color = RGB(15, 174, 243);
			COLORREF coverd_fill_color = RGB(15, 174, 243);
			COLORREF coverd_text_color = RGB(255, 255, 255);

			COLORREF pushed_line_color = RGB(18, 178, 234);
			COLORREF pushed_fill_color = RGB(18, 178, 234);
			COLORREF pushed_text_color = RGB(255, 255, 255);

		public:
			std::function<void()> mouseOnClicked;
			std::function<void()> mouseRleased;
			std::function<void()> mouseOnCover;
			std::function<void()> mouseOnRightClicked;

		public:
			Button(int nwidth, int nheight, bool nshadow = false, Object* nparent = nullptr)
			{
				width = nwidth;
				height = nheight;
				shadow = nshadow;

				geomtery_type = RoundedRectangle;
				radius = 9;

				if (shadow == false)
				{
					CreateRoundRectangleMask(width, height, radius);
				}
				else
				{
					width += 30;
					height += 30;

					x -= 15;
					y -= 15;

					CreateRoundRectangleMask(width - 15, height - 15, radius);
				}

				SetParent(nparent);
			}

			void Draw()
			{
				settextstyle(&_font);

				text_x = width / 2 - textwidth(plane_text.c_str()) / 2;
				text_y = height / 2 - textheight(plane_text.c_str()) / 2;

				if (status == 0)
				{
					setlinecolor(normal_line_color);
					setfillcolor(normal_fill_color);

					settextcolor(normal_text_color);
				}
				if (status == 1)
				{
					setlinecolor(coverd_line_color);
					setfillcolor(coverd_fill_color);

					settextcolor(coverd_text_color);
				}
				if (status == 2)
				{
					setlinecolor(pushed_line_color);
					setfillcolor(pushed_fill_color);

					settextcolor(pushed_text_color);
				}

				if (shadow == false)
				{
					drawLinedRoundedRectangle(0, 0, width - 1, height - 1, radius);
				}
				else
				{
					drawRoundedRectangleShadow(0, 0, width, height, radius + 2);
					drawLinedRoundedRectangle(15, 15, width - 30, height - 30, radius);

					height -= 30;
					width -= 30;

					x += 15;
					y += 15;
				}

				setbkmode(TRANSPARENT);

				settextstyle(&_font);

				outtextxy(text_x, text_y, plane_text.c_str());

				if (plane_text.empty() == false)
				{
					putimage(&icon_image, 24, height / 2 - icon_image.getheight() / 2, icon_image.getwidth(),
						icon_image.getheight(), 255, object_content);
				}
				else
				{
					putimage(&icon_image, 0, 0, icon_image.getwidth(),
						icon_image.getheight(), 255, object_content);
				}

				if (shadow == true)
				{
					height += 30;
					width += 30;

					x -= 15;
					y -= 15;
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

				if (geomtery_type == 0)
				{
					CreateRectangleMask(width, height);
				}
				else if (geomtery_type == 1)
				{
					CreateRoundRectangleMask(width, height, radius);
				}
				else if (geomtery_type == 2)
				{
					CreateCircleMask(width, height);
				}
			}

		public:
			void SetBorder(int nradius)
			{
				radius = nradius;

				PDraw();
			}

			void SetPlaneText(std::wstring text)
			{
				plane_text = text;

				PDraw();
			}

			void SetIcon(IMAGE image)
			{
				icon_image = image;

				PDraw();
			}

			void SetTextHeight(int height)
			{
				_font.lfHeight = height;

				PDraw();
			}

			void SetNormalLineColor(COLORREF color)
			{
				normal_line_color = color;

				PDraw();
			}
			void SetNormalFillColor(COLORREF color)
			{
				normal_fill_color = color;

				PDraw();
			}
			void SetNormalTextColor(COLORREF color)
			{
				normal_text_color = color;

				PDraw();
			}

			void SetCoverdLineColor(COLORREF color)
			{
				coverd_line_color = color;

				PDraw();
			}
			void SetCoverdFillColor(COLORREF color)
			{
				coverd_fill_color = color;

				PDraw();
			}
			void SetCoverdTextColor(COLORREF color)
			{
				coverd_text_color = color;

				PDraw();
			}

			void SetPushedLineColor(COLORREF color)
			{
				pushed_line_color = color;

				PDraw();
			}
			void SetPushedFillColor(COLORREF color)
			{
				pushed_fill_color = color;

				PDraw();
			}
			void SetPushedTextColor(COLORREF color)
			{
				pushed_text_color = color;

				PDraw();
			}

		public:
			void MouseCoverd(ExMessage message)
			{
				if (status != 1)
				{
					status = 1;

					PDraw();

					if (mouseOnCover != NULL)
					{
						mouseOnCover();
					}
				}
			}

			void MouseLeft(ExMessage message)
			{
				status = 0;

				PDraw();

				if (mouseRleased != NULL)
				{
					mouseRleased();
				}
			}

			void LeftButtonOnClicked(ExMessage message)
			{
				status = 2;

				PDraw();

				if (mouseOnClicked != NULL)
				{
					mouseOnClicked();
				}
			}
			void RightButtonOnClicked(ExMessage message)
			{
				status = 2;

				PDraw();

				if (mouseOnRightClicked != NULL)
				{
					mouseOnRightClicked();
				}
			}
		};
	}
}
