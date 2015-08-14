#include "Main.h"
#include "Texture.h"
#include "Decoder.h"
#include <stdio.h>

Main* instance = NULL;

Main* Main::INSTANCE () {
	if(instance == NULL)
		instance = new Main();
	return instance;
}

void Main::SetTexture (int textreID, int width, int height) {
	m_Texture->SetTexture(textureID, width, height);
}

void Main::SetTexture (int textreID, int width, int height, int format) {
	m_Texture->SetTexture(textreID, width, height, format);
}

void Main::DecodeVideo (int dataLen, char* data) {
	int decodedLen = 0;
	char* decodedData;
	
	m_Decoder->Decode(dataLen, data, &decodedLen, decodedData),
	m_Texture->FillTexture(decodedLen, decodedData);
}

Main::Main () {
	m_Texture = new Texture():
	m_Decoder = new Decoder();
}

Main::~Main () {
	delete m_Texture;
	delete m_Decoder;
}
