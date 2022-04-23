#pragma once
#pragma warning(disable: 26812)
#pragma warning(disable: 26451)

#include "pe.ui.object.hpp"

namespace PDotE
{
	namespace UI
	{
		enum AnimationType
		{
			FadeIn, FadeOut, FadeMove, DecelerateInterpolator
		};

		class Animation
		{
		private:
			AnimationType type;

			Object*		  animation_object;

		private:
			double		  delta_x = 0.01;
			double        x       = 0;

			int			  target_x = 0;
			int			  target_y = 0;

		private:
			double GetOneFrame()
			{
				if (AnimationEnd() == true)
				{
					if (type == FadeOut)
					{
						double result = pow(x, 2);

						x += delta_x;

						return result;
					}
					if (type == FadeIn)
					{
						double result = (x - 1) * (x - 1) * ((2 + 1) * (x - 1) + 2) + 1;

						x += delta_x;

						return result;
					}
					if (type == FadeMove)
					{
						double result = (cos((x + 1) * 3.1415) / 2.0) + 0.5;

						x += delta_x;

						return result;
					}
					if (type == DecelerateInterpolator)
					{
						double result = 1.0 - pow((1.0 - x), 2 * 1);

						x += delta_x;

						return result;
					}
				}

				return 0;
			}

			bool   AnimationEnd()
			{
				return (x <= 1);
			}

		public:
			Animation(Object* bind_object, AnimationType ntype, unsigned int time = 100)
			{
				type = ntype;

				animation_object = bind_object;

				delta_x = 1 / (double)time;
			}

		public:
			void SetAnimationType(AnimationType ntype)
			{
				type = ntype;
			}
			void SetTargetPosition(int nx, int ny)
			{
				target_x = nx;
				target_y = ny;
			}

		public:
			void Play()
			{
				double one_frame;

				int mX;
				int mY;
				int nX;
				int nY;

				mX = target_x;
				nX = animation_object->GetX();
				mY = target_y;
				nY = animation_object->GetY();

				while (AnimationEnd())
				{
					one_frame = GetOneFrame();

					animation_object->Move(nX + (mX - nX) * one_frame, nY + (mY - nY) * one_frame);

					FlushBatchDraw();

					Sleep(1);
				}
			}
		};
		class GrowAnimation
		{
		private:
			AnimationType type;

			Object* animation_object;

		private:
			double		  delta_x = 0.01;
			double        x = 0;

			int			  target_width  = 0;
			int			  target_height = 0;

			int			  target_x		= 0;
			int			  target_y		= 0;


		private:
			double GetOneFrame()
			{
				if (AnimationEnd() == true)
				{
					if (type == FadeOut)
					{
						double result = pow(x, 2);

						x += delta_x;

						return result;
					}
					if (type == FadeIn)
					{
						double result = (x - 1) * (x - 1) * ((2 + 1) * (x - 1) + 2) + 1;

						x += delta_x;

						return result;
					}
					if (type == FadeMove)
					{
						double result = (cos((x + 1) * 3.1415) / 2.0) + 0.5;

						x += delta_x;

						return result;
					}
					if (type == DecelerateInterpolator)
					{
						double result = 1.0 - pow((1.0 - x), 2 * 1);

						x += delta_x;

						return result;
					}
				}

				return 0;
			}

			bool   AnimationEnd()
			{
				return (x <= 1);
			}

		public:
			GrowAnimation(Object* bind_object, AnimationType ntype, unsigned int time = 100)
			{
				type = ntype;

				animation_object = bind_object;

				delta_x = 1 / (double)time;
			}

		public:
			void SetAnimationType(AnimationType ntype)
			{
				type = ntype;
			}
			void SetTargetGeomtery(int nx, int ny)
			{
				target_width = nx;
				target_height = ny;
			}

		public:
			void Play()
			{
				double one_frame;

				while (AnimationEnd())
				{
					one_frame = GetOneFrame();

					animation_object->Resize(animation_object->GetWidth() + (target_width - animation_object->GetWidth()) * one_frame,
						animation_object->GetHeight() + (target_height - animation_object->GetHeight()) * one_frame);

					FlushBatchDraw();

					Sleep(1);
				}
			}
		};
	}
}
