#pragma once

#include <fstream>
#include <codecvt>
#include <comdef.h>
#include <string>

namespace PDotE
{
	namespace File
	{
		// Unicode 转换为 ANSI 编码
		std::string UnicodeToUTF8(const std::wstring& src)
		{
			std::string dst;
			int len = WideCharToMultiByte(CP_UTF8, 0, src.c_str(), -1, NULL, 0, NULL, NULL);		// 获取转换后的长度（包括结尾 \0）
			dst.resize(len);																		// 调整 dst 容量
			WideCharToMultiByte(CP_ACP, 0, src.c_str(), -1, &dst[0], (int)dst.size(), NULL, NULL);	// 转换
			return  dst;
		}

		std::string ReadUTF8File(std::string path)
		{
			std::ifstream stream;

			// Set exceptions to be thrown on failure
			stream.exceptions(std::ifstream::failbit | std::ifstream::badbit);

			try {
				stream.open(path);
			}
			catch (std::system_error& e) {
				return e.code().message();
			}
			std::wstring_convert<std::codecvt_utf8<wchar_t>> convert;

			std::string line;
			std::string all;

			while (!stream.eof())
			{
				std::getline(stream, line);

				all += line + "\n";
			}

			stream.close();

			std::wstring temp_string = convert.from_bytes(all);
			_bstr_t convert_string   = temp_string.c_str();
			std::string result       = (char*)convert_string;

			return result;
		}
	}
}