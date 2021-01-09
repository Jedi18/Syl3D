#pragma once

#include <string>
#include <vector>
#include <filesystem>

namespace utility
{
	class FileIO
	{
	public:
		static std::vector<std::string> filesInPath(const std::string& path);
	};
}

