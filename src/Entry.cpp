#include "Entry.h"

#ifndef MAIN
	#define MAIN() Main::INSTANCE()
#endif

extern "C" {
	void SetTexture (int textreID, int width, int height) {
		MAIN()->SetTexture(textureID, width, height);
	}

	void SetTexture (int textreID, int width, int height, int format) {
		MAIN()->SetTexture(textureID, width, height, format);
	}

	void DecodeVideo (int dataLen, char* data) {
		MAIN()->DecodeVideo(dataLen, data);
	}

}