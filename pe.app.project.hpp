#pragma once

#include <Windows.h>

void CreatePorject()
{
select:
	OPENFILENAME openfiler		= { 0 };
	TCHAR strFilename[MAX_PATH] = { 0 };

	openfiler.lStructSize	  = sizeof(OPENFILENAME);
	openfiler.hwndOwner	      = NULL;
	openfiler.lpstrFilter     = TEXT("所有文件\0*.*\0\0");
	openfiler.nFilterIndex    = 1;
	openfiler.lpstrFile       = strFilename;
	openfiler.nMaxFile        = sizeof(strFilename);
	openfiler.lpstrInitialDir = NULL;
	openfiler.lpstrTitle      = TEXT("新建项目");
	openfiler.Flags			  = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY;

	if (GetOpenFileName(&openfiler))
	{
		
	}
	else 
	{
		MessageBox(NULL, TEXT("请选择一个文件！"), NULL, MB_ICONERROR);
		goto select;
	}
}