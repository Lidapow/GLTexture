#ifndef GLTEXTURE_MAIN
#define GLTEXTURE_MAIN

#include "Texture.h"
#include "Decoder.h"

class Main {
	public:
		static Main* INSTANCE ();

		void Release ();
		void SetGraphicDevice (void* device, int deviceType, int eventType);
		void SetTexture (int textreID, int width, int height);
		void SetTexture (int textreID, int width, int height, int format);
		void DecodeVideo (int dataLen, char* data);
		void FillTexture ();
	private:
		Texture* m_Texture;
		Decoder* m_Decoder;
		Main ();
		~Main ();
};

#endif