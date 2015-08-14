#include "Decoder.h"

Decoder::Decoder () {

}

void Decoder::Decode (int dataLen, char* data, int* out_DecodedLen, char* out_DecodedData) {
	*out_DecodedLen = dataLen;
	out_DecodedData = malloc(sizeof(char) * dataLen);
	memcpy(out_DecodedData, data, dataLen);
}

