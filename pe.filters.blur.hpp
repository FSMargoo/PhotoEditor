/////////////////////////////////////////////////////
//    pe.filters.blur.h:
//		@description : Photo Filters (Blur model)
//		@brith       : 2022/1/24
//
#pragma once
#pragma warning(disable : 4244)

#include <graphics.h>
#include <vector>

namespace PDotE
{
	namespace Filters
	{
		// Fast Gass Blur :
		//		Three times Boxex Blur
		namespace GassBlurFilters
		{
			std::vector<int> BoxForGass(double sigma, int box_number)
			{
				double wIdeal = sqrt((12 * sigma * sigma / box_number) + 1);
				double wl = floor(wIdeal);

				if (int(wl) % 2 == 0)
				{
					--wl;
				}

				double wu = wl + 2;

				double mIdeal = (12 * sigma * sigma - box_number * wl * wl - 4 * box_number
					* wl - 3 * box_number) / (-4 * wl - 4);
				int    m = round(mIdeal);

				std::vector<int> sizes;

				for (int i = 0; i < box_number; ++i)
				{
					sizes.push_back(i < m ? wl : wu);
				}

				return sizes;
			}

			void GassBlurHeight(IMAGE* source_channel_image, IMAGE* target_channel_image,
				int width, int height,
				double radius)
			{
				auto source_channel = GetImageBuffer(source_channel_image);
				auto target_channel = GetImageBuffer(target_channel_image);

				double iArray = 1 / (radius + radius + 1);

				int ti;
				int li;
				int ri;

				int rfv;
				int rlv;

				int gfv;
				int glv;

				int bfv;
				int blv;

				int rval;
				int gval;
				int bval;

				for (int i = 0; i < height; ++i)
				{
					ti = i * width;
					li = ti;
					ri = ti + radius;

					rfv = GetRValue(source_channel[ti]);
					rlv = GetRValue(source_channel[ti + width - 1]);

					gfv = GetGValue(source_channel[ti]);
					glv = GetGValue(source_channel[ti + width - 1]);

					bfv = GetBValue(source_channel[ti]);
					blv = GetBValue(source_channel[ti + width - 1]);

					rval = (radius + 1) * rfv;
					gval = (radius + 1) * gfv;
					bval = (radius + 1) * bfv;

					for (int j = 0; j < radius; ++j)
					{
						rval += GetRValue(source_channel[ti + j]);
						gval += GetGValue(source_channel[ti + j]);
						bval += GetBValue(source_channel[ti + j]);
					}

					for (int j = 0; j <= radius; ++j)
					{
						rval += GetRValue(source_channel[ri]) - rfv;
						gval += GetGValue(source_channel[ri]) - gfv;
						bval += GetBValue(source_channel[ri]) - bfv;

						target_channel[ti] = RGB(int(round(rval * iArray)), int(round(gval * iArray)), int(round(bval * iArray)));

						++ri;
						++ti;
					}

					for (int j = radius + 1; j < width - radius; ++j)
					{
						rval += GetRValue(source_channel[ri]) - GetRValue(source_channel[li]);
						gval += GetGValue(source_channel[ri]) - GetGValue(source_channel[li]);
						bval += GetBValue(source_channel[ri]) - GetBValue(source_channel[li]);

						target_channel[ti] = RGB(int(round(rval * iArray)), int(round(gval * iArray)), int(round(bval * iArray)));

						++ri;
						++li;
						++ti;
					}

					for (int j = width - radius; j < width; ++j)
					{
						rval += rlv - GetRValue(source_channel[li]);
						gval += glv - GetGValue(source_channel[li]);
						bval += blv - GetBValue(source_channel[li]);

						target_channel[ti] = RGB(int(round(rval * iArray)), int(round(gval * iArray)), int(round(bval * iArray)));

						++li;
						++ti;
					}
				}
			}
			void GassBlurWidth(IMAGE* source_channel_image, IMAGE* target_channel_image,
				int width, int height,
				double radius)
			{
				auto source_channel = GetImageBuffer(source_channel_image);
				auto target_channel = GetImageBuffer(target_channel_image);

				double iArray = 1 / (radius + radius + 1);

				int ti;
				int li;
				int ri;

				int rfv;
				int rlv;

				int gfv;
				int glv;

				int bfv;
				int blv;

				int rval;
				int gval;
				int bval;

				for (int i = 0; i < width; ++i)
				{
					ti = i;
					li = ti;
					ri = ti + radius * width;

					rfv = GetRValue(source_channel[ti]);
					rlv = GetRValue(source_channel[ti + width * (height - 1)]);

					gfv = GetGValue(source_channel[ti]);
					glv = GetGValue(source_channel[ti + width * (height - 1)]);

					bfv = GetBValue(source_channel[ti]);
					blv = GetBValue(source_channel[ti + width * (height - 1)]);

					rval = (radius + 1) * rfv;
					gval = (radius + 1) * gfv;
					bval = (radius + 1) * bfv;

					for (int j = 0; j < radius; ++j)
					{
						rval += GetRValue(source_channel[ti + j * width]);
						gval += GetGValue(source_channel[ti + j * width]);
						bval += GetBValue(source_channel[ti + j * width]);
					}

					for (int j = 0; j <= radius; ++j)
					{
						rval += GetRValue(source_channel[ri]) - rfv;
						gval += GetGValue(source_channel[ri]) - gfv;
						bval += GetBValue(source_channel[ri]) - bfv;

						target_channel[ti] = RGB(int(round(rval * iArray)), int(round(gval * iArray)), int(round(bval * iArray)));

						ri += width;
						ti += width;
					}

					for (int j = radius + 1; j < height - radius; ++j)
					{
						rval += GetRValue(source_channel[ri]) - GetRValue(source_channel[li]);
						gval += GetGValue(source_channel[ri]) - GetGValue(source_channel[li]);
						bval += GetBValue(source_channel[ri]) - GetBValue(source_channel[li]);

						target_channel[ti] = RGB(int(round(rval * iArray)), int(round(gval * iArray)), int(round(bval * iArray)));

						li += width;
						ri += width;
						ti += width;
					}

					for (int j = height - radius; j < height; ++j)
					{
						rval += rlv - GetRValue(source_channel[li]);
						gval += glv - GetGValue(source_channel[li]);
						bval += blv - GetBValue(source_channel[li]);

						target_channel[ti] = RGB(int(round(rval * iArray)), int(round(gval * iArray)), int(round(bval * iArray)));

						li += width;
						ti += width;
					}
				}
			}
			void GassBlur(IMAGE* source_channel_image, IMAGE* target_channel_image,
				int width, int height,
				double radius)
			{
				int N = width * height;

				auto buffer = GetImageBuffer(source_channel_image);
				auto target_buffer = GetImageBuffer(target_channel_image);

				for (int i = 0; i < N; ++i)
				{
					target_buffer[i] = buffer[i];
				}

				GassBlurHeight(target_channel_image, source_channel_image, width, height, radius);
				GassBlurWidth(source_channel_image, target_channel_image, width, height, radius);
			}


		}
		// Fast Gass Blur with O(n)
		IMAGE* GassBlurFilter(IMAGE* input_image, int blur_radius)
		{
			IMAGE* output_image = new IMAGE(input_image->getwidth(), input_image->getheight());

			using namespace GassBlurFilters;

			auto boxes = BoxForGass(blur_radius, 3);

			GassBlur(input_image, output_image, input_image->getwidth(), input_image->getheight(),
				(boxes[0] - 1) / 2);
			GassBlur(output_image, input_image, input_image->getwidth(), input_image->getheight(),
				(boxes[1] - 1) / 2);
			GassBlur(input_image, output_image, input_image->getwidth(), input_image->getheight(),
				(boxes[2] - 1) / 2);

			return output_image;
		}

		// Masco Blur Image
		IMAGE* MascoBlurFilter(IMAGE* input_image, int masco_radius)
		{
			unsigned long long red_average	  = 0;
			unsigned long long green_average  = 0;
			unsigned long long blue_average   = 0;

			auto width  = input_image->getwidth();
			auto height = input_image->getheight();

			auto buffer = GetImageBuffer(input_image);

			for (int i = 0; i < height; i += masco_radius)
			{
				for (int j = 0; j < width; j += masco_radius)
				{
					int ix = min(height - 1, i);
					int iy = min(width - 1, j);

					red_average = GetRValue(buffer[ix * width + iy]);
					green_average = GetGValue(buffer[ix * width + iy]);
					blue_average = GetBValue(buffer[ix * width + iy]);

					for (int iw = i; iw < i + masco_radius; ++iw)
					{
						for (int ih = j; ih < j + masco_radius; ++ih)
						{
							ix = min(height - 1, iw);
							iy = min(width - 1, ih);

							buffer[ix * width + iy] = (RGB(red_average, green_average, blue_average));
						}
					}
				}
			}

			return input_image;
		}
	}
}