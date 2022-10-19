#pragma once
#include "GLTexture.h"
#include <string>

namespace efe
{
	class ImageLoader
	{
	public:
		static GLTexture loadPNG(std::string filePath);
	};

}