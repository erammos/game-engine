#include "Texture.h"

Engine::Graphics::Texture::Texture(const char* path)
{
	BYTE* data = load(path);

	glGenTextures(1, &m_TID);
	bind();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height,
		0, GL_RGB, GL_UNSIGNED_BYTE, data);
	unbind();
}

Engine::Graphics::Texture::~Texture()
{
}

void Engine::Graphics::Texture::bind() const
{
	glBindTexture(GL_TEXTURE_2D, m_TID);
}

void Engine::Graphics::Texture::unbind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

BYTE* Engine::Graphics::Texture::load(const char* filename)
{
	// image format
		FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
	//pointer to the image, once loaded
	FIBITMAP *dib(0);
	//pointer to the image data
	BYTE* bits(0);
	//image width and height
	
	//OpenGL's image ID to map to

	//check the file signature and deduce its format
	fif = FreeImage_GetFileType(filename, 0);
	//if still unknown, try to guess the file format from the file extension
	if (fif == FIF_UNKNOWN)
		fif = FreeImage_GetFIFFromFilename(filename);
	//if still unkown, return failure
	if (fif == FIF_UNKNOWN)
		return NULL;

	//check that the plugin has reading capabilities and load the file
	if (FreeImage_FIFSupportsReading(fif))
		dib = FreeImage_Load(fif, filename);
	//if the image failed to load, return failure
	if (!dib)
		return NULL;

	//retrieve the image data
	bits = FreeImage_GetBits(dib);
	//get the image width and height
	width = FreeImage_GetWidth(dib);
	height = FreeImage_GetHeight(dib);
	return bits;
}
