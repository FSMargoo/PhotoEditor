#pragma once

#include "pe.ui.xml.ui.hpp"
#include "pe.app.messagebox.hpp"
#include "pe.app.mainui.hpp"

#include "pe.app.data.hpp"

#include <direct.h>
#include <io.h>
#include <fstream>

namespace PDotE
{
	namespace AppStart
	{
		class Start
		{
		private:
			UI::XmlWidget* parent;

			AppMainUI::MainUI* ui = nullptr;

			char work_space[MAX_PATH]{ 0 };

		private:
			std::string ReadStartXml()
			{
				return File::ReadUTF8File("./PDotE/XML/startup.xml");
			}

			bool CreateProjectBackdoor(AppMainUI::ProjectFile& project_file)
			{
			select:
				_getcwd(work_space, MAX_PATH);

				_chdir(work_space);

				OPENFILENAME* file = new OPENFILENAME { 0 };
				TCHAR file_path[MAX_PATH];

				file->lStructSize = sizeof(OPENFILENAME);

				file->hwndOwner = GetHWnd();
				file->lpstrFile = file_path;
				file->lpstrFile[0] = '\0';

				file->nMaxFile = sizeof(file_path);

				file->lpstrFilter = L"All(*.*)\0*.*\0";
				file->nFilterIndex = 1;
				file->lpstrFileTitle = NULL;
				file->nMaxFileTitle = 0;
				file->Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

				if (GetSaveFileName(file))
				{
					_chdir(work_space);

					if (_waccess(file_path, 0) == 0 &&
						_waccess(file_path, 2) == 0)
					{
						if (_waccess(file_path, 4) == 0)
						{
							project_file.read_only_mode = false;
							project_file.file_path	    = file_path;

							_chdir(work_space);

							return true;
						}
						else
						{
							_chdir(work_space);

							AppMessageBox::InfoMessage assert_box;

							if (assert_box(parent, L"提示", L"权限不足，无法读取该文件，是否以只读模式打开？") == 1)
							{
								project_file.read_only_mode = true;
								project_file.file_path      = file_path;

								_chdir(work_space);

								return true;
							}
							else
							{
								return false;
							}
						}
					}
					else
					{
						AppMessageBox::AssertMessage assert_box;

						assert_box(parent, L"错误", L"文件不存在或权限不足无法读取！尝试管理员运行！");

						_chdir(work_space);

						return false;
					}
				}
				else
				{
					AppMessageBox::AssertMessage assert_box;

					if (assert_box(parent->GetWidget(), L"错误", L"请选择一个文件") == 0)
					{
						_chdir(work_space);

						return false;
					}

					_chdir(work_space);

					goto select;
				}

				return false;
			}
			void CreateProject()
			{
				AppMainUI::ProjectFile file;

				if (CreateProjectBackdoor(file) == true)
				{
					_chdir(work_space);

					ui = new AppMainUI::MainUI(file, parent);

					parent->GetWidget()->ClearAllChild();

					ui->InitMainUI();
					ui->exec();
				}
				else
				{
					return;
				}
			}

		public:
			Start(UI::XmlWidget* nparent)
			{
				AddFontResource(L"./ODotE/UIResource/Font/Bold.ttf");
				AddFontResource(L"./ODotE/UIResource/Font/Light.ttf");
				AddFontResource(L"./ODotE/UIResource/Font/Medium.ttf");
				AddFontResource(L"./ODotE/UIResource/Font/Regular.ttf");
				AddFontResource(L"./ODotE/UIResource/Font/Thin.ttf");

				auto font = GetFont(REGULAR);

				InitStartUI(nparent);

				RemoveFontResource(L"./ODotE/UIResource/Font/Bold.ttf");
				RemoveFontResource(L"./ODotE/UIResource/Font/Light.ttf");
				RemoveFontResource(L"./ODotE/UIResource/Font/Medium.ttf");
				RemoveFontResource(L"./ODotE/UIResource/Font/Regular.ttf");
				RemoveFontResource(L"./ODotE/UIResource/Font/Thin.ttf");
			}

			void InitStartUI(UI::XmlWidget* nparent)
			{
				Data::start_xml = ReadStartXml();
				Data::main_ui_xml = File::ReadUTF8File("./PDotE/XML/main.xml");

				nparent->PushFunctional(std::bind(&Start::CreateProject, this), "CreateProject");

				nparent->SetXml(Data::start_xml);

				nparent->GetWidget()->SetFontStyle(GetFont(REGULAR));

				parent = nparent;

			}
		};
	}
}