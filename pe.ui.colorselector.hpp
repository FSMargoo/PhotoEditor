#pragma once

#include "pe.ui.radiuslabel.hpp"
#include "pe.ui.imagelabel.hpp"

namespace PDotE
{
	namespace UI
	{
		namespace ColorSelectorPrivate
		{
			IMAGE* _ColorSelector_Lambda_Select_Map = nullptr;
		}

		class ColorSelectorTransparentButton : public Object
		{
		private:
			IMAGE background_image;

		public:
			int							  circle_x = 0;
			int							  circle_y = 0;

			std::function<void(int, int)> button_move;

		public:
			ColorSelectorTransparentButton(int nwidth, int nheight, Object* nparent = nullptr)
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
				auto working_image = GetWorkingImage();
				auto mask_image    = new IMAGE(background_image.getwidth(), background_image.getheight());

				SetWorkingImage(mask_image);

				setfillcolor(BLACK);
				setbkcolor(WHITE);

				cleardevice();

				drawRoundedRectangle(0, 0, background_image.getwidth(), background_image.getheight(), 6);

				SetWorkingImage(working_image);

				saveimage(L"./mask_.png", mask_image);

				putimage(2, 2, mask_image, SRCAND);
				putimage(2, 2, &background_image, SRCPAINT);

				delete mask_image;

				setlinecolor(RGB(211, 211, 211));

				drawSoildCircle(circle_x - 12, circle_y - 12, 24, 24);
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

			void SetBackgroundImage(IMAGE image)
			{
				background_image = image;
				background_image.Resize(background_image.getwidth() - 4, background_image.getheight() - 4);
			}

		public:
			bool ProcessMessage(ExMessage message, bool calle_from_parent = false)
			{
				if (is_invisble == true)
				{
					return false;
				}

				if (IsTrigger(message) == true)
				{
					used_to_focus = true;

					switch (message.message)
					{
					case WM_LBUTTONDOWN:
					{
						ExMessage new_message;

						Object* d_parent = parent;

						int real_x = 0;
						int real_y = 0;

						while (d_parent != nullptr)
						{
							real_x += d_parent->GetX();
							real_y += d_parent->GetY();

							d_parent = d_parent->GetParent();
						}
						
						delete d_parent;

						bool flag = true;

						while (flag)
						{
							while (peekmessage(&new_message))
							{
								if (new_message.message == WM_LBUTTONUP)
								{
									flag = false;

									break;
								}
								if (new_message.message == WM_MOUSEMOVE)
								{
									new_message.x -= real_x;
									new_message.y -= real_y;
									
									circle_x = new_message.x;
									circle_y = new_message.y;

									if (new_message.x <= 0)
									{
										circle_x = 0;
									}
									if (new_message.y <= 0)
									{
										circle_y = 0;
									}

									if (new_message.x >= GetWidth())
									{
										circle_x = background_image.getwidth() - 1;
									}
									if (new_message.y >= GetHeight())
									{
										circle_y = background_image.getheight() - 1;
									}

									PDraw();

									FlushBatchDraw();

									button_move(circle_x, circle_y);
								}
							}

							Sleep(20);
						}

						break;
					}
					}

					if (calle_from_parent == false)
					{
						this->redraw = true;
					}

					return true;
				}

				if (calle_from_parent == false)
				{
					FlushBatchDraw();
				}

				return false;
			}
		};

		class ColorSelector : public
			Object
		{
		public:
			std::function<void(COLORREF)> ColorOnChanged;

		private:
			RadiusLabel* main_label;
			RadiusLabel* lambda_label;

			IMAGE*  lambda_image;
			IMAGE*  main_image;

			ColorSelectorTransparentButton* main_button;
			ColorSelectorTransparentButton* lambda_button;


			COLORREF     local_lambda_color;
			COLORREF     local_main_color;

			int          lambda_x;
			int			 lambda_y;
			int			 main_x;
			int			 main_y;

		private:
			COLORREF LambdaToRGB(double lambda, double gamma = 0.8, double intensity_max = 255.)
			{
				double r = 0.;
				double g = 0.;
				double b = 0.;
				int a = 0;

				if (lambda >= 380. && lambda < 440.)
				{
					r = -1. * (lambda - 440.) / (440. - 380.);
					g = 0.;
					b = 1.;
				}
				if (lambda >= 440. && lambda < 490.) 
				{
					r = 0.;
					g = (lambda - 440.) / (490. - 440.);
					b = 1.;
				}
				if (lambda >= 490. && lambda < 510.) 
				{
					r = 0.;
					g = 1.;
					b = -1. * (lambda - 510.) / (510. - 490.);
				}
				if (lambda >= 510. && lambda < 580.) 
				{
					r = (lambda - 510.) / (580. - 510.);
					g = 1.;
					b = 0.;
				}
				if (lambda >= 580. && lambda < 645.) 
				{
					r = 1.;
					g = -1. * (lambda - 645.) / (645. - 580.);
					b = 0.;
				}
				if (lambda >= 645. && lambda <= 780.) 
				{
					r = 1.;
					g = 0.;
					b = 0.;
				}

				r *= 100;
				g *= 100;
				b *= 100;

				float H;
				float S;
				float L;

				RGBtoHSL(RGB(r, g, b), &H, &S, &L);

				L = L + 0.2;

				COLORREF result = HSLtoRGB(H, S, L);

				return result;
			}

			void     CreateLambdaSelectMap(IMAGE* image)
			{
				auto buffer = GetImageBuffer(image);

				for (int lambda = 380, y = 0; lambda <= 780; lambda += 1, ++y)
				{
					for (int x = 26; x >= 0; --x)
					{
						buffer[26 * y + x] = LambdaToRGB(lambda);
					}
				}
			}
			IMAGE    DrawColorSendMap(COLORREF target_color)
			{
				/////////////////////////////////////////////
				//           C o l o r  M a p
				//  WHITE       ->         target_color
				//    |
				//    v
				//  BLACK
				//    [Line Insert]
				//
				IMAGE result(256, 190);
				auto buffer = GetImageBuffer(&result);

				target_color = BGR(target_color);

				// Foot Insert
				int var = 255;
				int vag = 255;
				int vab = 255;

				int vbr = GetRValue(target_color);
				int vbg = GetGValue(target_color);
				int vbb = GetBValue(target_color);

				int xa = 0;
				int xb = 256;
				int xp = 0;

				int vpr;
				int vpg;
				int vpb;

				for (int xp = 0; xp < xb; ++xp)
				{
					vpr = var + (xp - xa) * (vbr - var) / (xb - xa);
					vpg = vag + (xp - xa) * (vbg - vag) / (xb - xa);
					vpb = vab + (xp - xa) * (vbb - vab) / (xb - xa);

					buffer[xp] = BGR(RGB(vpr, vpg, vpb));
				}

				vbr = 0;
				vbg = 0;
				vbb = 0;

				for (int i = 0; i < 256; ++i)
				{
					xb = 190;
					xp = 0;

					var = GetRValue(buffer[i]);
					vag = GetGValue(buffer[i]);
					vab = GetBValue(buffer[i]);

					for (xp = 0; xp < xb; ++xp)
					{
						vpr = var + (xp - xa) * (vbr - var) / (xb - xa);
						vpg = vag + (xp - xa) * (vbg - vag) / (xb - xa);
						vpb = vab + (xp - xa) * (vbb - vab) / (xb - xa);

						buffer[xp * 256 + i] = BGR(RGB(vpr, vpg, vpb));
					}
				}

				return result;
			}

		private:
			void MainButtonPushed(int x, int y)
			{

			}
			void LambdaButtonPushed(int x, int y)
			{

			}

			COLORREF get_lambda_color()
			{
				auto buffer = GetImageBuffer(ColorSelectorPrivate::_ColorSelector_Lambda_Select_Map);

				return BGR(buffer[lambda_y * 26 + lambda_x]);
			}
			COLORREF get_main_color(IMAGE main_color)
			{
				auto buffer = GetImageBuffer(&main_color);

				return buffer[main_y * 256 + main_x];
			}

		public:
			void MainColorOnChange(int x, int y)
			{
				main_x = x;
				main_y = y;

				local_main_color = get_main_color(*main_image);

				ColorOnChanged(local_main_color);
			}
			void LambdaColorOnChange(int x, int y)
			{
				lambda_x = x;
				lambda_y = y;

				local_lambda_color = get_lambda_color();

				*main_image		   = DrawColorSendMap(local_lambda_color);

				local_main_color   = get_main_color(*main_image);
				
				main_button->SetBatchDraw(true);
				main_button->SetBackgroundImage(*main_image);
				main_button->SetBatchDraw(false);

				ColorOnChanged(local_main_color);
			}

		public:
			ColorSelector(Object* nparent)
			{
				using namespace ColorSelectorPrivate;

				width  = 311;
				height = 193;

				CreateRectangleMask(320, 200);

				SetParent(nparent);

				Hide();

				main_label   = new RadiusLabel(256, 190, 8, false, this);
				lambda_label = new RadiusLabel(26, 190, 8, false, this);

				main_label->SetLineColor(RGB(234, 234, 234));
				main_label->SetRadius(10);

				lambda_label->SetLineColor(RGB(234, 234, 234));
				lambda_label->SetRadius(10);
				lambda_label->Move(280, 0);

				main_label->Show();
				lambda_label->Show();

				main_button   = new ColorSelectorTransparentButton(256, 190, main_label);
				lambda_button = new ColorSelectorTransparentButton(26, 190, lambda_label);

				if (_ColorSelector_Lambda_Select_Map == nullptr)
				{
					auto image = new IMAGE(26, 400);
					ColorSelectorPrivate::_ColorSelector_Lambda_Select_Map = new IMAGE(26, 190);

					CreateLambdaSelectMap(image);

					SetWorkingImage(ColorSelectorPrivate::_ColorSelector_Lambda_Select_Map);

					auto new_image = resetImage(image, 26, 190);

					putimage(0, 0, new_image);

					SetWorkingImage();

					delete new_image;
					delete image;
				}
				
				local_lambda_color = get_lambda_color();

				main_image		   = new IMAGE(256, 190);

				local_main_color   = RGB(202, 0, 201);

				*main_image		   = DrawColorSendMap(local_main_color);
				local_main_color   = get_main_color(*main_image);

				main_button->SetBackgroundImage(*main_image);
				lambda_button->SetBackgroundImage(*ColorSelectorPrivate::_ColorSelector_Lambda_Select_Map);

				main_button->button_move   = std::bind(&ColorSelector::MainColorOnChange, this, std::placeholders::_1, std::placeholders::_2);
				lambda_button->button_move = std::bind(&ColorSelector::LambdaColorOnChange, this, std::placeholders::_1, std::placeholders::_2);

				main_button->Show();
				lambda_button->Show();

				Show();
			}

		public:
			COLORREF GetUserRGB()
			{
				return local_main_color;
			}

		public:
			void Draw()
			{
				main_label->PDraw(true);
				main_label->PDraw(true);
			}
		};
	}
}
