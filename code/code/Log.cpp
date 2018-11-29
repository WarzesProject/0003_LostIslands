// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "stdafx.h"
#include "Log.h"

//-----------------------------------------------------------------------------
Log& Log::Instance()
{
	static Log instance;
	return instance;
}
//-----------------------------------------------------------------------------
void Log::Write(Level level, const std::wstring &what)
{
	std::wostringstream ss;
	ss << " [" << level << "] " << what << std::endl;
	std::wcout << ss.str() << std::endl;
#if _WIN32
	OutputDebugString((ss.str() + L"\n").c_str());
#endif
}
//-----------------------------------------------------------------------------
std::wostream& operator<<(std::wostream &s, Log::Level value)
{
	switch (value)
	{
	case Log::Level::Fatal:
		s << L"fatal";
		break;
	case Log::Level::Error:
		s << L"error";
		break;
	case Log::Level::Warning:
		s << L"warning";
		break;
	case Log::Level::Info:
		s << L"info";
		break;
	case Log::Level::Debug:
		s << L"debug";
		break;
	case Log::Level::Trace:
		s << L"trace";
		break;
	}

	return s;
}
//-----------------------------------------------------------------------------
std::wostream& operator<< (std::wostream& s, Log::Mode value)
{
	switch (value)
	{
	case Log::Mode::Truncate:
		s << L"truncate";
		break;
	case Log::Mode::Append:
		s << L"append";
		break;
	}

	return s;
}
//-----------------------------------------------------------------------------