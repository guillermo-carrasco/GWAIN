#include "TextureManager.h"


CTextureManager* CTextureManager::m_pInstance = 0;

CTextureManager::CTextureManager(){
	m_mTextures.empty();
}


CTextureManager::~CTextureManager(){
}

CTextureManager* CTextureManager::pGetInstance() {
	if (m_pInstance == 0) {
		m_pInstance = new CTextureManager();
	}
	return m_pInstance;
}


GLuint CTextureManager::Load(char *filename,int type,int wraps,int wrapt,int magf,int minf,bool mipmap){
	corona::Image* img;
	int components;

	img = corona::OpenImage(filename);
	if(type==GL_RGB)
	{
		//img = corona::OpenImage(filename,corona::PF_R8G8B8);
		components = 3;
	}
	else if(type==GL_RGBA)
	{
		//img = corona::OpenImage(filename,corona::PF_R8G8B8A8);
		components = 4;
	}
	else return -1;

	if(img==NULL) return -1;

	int width  = img->getWidth();
	int height = img->getHeight();

	GLuint id;
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D,id);

	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,wraps);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,wrapt);

	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,magf);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,minf);

	if(!mipmap){
		glTexImage2D(GL_TEXTURE_2D,0,components,width,height,0,type,
					 GL_UNSIGNED_BYTE,img->getPixels());
	}

	else{
		gluBuild2DMipmaps(GL_TEXTURE_2D,components,width,height,type,
						  GL_UNSIGNED_BYTE,img->getPixels());
	}

	return id;
}


GLuint CTextureManager::loadTexture(std::string _filename)
{
	std::map<std::string,GLuint>::iterator iter = m_mTextures.find(_filename);

	// La textura ya está cargada, así que devolvemos su ID
	if(iter != m_mTextures.end()) return iter->second;

	// La ruta donde iremos a buscar todas las texturas es ../../data/
	std::string sRuta = std::string("./data/textures/") + _filename + std::string(".png");
	GLuint uiID = Load((char*)sRuta.c_str());

	// preparamos la estructura y la insertamos
	m_mTextures[_filename] = uiID;
	return uiID;
}


void CTextureManager::deleteTexture(std::string filename)
{
	if(m_mTextures.find(filename) != m_mTextures.end())
	{
		GLuint uiID = m_mTextures[filename];
		glDeleteTextures(1,&uiID);
		m_mTextures.erase(filename);
	}
} 

unsigned int CTextureManager::uiNumOfTextures()
{
    return (unsigned int)m_mTextures.size();
}
