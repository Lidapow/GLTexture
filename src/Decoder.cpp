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

	int len = m_Width * m_Height * 1;
	m_BufferLen[0] = len;
	m_BufferLen[1] = len;
	m_Buffer[0] = new char[len];
	m_Buffer[1] = new char[len];
	m_TempBuffer = new char[len];
	memset(m_Buffer[0], 0, len);
	memset(m_Buffer[1], 0, len);
	memset(m_TempBuffer, 0, len);
}

void Decoder::Decode (int dataLen, char* data) {
	// *out_DecodedLen = dataLen;
	// out_DecodedData = malloc(sizeof(char) * dataLen);
	int index = (m_BufferIndex + 1) % 2;
	int remain = 0;
	if(dataLen + m_TempFilled <= m_BufferLen[index]) {
		memcpy(&m_TempBuffer[m_TempFilled], data, dataLen);
		m_TempFilled += dataLen;
	} else {
		//Temporary use remain
		remain = (dataLen + m_TempFilled) - m_BufferLen[index];

		memcpy(&m_TempBuffer[m_TempFilled], data, remain);
		m_TempFilled += remain;
		remain = dataLen - remain;
	}

	if(m_TempFilled < m_BufferLen[index])
		return;

	YUVY422TORGB888((unsigned char *)m_TempBuffer, m_Width, m_Height, (unsigned char *)m_Buffer[index]);

	if(remain > 0) {
		memcpy(m_TempBuffer, &data[dataLen - remain], remain);
		m_TempFilled = remain;
	} else {
		m_TempFilled = 0;
	}
	// memcpy(m_Buffer[index], data, dataLen);
	m_DecodeCount++;
	m_BufferIndex = (m_BufferIndex + 1) % 2;
	return;
}

void Decoder::Release () {
	delete[] m_Buffer[0];
	delete[] m_Buffer[1];
}

//输入YUV422I buffer数据，输出RGB buffer数据；  
int Decoder::YUVY422TORGB888(unsigned char *src_buffer, int w, int h, unsigned char *des_buffer)  
{  
    unsigned char *yuv, *rgb;  
    unsigned char u, v, y1, y2;  
  
    yuv = src_buffer;  
    rgb = des_buffer;  
  
    if (yuv == NULL || rgb == NULL)  
    {  
        printf ("error: input data null!\n");     
        return -1;  
    }  
  
    int size = w * h;  
  
    for(int i = 0; i < size; i += 2)  
    {  
        y1 = yuv[2*i + 1];  
        y2 = yuv[2*i + 3];
        u = yuv[2*i];  
        v = yuv[2*i + 2];  
  
#if 0  
        rgb[3*i]     = (unsigned char)(y1 + 1.402*(u - 128));  
        rgb[3*i + 1] = (unsigned char)(y1 - 0.344*(u - 128) - 0.714*(v - 128));  
        rgb[3*i + 2] = (unsigned char)(y1 + 1.772*(v - 128));  
  
        rgb[3*i + 3] = (unsigned char)(y2 + 1.375*(u - 128));  
        rgb[3*i + 4] = (unsigned char)(y2 - 0.344*(u - 128) - 0.714*(v - 128));  
        rgb[3*i + 5] = (unsigned char)(y2 + 1.772*(v - 128));  
#endif   
      
        //为提高性能此处用移位运算；  
        rgb[3*i]     = (unsigned char)(y1 + (u - 128) + ((104*(u - 128))>>8));  
        rgb[3*i + 1] = (unsigned char)(y1 - (89*(v - 128)>>8) - ((183*(u - 128))>>8));  
        rgb[3*i + 2] = (unsigned char)(y1 + (v - 128) + ((199*(v - 128))>>8));  
  
        rgb[3*i + 3] = (unsigned char)(y2 + (u - 128) + ((104*(u - 128))>>8));  
        rgb[3*i + 4] = (unsigned char)(y2 - (89*(v - 128)>>8) - ((183*(u - 128))>>8));  
        rgb[3*i + 5] = (unsigned char)(y2 + (v - 128) + ((199*(v - 128))>>8));  
    }  
      
    return 0;  
} 

