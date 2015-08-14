#include "Texture.h"
#include "UnityPluginInterface.h"

#if SUPPORT_D3D9
	#include <d3d9.h>
#endif
#if SUPPORT_D3D11
	#include <d3d11.h>
#endif
#if SUPPORT_OPENGL
	#if UNITY_WIN || UNITY_LINUX
		#include <GL/gl.h>
	#else
		#include <OpenGL/OpenGL.h>
	#endif
#endif


Texture::Texture () {
	m_TextureID = -1;
	m_Width = -1;
	m_Height = -1;
	m_Format = RGB;
}

void Texture::SetTexture (int textureID, int width, int height) {
	m_TextureID = textureID;
	m_Width = width;
	m_Height = height;
}

void Texture::SetTexture (int textureID, int width, int height, int format) {
	SetTexture(textureID, width, height);
	switch (format) {
		case 0:
			m_Format = RGB;
			break;
		case 1:
			m_Format = RGBA;
			break;
		default:
			m_Format = RGB;
	}
}

void Texture::FillTexture (int dataLen, char* data) {
	if(m_TextureID == -1)
		return;

	#if SUPPORT_OPENGL

	glDisable (GL_CULL_FACE);
	glDisable (GL_LIGHTING);
	glDisable (GL_BLEND);
	glDisable (GL_ALPHA_TEST);
	glDepthFunc (GL_LEQUAL);
	glEnable (GL_DEPTH_TEST);
	glDepthMask (GL_FALSE);;

	glBindTexture (GL_TEXTURE_2D, m_TextureID);
	glTexSubImage2D (GL_TEXTURE_2D, 0, 0, 0, m_Width, m_Height, GL_RGB, GL_UNSIGNED_BYTE, &data[0]);

	#endif
}

