#pragma once

#include "pe.ui.textlabel.hpp"

namespace PDotE
{
	namespace UI
	{
		class ImageLabel : public Object
		{
		private:
			bool shadow = false;

			IMAGE* image = nullptr;

		public:
			ImageLabel(int nwidth, int nheight, IMAGE* nimage, bool nshadow = false, Object* nparent = nullptr)
			{
				if (nimage != nullptr)
				{
					image = new IMAGE(nimage->getwidth(), nimage->getheight());

					*image = *nimage;
				}
				width  = nwidth;
				height = nheight;

				shadow = nshadow;

				parent = nparent;


				if (shadow == true)
				{
					width += 30;
					height += 30;

					x -= 30;
					y -= 30;
				}

				SetParent(parent);

				if (image != nullptr)
				{
					CreateAlphaImageMask(image);
				}
			}

			void Draw()
			{
				if (shadow == false)
				{
					putimage(image, 0, 0, width, height);
				}
				else
				{
					drawRoundedRectangleShadow(0, 0, width, height, 8);

					putimage(image, 15, 15, width - 30, height - 30);
				}
			}

			void Move(int nx, int ny)
			{
				x = nx;
				y = ny;

				if (shadow == true)
				{
					x -= 30;
					y -= 30;
				}

				PDraw();
			}

			void Resize(int nwidth, int nheight)
			{
				if (shadow == false)
				{
					width = nwidth;
					height = nheight;
				}
				else
				{
					width = nwidth;
					height = nheight;

					width += 30;
					height += 30;
				}

				PDraw();

				if (shadow == true)
				{
					image->Resize(width - 30, height - 30);
				}
				else
				{
					image->Resize(width, height);
				}

				CreateAlphaImageMask(image);
			}

		public:
			void SetImage(IMAGE* nimage)
			{
				if (image != nullptr)
				{
					if (ImageEmptyPtr(image) == true)
					{
						delete image;
					}
				}

				if (nimage != nullptr)
				{
					image = new IMAGE(nimage->getwidth(), nimage->getheight());

					*image = *nimage;
					
					if (shadow == true)
					{
						image->Resize(width - 30, height - 30);
					}
					else
					{
						image->Resize(width, height);
					}
					
					CreateAlphaImageMask(image);

					PDraw();
				}
				else
				{
					image = nullptr;
				}
			}
			void SetImage(IMAGE nimage)
			{
				if (image != nullptr)
				{
					if (ImageEmptyPtr(image) == true)
					{
						delete image;
					}
				}

				image = new IMAGE(nimage.getwidth(), nimage.getheight());

				*image = nimage;

				if (shadow == true)
				{
					image->Resize(width - 30, height - 30);
				}
				else
				{
					image->Resize(width, height);
				}

				CreateAlphaImageMask(image);

				PDraw();
			}

			void SetShadow(bool nshadow)
			{
				shadow = nshadow;

				PDraw();
			}
		};
	}
}
