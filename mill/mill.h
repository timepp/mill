#pragma once

#include <vector>
#include <string>

typedef std::vector<std::wstring> strlist_t;

__interface SuggestionProvider
{
	std::vector<std::wstring> GetSuggestion(const std::wstring& input);
};
