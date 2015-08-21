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
	delete[] m_TempBuffer;
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
	m_BufferIndex = 0;
	m_TempFilled = 0;

	int len = m_Width * m_Height * 3;
	m_TempBufferLen = m_Width * m_Height * 3;
	m_BufferLen[0] = len;
	m_BufferLen[1] = len;
	m_Buffer[0] = new char[len];
	m_Buffer[1] = new char[len];
	m_TempBuffer = new char[m_TempBufferLen];
	memset(m_Buffer[0], 0, len);
	memset(m_Buffer[1], 0, len);
	memset(m_TempBuffer, 0, m_TempBufferLen);
}

void Decoder::Decode (int dataLen, char* data) {
	int index = (m_BufferIndex + 1) % 2;
	int right = 0, left = 0;
	if(dataLen + m_TempFilled <= m_TempBufferLen) {
		memcpy(&m_TempBuffer[m_TempFilled], data, dataLen);
		m_TempFilled += dataLen;
	} else {
		//Temporary use remain
		left = m_TempBufferLen - m_TempFilled;
		right = (dataLen + m_TempFilled) - m_TempBufferLen;

		memcpy(&m_TempBuffer[m_TempFilled], data, left);
		m_TempFilled += left;
	}

	if(m_TempFilled < m_TempBufferLen)
		return;

	memcpy(m_Buffer[index], m_TempBuffer, m_TempBufferLen);

	if(right > 0) {
		memcpy(m_TempBuffer, &data[dataLen - right], right);
		m_TempFilled = right;
	} else {
		m_TempFilled = 0;
	}
	// memcpy(m_Buffer[index], data, dataLen);
	m_BufferIndex = (m_BufferIndex + 1) % 2;
	return;
}

void Decoder::Release () {
	delete[] m_Buffer[0];
	delete[] m_Buffer[1];
	delete[] m_TempBuffer;
	m_BufferIndex = 0;
	m_TempFilled = 0;
}

