#pragma once

std::wstring FixPathSeparators(std::wstring name);

std::vector<uint8_t> ReadFile(std::wstring name);

std::wstring GetClipboardContents();