#include "UnityPluginInterface.h"

extern "C" {
	void EXPORT_API SetTexture (int textreID, int width, int height, int format);
	void EXPORT_API DecodeVideo (int dataLen, char* data);

	void EXPORT_API Release ();
}