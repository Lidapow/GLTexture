#ifndef GLTEXTURE_TEXTURE
#define GLTEXTURE_TEXTURE

class Texture {
public:
	enum Format {
		RGB,
		RGBA,
		Count
	};
	Texture ();
	void SetGraphicDevice (void* device, int deviceType, int eventType);
	void SetTexture (int textureID, int width, int height);
	void SetTexture (int textureID, int width, int height, int format);
	void FillTexture (int dataLen, char* data);
	void Release ();
private:
	int m_TextureID;
	int m_Width;
	int m_Height;
	Format m_Format;
	void* m_Device;
	int m_DeviceType;
	int m_EventType;
};

#endif