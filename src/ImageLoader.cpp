#include "pch.h"
#include "ImageLoader.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

unsigned char* ImageLoader::Load(char const* filename, int* x, int* y, int* comp, const int req_comp)
{
	return stbi_load(filename, x, y, comp, req_comp);
}

void ImageLoader::FlipVerticalOnLoad(const bool flagTrueIfShouldFlip)
{
	stbi_set_flip_vertically_on_load(flagTrueIfShouldFlip);
}

void ImageLoader::ImageFree(void* free)
{
	stbi_image_free(free);
}
