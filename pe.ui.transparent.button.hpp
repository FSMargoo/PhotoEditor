#pragma once

#pragma once

#include "pe.ui.object.hpp"

#include <string>

namespace PDotE
{
	namespace UI
	{
		typedef class TransparentButton : public Object
		{
		public:
			std::function<void()> mouseOnClicked;
			std::function<void()> mouseRleased;
			std::function<void()> mouseOnCover;
			std::function<void()> mouseOnRightClicked;

		public:
			TransparentButton(int nwidth, int nheight, Object* nparent = nullptr)
			{
				width = nwidth;
				height = nheight;

				geomtery_type = RoundedRectangle;
				radius = 9;

				_font.lfHeight = 17;
				_font.lfWeight = FW_REGULAR;

				gettextstyle(&_font);

				CreateRoundRectangleMask(width, height, radius);
				SetParent(nparent);
			}

			void Draw()
			{
				
			}

			void Move(int nx, int ny)
			{
				x = nx;
				y = ny;

				PDraw();
			}

			void Resize(int nwidth, int nheight)
			{
				width = nwidth;
				height = nheight;

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
				if (status != 0)
				{
					status = 0;

					PDraw();

					if (mouseRleased != NULL)
					{
						mouseRleased();
					}
				}
			}

			void LeftButtonOnClicked(ExMessage message)
			{
				if (status != 2)
				{
					status = 2;

					PDraw();

					if (mouseOnClicked != NULL)
					{
						mouseOnClicked();
					}
				}
			}
			void RightButtonOnClicked(ExMessage message)
			{
				if (status != 2)
				{
					status = 2;

					PDraw();

					if (mouseOnRightClicked != NULL)
					{
						mouseOnRightClicked();
					}
				}
			}
		} RectanglePushed;
	}
}
