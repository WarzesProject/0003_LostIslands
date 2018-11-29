#pragma once

class Log
{
public:
	enum class Level { Fatal, Error, Warning, Info, Debug, Trace };
	enum class Mode { Truncate, Append };

	void Write(Level level, const std::wstring &what);
	
	static Log& Instance();

	Level level = Level::Trace;
	Mode mode = Mode::Truncate;

private:
	Log() = default;
	bool m_truncated;
};

std::wostream& operator<<(std::wostream &stream, Log::Level value);
std::wostream& operator<<(std::wostream &stream, Log::Mode value);

#define LOG(level_, what)\
	do\
	{\
		if (Log::Level::level_ <= Log::Instance().level)\
		{\
			std::wostringstream wss_;\
			wss_ << what;\
			Log::Instance().Write(Log::Level::level_, wss_.str());\
		}\
	}\
	while (0)