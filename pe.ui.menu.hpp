#pragma once

#include "pe.ui.object.hpp"

#include <string>

namespace PDotE
{
	namespace UI
	{
		struct MenuChoosenUser
		{
			std::wstring title;

			IMAGE*		 icon = nullptr;
			IMAGE*		 coverd_icon = nullptr;

			std::function<void()> onClicked;
		};

		struct MenuChoosen
		{
			std::wstring title;

			std::function<void()> onClicked;

			IMAGE*		 icon = nullptr;

			static MenuChoosen BuildFromUser(MenuChoosenUser user)
			{
				MenuChoosen result;

				result.icon  = user.icon;
				result.title = user.title;
				result.onClicked = user.onClicked;

				return result;
			}

			int  x = 0;
			int  y = 0;

			// 0 : Normal
			// 1 : On cover
			// 2 : Pushed
			int  status = 0;

		};

		class Menu : public Object
		{
		private:
			std::vector<MenuChoosen> choosen;

		public:
			Menu(int nwidth, Object* parnet = nullptr)
			{
				is_invisble = true;

				width   = nwidth;

				SetParent(parent);
				
				width += 15;
				height += 45;
				
				CreateRoundRectangleMask(width - 15, height - 15, radius);
			}

		public:
			void Draw()
			{
				setbkmode(TRANSPARENT);

				settextstyle(&_font);

				if (choosen.empty() == false)
				{
					if (choosen.size() == 1)
					{
						auto first_element = choosen[0];

						int text_x = width / 2 - textwidth(first_element.title.c_str()) / 2;
						int text_y = height / 2 - textheight(first_element.title.c_str()) / 2;

						if (first_element.status == 0)
						{
							setfillcolor(WHITE);
							settextcolor(RGB(128, 128, 128));
						}
						else if (first_element.status == 1 || first_element.status == 2)
						{
							setfillcolor(RGB(15, 174, 243));
							settextcolor(RGB(255, 255, 255));
						}
						else if (first_element.status == 3)
						{
							setfillcolor(RGB(18, 178, 243));
							settextcolor(RGB(255, 255, 255));
						}

						drawRoundedRectangleShadow(0, 0, width, height, 9);
						drawLinedRoundedRectangle(15, 15, width - 30, height - 30, 7);

						outtextxy(text_x, text_y, first_element.title.c_str());
					}
					else
					{
						auto first_element = choosen[0];

						int text_x = width / 2 - textwidth(first_element.title.c_str()) / 2;
						int text_y = 46 / 2 - textheight(first_element.title.c_str()) / 2;

						if (first_element.status == 0)
						{
							setfillcolor(WHITE);
							settextcolor(RGB(128, 128, 128));
						}
						else if (first_element.status == 1 || first_element.status == 2)
						{
							setfillcolor(RGB(15, 174, 243));
							settextcolor(RGB(255, 255, 255));
						}
						else if (first_element.status == 3)
						{
							setfillcolor(RGB(18, 178, 243));
							settextcolor(RGB(255, 255, 255));
						}

						drawRoundedRectangleShadow(0, 0, width, height, 9);
						drawRoundedRectangle(15, 15, width - 30, 50, 7);

						outtextxy(text_x, text_y + 15, first_element.title.c_str());

						int position = 0;

						IMAGE last_image;

						setlinecolor(RGB(238, 238, 238));

						for (auto item = choosen.begin() + 1; item != choosen.end() - 1; ++item)
						{
							++position;

							text_x = width / 2 - textwidth(item->title.c_str()) / 2;
							text_y = 46 / 2 - textheight(item->title.c_str()) / 2;

							if (item->status == 0)
							{
								setfillcolor(WHITE);
								settextcolor(RGB(128, 128, 128));
							}
							else if (item->status == 1 || item->status == 2)
							{
								setfillcolor(RGB(15, 174, 243));
								settextcolor(RGB(255, 255, 255));
							}
							else if (item->status == 3)
							{
								setfillcolor(RGB(18, 178, 243));
								settextcolor(RGB(255, 255, 255));
							}

							getimage(&last_image, 15, 15 + 46 * (position - 1), width, 46);
							
							solidrectangle(15, 15 + 46 * position, width - 15, height - 30);

							putimage(15, 15 + 46 * (position - 1), &last_image);

							outtextxy(text_x, text_y + 15 + 46 * (position), item->title.c_str());
						}

						auto last_element = choosen.rbegin().operator*();

						++position;

						text_x = width / 2 - textwidth(last_element.title.c_str()) / 2;
						text_y = 46 / 2 - textheight(last_element.title.c_str()) / 2;

						if (last_element.status == 0)
						{
							setfillcolor(WHITE);
							settextcolor(RGB(128, 128, 128));
						}
						else if (last_element.status == 1 || last_element.status == 2)
						{
							setfillcolor(RGB(15, 174, 243));
							settextcolor(RGB(255, 255, 255));
						}
						else if (last_element.status == 3)
						{
							setfillcolor(RGB(18, 178, 243));
							settextcolor(RGB(255, 255, 255));
						}

						getimage(&last_image, 15, 15 + 46 * (position - 1), width, 46);

						solidrectangle(15, 15 + 46 * position, width - 15, height - 30);
						drawRoundedRectangle(15, 15 + 46 * position, width - 30, 46, 9);

						putimage(15, 15 + 46 * (position - 1), &last_image);

						outtextxy(text_x, text_y + 15 + 46 * (position), last_element.title.c_str());

						position = 0;

						for (auto item = choosen.begin() + 1; item != choosen.end(); ++item)
						{
							++position;

							line(15, 15 + 46 * (position), width - 15, 15 + 46 * (position));
						}
					}
				}
			}

			void Move(int nx, int ny)
			{
				x = nx;
				y = ny;

				x -= 15;
				y -= 15;

				PDraw();
			}

			void Resize(int nwidth, int nheight)
			{
				width = nwidth;

				width += 30;

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
			void AppendChoosen(MenuChoosenUser nchoosen)
			{
				auto object = (MenuChoosen::BuildFromUser(nchoosen));

				object.x = 15;
				object.y = int(15 + choosen.size() * 46);

				choosen.push_back(object);

				height += 42;

				PDraw();

				CreateRoundRectangleMask(width - 15, height - 15, radius);
			}

		public:
			void MouseCoverd(ExMessage message)
			{
				message.x;
				message.y;

				bool flag = false;

				for (auto& item : choosen)
				{
					if (message.x >= item.x && message.x <= item.x + width - 15 &&
						message.y >= item.y && message.y <= item.y + 46)
					{
						if (item.status != 2)
						{
							flag = true;

							item.status = 2;
						}
					}
					else
					{
						if (item.status != 0)
						{
							item.status = 0;

							flag = true;
						}
					}
				}

				if (flag == true)
				{
					PDraw();
				}
			}

			void MouseLeft(ExMessage message)
			{
				for (auto& item : choosen)
				{
					item.status = 0;
				}

				PDraw();
			}

			void LeftButtonOnClicked(ExMessage message)
			{
				message.x;
				message.y;

				std::function<void()> on_clicked_function;

				for (auto& item : choosen)
				{
					if (message.x >= item.x && message.x <= item.x + width - 15 &&
						message.y >= item.y && message.y <= item.y + 46)
					{
						item.status = 3;

						on_clicked_function = item.onClicked;
					}
					else
					{
						item.status = 0;
					}
				}

				PDraw();

				if (on_clicked_function != NULL)
				{
					on_clicked_function();
				}
			}
			void RightButtonOnClicked(ExMessage message)
			{
				message.x -= x;
				message.y -= y;

				std::function<void()> on_clicked_function;

				for (auto& item : choosen)
				{
					if (message.x >= item.x && message.x <= item.x + width - 15 &&
						message.y >= item.y && message.y <= item.y + 46)
					{
						item.status = 3;

						on_clicked_function = item.onClicked;
					}
					else
					{
						item.status = 0;
					}
				}

				PDraw();

				if (on_clicked_function != NULL)
				{
					on_clicked_function();
				}
			}

			static bool CanMenuHoldOn(int ox, int oy, int owidth, int pwidth, int phegiht,
									int choosen_count)
			{
				if (ox + owidth + 15 <= pwidth &&
					oy + choosen_count * 46 + 15 <= phegiht)
				{
					return true;
				}

				return false;
			}
		};
	}
}
