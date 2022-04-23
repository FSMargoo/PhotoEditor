////////////////////////////////////////////////////
//    pe.ui.gdiplus.h:
//		@description : The gdiplus init and free
//		@brith       : 2022/1/24
//
#pragma once

#include <windows.h>
#include <gdiplus.h>
#include <graphics.h>

#pragma comment(lib, "gdiplus.lib")
#pragma comment(lib, "MSIMG32.LIB")

namespace PDotE
{
#define ImageEmpty(IObject) (IObject.getwidth() == 0 && IObject.height() == 0)
#define ImageEmptyPtr(IObject) (IObject->getwidth() == 0 && IObject->getheight() == 0)
	namespace UI
	{
		class GdiplusAutoInitAndFree
		{
		private:
			ULONG_PTR token;

		public:
			GdiplusAutoInitAndFree()
			{Gdiplus::GdiplusStartup(&token, NULL, NULL);
			}
			~GdiplusAutoInitAndFree()
			{
				EndBatchDraw();
				Gdiplus::GdiplusShutdown(token);
			}
		};

		GdiplusAutoInitAndFree _GdiplusAutoInitAndFreeObject;

		void putimage(IMAGE* imageBeput, int x, int y, int width = 0, int height = 0,
			int transparency = 255, IMAGE* target = nullptr)
		{
			if (target == nullptr)
			{
				target = GetWorkingImage();
			}

			HDC targertHDC = GetImageHDC(target);
			HDC imageHDC = GetImageHDC(imageBeput);

			if (width == 0)
			{
				int width = imageBeput->getwidth();
			}
			if (height == 0)
			{
				int height = imageBeput->getheight();
			}

			BLENDFUNCTION blendFunction = { AC_SRC_OVER, 0, static_cast<BYTE>(transparency), AC_SRC_ALPHA };
			AlphaBlend(targertHDC, x, y, width, height,
				imageHDC, 0, 0, width, height,
				blendFunction);
		}

		// High Quanlity Graphics Function 
		void drawRoundedRectangle(int x1, int y1, int width, int height, int radius)
		{
			Gdiplus::Graphics	graphics(GetImageHDC(GetWorkingImage()));
			Gdiplus::SolidBrush	brush(Gdiplus::Color(GetRValue(getfillcolor()), GetGValue(getfillcolor()), GetBValue(getfillcolor())));
			Gdiplus::Pen    	line_pen(Gdiplus::Color(GetRValue(getfillcolor()), GetGValue(getfillcolor()), GetBValue(getfillcolor())));

			graphics.SetSmoothingMode(Gdiplus::SmoothingMode::
				SmoothingModeHighQuality);

			radius *= 2;

			graphics.FillEllipse(&brush, Gdiplus::Rect{ x1, y1, radius, radius });
			graphics.FillEllipse(&brush, Gdiplus::Rect{ x1, y1 + height - radius, radius, radius });
			graphics.FillEllipse(&brush, Gdiplus::Rect{ x1 + width - radius, y1 + height - radius, radius, radius });
			graphics.FillEllipse(&brush, Gdiplus::Rect{ x1 + width - radius, y1, radius, radius });

			radius /= 2;

			graphics.DrawLine(&line_pen, x1 + radius, y1, x1 + width - radius, y1);
			graphics.DrawLine(&line_pen, x1 + radius, y1 + height, x1 + width - radius,
				y1 + height);
			graphics.DrawLine(&line_pen, x1, y1 + radius, x1, y1 + height - radius);
			graphics.DrawLine(&line_pen, x1 + width, y1 + radius, x1 + width, y1 + height - radius);

			graphics.FillRectangle(&brush, Gdiplus::Rect{ x1 + radius, y1, width - radius * 2, height });
			graphics.FillRectangle(&brush, Gdiplus::Rect{ x1, y1 + radius, width, height - radius * 2 });
		}
		void drawLinedRoundedRectangle(int x1, int y1, int width, int height, int radius, int pixel_line = 1)
		{
			auto fillcolor = getfillcolor();

			setfillcolor(getlinecolor());

			if (radius <= 5)
			{
				drawRoundedRectangle(x1, y1, width, height, radius - 1);

				setfillcolor(fillcolor);

				drawRoundedRectangle(x1 + pixel_line, y1 + pixel_line, width - pixel_line * 2, height - pixel_line * 2, radius - 2);
			}
			else
			{
				drawRoundedRectangle(x1, y1, width, height, radius);

				setfillcolor(fillcolor);

				drawRoundedRectangle(x1 + pixel_line, y1 + pixel_line, width - pixel_line * 2, height - pixel_line * 2 , radius - 5);
			}
		}
		void drawCircle(int x, int y, int width, int height)
		{
			Gdiplus::Graphics	graphics(GetImageHDC(GetWorkingImage()));
			Gdiplus::SolidBrush	brush(Gdiplus::Color(GetRValue(getfillcolor()), GetGValue(getfillcolor()), GetBValue(getfillcolor())));
			Gdiplus::Pen    	line_pen(Gdiplus::Color(GetRValue(getfillcolor()), GetGValue(getfillcolor()), GetBValue(getfillcolor())));

			graphics.SetSmoothingMode(Gdiplus::SmoothingMode::
				SmoothingModeHighQuality);

			graphics.FillEllipse(&brush, Gdiplus::Rect{ x, y, width, height });
		}
		void drawSoildCircle(int x, int y, int width, int height)
		{
			Gdiplus::Graphics	graphics(GetImageHDC(GetWorkingImage()));
			Gdiplus::SolidBrush	brush(Gdiplus::Color(GetRValue(getlinecolor()), GetGValue(getlinecolor()), GetBValue(getlinecolor())));
			Gdiplus::Pen    	line_pen(Gdiplus::Color(GetRValue(getlinecolor()), GetGValue(getlinecolor()), GetBValue(getlinecolor())));

			graphics.SetSmoothingMode(Gdiplus::SmoothingMode::
				SmoothingModeHighQuality);

			graphics.DrawEllipse(&line_pen, Gdiplus::Rect{ x, y, width, height });
			graphics.DrawEllipse(&line_pen, Gdiplus::Rect{ x + 1, y + 1, width - 1, height - 1 });
		}
		void drawRoundedRectangleShadow(int x1, int y1, int width, int height, int radius)
		{
			using namespace Gdiplus;

			Gdiplus::Graphics	graphics(GetImageHDC(GetWorkingImage()));
			Gdiplus::GraphicsPath	path;

			Gdiplus::Color colors[3] = { Gdiplus::Color::Transparent,

								Gdiplus::Color::MakeARGB(70, GetRValue(Gdiplus::Color::DimGray),
									GetGValue(Gdiplus::Color::DimGray), GetBValue(Gdiplus::Color::DimGray)),

								Gdiplus::Color::MakeARGB(180, GetRValue(Gdiplus::Color::DimGray),
									GetGValue(Gdiplus::Color::DimGray), GetBValue(Gdiplus::Color::DimGray)) };

			REAL position[3] = { 0.0f, 0.8f, 1.0f };

			if (width >= 400)
			{
				position[1] = 0.6f;
			}
			if (width >= 800)
			{
				position[1] = 0.2f;
			}

			graphics.SetSmoothingMode(Gdiplus::SmoothingMode::
				SmoothingModeHighQuality);

			path.AddLine(x1 + radius, y1, x1 + width - (radius * 2), y1);
			path.AddArc(x1 + width - (radius * 2), y1, radius * 2, radius * 2, 270, 90);
			path.AddLine(x1 + width, y1 + radius, x1 + width, y1 + height - (radius * 2));
			path.AddArc(x1 + width - (radius * 2), y1 + height - (radius * 2), radius * 2, radius * 2, 0, 90);
			path.AddLine(x1 + width - (radius * 2), y1 + height, x1 + radius, y1 + height);
			path.AddArc(x1, y1 + height - (radius * 2), radius * 2, radius * 2, 90, 90);
			path.AddLine(x1, y1 + height - (radius * 2), x1, y1 + radius);
			path.AddArc(x1, y1, radius * 2, radius * 2, 180, 90);

			Gdiplus::PathGradientBrush brush(&path);

			brush.SetWrapMode(WrapMode::WrapModeClamp);
			brush.SetInterpolationColors(colors, position, 3);

			graphics.FillPath(&brush, &path);
		}
		void drawRectangleShadow(int x1, int y1, int width, int height)
		{
			using namespace Gdiplus;

			Gdiplus::Graphics	graphics(GetImageHDC(GetWorkingImage()));
			Gdiplus::GraphicsPath	path;

			Gdiplus::Color colors[3] = { Gdiplus::Color::Transparent,

								Gdiplus::Color::MakeARGB(70, GetRValue(Gdiplus::Color::DimGray),
									GetGValue(Gdiplus::Color::DimGray), GetBValue(Gdiplus::Color::DimGray)),

								Gdiplus::Color::MakeARGB(180, GetRValue(Gdiplus::Color::DimGray),
									GetGValue(Gdiplus::Color::DimGray), GetBValue(Gdiplus::Color::DimGray)) };

			REAL position[3] = { 0.0f, 0.8f, 1.0f };

			if (width >= 400)
			{
				position[1] = 0.6f;
			}
			else if (width >= 800)
			{
				position[1] = 0.2f;
			}
			else
			{
				position[1] = .1f;
				colors[1] = Gdiplus::Color::MakeARGB(40, GetRValue(Gdiplus::Color::DimGray),
					GetGValue(Gdiplus::Color::DimGray), GetBValue(Gdiplus::Color::DimGray));
			}

			graphics.SetSmoothingMode(Gdiplus::SmoothingMode::
				SmoothingModeHighQuality);

			path.AddRectangle(Rect{ x1, y1, width, height });

			Gdiplus::PathGradientBrush brush(&path);

			brush.SetWrapMode(WrapMode::WrapModeClamp);
			brush.SetInterpolationColors(colors, position, 3);

			graphics.FillPath(&brush, &path);
		}

		IMAGE* SetAlpha(IMAGE* image)
		{
			auto          buffer = GetImageBuffer(image);

			unsigned long total  = image->getwidth() * image->getheight();

			for (unsigned long i = 0; i < total; ++i)
			{
				buffer[i] = 255 << 24 | BGR(RGB(GetRValue(buffer[i]), GetGValue(buffer[i]), GetBValue(buffer[i])));
			}

			return image;
		}

		IMAGE* resetImage(IMAGE* source_image, int width, int height)
		{
			IMAGE* result = new IMAGE(width, height);

			HDC result_hdc = GetImageHDC(result);
			HDC source_hdc = GetImageHDC(source_image);

			SetStretchBltMode(result_hdc, HALFTONE);
			SetStretchBltMode(source_hdc, HALFTONE);
			StretchBlt(result_hdc, 0, 0, width, height, source_hdc, 0, 0, source_image->getwidth(), source_image->getheight(), SRCCOPY);

			return result;
		}
	}
}
