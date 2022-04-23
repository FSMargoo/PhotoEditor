/////////////////////////////////////////////////////
//    pe.ui.widget.hpp":
//		@description : Widget and nothing
//		@brith       : 2022/1/24
//
#pragma once

#include "pe.ui.object.hpp"

#include <ctime>

namespace PDotE
{
	namespace UI
	{
		class Widget : public Object
		{
		private:
			COLORREF bk_color = WHITE;
		public:
			Widget(int nwidth, int nheight)
			{
				initgraph(nwidth, nheight);

				BeginBatchDraw();

				width  = nwidth;
				height = nheight;

				CreateRectangleMask(width, height);

				PDraw();
			}

			void Draw()
			{
				setbkcolor(bk_color);

				cleardevice();
			}

		public:
			void SetWindowTitle(const wchar_t* text)
			{
				SetWindowText(GetHWnd(), text);
			}

			HWND GetHandle()
			{
				return GetHWnd();
			}
		public:
			void SetBackgroundColor(COLORREF color)
			{
				bk_color = color;

				PDraw();
			}

			void ClearAllChild()
			{
				child_object.clear();

				PDraw();
			}

		public:
			int exec()
			{
				ExMessage message;

				while (true)
				{
					while (peekmessage(&message))
					{
						ProcessMessage(message);
					}

					Sleep(20);
				}

				return 0;
			}
		};
	}
}