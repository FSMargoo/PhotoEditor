#pragma once

#include "pe.ui.menu.hpp"

#include <ctime>
#include <comutil.h>

#pragma comment(lib, "comsuppwd.lib")

namespace PDotE
{
	namespace UI
	{
		class EditorTimer
		{
		private:
			time_t timer;

		public:
			EditorTimer()
			{
				timer = 0;
			}

			void start()
			{
				timer = clock();
			}
			unsigned long note()
			{
				return (clock() - timer) / 1000;
			}
		};

		class LineEdit : public Object
		{
		public:
			void CheckMouseOut(ExMessage message)
			{
				if (is_invisble == true)
				{
					return;
				}

				if (IsTrigger(message) == false)
				{
					if (used_to_focus == true)
					{
						used_to_focus = false;

						MouseLeft(message);
					}

					if (message.message == WM_LBUTTONDOWN)
					{
						status = 0;

						PDraw();

						left_clicked_menu.Hide();
					}
				}
			}

		private:
			Menu left_clicked_menu = Menu(120);
			
			int  cursor_position   = -1;

			int  select_start = -1;
			int  select_end   = -1;

			bool show_cursor = false;
			
			bool on_select   = false;

			std::wstring plane_text;

			void CopyFunction()
			{
				left_clicked_menu.Hide();
			}
			void PastedFunction()
			{
				if (OpenClipboard(NULL))
				{
					if (IsClipboardFormatAvailable(CF_TEXT))
					{
						HANDLE clipboard_handle;
						char* buffer;
						_bstr_t wbuffer;

						clipboard_handle = GetClipboardData(CF_TEXT);
						buffer = (char*)GlobalLock(clipboard_handle);

						wbuffer = (char*)buffer;

						GlobalUnlock(clipboard_handle);

						CloseClipboard();

						if (buffer != nullptr)
						{
							if (cursor_position != -1)
							{
								plane_text.insert(cursor_position, (wchar_t*)wbuffer);
							}
							else
							{
								plane_text.insert(0, (wchar_t*)wbuffer);
							}
						}
					}
				}

				left_clicked_menu.Hide();
			}
			void SelectedAllFunction()
			{
				left_clicked_menu.Hide();
			}

		private:
			bool password_type = false;

			bool only_number = false;

		private:
			void Input()
			{
				ExMessage   message;
				EditorTimer timer;

				timer.start();

				while (true)
				{
					while (peekmessage(&message))
					{
						if (left_clicked_menu.IsVisble() == false)
						{
							if (left_clicked_menu.ProcessMessage(message) == true)
							{
								continue;
							}
						}

						if (IsTrigger(message) == false &&
							(message.message == WM_LBUTTONDOWN))
						{
							status = 0;

							MouseLeft(message);

							PDraw();

							left_clicked_menu.Hide();

							show_cursor = false;

							return;
						}

						if (IsTrigger(message) == true &&
							message.message == WM_RBUTTONDOWN)
						{
							RightButtonOnClicked(message);
						}
						if (IsTrigger(message) == true &&
							message.message == WM_LBUTTONDOWN)
						{
							left_clicked_menu.Hide();

							FlushBatchDraw();
						}

						if (message.message == WM_CHAR)
						{
							if (message.ch == L'\b')
							{
								if (plane_text.empty() == false &&
									cursor_position != -1)
								{
									plane_text.erase(plane_text.begin() + cursor_position);

									--cursor_position;
								}

								if (CharOnPut != NULL)
								{
									if (CharOnPut(message.ch) == false)
									{
										continue;
									}
								}
							}
							else if (message.ch == L'\r')
							{
								status = 0;

								show_cursor = false;

								PDraw();

								FlushBatchDraw();

								return;
							}
							else
							{
								if (only_number == true &&
									(message.ch < L'0' || message.ch > '9'))
								{
									continue;
								}

								if (plane_text.empty() == false &&
									cursor_position != -1)
								{
									plane_text.insert(plane_text.begin() + cursor_position + 1, message.ch);
								}
								else if (plane_text.empty() == true)
								{
									plane_text.push_back(message.ch);
								}
								else if (cursor_position == -1)
								{
									plane_text.insert(plane_text.begin(), message.ch);
								}

								if (CharOnPut != NULL)
								{
									if (CharOnPut(message.ch) == false)
									{
										continue;
									}
								}

								++cursor_position;
							}
						}
						if (message.message == WM_KEYDOWN)
						{
							if (GetAsyncKeyState(VK_SHIFT) & 0x8000)
							{/*
								if (message.vkcode == VK_LEFT)
								{
									select_end = cursor_position;

									while (peekmessage(&message))
									{
										if (message.message == WM_KEYDOWN && message.shift == true)
										{
											if (cursor_position - 1 != -1)
											{
												--cursor_position;
											}
										}

										PDraw();

										FlushBatchDraw();
									}

									select_start = cursor_position;
								}
								if (message.vkcode == VK_RIGHT)
								{
									select_start = cursor_position;

									while (peekmessage(&message))
									{
										if (message.message == WM_KEYDOWN && message.shift == true)
										{
											if (cursor_position + 1 != plane_text.size())
											{
												++cursor_position;
											}
										}

										PDraw();

										FlushBatchDraw();
									}

									select_end = cursor_position;
								}
								*/
							}
							else
							{
								if (message.vkcode == VK_LEFT)
								{
									if (cursor_position != -1)
									{
										--cursor_position;
									}
								}
								if (message.vkcode == VK_RIGHT)
								{
									if (cursor_position + 1 != plane_text.size())
									{
										++cursor_position;
									}
								}
								if (message.vkcode == VK_DELETE)
								{
									if (plane_text.empty() == false &&
										cursor_position + 1 != plane_text.size())
									{
										if (cursor_position != -1)
										{
											plane_text.erase(plane_text.begin() + cursor_position + 1);
										}
										else
										{
											plane_text = plane_text.substr(1, plane_text.size() - 1);
										}
									}
								}
								if (message.vkcode == VK_HOME)
								{
									cursor_position = -1;
								}
								if (message.vkcode == VK_END)
								{
									cursor_position = static_cast<int>(plane_text.size() - 1);
								}
							}
						}
					}

					FlushBatchDraw();

					if (timer.note() >= 1)
					{
						timer.start();
						
						show_cursor = (show_cursor == false) ? true : false;

						PDraw();

						FlushBatchDraw();
					}

					Sleep(80);
				}
			}

		public:
			std::function<bool(wchar_t)> CharOnPut;

		public:
			LineEdit(int nwidth, int nheight, Object* nparent = nullptr)
			{
				_font.lfHeight = 0;

				width  = nwidth;
				height = nheight;

				SetParent(nparent);

				CreateRoundRectangleMask(width, height, 5);

				left_clicked_menu.AppendChoosen({ L"¸´ÖÆ", nullptr, nullptr, std::bind(&LineEdit::CopyFunction, this) });
				left_clicked_menu.AppendChoosen({ L"Õ³Ìù", nullptr, nullptr, std::bind(&LineEdit::PastedFunction, this) });

				left_clicked_menu.SetParent(parent);

				left_clicked_menu.Hide();
				left_clicked_menu.LockStatus(true);
			}

			void Draw()
			{
				if (status == 0 ||
					status == 1)
				{
					setfillcolor(WHITE);
					setlinecolor(RGB(234, 234, 234));
					
					drawLinedRoundedRectangle(0, 0, width - 1, height - 1, 5);
				}
				if (status == 2 ||
					status == 3)
				{
					setfillcolor(WHITE);
					setlinecolor(RGB(15, 174, 243));

					drawLinedRoundedRectangle(0, 0, width - 1, height - 1, 5);
				}

				if (_font.lfHeight == 0)
				{
					_font.lfHeight = height - 15;
				}

				settextstyle(&_font);

				int text_y = height / 2 - textheight(plane_text.c_str()) / 2;
				int text_x = 5;
				
				for (int i = 0; i < plane_text.size(); ++i)
				{
					if (i >= select_start &&
						i <= select_end)
					{
						setbkmode(OPAQUE);

						setbkcolor(RGB(0, 120, 215));
						settextcolor(WHITE);
					}
					else
					{
						setbkmode(TRANSPARENT);

						settextcolor(RGB(159, 159, 159));
					}

					if (password_type == false)
					{
						outtextxy(5 + textwidth(plane_text.substr(0, i).c_str()), text_y, plane_text[i]);

						text_x += textwidth(plane_text[i]);
					}
					else
					{
						outtextxy(5 + textwidth(L'*') * i, text_y, L'*');

						text_x += textwidth(L'*');
					}
					
					if (i == cursor_position &&
						show_cursor == true)
					{
						line(text_x, 4, text_x, _font.lfHeight);

						text_x += 4;
					}
				}

				if (cursor_position == -1 &&
					show_cursor == true)
				{
					line(5, 4, 5, _font.lfHeight);
				}
			}

		public:
			void MouseCoverd(ExMessage message)
			{
				HCURSOR cousor = LoadCursor(NULL, IDC_IBEAM);
				SetClassLongPtr(GetHWnd(), GCLP_HCURSOR, (LONG_PTR)cousor);

				PDraw();
			}

			void MouseLeft(ExMessage message)
			{
				HCURSOR cousor = LoadCursor(NULL, IDC_ARROW);			
				SetClassLongPtr(GetHWnd(), GCLP_HCURSOR, (LONG_PTR)cousor);

				PDraw();
			}

			void LeftButtonOnClicked(ExMessage message)
			{
				status = 2;

				PDraw();

				FlushBatchDraw();

				Input();
			}
			void RightButtonOnClicked(ExMessage message)
			{
				status = 3;

				PDraw();

				left_clicked_menu.SetParent(parent);

				left_clicked_menu.Hide();

				if (Menu::CanMenuHoldOn(message.x, message.y, 120, parent->GetWidth(), parent->GetHeight(), 3) == true)
				{
					//left_clicked_menu.Move(message.x, message.y);
					//left_clicked_menu.Show();
				}
			}

		public:
			void SetPlaneText(std::wstring text)
			{
				plane_text = text;

				cursor_position = static_cast<int>(text.size() - 1);

				PDraw();
			}

			std::wstring GetPlaneText()
			{
				return plane_text;
			}

			void SetPasswordStatus(bool status)
			{
				password_type = status;

				PDraw();
			}
			void OnlyNumber(bool value)
			{
				only_number = value;
			}
		};
	}
}
