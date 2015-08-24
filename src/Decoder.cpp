#include "Decoder.h"
#include <stdio.h>
#include <cstring>

Decoder::Decoder () {
	m_BufferIndex = 0;
}

Decoder::~Decoder () {
	delete[] m_Buffer[0];
	delete[] m_Buffer[1];
	m_BufferIndex = 0;
}

int Decoder::GetDecodedLen() {
	return m_BufferLen;
}

char* Decoder::GetDecodedData() {
	return m_Buffer[m_BufferIndex];
}

void Decoder::SetDimension (int width, int height) {
	m_Width = width;
	m_Height = height;
	m_BufferIndex = 0;
	m_BufferFilled = 0;

	int len = m_Width * m_Height * 3;
	m_BufferLen = len;
	m_Buffer[0] = new char[len];
	m_Buffer[1] = new char[len];
	memset(m_Buffer[0], 0, len);
	memset(m_Buffer[1], 0, len);
}

void Decoder::Decode (int dataLen, char* data) {
	char* workingBuff = m_Buffer[(m_BufferIndex + 1) % 2];
	int right = 0, left = 0;

	if(dataLen + m_BufferFilled <= m_BufferLen) {
		memcpy(&workingBuff[m_BufferFilled], data, dataLen);
		m_BufferFilled += dataLen;
	} else {
		left = m_BufferLen - m_BufferFilled;
		right = (dataLen + m_BufferFilled) - m_BufferLen;

		memcpy(&workingBuff[m_BufferFilled], data, left);
		m_BufferFilled += left;
	}

	if(m_BufferFilled < m_BufferLen)
		return;

	if(right > 0) {
		workingBuff = m_Buffer[m_BufferIndex];
		memcpy(workingBuff, &data[dataLen - right], right);
		m_BufferFilled = right;
	} else {
		m_BufferFilled = 0;
	}

	m_BufferIndex = (m_BufferIndex + 1) % 2;
	return;
}

void Decoder::Release () {
	delete[] m_Buffer[0];
	delete[] m_Buffer[1];
	m_BufferIndex = 0;
	m_BufferFilled = 0;
}

