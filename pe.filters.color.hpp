/////////////////////////////////////////////////////
//    pe.filters.color.h:
//		@description : Photo Filters (Color model)
//		@brith       : 2022/1/24
//
#pragma once

#include <graphics.h>

namespace PDotE
{
	namespace Filters
	{
		// Red Gray Filter
		IMAGE* RGrayFilter(IMAGE* input_image)
		{
			auto buffer = GetImageBuffer(input_image);

			int  pixel_count = input_image->getwidth() * input_image->getheight();
			int  red_value;

			for (int i = 0; i < pixel_count; ++i)
			{
				red_value = GetRValue(buffer[i]);

				buffer[i] = RGB(red_value, red_value, red_value);
			}

			return input_image;
		}
		// Green Gray Filter
		IMAGE* GGrayFilter(IMAGE* input_image)
		{
			auto buffer = GetImageBuffer(input_image);

			int  pixel_count = input_image->getwidth() * input_image->getheight();
			int  green_value;

			for (int i = 0; i < pixel_count; ++i)
			{
				green_value = GetGValue(buffer[i]);

				buffer[i] = RGB(green_value, green_value, green_value);
			}

			return input_image;
		}
		// Blue Gray Filter
		IMAGE* BGrayFilter(IMAGE* input_image)
		{
			auto buffer = GetImageBuffer(input_image);

			int  pixel_count = input_image->getwidth() * input_image->getheight();
			int  blue_value;

			for (int i = 0; i < pixel_count; ++i)
			{
				blue_value = GetBValue(buffer[i]);

				buffer[i] = RGB(blue_value, blue_value, blue_value);
			}

			return input_image;
		}

		// Resever Color
		IMAGE* ResverColor(IMAGE* input_image)
		{
			auto width = input_image->getwidth();
			auto height = input_image->getheight();

			auto pixel_number = width * height;

			auto buffer = GetImageBuffer(input_image);

			for (int i = 0; i < pixel_number; ++i)
			{
				buffer[i] = BGR(buffer[i]);
			}

			return input_image;
		}

		// Invert Color
		IMAGE* InvertColor(IMAGE* input_image)
		{
			auto width = input_image->getwidth();
			auto height = input_image->getheight();

			auto pixel_number = width * height;

			auto buffer = GetImageBuffer(input_image);

			for (int i = 0; i < pixel_number; ++i)
			{
				buffer[i] = RGB(
					255 - GetRValue(buffer[i]),
					255 - GetGValue(buffer[i]),
					255 - GetBValue(buffer[i])
				);
			}

			return input_image;
		}

		// Thresholding Image
		IMAGE* ThresholdingColor(IMAGE* input_image)
		{
			auto  sum = input_image->getheight() * input_image->getwidth();
			long long sum_value = 0;

			auto  buffer = GetImageBuffer(input_image);

			for (int i = 0; i < sum; ++i)
			{
				sum_value += GetRValue(buffer[i]);
			}

			sum_value /= sum;

			for (int i = 0; i < sum; ++i)
			{
				if (GetRValue(buffer[i]) < sum_value)
				{
					buffer[i] = BLACK;
				}
				else
				{
					buffer[i] = WHITE;
				}
			}

			return input_image;
		}
	}
}
