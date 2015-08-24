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

		int m_BufferLen;
		int m_BufferFilled;
		char* m_Buffer[2];
};

#endif