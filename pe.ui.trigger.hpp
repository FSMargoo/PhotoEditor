/////////////////////////////////////////////////////
//    pe.ui.trigger.h:
//		@description : The trigger head in ui
//		@brith       : 2022/1/24
//
#pragma once

#include "pe.ui.gdiplus.hpp"
#include "pe.filters.blur.hpp"

#include <graphics.h>

namespace PDotE
{
	namespace UI
	{
		class Trigger
		{
		protected:
			IMAGE* mask_image;

			int x;
			int y;
			int width;
			int height;

			bool is_rectagnle = false;

		public:
			Trigger()
			{
				mask_image = nullptr;
				
				x = 0;
				y = 0;
				width  = 0;
				height = 0;
			}
			Trigger(IMAGE* mask, int sx, int sy)
			{
				mask_image = mask;

				x = sx;
				y = sy;

				width  = mask->getwidth();
				height = mask->getheight();
			}

			bool IsTrigger(ExMessage message)
			{
				if (message.x >= x && message.x <= x + width &&
					message.y >= y && message.y <= y + height)
				{
					if (is_rectagnle == true)
					{
						return true;
					}

					auto buffer = GetImageBuffer(mask_image);

					message.y -= y;
					message.x -= x;

					if (mask_image->getwidth() * message.y + message.x < mask_image->getwidth() * mask_image->getheight())
					{
						int r = GetRValue(buffer[mask_image->getwidth() * message.y + message.x]);
						int g = GetGValue(buffer[mask_image->getwidth() * message.y + message.x]);
						int b = GetBValue(buffer[mask_image->getwidth() * message.y + message.x]);

						if (r == 0 &&
							g == 0 &&
							b == 0)
						{
							return true;
						}

						return false;
					}
					else
					{
						return false;
					}
				}

				return false;
			}

		public:
			void CreateRoundRectangleMask(int width, int height, int radius)
			{
				if (width == 0 || height == 0)
				{
					return;
				}

				if (mask_image != nullptr)
				{
					delete mask_image;

					mask_image = nullptr;
				}

				if (radius <= 7)
				{
					is_rectagnle = true;

					return;
				}

				mask_image = new IMAGE(width, height);

				SetWorkingImage(mask_image);

				setfillcolor(BLACK);

				drawRoundedRectangle(0, 0, width, height, radius);

				SetWorkingImage();
			}
			void CreateRectangleMask(int width, int height)
			{
				if (width == 0 || height == 0)
				{
					return;
				}

				if (mask_image != nullptr)
				{
					delete mask_image;

					mask_image = nullptr;
				}

				is_rectagnle = true;
			}
			void CreateCircleMask(int width, int height)
			{
				if (width == 0 || height == 0)
				{
					return;
				}

				if (mask_image != nullptr)
				{
					delete mask_image;

					mask_image = nullptr;
				}

				mask_image = new IMAGE(width, height);

				SetWorkingImage(mask_image);

				setfillcolor(BLACK);

				drawCircle(0, 0, width, height);

				SetWorkingImage();
			}
			void CreateAlphaImageMask(IMAGE* image)
			{
				if (width == 0 || height == 0)
				{
					return;
				}

				if (mask_image != nullptr)
				{
					delete mask_image;

					mask_image = nullptr;
				}

				mask_image = new IMAGE(width, height);

				auto mask_buffer = GetImageBuffer(mask_image);

				auto buffer = GetImageBuffer(image);
				int  all    = image->getheight() * image->getwidth();

				for (int i = 0; i < all; ++i)
				{
					if (LOBYTE(buffer[i]) != 0)
					{
						mask_buffer[i] = BLACK;
					}
					else
					{
						mask_buffer[i] = WHITE;
					}
				}
			}

			inline int GetWidth()
			{
				return width;
			}
			inline int GetHeight()
			{
				return height;
			}
			inline int GetX()
			{
				return x;
			}
			inline int GetY()
			{
				return y;
			}
		};
	}
}
