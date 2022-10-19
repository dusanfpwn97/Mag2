#pragma once
#include <string>
#include <vector>

namespace efe
{
	class IOManager
	{
	public:
		static bool readFileToBuffer(std::string filePath, std::vector<unsigned char>& buffer);
	};
}