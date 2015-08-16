#include "Decoder.h"
#include <stdio.h>
#include <cstring>

Decoder::Decoder () {
	m_BufferIndex = 0;
	// m_DecodedLen = len;
	// m_DecodedData = new char[100];
	// memset(m_DecodedData, 0, sizeof(int) * 2);
}

Decoder::~Decoder () {
	delete[] m_Buffer[0];
	delete[] m_Buffer[1];
	m_BufferIndex = 0;
}

int Decoder::GetDecodedLen() {
	return m_BufferLen[m_BufferIndex];
}

char* Decoder::GetDecodedData() {
	return m_Buffer[m_BufferIndex];
}

void Decoder::SetDimension (int width, int height) {
	m_Width = width;
	m_Height = height;

	int len = m_Width * m_Height * 3;
	m_BufferLen[0] = len;
	m_BufferLen[1] = len;
	m_Buffer[0] = new char[len];
	m_Buffer[1] = new char[len];
	memset(m_Buffer[0], 50, len);
	memset(m_Buffer[1], 150, len);
}

void Decoder::Decode (int dataLen, char* data) {
	// *out_DecodedLen = dataLen;
	// out_DecodedData = malloc(sizeof(char) * dataLen);
	// memcpy(out_DecodedData, data, dataLen);
	// return;
	int index = (m_BufferIndex + 1) % 2;
	int currDataIndex = 0, colorData = 0;
	int id = 0;
	for(int w = 0; w < m_Width; w++) {
		for(int h = 0; h < m_Height; h++) {
			id = (w * 3) + (h * m_Width * 3);

			colorData = (currDataIndex < dataLen) ? data[currDataIndex] : m_DecodeCount;
			m_Buffer[index][id]     = (unsigned char)colorData % 255;
			m_Buffer[index][id + 1] = (unsigned char)128;//m_DecodeCount % 255;
			m_Buffer[index][id + 2] = (unsigned char)128;//m_DecodeCount % 255;
			// m_Buffer[index][id] = m_DecodeCount % 255;
			currDataIndex++;
		}
	}
	m_DecodeCount ++;
	m_BufferIndex = (m_BufferIndex + 1) % 2;
}

void Decoder::Release () {
	delete[] m_Buffer[0];
	delete[] m_Buffer[1];
}

