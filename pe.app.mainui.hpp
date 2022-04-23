#pragma once

#include "pe.ui.xml.ui.hpp"
#include "pe.filters.blur.hpp"
#include "pe.filters.color.hpp"
#include "pe.effect.hpp"
#include "pe.app.messagebox.hpp"
#include "pe.app.data.hpp"
#include "pe.filters.blur.hpp"
#include "pe.app.file.hpp"

namespace PDotE
{
	namespace AppMainUI
	{
		struct ProjectFile
		{
			bool         read_only_mode = false;
			std::wstring file_path;
		};

		class MainUI
		{
		private:
			ProjectFile    file;
			UI::XmlWidget* parent;

			IMAGE		   process_image;

			bool           cancel_clicked;
			bool           yes_clicked;

		private:
			std::string ReadMainXml()
			{
				return PDotE::Data::main_ui_xml;
			}

			void FileMenu()
			{
				parent->GetElementById("Application")->GetElementById("SelectedLine")->object->Show();

				UI::Animation animation(parent->GetElementById("Application")->GetElementById("SelectedLine")->object, UI::DecelerateInterpolator, 5);
				animation.SetTargetPosition(161, 55);
				animation.Play();

				parent->GetElementById("Application")->GetElementById("FileMenu")->object->Show();

				ExMessage message;

				while (true)
				{
					while (peekmessage(&message))
					{
						if (parent->GetElementById("Application")->GetElementById("FileMenu")->object->IsTrigger(message) == false &&
							message.message == WM_LBUTTONDOWN)
						{
							parent->GetElementById("Application")->GetElementById("SelectedLine")->object->Hide();
							parent->GetElementById("Application")->GetElementById("FileMenu")->object->Hide();

							parent->GetWidget()->ProcessMessage(message);

							return;
						}

						parent->GetWidget()->ProcessMessage(message);
					}

					FlushBatchDraw();

					Sleep(20);
				}
			}
			void FilterMenu()
			{
				parent->GetElementById("Application")->GetElementById("SelectedLine")->object->Show();

				UI::Animation animation(parent->GetElementById("Application")->GetElementById("SelectedLine")->object, UI::DecelerateInterpolator, 5);
				animation.SetTargetPosition(220, 55);
				animation.Play();

				parent->GetElementById("Application")->GetElementById("FilterMenu")->object->Show();

				ExMessage message;

				while (true)
				{
					while (peekmessage(&message))
					{
						if (parent->GetElementById("Application")->GetElementById("FilterMenu")->object->IsTrigger(message) == false &&
							message.message == WM_LBUTTONDOWN)
						{
							parent->GetElementById("Application")->GetElementById("SelectedLine")->object->Hide();
							parent->GetElementById("Application")->GetElementById("FilterMenu")->object->Hide();

							parent->GetWidget()->ProcessMessage(message);

							return;
						}

						parent->GetWidget()->ProcessMessage(message);
					}

					FlushBatchDraw();

					Sleep(20);
				}
			}
			void ImageMenu()
			{
				parent->GetElementById("Application")->GetElementById("SelectedLine")->object->Show();

				UI::Animation animation(parent->GetElementById("Application")->GetElementById("SelectedLine")->object, UI::DecelerateInterpolator, 5);
				animation.SetTargetPosition(279, 55);
				animation.Play();

				parent->GetElementById("Application")->GetElementById("ImageMenu")->object->Show();

				ExMessage message;

				while (true)
				{
					while (peekmessage(&message))
					{
						if (parent->GetElementById("Application")->GetElementById("ImageMenu")->object->IsTrigger(message) == false &&
							message.message == WM_LBUTTONDOWN)
						{
							parent->GetElementById("Application")->GetElementById("SelectedLine")->object->Hide();
							parent->GetElementById("Application")->GetElementById("ImageMenu")->object->Hide();

							parent->GetWidget()->ProcessMessage(message);

							return;
						}

						parent->GetWidget()->ProcessMessage(message);
					}

					FlushBatchDraw();

					Sleep(20);
				}
			}
			void HelpMenu()
			{
				parent->GetElementById("Application")->GetElementById("SelectedLine")->object->Show();

				UI::Animation animation(parent->GetElementById("Application")->GetElementById("SelectedLine")->object, UI::DecelerateInterpolator, 5);
				animation.SetTargetPosition(397, 55);
				animation.Play();

				parent->GetElementById("Application")->GetElementById("HelpMenu")->object->Show();

				ExMessage message;

				while (true)
				{
					while (peekmessage(&message))
					{
						if (parent->GetElementById("Application")->GetElementById("HelpMenu")->object->IsTrigger(message) == false &&
							message.message == WM_LBUTTONDOWN)
						{
							parent->GetElementById("Application")->GetElementById("HelpMenu")->object->Hide();
							parent->GetElementById("Application")->GetElementById("SelectedLine")->object->Hide();

							parent->GetWidget()->ProcessMessage(message);

							return;
						}

						parent->GetWidget()->ProcessMessage(message);
					}

					FlushBatchDraw();

					Sleep(20);
				}
			}
			void EffectMenu()
			{
				parent->GetElementById("Application")->GetElementById("SelectedLine")->object->Show();

				UI::Animation animation(parent->GetElementById("Application")->GetElementById("SelectedLine")->object, UI::DecelerateInterpolator, 5);
				animation.SetTargetPosition(339, 55);
				animation.Play();

				parent->GetElementById("Application")->GetElementById("EffectMenu")->object->Show();

				ExMessage message;

				while (true)
				{
					while (peekmessage(&message))
					{
						if (parent->GetElementById("Application")->GetElementById("EffectMenu")->object->IsTrigger(message) == false &&
							message.message == WM_LBUTTONDOWN)
						{
							parent->GetElementById("Application")->GetElementById("EffectMenu")->object->Hide();
							parent->GetElementById("Application")->GetElementById("SelectedLine")->object->Hide();

							parent->GetWidget()->ProcessMessage(message);

							return;
						}

						parent->GetWidget()->ProcessMessage(message);
					}

					FlushBatchDraw();

					Sleep(20);
				}
			}

			void AboutWidget()
			{
				parent->GetElementById("Application")->GetElementById("SelectedLine")->object->Hide();
				parent->GetElementById("Application")->GetElementById("HelpMenu")->object->Hide();

				AppMessageBox::InfoMessage* message = new AppMessageBox::InfoMessage;

				(*message)(parent->GetWidget(), L"关于", L"PhotoEdtior ( v 0.0.1 beta ) 2022/2/5");

				delete message;
			}

			void GassBlurCancel()
			{
				cancel_clicked = true;
			}
			void ApplyGassBlur()
			{
				yes_clicked = true;
			}

			bool GassBlurRadiusOnPut(wchar_t ch)
			{
				cancel_clicked = false;
				yes_clicked	   = false;

				if ((!(ch >= L'0' && ch <= L'9')) &&
					ch != L'\b')
				{
					((UI::TextLabel*)(parent->GetElementById("Application")->GetElementById("GassBlurMask")->GetElementById("GassBlurBackground")->GetElementById("BlurWarningText")->object))
						->SetPlaneText(L"！只允许输入数字");

					return true;
				}
				else
				{
					auto radius = _ttoi64(((UI::LineEdit*)(parent->GetElementById("Application")->GetElementById("GassBlurMask")->GetElementById("GassBlurBackground")->GetElementById("BlurRadiusInputBox")->object))
						->GetPlaneText().c_str());

					if (radius >= 100)
					{
						((UI::TextLabel*)(parent->GetElementById("Application")->GetElementById("GassBlurMask")->GetElementById("GassBlurBackground")->GetElementById("BlurWarningText")->object))
							->SetPlaneText(L"！半径过大");

						((UI::LineEdit*)(parent->GetElementById("Application")->GetElementById("GassBlurMask")->GetElementById("GassBlurBackground")->GetElementById("BlurRadiusInputBox")->object))
							->SetPlaneText(L"100");

						return false;
					}

					IMAGE show_image = process_image;

					show_image.Resize(100, 100);

					if (radius != 0)
					{
						show_image = *Filters::GassBlurFilter(&show_image, radius);
					}

					show_image = *Filters::ResverColor(&show_image);
					show_image = *UI::SetAlpha(&show_image);

					((UI::ImageLabel*)(parent->GetElementById("Application")->GetElementById("GassBlurMask")->GetElementById("GassBlurBackground")->GetElementById("BlurViewImage")->object))
						->SetImage(show_image);

					return true;
				}
			}
			bool MascoBlurRadiusOnPut(wchar_t ch)
			{
				cancel_clicked = false;
				yes_clicked	   = false;

				if ((!(ch >= L'0' && ch <= L'9')) &&
					ch != L'\b')
				{
					((UI::TextLabel*)(parent->GetElementById("Application")->GetElementById("MascoBlurMask")->GetElementById("MascoBlurBackground")->GetElementById("BlurWarningText")->object))
						->SetPlaneText(L"！只允许输入数字");

					return true;
				}
				else
				{
					auto radius = _ttoi64(((UI::LineEdit*)(parent->GetElementById("Application")->GetElementById("MascoBlurMask")->GetElementById("MascoBlurBackground")->GetElementById("BlurRadiusInputBox")->object))
						->GetPlaneText().c_str());

					if (radius >= 100)
					{
						((UI::TextLabel*)(parent->GetElementById("Application")->GetElementById("MascoBlurMask")->GetElementById("MascoBlurBackground")->GetElementById("BlurWarningText")->object))
							->SetPlaneText(L"！半径过大");

						((UI::LineEdit*)(parent->GetElementById("Application")->GetElementById("MascoBlurMask")->GetElementById("MascoBlurBackground")->GetElementById("BlurRadiusInputBox")->object))
							->SetPlaneText(L"100");

						return false;
					}

					IMAGE show_image = process_image;

					show_image.Resize(100, 100);

					if (radius != 0)
					{
						show_image = *Filters::MascoBlurFilter(&show_image, radius);
					}

					show_image = *Filters::ResverColor(&show_image);
					show_image = *UI::SetAlpha(&show_image);

					((UI::ImageLabel*)(parent->GetElementById("Application")->GetElementById("MascoBlurMask")->GetElementById("MascoBlurBackground")->GetElementById("BlurViewImage")->object))
						->SetImage(show_image);

					return true;
				}
			}

			void GassBlurImage()
			{
				cancel_clicked = false;
				yes_clicked	   = false;
				parent->GetElementById("Application")->GetElementById("SelectedLine")->object->Hide();
				parent->GetElementById("Application")->GetElementById("FilterMenu")->object->Hide();

				UI::MaskLabel* label = ((UI::MaskLabel*)(parent->GetElementById("Application")->GetElementById("GassBlurMask")->object));

				label->ShowOffChild();

				IMAGE temp_image;
				IMAGE show_image = process_image;

				show_image.Resize(100, 100);

				((UI::ImageLabel*)(parent->GetElementById("Application")->GetElementById("GassBlurMask")->GetElementById("GassBlurBackground")->GetElementById("BlurViewImage")->object))
					->SetImage(show_image);
				
				ExMessage message;

				while (true)
				{
					while (peekmessage(&message))
					{
						if (parent->GetWidget()->ProcessMessage(message) == true)
						{
							if (cancel_clicked == true)
							{
								label->Hide();

								return;
							}
							if (yes_clicked == true)
							{
								label->Hide();

								auto radius_string = 
										((UI::LineEdit*)(parent->GetElementById("Application")->GetElementById("GassBlurMask")->GetElementById("GassBlurBackground")->GetElementById("BlurRadiusInputBox")->object))
										->GetPlaneText();

								auto radius = _wtoll(radius_string.c_str());

								process_image = *Filters::GassBlurFilter(&process_image, radius);

								FlashImage();

								return;
							}
						}
					}

					Sleep(1);
				}
			}

			void GrayRImage()
			{
				parent->GetElementById("Application")->GetElementById("SelectedLine")->object->Hide();
				parent->GetElementById("Application")->GetElementById("FilterMenu")->object->Hide();

				process_image = *Filters::RGrayFilter(&process_image);

				FlashImage();
			}
			void GrayGImage()
			{
				parent->GetElementById("Application")->GetElementById("SelectedLine")->object->Hide();
				parent->GetElementById("Application")->GetElementById("FilterMenu")->object->Hide();

				process_image = *Filters::GGrayFilter(&process_image);

				FlashImage();
			}
			void GrayBImage()
			{
				parent->GetElementById("Application")->GetElementById("SelectedLine")->object->Hide();
				parent->GetElementById("Application")->GetElementById("FilterMenu")->object->Hide();

				process_image = *Filters::BGrayFilter(&process_image);

				FlashImage();
			}

			void ResverColor()
			{
				parent->GetElementById("Application")->GetElementById("SelectedLine")->object->Hide();
				parent->GetElementById("Application")->GetElementById("FilterMenu")->object->Hide();

				process_image = *Filters::ResverColor(&process_image);

				FlashImage();
			}

			void InvertColor()
			{
				parent->GetElementById("Application")->GetElementById("SelectedLine")->object->Hide();
				parent->GetElementById("Application")->GetElementById("FilterMenu")->object->Hide();

				process_image = *Filters::InvertColor(&process_image);

				FlashImage();
			}

			void ThresholdingImage()
			{
				parent->GetElementById("Application")->GetElementById("SelectedLine")->object->Hide();
				parent->GetElementById("Application")->GetElementById("FilterMenu")->object->Hide();

				process_image = *Filters::ThresholdingColor(&process_image);

				FlashImage();
			}

			void MascoImage()
			{
				cancel_clicked = false;
				yes_clicked    = false;

				parent->GetElementById("Application")->GetElementById("SelectedLine")->object->Hide();
				parent->GetElementById("Application")->GetElementById("FilterMenu")->object->Hide();

				UI::MaskLabel* label = ((UI::MaskLabel*)(parent->GetElementById("Application")->GetElementById("MascoBlurMask")->object));

				label->ShowOffChild();

				IMAGE temp_image;
				IMAGE show_image = process_image;

				show_image.Resize(100, 100);

				((UI::ImageLabel*)(parent->GetElementById("Application")->GetElementById("MascoBlurMask")->GetElementById("MascoBlurBackground")->GetElementById("BlurViewImage")->object))
					->SetImage(show_image);
				
				ExMessage message;

				while (true)
				{
					while (peekmessage(&message))
					{
						if (parent->GetWidget()->ProcessMessage(message) == true)
						{
							if (cancel_clicked == true)
							{
								label->Hide();

								return;
							}
							if (yes_clicked == true)
							{
								label->Hide();

								auto radius_string = 
										((UI::LineEdit*)(parent->GetElementById("Application")->GetElementById("MascoBlurMask")->GetElementById("MascoBlurBackground")->GetElementById("BlurRadiusInputBox")->object))
										->GetPlaneText();

								auto radius = _wtoll(radius_string.c_str());

								process_image = *Filters::MascoBlurFilter(&process_image, radius);

								FlashImage();

								return;
							}
						}
					}

					Sleep(1);
				}
			}

			void ImageInformation()
			{
				parent->GetElementById("Application")->GetElementById("SelectedLine")->object->Hide();
				parent->GetElementById("Application")->GetElementById("ImageMenu")->object->Hide();

				auto position = file.file_path.find_last_of(L"\\") + 1;
				auto file_path = file.file_path.substr(position, file.file_path.size() - position);

				if (file.read_only_mode == true)
				{
					file_path += L"（只读模式）";
				}
				else
				{
					file_path += L"（缩放模式）";
				}

				file_path += std::to_wstring(process_image.getwidth()) + L"x" + std::to_wstring(process_image.getheight()) + L" px";

				AppMessageBox::InfoMessage information;

				information(parent->GetWidget(), L"图片信息", file_path);
			}

			void ReliefEffect()
			{
				parent->GetElementById("Application")->GetElementById("SelectedLine")->object->Hide();
				parent->GetElementById("Application")->GetElementById("EffectMenu")->object->Hide();

				process_image = *Effect::ReliefEffect(&process_image);

				FlashImage();
			}
			void CartoonEffect()
			{
				parent->GetElementById("Application")->GetElementById("SelectedLine")->object->Hide();
				parent->GetElementById("Application")->GetElementById("EffectMenu")->object->Hide();

				process_image = *Effect::CartoonEffect(&process_image);

				FlashImage();
			}
			void ColorEffect()
			{
				parent->GetElementById("Application")->GetElementById("SelectedLine")->object->Hide();
				parent->GetElementById("Application")->GetElementById("EffectMenu")->object->Hide();

				process_image = *Effect::ColorEffect(&process_image);

				FlashImage();
			}
			void OldStewfEffect()
			{
				parent->GetElementById("Application")->GetElementById("SelectedLine")->object->Hide();
				parent->GetElementById("Application")->GetElementById("EffectMenu")->object->Hide();

				process_image = *Effect::OldStewfEffect(&process_image);

				FlashImage();
			}

			void GetTempImage()
			{
				IMAGE temp_image = process_image;

				auto width  = temp_image.getwidth();
				auto height = temp_image.getheight();

				while (true) 
				{
					if (width > 1298 ||
						height > 729)
					{
						width  /= 2;
						height /= 2;
					}

					if (width <= 1298 &&
						height <= 729)
					{
						break;
					}
				}

				temp_image = *(UI::resetImage(&process_image, width, height));

				temp_image = *Filters::ResverColor(&temp_image);

				UI::SetAlpha(&temp_image);

				int y = 872 / 2 - height / 2;

				if (y <= 82)
				{
					y = 92;
				}

				((UI::ImageLabel*)(parent->GetElementById("Application")->GetElementById("EditImage")->object))->Resize(width, height);
				((UI::ImageLabel*)(parent->GetElementById("Application")->GetElementById("EditImage")->object))->SetImage(temp_image);
				((UI::ImageLabel*)(parent->GetElementById("Application")->GetElementById("EditImage")->object))->Move(1476 / 2 - width / 2, y);
			}

			/*
			void ChangeToDetla()
			{
				parent->GetWidget()->Hide();

				((UI::TextLabel*)(parent->GetElementById("Application")->GetElementById("DeltaSettingText")->object))
					->SetTextColor(RGB(145, 145, 145));
				((UI::ImageLabel*)(parent->GetElementById("Application")->GetElementById("DeltaSetting")->object))->
					SetImage(GetIcon(L"delta_selected"));

				((UI::TextLabel*)(parent->GetElementById("Application")->GetElementById("PaintText")->object))
					->SetTextColor(RGB(145, 145, 145));
				((UI::ImageLabel*)(parent->GetElementById("Application")->GetElementById("Paint")->object))->
					SetImage(GetIcon(L"pen_selected"));

				((UI::TextLabel*)(parent->GetElementById("Application")->GetElementById("TextToolText")->object))
					->SetTextColor(RGB(145, 145, 145));
				((UI::ImageLabel*)(parent->GetElementById("Application")->GetElementById("TextTool")->object))->
					SetImage(GetIcon(L"text_selected"));

				((UI::TextLabel*)(parent->GetElementById("Application")->GetElementById("SelectToolText")->object))
					->SetTextColor(RGB(145, 145, 145));
				((UI::ImageLabel*)(parent->GetElementById("Application")->GetElementById("SelectTool")->object))->
					SetImage(GetIcon(L"select_selected"));

				parent->GetWidget()->Show();

				((UI::TextLabel*)(parent->GetElementById("Application")->GetElementById("DeltaSettingText")->object))
					->SetTextColor(RGB(15, 174, 243));

				((UI::ImageLabel*)(parent->GetElementById("Application")->GetElementById("DeltaSetting")->object))->
					SetImage(GetIcon(L"delta"));

				UI::Animation animation(parent->GetElementById("Application")->GetElementById("SideSelectLine")->object, UI::DecelerateInterpolator, 10);
				animation.SetTargetPosition(3, 124);
				animation.Play();
			}
			void ChangeToPaint()
			{
				parent->GetWidget()->Hide();

				((UI::TextLabel*)(parent->GetElementById("Application")->GetElementById("DeltaSettingText")->object))
					->SetTextColor(RGB(145, 145, 145));
				((UI::ImageLabel*)(parent->GetElementById("Application")->GetElementById("DeltaSetting")->object))->
					SetImage(GetIcon(L"delta_selected"));

				((UI::TextLabel*)(parent->GetElementById("Application")->GetElementById("PaintText")->object))
					->SetTextColor(RGB(145, 145, 145));
				((UI::ImageLabel*)(parent->GetElementById("Application")->GetElementById("Paint")->object))->
					SetImage(GetIcon(L"pen_selected"));

				((UI::TextLabel*)(parent->GetElementById("Application")->GetElementById("TextToolText")->object))
					->SetTextColor(RGB(145, 145, 145));
				((UI::ImageLabel*)(parent->GetElementById("Application")->GetElementById("TextTool")->object))->
					SetImage(GetIcon(L"text_selected"));

				((UI::TextLabel*)(parent->GetElementById("Application")->GetElementById("SelectToolText")->object))
					->SetTextColor(RGB(145, 145, 145));
				((UI::ImageLabel*)(parent->GetElementById("Application")->GetElementById("SelectTool")->object))->
					SetImage(GetIcon(L"select_selected"));

				parent->GetWidget()->Show();

				((UI::TextLabel*)(parent->GetElementById("Application")->GetElementById("PaintText")->object))
					->SetTextColor(RGB(15, 174, 243));

				((UI::ImageLabel*)(parent->GetElementById("Application")->GetElementById("Paint")->object))->
					SetImage(GetIcon(L"pen"));

				UI::Animation animation(parent->GetElementById("Application")->GetElementById("SideSelectLine")->object, UI::DecelerateInterpolator, 10);
				animation.SetTargetPosition(3, 200);
				animation.Play();
			}
			void ChangeToText()
			{
				parent->GetWidget()->Hide();

				((UI::TextLabel*)(parent->GetElementById("Application")->GetElementById("DeltaSettingText")->object))
					->SetTextColor(RGB(145, 145, 145));
				((UI::ImageLabel*)(parent->GetElementById("Application")->GetElementById("DeltaSetting")->object))->
					SetImage(GetIcon(L"delta_selected"));

				((UI::TextLabel*)(parent->GetElementById("Application")->GetElementById("PaintText")->object))
					->SetTextColor(RGB(145, 145, 145));
				((UI::ImageLabel*)(parent->GetElementById("Application")->GetElementById("Paint")->object))->
					SetImage(GetIcon(L"pen_selected"));

				((UI::TextLabel*)(parent->GetElementById("Application")->GetElementById("TextToolText")->object))
					->SetTextColor(RGB(145, 145, 145));
				((UI::ImageLabel*)(parent->GetElementById("Application")->GetElementById("TextTool")->object))->
					SetImage(GetIcon(L"text_selected"));

				((UI::TextLabel*)(parent->GetElementById("Application")->GetElementById("SelectToolText")->object))
					->SetTextColor(RGB(145, 145, 145));
				((UI::ImageLabel*)(parent->GetElementById("Application")->GetElementById("SelectTool")->object))->
					SetImage(GetIcon(L"select_selected"));

				parent->GetWidget()->Show();

				((UI::TextLabel*)(parent->GetElementById("Application")->GetElementById("TextToolText")->object))
					->SetTextColor(RGB(15, 174, 243));

				((UI::ImageLabel*)(parent->GetElementById("Application")->GetElementById("TextTool")->object))->
					SetImage(GetIcon(L"text"));

				UI::Animation animation(parent->GetElementById("Application")->GetElementById("SideSelectLine")->object, UI::DecelerateInterpolator, 10);
				animation.SetTargetPosition(3, 281);
				animation.Play();
			}
			void ChangeToSelect()
			{
				parent->GetWidget()->Hide();

				((UI::TextLabel*)(parent->GetElementById("Application")->GetElementById("DeltaSettingText")->object))
					->SetTextColor(RGB(145, 145, 145));
				((UI::ImageLabel*)(parent->GetElementById("Application")->GetElementById("DeltaSetting")->object))->
					SetImage(GetIcon(L"delta_selected"));

				((UI::TextLabel*)(parent->GetElementById("Application")->GetElementById("PaintText")->object))
					->SetTextColor(RGB(145, 145, 145));
				((UI::ImageLabel*)(parent->GetElementById("Application")->GetElementById("Paint")->object))->
					SetImage(GetIcon(L"pen_selected"));

				((UI::TextLabel*)(parent->GetElementById("Application")->GetElementById("TextToolText")->object))
					->SetTextColor(RGB(145, 145, 145));
				((UI::ImageLabel*)(parent->GetElementById("Application")->GetElementById("TextTool")->object))->
					SetImage(GetIcon(L"text_selected"));

				((UI::TextLabel*)(parent->GetElementById("Application")->GetElementById("SelectToolText")->object))
					->SetTextColor(RGB(145, 145, 145));
				((UI::ImageLabel*)(parent->GetElementById("Application")->GetElementById("SelectTool")->object))->
					SetImage(GetIcon(L"select_selected"));

				parent->GetWidget()->Show();

				((UI::TextLabel*)(parent->GetElementById("Application")->GetElementById("SelectToolText")->object))
					->SetTextColor(RGB(15, 174, 243));

				((UI::ImageLabel*)(parent->GetElementById("Application")->GetElementById("SelectTool")->object))->
					SetImage(GetIcon(L"select"));

				UI::Animation animation(parent->GetElementById("Application")->GetElementById("SideSelectLine")->object, UI::DecelerateInterpolator, 10);
				animation.SetTargetPosition(3, 363);
				animation.Play();
			}
			*/
		
		private:
			void SaveImage()
			{
				parent->GetElementById("Application")->GetElementById("FileMenu")->object->Hide();
				parent->GetElementById("Application")->GetElementById("SelectedLine")->object->Hide();

				if (file.read_only_mode == true)
				{
					AppMessageBox::AssertMessage assert_box;

					assert_box(parent->GetWidget(), L"保存失败！", L"处于只读模式中！");

					return;
				}

				saveimage(file.file_path.c_str(), &process_image);

				std::ifstream stream;
				
				stream.open(file.file_path);

				if (stream.is_open() == false)
				{
					AppMessageBox::AssertMessage assert_box;

					assert_box(parent->GetWidget(), L"保存失败！", L"无法打开文件！");
				}

				stream.close();
			}

		public:
			MainUI(ProjectFile input_file, UI::XmlWidget* nparent)
			{
				file = input_file;

				parent = nparent;
			}

			void FlashImage()
			{
				GetTempImage();
			}

			void InitMainUI()
			{
				auto xml = ReadMainXml();

				parent->PushFunctional(std::bind(&MainUI::FileMenu, this), "FileMenu");
				parent->PushFunctional(std::bind(&MainUI::FilterMenu, this), "FilterMenu");
				parent->PushFunctional(std::bind(&MainUI::ImageMenu, this), "ImageMenu");
				parent->PushFunctional(std::bind(&MainUI::HelpMenu, this), "HelpMenu");
				parent->PushFunctional(std::bind(&MainUI::EffectMenu, this), "EffectMenu");

				parent->PushFunctional(std::bind(&MainUI::AboutWidget, this), "AboutWidget");

				parent->PushFunctional(std::bind(&MainUI::SaveImage, this), "SaveImage");

				parent->PushFunctional(std::bind(&MainUI::GassBlurImage, this), "GassBlurImage");
				parent->PushFunctional(std::bind(&MainUI::GassBlurCancel, this), "GassBlurCancel");
				parent->PushFunctional(std::bind(&MainUI::ApplyGassBlur, this), "ApplyGassBlur");

				parent->PushFunctional(std::bind(&MainUI::GrayRImage, this), "GrayRImage");
				parent->PushFunctional(std::bind(&MainUI::GrayGImage, this), "GrayGImage");
				parent->PushFunctional(std::bind(&MainUI::GrayBImage, this), "GrayBImage");

				parent->PushFunctional(std::bind(&MainUI::ResverColor, this), "ResverColor");
				parent->PushFunctional(std::bind(&MainUI::ThresholdingImage, this), "ThresholdingImage");
				parent->PushFunctional(std::bind(&MainUI::InvertColor, this), "InvertColor");

				parent->PushFunctional(std::bind(&MainUI::MascoImage, this), "MascoImage");

				parent->PushFunctional(std::bind(&MainUI::ImageInformation, this), "ImageInformation");
				parent->PushFunctional(std::bind(&MainUI::ReliefEffect, this), "ReliefEffect");
				parent->PushFunctional(std::bind(&MainUI::CartoonEffect, this), "CartoonEffect");
				parent->PushFunctional(std::bind(&MainUI::ColorEffect, this), "ColorEffect");
				parent->PushFunctional(std::bind(&MainUI::OldStewfEffect, this), "OldStewfEffect");

				parent->SetXml(xml);
				parent->GetWidget()->SetFontStyle(GetFont(REGULAR));

				IMAGE temp_image;

				loadimage(&process_image, file.file_path.c_str());

				auto position  = file.file_path.find_last_of(L"\\") + 1;
				auto file_path = file.file_path.substr(position, file.file_path.size() - position);

				file_path     += L"（缩放模式）";

				GetTempImage();

				((UI::TextLabel*)(parent->GetElementById("Application")->GetElementById("FilePath")->object))->SetPlaneText(file_path);
				((UI::LineEdit*)(parent->GetElementById("Application")->GetElementById("GassBlurMask")->GetElementById("GassBlurBackground")->GetElementById("BlurRadiusInputBox")->object))
					->CharOnPut = std::bind(&MainUI::GassBlurRadiusOnPut, this, std::placeholders::_1);
				((UI::LineEdit*)(parent->GetElementById("Application")->GetElementById("MascoBlurMask")->GetElementById("MascoBlurBackground")->GetElementById("BlurRadiusInputBox")->object))
					->CharOnPut = std::bind(&MainUI::MascoBlurRadiusOnPut, this, std::placeholders::_1);

			}

			int  exec()
			{
				return parent->GetWidget()->exec();
			}
		};
	}
}
