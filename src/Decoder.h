#ifndef GLTEXTURE_DECODER
#define GLTEXTURE_DECODER

class Decoder {
	public:
		Decoder ();
		~Decoder ();
		int GetDecodedLen();
		char* GetDecodedData();
		void SetDimension (int width, int height);
		void Decode (int dataLen, char* data);
		void Release ();
	private:
		int m_BufferIndex;
		int m_Width;
		int m_Height;
		int m_DecodeCount;

		char* m_TempBuffer;
		int m_TempFilled;

		int m_BufferLen[2];
		char* m_Buffer[2];

		int YUVY422TORGB888 (unsigned char *src_buff, int w, int h, unsigned char *dest);
};

#endif