#pragma once
#pragma warning(disable : 26812)

#include <graphics.h>
#include <string>

namespace PDotE
{
	IMAGE GetIcon(std::wstring icon_name)
	{
		IMAGE result;

		loadimage(&result, (L"./PDotE/UIResource/Icon/" + icon_name + L".png").c_str());

		return result;
	}

	enum FontType
	{
		BOLD, MEDIUM, THIN, LIGHT, REGULAR
	};

	LOGFONT GetFont(FontType type)
	{
		LOGFONT result;

		gettextstyle(&result);
		
		result.lfQuality = PROOF_QUALITY;
		
		if (type == BOLD)
		{
			_tcscpy_s(result.lfFaceName, L"Î¢ÈíÑÅºÚ Light");

			result.lfWeight = FW_BOLD;
		}
		if (type == REGULAR)
		{
			_tcscpy_s(result.lfFaceName, L"Î¢ÈíÑÅºÚ Light");

			result.lfWeight = FW_REGULAR;
		}
		if (type == LIGHT)
		{
			_tcscpy_s(result.lfFaceName, L"Î¢ÈíÑÅºÚ Light");

			result.lfWeight = FW_LIGHT;
		}
		if (type == MEDIUM)
		{
			_tcscpy_s(result.lfFaceName, L"Î¢ÈíÑÅºÚ Light");

			result.lfWeight = FW_MEDIUM;
		}
		if (type == THIN)
		{
			_tcscpy_s(result.lfFaceName, L"Î¢ÈíÑÅºÚ Light");

			result.lfWeight = FW_THIN;
		}

		return result;
	}
	IMAGE   GetUIImage(std::wstring surface_name, std::wstring source_name)
	{
		IMAGE result;

		loadimage(&result, (L"./PDotE/UIResource/" + surface_name + L"/" + source_name).c_str());

		return result;
	}
}