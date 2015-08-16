#include "Main.h"
#include "Texture.h"
#include "Decoder.h"
#include <stdio.h>

static Main* instance;

Main* Main::INSTANCE () {
	if(instance == NULL)
		instance = new Main();
	return instance;
}

void Main::Release () {
	m_Decoder->Release();
}

void Main::SetGraphicDevice (void* device, int deviceType, int eventType) {
	m_Texture->SetGraphicDevice(device, deviceType, eventType);
}

void Main::SetTexture (int textureID, int width, int height) {
	m_Texture->SetTexture(textureID, width, height);
	m_Decoder->SetDimension(width, height);
}

void Main::SetTexture (int textureID, int width, int height, int format) {
	m_Texture->SetTexture(textureID, width, height, format);
	m_Decoder->SetDimension(width, height);
}

void Main::DecodeVideo (int dataLen, char* data) {
	m_Decoder->Decode(dataLen, data);
}

void Main::FillTexture () {
	int len = m_Decoder->GetDecodedLen();
	if(len == -1)
		return;

	m_Texture->FillTexture(len, m_Decoder->GetDecodedData());
}

Main::Main () {
	m_Texture = new Texture();
	m_Decoder = new Decoder();
}

Main::~Main () {
	delete m_Texture;
	delete m_Decoder;
}

