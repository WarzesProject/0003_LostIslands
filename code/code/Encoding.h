#pragma once

template<typename CharT> struct Encoding
{
	virtual ~Encoding() { }
	virtual wchar_t Convert(int value) const = 0;
	virtual int Convert(wchar_t value) const = 0;
	virtual std::wstring Convert(const std::basic_string<CharT>& value) const = 0;
	virtual std::basic_string<CharT> Convert(const std::wstring& value) const = 0;
	virtual std::wstring GetName() const = 0;
	bool operator==(const Encoding& another) const { return GetName() == another.GetName(); }
	bool operator!=(const Encoding& another) const { return GetName() != another.GetName(); }
};

typedef Encoding<char> Encoding8;
typedef Encoding<char16_t> Encoding16;
typedef Encoding<char32_t> Encoding32;

std::unique_ptr<Encoding8> GetUnibyteEncoding(const std::wstring& name);

struct UTF8Encoding : Encoding8
{
	wchar_t Convert(int value) const;
	int Convert(wchar_t value) const;
	std::wstring Convert(const std::string& value) const;
	std::string Convert(const std::wstring& value) const;
	std::wstring GetName() const;
};

struct UCS2Encoding : Encoding16
{
	wchar_t Convert(int value) const;
	int Convert(wchar_t value) const;
	std::wstring Convert(const std::u16string& value) const;
	std::u16string Convert(const std::wstring& value) const;
	std::wstring GetName() const;
};

struct UCS4Encoding : Encoding32
{
	wchar_t Convert(int value) const;
	int Convert(wchar_t value) const;
	std::wstring Convert(const std::u32string& value) const;
	std::u32string Convert(const std::wstring& value) const;
	std::wstring GetName() const;
};

static const char32_t kUnicodeReplacementCharacter = 0xFFFD;

template<typename T> struct Encodings
{ };

template<> struct Encodings<char>
{
	typedef UTF8Encoding type;
};

template<> struct Encodings<char16_t>
{
	typedef UCS2Encoding type;
};

template<> struct Encodings<char32_t>
{
	typedef UCS4Encoding type;
};