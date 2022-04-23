/////////////////////////////////////////////////////
//    pe.ui.obhect.h:
//		@description : The basic head in UI kits
//		@brith       : 2022/1/24
//
#pragma once

#include "pe.ui.trigger.hpp"

#include <functional>
#include <map>

#ifdef _DEBUG
#	include <time.h>
#endif

namespace PDotE
{
	namespace UI
	{
#define Rectangle		 0
#define RoundedRectangle 1
#define Circle			 2

		class Object : public Trigger
		{
		protected:
			bool batch_mode = false;
			bool redraw     = false;

		protected:
			bool used_to_focus = false;

			bool is_invisble   = true;

			unsigned long child_id  = 0;
			unsigned long parent_id = 0;

			short free_count = 0;

			bool lock_status = false;

		protected:
			LOGFONT  _font;

			std::map<unsigned long, Object*> child_object;

			Object*							 parent = nullptr;

			short radius = 0;

			short geomtery_type = Rectangle;
			IMAGE* object_content;

			// 0 : Normal
			// 1 : On cover
			// 2 : Pushed
			short status = 0;

		public:
			virtual void PDraw(bool callFromParent = false)
			{
				settextstyle(&_font);

				if (is_invisble == false)
				{
					if (parent != nullptr &&
						callFromParent == false)
					{
						parent->PDraw();

						return;
					}

					if (batch_mode == true)
					{
						redraw = true;

						return;
					}

					object_content = new IMAGE(width, height);

					SetWorkingImage();

					if (parent != nullptr)
					{
						SetWorkingImage(parent->object_content);
					}

					getimage(object_content, x, y, width, height);

					SetWorkingImage();

					if (parent == nullptr)
					{
						Draw();

						getimage(object_content, x, y, width, height);
					}
					else
					{
						SetWorkingImage(object_content);

						Draw();

						SetWorkingImage();
					}

					for (auto item = child_object.begin(); item != child_object.end(); ++item)
					{
						item->second->PDraw(true);
					}

					if (parent == nullptr)
					{
						object_content->Resize(width, height);

						SetWorkingImage();

						putimage(x, y, object_content);
					}
					else
					{
						SetWorkingImage(parent->object_content);

						putimage(x, y, object_content);
						
						SetWorkingImage();
					}

					delete object_content;

					object_content = nullptr;
				}
			}

		public:
			virtual void Draw()
			{

			}
			
			void Show()
			{
				is_invisble = false;

				PDraw();
			}
			void Hide()
			{
				is_invisble = true;

				if (parent != nullptr)
				{
					parent->PDraw();
				}
			}

			virtual void Move(int nx, int ny)
			{
				x = nx;
				y = ny;

				PDraw();
			}
			virtual void Resize(int nwidth, int nheight)
			{
				width  = nwidth;
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

		public:
			bool IsVisble()
			{
				return is_invisble;
			}

		public:
			Object(int nwidth = 0, int nheight = 0, Object* nparent = nullptr)
			{
				if (GetHWnd() != NULL)
				{
					gettextstyle(&_font);
				}

				width = nwidth;
				height = nheight;

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

				SetParent(nparent);
			}

		public:
			void SetParent(Object* nparent)
			{
				if (parent != nullptr)
				{
					parent->child_object.erase(parent_id);
					parent->PDraw();
				}

				parent = nparent;

				if (parent != nullptr)
				{
					++nparent->child_id;

					parent_id = nparent->child_id;

					parent->child_object.insert(std::pair<unsigned long long, Object*>
						(parent_id, this));
				}
			}

			Object* GetParent()
			{
				return parent;
			}

		public:
			virtual void LeftButtonOnClicked(ExMessage message)
			{
			}
			virtual void RightButtonOnClicked(ExMessage message)
			{
			}
			virtual void MouseCoverd(ExMessage message)
			{
			}
			virtual void MouseLeft(ExMessage message)
			{
			}

		public:
			virtual void CheckMouseOut(ExMessage message)
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
				}
				else
				{
					message.x -= x;
					message.y -= y;

					for (auto& child : child_object)
					{
						child.second->CheckMouseOut(message);
					}
				}
			}

			virtual bool ProcessMessage(ExMessage message, bool calle_from_parent = false)
			{
				if (is_invisble == true)
				{
					return false;
				}

				if (IsTrigger(message) == true)
				{
					used_to_focus = true;

					message.x -= x;
					message.y -= y;

					bool repaint = false;

					// Idk why , but i wrote this code and the program ran successfully :)
					for (auto item = child_object.rbegin(); item != child_object.rend();
						++item)
					{
						item->second->CheckMouseOut(message);
					}

					for (auto item = child_object.rbegin(); item != child_object.rend();
						++item)
					{
						item->second->SetBatchDraw(false);

						if (item->second->ProcessMessage(message, true) == true)
						{
							if (item->second->redraw == true)
							{
								item->second->redraw = false;

								if (calle_from_parent == false)
								{
									repaint = true;
								}
								else
								{
									redraw = true;
								}
							}

							if (calle_from_parent == false)
							{
								if (repaint == true)
								{
									PDraw();
								}

								FlushBatchDraw();
							}

							return true;
						}
					}

					switch (message.message)
					{
					case WM_LBUTTONDOWN:
					{
						LeftButtonOnClicked(message);

						break;
					}
					case WM_RBUTTONDOWN:
					{
						RightButtonOnClicked(message);

						break;
					}

					default:
					{
						MouseCoverd(message);

						break;
					}
					}

					if (calle_from_parent == false)
					{
						FlushBatchDraw();
					}

					return true;
				}

				if (calle_from_parent == false)
				{
					FlushBatchDraw();
				}

				return false;
			}

		public:
			void SetFontStyle(LOGFONT style, bool calle_from_parent = false)
			{
				int height = _font.lfHeight;

				_font = style;
				_font.lfHeight = height;

				for (auto& item : child_object)
				{
					item.second->SetFontStyle(style, true);
				}

				if (calle_from_parent == false)
				{
					PDraw();
				}
			}
			
		public:
			void ShowOffChild(bool calle_from_parent = false)
			{
				is_invisble = false;

				for (auto& item : child_object)
				{
					if (item.second->lock_status == false)
					{
						item.second->is_invisble = false;

						item.second->ShowOffChild(true);
					}
				}

				if (calle_from_parent == false)
				{
					PDraw();
				}
			}
			void HideOffChild(bool calle_from_parent = false)
			{
				for (auto& item : child_object)
				{
					if (item.second->lock_status == false)
					{
						item.second->is_invisble = true;

						item.second->HideOffChild(true);
					}
				}

				if (calle_from_parent == false)
				{
					PDraw();
				}
			}
			Object* GetChild(int id)
			{
				return child_object[id];
			}

			unsigned long GetID()
			{
				return parent_id;
			}

			void LockStatus(bool nstatus)
			{
				lock_status = nstatus;
			}

			void SetTextHeight(int fheight)
			{
				_font.lfHeight = fheight;

				PDraw();
			}

			void SetBatchDraw(bool value)
			{
				batch_mode = value;
			}
			void SetRedraw(bool value)
			{
				redraw = value;
			}

			void ClearChild()
			{
				child_object.clear();
			}
		};
	}
}
