#pragma once

#include <Windows.h>

void CreatePorject()
{
select:
	OPENFILENAME openfiler		= { 0 };
	TCHAR strFilename[MAX_PATH] = { 0 };

	openfiler.lStructSize	  = sizeof(OPENFILENAME);
	openfiler.hwndOwner	      = NULL;
	openfiler.lpstrFilter     = TEXT("�����ļ�\0*.*\0\0");
	openfiler.nFilterIndex    = 1;
	openfiler.lpstrFile       = strFilename;
	openfiler.nMaxFile        = sizeof(strFilename);
	openfiler.lpstrInitialDir = NULL;
	openfiler.lpstrTitle      = TEXT("�½���Ŀ");
	openfiler.Flags			  = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY;

	if (GetOpenFileName(&openfiler))
	{
		
	}
	else 
	{
		MessageBox(NULL, TEXT("��ѡ��һ���ļ���"), NULL, MB_ICONERROR);
		goto select;
	}
}