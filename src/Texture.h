class Texture {
public:
	enum Format {
		RGB,
		RGBA,
		Count
	};
	Texture ();
	void SetTexture (int textureID, int width, int height);
	void SetTexture (int textureID, int width, int height, int format);
	void FillTexture (int dataLen, char* data);
private:
	int m_Width;
	int m_Height;
	Format m_Format;
}