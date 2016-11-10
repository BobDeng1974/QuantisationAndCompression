#include "StdAfx.h"
#include "AppCompress.h"

CAppCompress::CAppCompress(void)
{
	// Class Constructor
}

CAppCompress::~CAppCompress(void)
{
	// Class Destructor
	// Must call Final() function in the base class

	Final() ;
}

void CAppCompress::CustomInit(CView *pView) {
	// Add custom initialization code here
	// This initialization code will be called when this application is added to a processing task lists
}

void CAppCompress::CustomFinal(void) {
	// Add custom finalization code here
}

// This function compresses input 24-bit image (8-8-8 format, in pInput pointer).
// This function shall allocate storage space for compressedData, and return it as a pointer.
// The input reference variable cDataSize, is also serve as an output variable to indicate the size (in bytes) of the compressed data.
unsigned char *CAppCompress::Compress(int &cDataSize) {

	// ѹ���������
	unsigned char *compressedData ;
	// ��󳤶ȣ����compressedSize>=cDataSize,ѹ��ʧ��
	cDataSize = width * height * 3 ;	
	// �洢ѹ���������					
	compressedData = new unsigned char[cDataSize] ; 

	/*****************************************************************************************************/
	// ʵ��ѹ���ַ�����
	int compressedSize = 0;
	// ���÷�ͨ������ķ���������ÿ��ͨ���������ص��ظ��Խ���ѹ��
	// bͨ��
	unsigned short curB = pInput[0];// ��һ�����ص�b
	unsigned short repeat = 1;// �ظ�����
	for (int i = 1; i < cDataSize; i++) {
		unsigned short nextB = pInput[i * 3 + 0];// ��һ�����ص�b
		if (nextB == curB) {
			++repeat;

			// ��������һ����洢
			if (i == cDataSize-1)
			{
				// �洢���һ��bֵ��
				compressedData[compressedSize] = repeat & 0xFF;
				compressedData[compressedSize + 1] = curB & 0xFF;
				// ���ӱ������ݳ���
				compressedSize += 2;
			}
		}else{
			// �洢��һ��bֵ��
			compressedData[compressedSize] = repeat & 0xFF;
			compressedData[compressedSize + 1] = curB & 0xFF;
			// ���ӱ������ݳ���
			compressedSize += 2;

			// ����һ��bֵ
			curB = nextB;
			repeat = 1;

			// ��������һ��
			if (i == cDataSize-1)
			{
				// �洢���һ��bֵ
				compressedData[compressedSize] = repeat & 0xFF;
				compressedData[compressedSize + 1] = curB & 0xFF;
				// ���ӱ������ݳ���
				compressedSize += 2;
			}
		}

		if (compressedSize > cDataSize)
		{
			// ѹ��ʧ��
			memcpy(compressedData, pInput, cDataSize);
			return compressedData;
		}
	}

	// gͨ��
	unsigned short curG = pInput[1];// ��һ�����ص�g
	repeat = 1;// �ظ�����
	for (int i = 1; i < cDataSize; i++) {
		unsigned short nextG = pInput[i * 3 + 1];// ��һ�����ص�g
		if (nextG == curG) {
			++repeat;

			// ��������һ����洢
			if (i == cDataSize - 1)
			{
				// �洢���һ��gֵ��
				compressedData[compressedSize] = repeat & 0xFF;
				compressedData[compressedSize + 1] = curG & 0xFF;
				// ���ӱ������ݳ���
				compressedSize += 2;
			}
		}
		else{
			// �洢��һ��gֵ��
			compressedData[compressedSize] = repeat & 0xFF;
			compressedData[compressedSize + 1] = curG & 0xFF;
			// ���ӱ������ݳ���
			compressedSize += 2;

			// ����һ��gֵ
			curG = nextG;
			repeat = 1;

			// ��������һ��
			if (i == cDataSize - 1)
			{
				// �洢���һ��gֵ
				compressedData[compressedSize] = repeat & 0xFF;
				compressedData[compressedSize + 1] = curB & 0xFF;
				// ���ӱ������ݳ���
				compressedSize += 2;
			}
		}

		if (compressedSize > cDataSize)
		{
			// ѹ��ʧ��
			memcpy(compressedData, pInput, cDataSize);
			return compressedData;
		}
	}

	// rͨ��
	unsigned short curR = pInput[2];// ��һ�����ص�r
	repeat = 1;// �ظ�����
	for (int i = 1; i < cDataSize; i++) {
		unsigned short nextR = pInput[i * 3 + 2];// ��һ�����ص�r
		if (nextR == curR) {
			++repeat;

			// ��������һ����洢
			if (i == cDataSize - 1)
			{
				// �洢���һ��gֵ��
				compressedData[compressedSize] = repeat & 0xFF;
				compressedData[compressedSize + 1] = curR & 0xFF;
				// ���ӱ������ݳ���
				compressedSize += 2;
			}
		}
		else{
			// �洢��һ��gֵ��
			compressedData[compressedSize] = repeat & 0xFF;
			compressedData[compressedSize + 1] = curR & 0xFF;
			// ���ӱ������ݳ���
			compressedSize += 2;

			// ����һ��rֵ
			curR = nextR;
			repeat = 1;

			// ��������һ��
			if (i == cDataSize - 1)
			{
				// �洢���һ��rֵ
				compressedData[compressedSize] = repeat & 0xFF;
				compressedData[compressedSize + 1] = curR & 0xFF;
				// ���ӱ������ݳ���
				compressedSize += 2;
			}
		}

		if (compressedSize > cDataSize)
		{
			// ѹ��ʧ��
			memcpy(compressedData, pInput, cDataSize);
			return compressedData;
		}
	}

	/*****************************************************************************************************/

	return compressedData ;		// return the compressed data
}

// This function takes in compressedData with size cDatasize, and decompresses it into 8-8-8 image.
// The decompressed image data should be stored into the uncompressedData buffer, with 8-8-8 image format
void CAppCompress::Decompress(unsigned char *compressedData, int cDataSize, unsigned char *uncompressedData) {

	// You can modify anything within this function, but you cannot change the function prototype.
	memcpy(uncompressedData, compressedData, cDataSize) ;	// Here, we simply copy the compressedData into the output buffer.

	/*****************************************************************************************************/



	/*****************************************************************************************************/

}


void CAppCompress::Process(void) {

	// Don't change anything within this function.

	int i, cDataSize ;

	unsigned char *compressedData ;
	unsigned char *verifyCompressedData ;

	SetTitle(pOutput, _T("Lossless Decompressed Image")) ;

	compressedData = Compress(cDataSize) ;

	verifyCompressedData = new unsigned char [cDataSize] ;

	memcpy(verifyCompressedData, compressedData, cDataSize) ;

	delete [] compressedData ;

	Decompress(verifyCompressedData, cDataSize, pOutput) ;

	for(i = 0; i < width * height * 3; i++) {
		if(pInput[i] != pOutput[i]) {
			printf(_T("Caution: Decoded Image is not identical to the Original Image!\r\n")) ;
			break ;
		}
	}

	printf(_T("Original Size = %d, Compressed Size = %d, Compression Ratio = %2.2f\r\n"), width * height * 3, cDataSize, (double) width * height * 3 / cDataSize) ;

	PutDC(pOutput) ;
}
