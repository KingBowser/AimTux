#pragma once

#include <string>
#include "SDK/SDK.h"
#include "interfaces.h"

namespace Util {
	char GetButtonString(ButtonCode_t key);
	char GetUpperValueOf(ButtonCode_t key);
	std::string ReplaceString(std::string subject, const std::string& search, const std::string& replace);
	template<typename ST> void StdReplaceStr(ST&, const ST&, const ST&);
}
