#pragma once

#include "pe.ui.object.hpp"

namespace PDotE
{
	namespace UI
	{
		class MaskLabel : public Object
		{
		private:
			int      transparency = 0;

			COLORREF _line_color       = BLACK;
			COLORREF _background_color = BLACK;

		public:
			MaskLabel(int nwidth, int nheight, int ntransparency = 255, Object* nparent = nullptr)
			{
				width = nwidth;
				height = nheight;

				transparency = ntransparency;

				parent = nparent;

				SetParent(parent);

				CreateRectangleMask(width, height);
			}

			void Draw()
			{
				auto working_image = GetWorkingImage();
				auto temp_image	   = new IMAGE(width, height);

				SetWorkingImage(temp_image);

				setfillcolor(_background_color);
				setlinecolor(_line_color);

				fillrectangle(0, 0, width, height);

				SetWorkingImage(working_image);

				temp_image = SetAlpha(temp_image);

				putimage(temp_image, 0, 0, width, height, transparency);

				delete temp_image;

				temp_image = nullptr;
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

				CreateRectangleMask(width, height);
			}

			void SetTransparency(int ntransparency)
			{
				transparency = ntransparency;

				PDraw();
			}

		public:
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