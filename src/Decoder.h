#ifndef GLTEXTURE_DECODER
#define GLTEXTURE_DECODER

class Decoder {
	public:
		Decoder ();
		void Decode (int dataLen, char* data, int* out_DecodedLen, char* out_DecodedData);
};

#endif