#pragma once
#pragma comment(lib,"corona")

#include "Globals.h"
#include <corona.h>
#include <map>
#include <string>


class CTextureManager {
	public:
		~CTextureManager(void);

		static CTextureManager* pGetInstance();

		GLuint       loadTexture(std::string _sFilename);
		void         deleteTexture(std::string _sFilename);
		unsigned int uiNumOfTextures();

	private:
		CTextureManager(void);
		GLuint Load(char *filename,int type = GL_RGBA,int wraps = GL_REPEAT,int wrapt = GL_REPEAT,
				  int magf = GL_NEAREST,int minf = GL_NEAREST,bool mipmap = false);

		static CTextureManager* m_pInstance;
		std::map<std::string, GLuint> m_mTextures;

};
