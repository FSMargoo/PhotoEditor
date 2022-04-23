#pragma once

#include <graphics.h>
#include <cmath>

namespace PDotE
{
	namespace Effect
	{
		IMAGE* ReliefEffect(IMAGE* input_image)
		{
			int  width  = input_image->getwidth();
			int  height = input_image->getheight();
			auto buffer = GetImageBuffer(input_image);

			int rb1;
			int rb2;

			int gb1;
			int gb2;

			int bb1;
			int bb2;

			for (int i = 0; i < width; ++i)
			{
				for (int j = 0; j < height; ++j)
				{
					--i;

					if (i == -1 || i == 0)
					{
						rb1 = GetRValue(buffer[j * width + (width - 1)]);
						gb1 = GetGValue(buffer[j * width + (width - 1)]);
						bb1 = GetBValue(buffer[j * width + (width - 1)]);
					}
					else
					{
						rb2 = GetRValue(buffer[j * width + (i - 1)]);
						gb2 = GetGValue(buffer[j * width + (i - 1)]);
						bb2 = GetBValue(buffer[j * width + (i - 1)]);
					}

					++i;

					rb2 = GetRValue(buffer[j * width + i]);
					gb2 = GetGValue(buffer[j * width + i]);
					bb2 = GetBValue(buffer[j * width + i]);

					buffer[j * width + i] = RGB(rb1 - rb2 + 128, gb1 - gb2 + 128,
													bb1 - bb2 + 128);
				}
			}

			return input_image;
		}
		IMAGE* CartoonEffect(IMAGE* input_image)
		{
			int  sum    = input_image->getwidth() * input_image->getheight();
			auto buffer = GetImageBuffer(input_image);

			int r;
			int g;
			int b;

			int nr;
			int ng;
			int nb;

			for (int i = 0; i < sum; ++i)
			{
				r = GetRValue(buffer[i]);
				g = GetGValue(buffer[i]);
				b = GetBValue(buffer[i]);

				nr = abs(b - g + b + r) * g / 256;
				ng = abs(b - g + b + r) * r / 256;
				nb = abs(g - b + g + r) * r / 256;

				if (nr > 255)
				{
					nr = 255;
				}
				if (ng > 255)
				{
					ng = 255;
				}
				if (nb > 255)
				{
					nb = 255;
				}

				buffer[i] = BGR(RGB(nr, ng, nb));
			}

			return input_image;
		}
		IMAGE* ColorEffect(IMAGE* input_image)
		{
			int  sum = input_image->getwidth() * input_image->getheight();
			auto buffer = GetImageBuffer(input_image);

			int r;
			int g;
			int b;

			for (int i = 0; i < sum; ++i)
			{
				r = GetRValue(buffer[i]);
				g = GetGValue(buffer[i]);
				b = GetBValue(buffer[i]);

				b = (max(max(r, g), b) + min(min(r, g), b)) / 2;

				buffer[i] = RGB(r, g, b);
			}

			return input_image;
		}
		IMAGE* OldStewfEffect(IMAGE* input_image)
		{
			int  sum = input_image->getwidth() * input_image->getheight();
			auto buffer = GetImageBuffer(input_image);

			int r;
			int g;
			int b;

			for (int i = 0; i < sum; ++i)
			{
				r = GetRValue(buffer[i]);
				g = GetGValue(buffer[i]);
				b = GetBValue(buffer[i]);

				r = (272 * r + 534 * g + 131 * b) / 1000;
				g = (349 * r + 686 * g + 168 * b) / 1000;
				b = (393 * r + 769 * g + 189 * b) / 1000;

				if (r > 255)
				{
					r = 255;
				}
				if (g > 255)
				{
					g = 255;
				}
				if (b > 255)
				{
					b = 255;
				}

				buffer[i] = RGB(r, g, b);
			}

			return input_image;
		}
	}
}