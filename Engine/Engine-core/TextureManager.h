//**********************************************
//Singleton Texture Manager class
//Written by Ben English
//benjamin.english@oit.edu
//
//For use with OpenGL and the FreeImage library
//**********************************************

#ifndef TextureManager_H
#define TextureManager_H

#include <windows.h>
#include <GL/glew.h>
#include "FreeImage.h"
#include <map>
#include "Vec2.h"
#include "freetype-gl.h"
using namespace Engine;
using namespace Math;
using namespace ftgl;
class TextureManager
{
public:
	static TextureManager* Inst();
	std::map<unsigned int, GLuint> m_texID;

	std::map<std::string ,Vec2f> textures;
	texture_atlas_t* m_textureAtlas;
	texture_atlas_t* m_fontAtlas;

	int atlas_width = 0;
	int atlas_height = 0;
	virtual ~TextureManager();

	//load a texture an make it the current texture
	//if texID is already in use, it will be unloaded and replaced with this texture
	bool LoadTexture(const char* filename,	//where to load the file from
		const unsigned int texID,			//arbitrary id you will reference the texture by
		int& width, int& height,									//does not have to be generated with glGenTextures
		GLenum image_format = GL_BGRA,		//format the image is in
		GLint internal_format = GL_RGBA,		//format to store the image in
		GLint level = 0,					//mipmapping level
		GLint border = 0 );					//border size
	int LoadTexture(const char* filename, int& width, int& height);
	bool AddTexture(const char* filename, int& width, int& height);

	//free the memory for a texture
	bool UnloadTexture(const unsigned int texID);

	//set the current texture
	void BindTextures();
	void UnBindTextures();

	//free all texture memory
	void UnloadAllTextures();
	const int generateId()
	{
		 return ids++;
	}
	bool CreateTextureAtlas();
	ftgl::texture_font_t* LoadFont(const char* filename);

protected:
	TextureManager();
	TextureManager(const TextureManager& tm);
	TextureManager& operator=(const TextureManager& tm);

	static TextureManager* m_inst;
	int ids = 0;
	
	
};

#endif