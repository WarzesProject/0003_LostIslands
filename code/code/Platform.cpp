// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "stdafx.h"
#include "Platform.h"
#include "Log.h"
#include "Encoding.h"

//-----------------------------------------------------------------------------
std::wstring FixPathSeparators(std::wstring name)
{
#if defined(_WIN32)
	for (auto& c : name)
		if (c == L'/')
			c = L'\\';
#endif
	return std::move(name);
}
//-----------------------------------------------------------------------------
std::vector<uint8_t> ReadFile(std::wstring name)
{
	name = FixPathSeparators(std::move(name));
#if defined(_MSC_VER)
	std::ifstream file{ name, std::ios_base::in | std::ios_base::binary };
#else
	std::ifstream file{ UTF8Encoding().Convert(name), std::ios_base::in | std::ios_base::binary };
#endif
	if (file.fail())
		throw std::runtime_error("file \"" + UTF8Encoding().Convert(name) + "\" cannot be opened");

	file.seekg(0, std::ios_base::end);
	size_t size = file.tellg();
	file.seekg(0, std::ios_base::beg);
	std::vector<uint8_t> result(size);
	file.read((char*)&result[0], size);

	LOG(Debug, "Loaded resource from '" << name << "' (" << size << " bytes)");
	return std::move(result);
}
//-----------------------------------------------------------------------------
std::wstring GetClipboardContents()
{
#if defined(_WIN32)
	//if (!OpenClipboard(NULL))
	//{
	//	LOG(Error, "Failed to open clipboard");
	//	return L"";
	//}

	std::wstring text;
	//if (HGLOBAL handle = GetClipboardData(CF_UNICODETEXT))
	//{
	//	if (auto ptr = (const wchar_t*)GlobalLock(handle))
	//	{
	//		text = ptr;
	//		GlobalUnlock(handle);
	//	}
	//}

	//CloseClipboard();
	return text;
#else
	// XXX: Another refactoring is imminent.
	return g_instance ? g_instance->GetClipboard() : std::wstring{};
#endif
}