
#ifndef GLTEXTURE_ENTRY
#define GLTEXTURE_ENTRY

#include "Entry.h"
#include "Main.h"

extern "C" {
	void SetTexture (int textureID, int width, int height, int format) {
		(Main::INSTANCE())->SetTexture(textureID, width, height, format);
	}

	void DecodeVideo (int dataLen, char* data) {
		(Main::INSTANCE())->DecodeVideo(dataLen, data);
	}
}

#endif