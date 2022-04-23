
#pragma once

#include "pe.ui.hpp"
#include "pe.ui.xml.hpp"

#include <comdef.h>

#include <fstream>

namespace PDotE
{
	namespace UI
	{
		struct XmlObject
		{
			Object* object;

			std::map<std::string, XmlObject*> child;

			XmlObject* GetElementById(std::string id)
			{
				return child[id];
			}

			XmlObject* operator[](std::string id)
			{
				return child[id];
			}
		};

#define Slot(object) , #object
		class XmlWidget : 
			public Object
		{
		private:
			const wchar_t* codecv(const char* input)
			{
				_bstr_t output = input;

				return (const wchar_t*)output;
			}

		protected:
			Widget*  widget;
			XmlNode  node;

			std::map<std::string, XmlObject*>    objects;
			std::map<std::string, std::function<void()> > slots;

		private:
			void DrawXmlNode(_XmlNode* node, Object* nparnet, XmlObject* xml_parent)
			{
				if (node->node_name.empty() == true)
				{
					time_t tstart = clock();

					for (auto& item : node->child_object)
					{
						DrawXmlNode(item.second, nparnet, nullptr);
					}

					tstart = clock();
					widget->ShowOffChild();

					FlushBatchDraw();

					return;
				}

				if (node->propertys["Type"].value_as_string == "TransparentButton")
				{
					TransparentButton* button = new TransparentButton(
						static_cast<int>((*node)["Width"]->node_content.value_as_number),
						static_cast<int>((*node)["Height"]->node_content.value_as_number),
						nparnet
					);

					XmlObject* temp_object = new XmlObject;

					for (auto& item : node->child_object)
					{
						if (item.second->node_name == "PositionX")
						{
							button->Move(item.second->node_content.value_as_number, button->GetY());
						}
						if (item.second->node_name == "PositionY")
						{
							button->Move(button->GetX(), item.second->node_content.value_as_number);
						}
						if (item.second->node_name == "Child")
						{
							for (auto& child : item.second->child_object)
							{
								DrawXmlNode(child.second, button, temp_object);
							}
						}
					}

					button->SetParent(nparnet);

					if (node->IsProperty("OnClicked") == true)
					{
						button->mouseOnClicked = slots[node->propertys["OnClicked"].value_as_string];
					}
					if (node->IsProperty("OnCoverd") == true)
					{
						button->mouseOnCover = slots[node->propertys["OnCoverd"].value_as_string];
					}
					if (node->IsProperty("LoseFocus") == true)
					{
						button->mouseRleased = slots[node->propertys["LoseFocus"].value_as_string];
					}

					if (node->IsProperty("Visible") == true)
					{
						if (node->propertys["Visible"].value_as_boolean == false)
						{
							button->Hide();
							button->LockStatus(true);
						}
					}

					temp_object->object = button;

					if (xml_parent != nullptr)
					{
						xml_parent->child.insert(std::pair<std::string, XmlObject*>(node->node_name, temp_object));
					}
					else
					{
						objects.insert(std::pair<std::string, XmlObject*>(node->node_name, temp_object));
					}

					temp_object->object = nparnet->GetChild(button->GetID());
				}
				if (node->propertys["Type"].value_as_string == "Label")
				{
					FlatLabel* label = new FlatLabel(
						static_cast<int>((*node)["Width"]->node_content.value_as_number),
						static_cast<int>((*node)["Height"]->node_content.value_as_number), false,
						nparnet);

					XmlObject* temp_object = new XmlObject;

					for (auto& item : node->child_object)
					{
						if (item.second->node_name == "TextType")
						{
							LOGFONT font;

							gettextstyle(&font);

							if (item.second->node_content.value_as_string == "Thin")
							{
								font.lfWeight = FW_THIN;
							}
							if (item.second->node_content.value_as_string == "Regular")
							{
								font.lfWeight = FW_REGULAR;
							}
							if (item.second->node_content.value_as_string == "Light")
							{
								font.lfWeight = FW_LIGHT;
							}
							if (item.second->node_content.value_as_string == "Medium")
							{
								font.lfWeight = FW_MEDIUM;
							}
							if (item.second->node_content.value_as_string == "Bold")
							{
								font.lfWeight = FW_BOLD;
							}

							label->SetFontStyle(font);
						}
						if (item.second->node_name == "TextHeight")
						{
							label->SetTextHeight(item.second->node_content.value_as_number);
						}
						if (item.second->node_name == "ColorBackground")
						{
							label->SetBackgroundColor(item.second->node_content.value_as_number);
						}
						if (item.second->node_name == "ColorLine")
						{
							label->SetLineColor(item.second->node_content.value_as_number);
						}
						if (item.second->node_name == "PositionX")
						{
							label->Move(item.second->node_content.value_as_number, label->GetY());
						}
						if (item.second->node_name == "PositionY")
						{
							label->Move(label->GetX(), item.second->node_content.value_as_number);
						}
						if (item.second->node_name == "Shadow")
						{
							label->SetShadow(item.second->node_content.value_as_boolean);
						}
						if (item.second->node_name == "Child")
						{
							for (auto& child : item.second->child_object)
							{
								DrawXmlNode(child.second, label, temp_object);
							}
						}
					}

					label->SetParent(nparnet);

					if (node->IsProperty("Visible") == true)
					{
						if (node->propertys["Visible"].value_as_boolean == false)
						{
							label->Hide();
							label->LockStatus(true);
						}
					}

					if (xml_parent != nullptr)
					{
						xml_parent->child.insert(std::pair<std::string, XmlObject*>(node->node_name, temp_object));
					}
					else
					{
						objects.insert(std::pair<std::string, XmlObject*>(node->node_name, temp_object));
					}

					temp_object->object = nparnet->GetChild(label->GetID());
				}
				if (node->propertys["Type"].value_as_string == "RadiusLabel")
				{
					RadiusLabel* label = new RadiusLabel(
						static_cast<int>((*node)["Width"]->node_content.value_as_number),
						static_cast<int>((*node)["Height"]->node_content.value_as_number), false,
						nparnet);

					XmlObject* temp_object = new XmlObject;

					for (auto& item : node->child_object)
					{
						if (item.second->node_name == "TextType")
						{
							LOGFONT font;

							gettextstyle(&font);

							if (item.second->node_content.value_as_string == "Thin")
							{
								font.lfWeight = FW_THIN;
							}
							if (item.second->node_content.value_as_string == "Regular")
							{
								font.lfWeight = FW_REGULAR;
							}
							if (item.second->node_content.value_as_string == "Light")
							{
								font.lfWeight = FW_LIGHT;
							}
							if (item.second->node_content.value_as_string == "Medium")
							{
								font.lfWeight = FW_MEDIUM;
							}
							if (item.second->node_content.value_as_string == "Bold")
							{
								font.lfWeight = FW_BOLD;
							}

							label->SetFontStyle(font);
						}
						if (item.second->node_name == "TextHeight")
						{
							label->SetTextHeight(item.second->node_content.value_as_number);
						}
						if (item.second->node_name == "ColorBackground")
						{
							label->SetBackgroundColor(item.second->node_content.value_as_number);
						}
						if (item.second->node_name == "ColorLine")
						{
							label->SetLineColor(item.second->node_content.value_as_number);
						}
						if (item.second->node_name == "PositionX")
						{
							label->Move(item.second->node_content.value_as_number, label->GetY());
						}
						if (item.second->node_name == "PositionY")
						{
							label->Move(label->GetX(), item.second->node_content.value_as_number);
						}
						if (item.second->node_name == "Radius")
						{
							label->SetRadius(item.second->node_content.value_as_number);
						}
						if (item.second->node_name == "Shadow")
						{
							label->SetShadow(item.second->node_content.value_as_boolean);
						}
						if (item.second->node_name == "Child")
						{
							for (auto& child : item.second->child_object)
							{
								DrawXmlNode(child.second, label, temp_object);
							}
						}
					}

					label->SetParent(nparnet);

					if (node->IsProperty("Visible") == true)
					{
						if (node->propertys["Visible"].value_as_boolean == false)
						{
							label->Hide();
							label->LockStatus(true);
						}
					}

					temp_object->object = label;

					if (xml_parent != nullptr)
					{
						xml_parent->child.insert(std::pair<std::string, XmlObject*>(node->node_name, temp_object));
					}
					else
					{
						objects.insert(std::pair<std::string, XmlObject*>(node->node_name, temp_object));
					}

					temp_object->object = nparnet->GetChild(label->GetID());
				}
				if (node->propertys["Type"].value_as_string == "ImageLabel")
				{
					ImageLabel* label = new ImageLabel(
						static_cast<int>((*node)["Width"]->node_content.value_as_number),
						static_cast<int>((*node)["Height"]->node_content.value_as_number), nullptr, false,
						nparnet);

					XmlObject* temp_object = new XmlObject;

					temp_object->object = label;

					for (auto& item : node->child_object)
					{
						if (item.second->node_name == "PositionX")
						{
							label->Move(item.second->node_content.value_as_number, label->GetY());
						}
						if (item.second->node_name == "PositionY")
						{
							label->Move(label->GetX(), item.second->node_content.value_as_number);
						}
						if (item.second->node_name == "Shadow")
						{
							label->SetShadow(item.second->node_content.value_as_number);
						}
						if (item.second->node_name == "Image")
						{
							IMAGE image;

							loadimage(&image, codecv(item.second->node_content.value_as_string.c_str()));

							label->SetImage(image);
						}
						if (item.second->node_name == "Child")
						{
							for (auto& child : item.second->child_object)
							{
								DrawXmlNode(child.second, label, temp_object);
							}
						}

						if (item.second->node_name == "TextType")
						{
							LOGFONT font;

							gettextstyle(&font);

							if (item.second->node_content.value_as_string == "Thin")
							{
								font.lfWeight = FW_THIN;
							}
							if (item.second->node_content.value_as_string == "Regular")
							{
								font.lfWeight = FW_REGULAR;
							}
							if (item.second->node_content.value_as_string == "Light")
							{
								font.lfWeight = FW_LIGHT;
							}
							if (item.second->node_content.value_as_string == "Medium")
							{
								font.lfWeight = FW_MEDIUM;
							}
							if (item.second->node_content.value_as_string == "Bold")
							{
								font.lfWeight = FW_BOLD;
							}

							label->SetFontStyle(font);
						}
						if (item.second->node_name == "TextHeight")
						{
							label->SetTextHeight(item.second->node_content.value_as_number);
						}
					}

					label->SetParent(nparnet);

					if (node->IsProperty("Visible") == true)
					{
						if (node->propertys["Visible"].value_as_boolean == false)
						{
							label->Hide();
							label->LockStatus(true);
						}
					}

					if (xml_parent != nullptr)
					{
						xml_parent->child.insert(std::pair<std::string, XmlObject*>(node->node_name, temp_object));
					}
					else
					{
						objects.insert(std::pair<std::string, XmlObject*>(node->node_name, temp_object));
					}

					temp_object->object = nparnet->GetChild(label->GetID());
				}
				if (node->propertys["Type"].value_as_string == "Button")
				{
					Button* button = new Button(static_cast<int>((*node)["Width"]->node_content.value_as_number),
						static_cast<int>((*node)["Height"]->node_content.value_as_number), false,
						nparnet);

					button->SetParent(nparnet);

					XmlObject* temp_object = new XmlObject;

					temp_object->object = button;

					for (auto& item : node->child_object)
					{
						if (item.second->node_name == "Shadow")
						{
							button->SetShadow(item.second->node_content.value_as_boolean);
						}
						if (item.second->node_name == "PlaneText")
						{
							button->SetPlaneText(codecv(item.second->node_content.value_as_string.c_str()));
						}
						if (item.second->node_name == "PositionX")
						{
							button->Move(item.second->node_content.value_as_number, button->GetY());
						}
						if (item.second->node_name == "PositionY")
						{
							button->Move(button->GetX(), item.second->node_content.value_as_number);
						}

						if (item.second->node_name == "FillColorNormal")
						{
							button->SetNormalFillColor(item.second->node_content.value_as_number);
						}
						if (item.second->node_name == "FillColorCoverd")
						{
							button->SetCoverdFillColor(item.second->node_content.value_as_number);
						}
						if (item.second->node_name == "FillColorPushed")
						{
							button->SetPushedFillColor(item.second->node_content.value_as_number);
						}
						if (item.second->node_name == "LineColorNormal")
						{
							button->SetNormalLineColor(item.second->node_content.value_as_number);
						}
						if (item.second->node_name == "LineColorCoverd")
						{
							button->SetCoverdLineColor(item.second->node_content.value_as_number);
						}
						if (item.second->node_name == "LineColorPushed")
						{
							button->SetPushedLineColor(item.second->node_content.value_as_number);
						}
						if (item.second->node_name == "TextColorNormal")
						{
							button->SetNormalTextColor(item.second->node_content.value_as_number);
						}
						if (item.second->node_name == "TextColorCoverd")
						{
							button->SetCoverdTextColor(item.second->node_content.value_as_number);
						}
						if (item.second->node_name == "TextColorPushed")
						{
							button->SetPushedTextColor(item.second->node_content.value_as_number);
						}

						if (item.second->node_name == "Icon")
						{
							IMAGE image;

							loadimage(&image, codecv(item.second->node_content.value_as_string.c_str()));

							button->SetIcon(image);
						}
						if (item.second->node_name == "IconCoverd")
						{
							IMAGE image;

							loadimage(&image, codecv(item.second->node_content.value_as_string.c_str()));

							button->SetIconCoverd(image);
						}
						if (item.second->node_name == "TextCenter")
						{
							button->SetTextCenter(item.second->node_content.value_as_boolean);
						}

						if (item.second->node_name == "Child")
						{
							for (auto& child : item.second->child_object)
							{
								DrawXmlNode(child.second, button, temp_object);
							}
						}

						if (item.second->node_name == "TextType")
						{
							LOGFONT font;

							gettextstyle(&font);

							if (item.second->node_content.value_as_string == "Thin")
							{
								font.lfWeight = FW_THIN;
							}
							if (item.second->node_content.value_as_string == "Regular")
							{
								font.lfWeight = FW_REGULAR;
							}
							if (item.second->node_content.value_as_string == "Light")
							{
								font.lfWeight = FW_LIGHT;
							}
							if (item.second->node_content.value_as_string == "Medium")
							{
								font.lfWeight = FW_MEDIUM;
							}
							if (item.second->node_content.value_as_string == "Bold")
							{
								font.lfWeight = FW_BOLD;
							}

							button->SetFontStyle(font);
						}
						if (item.second->node_name == "TextHeight")
						{
							button->SetTextHeight(item.second->node_content.value_as_number);
						}
					}

					if (node->IsProperty("OnClicked") == true)
					{
						button->mouseOnClicked = slots[node->propertys["OnClicked"].value_as_string];
					}
					if (node->IsProperty("OnCoverd") == true)
					{
						button->mouseOnCover = slots[node->propertys["OnCoverd"].value_as_string];
					}
					if (node->IsProperty("LoseFocus") == true)
					{
						button->mouseRleased = slots[node->propertys["LoseFocus"].value_as_string];
					}

					if (node->IsProperty("Visible") == true)
					{
						if (node->propertys["Visible"].value_as_boolean == false)
						{
							button->Hide();
							button->LockStatus(true);
						}
					}

					if (node->IsProperty("Visible") == true)
					{
						if (node->propertys["Visible"].value_as_boolean == false)
						{
							button->Hide();
							button->LockStatus(true);
						}
					}

					if (xml_parent != nullptr)
					{
						xml_parent->child.insert(std::pair<std::string, XmlObject*>(node->node_name, temp_object));
					}
					else
					{
						objects.insert(std::pair<std::string, XmlObject*>(node->node_name, temp_object));
					}

					temp_object->object = nparnet->GetChild(button->GetID());
				}
				if (node->propertys["Type"].value_as_string == "LineEdit")
				{
					LineEdit* lineedit = new LineEdit(static_cast<int>((*node)["Width"]->node_content.value_as_number),
						static_cast<int>((*node)["Height"]->node_content.value_as_number), nparnet);

					lineedit->SetParent(nparnet);

					XmlObject* temp_object = new XmlObject;

					temp_object->object = lineedit;

					for (auto& item : node->child_object)
					{
						if (item.second->node_name == "PlaneText")
						{
							lineedit->SetPlaneText(codecv(item.second->node_content.value_as_string.c_str()));
						}
						if (item.second->node_name == "PositionX")
						{
							lineedit->Move(item.second->node_content.value_as_number, lineedit->GetY());
						}
						if (item.second->node_name == "PositionY")
						{
							lineedit->Move(lineedit->GetX(), item.second->node_content.value_as_number);
						}
						if (item.second->node_name == "Password")
						{
							lineedit->SetPasswordStatus(item.second->node_content.value_as_boolean);
						}

						if (item.second->node_name == "Child")
						{
							for (auto& child : item.second->child_object)
							{
								DrawXmlNode(child.second, lineedit, temp_object);
							}
						}

						if (item.second->node_name == "TextType")
						{
							LOGFONT font;

							gettextstyle(&font);

							if (item.second->node_content.value_as_string == "Thin")
							{
								font.lfWeight = FW_THIN;
							}
							if (item.second->node_content.value_as_string == "Regular")
							{
								font.lfWeight = FW_REGULAR;
							}
							if (item.second->node_content.value_as_string == "Light")
							{
								font.lfWeight = FW_LIGHT;
							}
							if (item.second->node_content.value_as_string == "Medium")
							{
								font.lfWeight = FW_MEDIUM;
							}
							if (item.second->node_content.value_as_string == "Bold")
							{
								font.lfWeight = FW_BOLD;
							}

							lineedit->SetFontStyle(font);
						}
						if (item.second->node_name == "TextHeight")
						{
							lineedit->SetTextHeight(item.second->node_content.value_as_number);
						}
						if (item.second->node_name == "OnlyNumber")
						{
							lineedit->OnlyNumber(item.second->node_content.value_as_boolean);
						}
					}

					if (node->IsProperty("Visible") == true)
					{
						if (node->propertys["Visible"].value_as_boolean == false)
						{
							lineedit->Hide();
							lineedit->LockStatus(true);
						}
					}

					if (xml_parent != nullptr)
					{
						xml_parent->child.insert(std::pair<std::string, XmlObject*>(node->node_name, temp_object));
					}
					else
					{
						objects.insert(std::pair<std::string, XmlObject*>(node->node_name, temp_object));
					}

					temp_object->object = nparnet->GetChild(lineedit->GetID());
				}
				if (node->propertys["Type"].value_as_string == "Menu")
				{
					Menu* menu = new Menu(static_cast<int>((*node)["Width"]->node_content.value_as_number), nparnet);

					menu->SetParent(nparnet);

					XmlObject* temp_object = new XmlObject;

					temp_object->object = menu;

					for (auto& item : node->child_object)
					{
						if (item.second->node_name == "PositionX")
						{
							menu->Move(item.second->node_content.value_as_number, menu->GetY());
						}
						if (item.second->node_name == "PositionY")
						{
							menu->Move(menu->GetX(), item.second->node_content.value_as_number);
						}
						if (item.second->node_name == "Choosen")
						{
							MenuChoosenUser choosen;

							choosen.title     = codecv(item.second->node_content.value_as_string.c_str());

							if (item.second->IsProperty("OnClicked") == true)
							{
								choosen.onClicked = slots[item.second->propertys["OnClicked"].value_as_string];
							}
							if (item.second->IsProperty("icon") == true)
							{
								IMAGE temp_image;
								
								loadimage(&temp_image, codecv(item.second->propertys["icon"].value_as_string.c_str()));

								*(choosen.icon) = temp_image;
							}

							menu->AppendChoosen(choosen);
						}

						if (item.second->node_name == "TextType")
						{
							LOGFONT font;

							gettextstyle(&font);

							if (item.second->node_content.value_as_string == "Thin")
							{
								font.lfWeight = FW_THIN;
							}
							if (item.second->node_content.value_as_string == "Regular")
							{
								font.lfWeight = FW_REGULAR;
							}
							if (item.second->node_content.value_as_string == "Light")
							{
								font.lfWeight = FW_LIGHT;
							}
							if (item.second->node_content.value_as_string == "Medium")
							{
								font.lfWeight = FW_MEDIUM;
							}
							if (item.second->node_content.value_as_string == "Bold")
							{
								font.lfWeight = FW_BOLD;
							}

							menu->SetFontStyle(font);
						}
						if (item.second->node_name == "TextHeight")
						{
							menu->SetTextHeight(item.second->node_content.value_as_number);
						}

						if (item.second->node_name == "Child")
						{
							for (auto& child : item.second->child_object)
							{
								DrawXmlNode(child.second, menu, temp_object);
							}
						}
					}

					if (node->IsProperty("Visible") == true)
					{
						if (node->propertys["Visible"].value_as_boolean == false)
						{
							menu->Hide();
							menu->LockStatus(true);
						}
					}

					if (xml_parent != nullptr)
					{
						xml_parent->child.insert(std::pair<std::string, XmlObject*>(node->node_name, temp_object));
					}
					else
					{
						objects.insert(std::pair<std::string, XmlObject*>(node->node_name, temp_object));
					}

					temp_object->object = nparnet->GetChild(menu->GetID());
				}
				if (node->propertys["Type"].value_as_string == "Text")
				{
					TextLabel* textlabel = new TextLabel(static_cast<int>((*node)["Width"]->node_content.value_as_number),
						static_cast<int>((*node)["Height"]->node_content.value_as_number), nparnet);

					textlabel->SetParent(nparnet);

					XmlObject* temp_object = new XmlObject;

					temp_object->object = textlabel;

					for (auto& item : node->child_object)
					{
						if (item.second->node_name == "PlaneText")
						{
							textlabel->SetPlaneText(codecv(item.second->node_content.value_as_string.c_str()));
						}
						if (item.second->node_name == "PositionX")
						{
							textlabel->Move(item.second->node_content.value_as_number, textlabel->GetY());
						}
						if (item.second->node_name == "PositionY")
						{
							textlabel->Move(textlabel->GetX(), item.second->node_content.value_as_number);
						}
						if (item.second->node_name == "TextColor")
						{
							textlabel->SetTextColor(item.second->node_content.value_as_number);
						}
						if (item.second->node_name == "TextType")
						{
							LOGFONT font;

							gettextstyle(&font);

							if (item.second->node_content.value_as_string == "Thin")
							{
								font.lfWeight = FW_THIN;
							}
							if (item.second->node_content.value_as_string == "Regular")
							{
								font.lfWeight = FW_REGULAR;
							}
							if (item.second->node_content.value_as_string == "Light")
							{
								font.lfWeight = FW_LIGHT;
							}
							if (item.second->node_content.value_as_string == "Medium")
							{
								font.lfWeight = FW_MEDIUM;
							}
							if (item.second->node_content.value_as_string == "Bold")
							{
								font.lfWeight = FW_BOLD;
							}

							textlabel->SetTextStyle(font);
						}
						if (item.second->node_name == "TextHeight")
						{
							textlabel->SetTextHeight(item.second->node_content.value_as_number);
						}
						if (item.second->node_name == "TextCenter")
						{
							textlabel->SetTextCenter(item.second->node_content.value_as_boolean);
						}
						if (item.second->node_name == "TextColor")
						{
							textlabel->SetTextColor(item.second->node_content.value_as_number);
						}

						if (item.second->node_name == "Child")
						{
							for (auto& child : item.second->child_object)
							{
								DrawXmlNode(child.second, textlabel, temp_object);
							}
						}
					}

					if (node->IsProperty("Visible") == true)
					{
						if (node->propertys["Visible"].value_as_boolean == false)
						{
							textlabel->Hide();
							textlabel->LockStatus(true);
						}
					}

					if (xml_parent != nullptr)
					{
						xml_parent->child.insert(std::pair<std::string, XmlObject*>(node->node_name, temp_object));
					}
					else
					{
						objects.insert(std::pair<std::string, XmlObject*>(node->node_name, temp_object));
					}

					temp_object->object = nparnet->GetChild(textlabel->GetID());
				}
				if (node->propertys["Type"].value_as_string == "MaskLabel")
				{
					MaskLabel* textlabel = new MaskLabel(static_cast<int>((*node)["Width"]->node_content.value_as_number),
						static_cast<int>((*node)["Height"]->node_content.value_as_number), 255, nparnet);

					textlabel->SetParent(nparnet);

					XmlObject* temp_object = new XmlObject;

					temp_object->object = textlabel;

					for (auto& item : node->child_object)
					{
						if (item.second->node_name == "PositionX")
						{
							textlabel->Move(item.second->node_content.value_as_number, textlabel->GetY());
						}
						if (item.second->node_name == "PositionY")
						{
							textlabel->Move(textlabel->GetX(), item.second->node_content.value_as_number);
						}
						if (item.second->node_name == "MaskTransparency")
						{
							textlabel->SetTransparency(item.second->node_content.value_as_number);
						}

						if (item.second->node_name == "Child")
						{
							for (auto& child : item.second->child_object)
							{
								DrawXmlNode(child.second, textlabel, temp_object);
							}
						}
					}

					if (node->IsProperty("Visible") == true)
					{
						if (node->propertys["Visible"].value_as_boolean == false)
						{
							textlabel->Hide();
							textlabel->LockStatus(true);
						}
					}

					if (xml_parent != nullptr)
					{
						xml_parent->child.insert(std::pair<std::string, XmlObject*>(node->node_name, temp_object));
					}
					else
					{
						objects.insert(std::pair<std::string, XmlObject*>(node->node_name, temp_object));
					}

					temp_object->object = nparnet->GetChild(textlabel->GetID());
				}
				if (node->propertys["Type"].value_as_string == "ColorSelector")
				{
					ColorSelector* selector = new ColorSelector(nparnet);

					XmlObject* temp_object = new XmlObject;

					temp_object->object    = selector;

					for (auto& item : node->child_object)
					{
						if (item.second->node_name == "PositionX")
						{
							selector->Move(item.second->node_content.value_as_number, selector->GetY());
						}
						if (item.second->node_name == "PositionY")
						{
							selector->Move(selector->GetX(), item.second->node_content.value_as_number);
						}

						if (item.second->node_name == "Child")
						{
							for (auto& child : item.second->child_object)
							{
								DrawXmlNode(child.second, selector, temp_object);
							}
						}
					}

					if (node->IsProperty("Visible") == true)
					{
						if (node->propertys["Visible"].value_as_boolean == false)
						{
							selector->Hide();
							selector->LockStatus(true);
						}
					}

					if (xml_parent != nullptr)
					{
						xml_parent->child.insert(std::pair<std::string, XmlObject*>(node->node_name, temp_object));
					}
					else
					{
						objects.insert(std::pair<std::string, XmlObject*>(node->node_name, temp_object));
					}
				}
			}

		public:
			XmlWidget(int width = 0, int height = 0, std::string xml_build = "")
			{
				is_invisble = true;

				XmlParser parser(xml_build);

				widget = new Widget(width, height);

				widget->Show();

				node   = parser.Parse();

				PDraw();
			}

			void Move(int x, int y)
			{
				widget->Move(x, y);
			}
			void Draw()
			{
				widget->Draw();

				auto temp_node = node.ToNode();

				DrawXmlNode(&temp_node, widget, nullptr);
			}

		public:
			void    SetXml(std::string xml)
			{
				XmlParser parser(xml);

				node = parser.Parse();

				objects.clear();

				PDraw();
			}
			XmlObject* GetElementById(std::string id)
			{
				return objects[id];
			}
			XmlObject* operator[](std::string id)
			{
				return objects[id];
			}

			void    PushFunctional(std::function<void()> function, std::string name)
			{
				slots.erase(name);
				slots.insert(std::pair<std::string, std::function<void()> >(name, function));
			}

			Widget* GetWidget()
			{
				return widget;
			}

		public:
			virtual int exec()
			{
				return widget->exec();
			}
		};
		class XmlHotview : 
			public XmlWidget
		{
		public:
			XmlHotview(int width, int height, std::string xml_build)
			{
				XmlParser parser(xml_build);

				widget = new Widget(width, height);
				node = parser.Parse();

				PDraw();
			}

			int exec()
			{
				ExMessage message;

				std::fstream stream("./test.pml");

				while (true)
				{
					while (peekmessage(&message))
					{
						ProcessMessage(message);

						FlushBatchDraw();
					}

					Sleep(20);

					std::string  line;
					std::string  allc;

					allc.clear();

					stream.seekg(0);

					while (!stream.eof())
					{
						std::getline(stream, line);

						allc += line + "\n";

						line.clear();
					}

					SetXml(allc);

					FlushBatchDraw();
				}

				stream.close();

				return 0;
			}
		};
	}
}
