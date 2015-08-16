
#ifndef GLTEXTURE_ENTRY
#define GLTEXTURE_ENTRY

#include "UnityPluginInterface.h"
#include "Entry.h"
#include "Main.h"


extern "C" {
	void EXPORT_API SetTexture (int textureID, int width, int height, int format) {
		(Main::INSTANCE())->SetTexture(textureID, width, height, format);
	}

	void EXPORT_API DecodeVideo (int dataLen, char* data) {
		(Main::INSTANCE())->DecodeVideo(dataLen, data);
	}

	void EXPORT_API UnitySetGraphicDevice(void* device, int deviceType, int eventType) {
		(Main::INSTANCE())->SetGraphicDevice(device, deviceType, eventType);
	}

	void EXPORT_API UnityRenderEvent(int eventID) {
		(Main::INSTANCE())->FillTexture();
	}

	void EXPORT_API Release () {
		(Main::INSTANCE())->Release();
	}
}

#endif