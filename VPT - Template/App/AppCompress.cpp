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

	unsigned char *compressedData ;
	cDataSize = width * height * 3 ;	

	/****************************************** My Cdoe **********************************************************/

	// �洢ѹ���������,��������ߴ�Ҳ���ᵽ����cDataSize * 2					
	compressedData = new unsigned char[cDataSize * 2];
	// ʵ��ѹ���ַ�����
	int compressedSize = 0;

	// ���÷�ͨ������ķ���������ÿ��ͨ���������ص��ظ��Խ���ѹ��
	// 1.bͨ��
	unsigned short curB = pInput[0];// ��һ�����ص�b
	unsigned short repeat = 1;// �ظ�����
	for (int i = 1; i < cDataSize / 3; i++)
	{
		unsigned short nextB = pInput[i * 3 + 0];// ��һ�����ص�b
		if (nextB == curB && repeat < 127)
		{
			++repeat;
			// ��������һ����洢
			if (i == cDataSize / 3 - 1)
			{
				// �洢���һ��bֵ��
				compressedData[compressedSize] = repeat;
				compressedData[compressedSize + 1] = curB;
				// ���ӱ������ݳ���
				compressedSize += 2;
			}
		}
		else
		{
			// �洢��һ��bֵ��
			compressedData[compressedSize] = repeat;
			compressedData[compressedSize + 1] = curB;
			// ���ӱ������ݳ���
			compressedSize += 2;
			// ����һ��bֵ
			curB = nextB;
			repeat = 1;
			// ��������һ��
			if (i == cDataSize / 3 - 1)
			{
				// �洢���һ��bֵ
				compressedData[compressedSize] = 1;
				compressedData[compressedSize + 1] = curB;
				// ���ӱ������ݳ���
				compressedSize += 2;
			}
		}
	}

	// 2.gͨ��
	unsigned short curG = pInput[1];// ��һ�����ص�g
	repeat = 1;// �ظ�����
	for (int i = 1; i < cDataSize / 3; i++)
	{
		unsigned short nextG = pInput[i * 3 + 1];// ��һ�����ص�g
		if (nextG == curG && repeat <= 127)
		{
			++repeat;
			// ��������һ����洢
			if (i == cDataSize / 3 - 1)
			{
				// �洢���һ��gֵ��
				compressedData[compressedSize] = repeat;
				compressedData[compressedSize + 1] = curG;
				// ���ӱ������ݳ���
				compressedSize += 2;
			}
		}
		else
		{
			// �洢��һ��gֵ��
			compressedData[compressedSize] = repeat;
			compressedData[compressedSize + 1] = curG;
			// ���ӱ������ݳ���
			compressedSize += 2;
			// ����һ��gֵ
			curG = nextG;
			repeat = 1;
			// ��������һ��
			if (i == cDataSize / 3 - 1)
			{
				// �洢���һ��gֵ
				compressedData[compressedSize] = 1;
				compressedData[compressedSize + 1] = curB;
				// ���ӱ������ݳ���
				compressedSize += 2;
			}
		}
	}

	// 3.rͨ��
	unsigned short curR = pInput[2];// ��һ�����ص�r
	repeat = 1;// �ظ�����
	for (int i = 1; i < cDataSize / 3; i++)
	{
		unsigned short nextR = pInput[i * 3 + 2];// ��һ�����ص�r
		if (nextR == curR && repeat <= 127)
		{
			++repeat;
			// ��������һ����洢
			if (i == cDataSize / 3 - 1)
			{
				// �洢���һ��gֵ��
				compressedData[compressedSize] = repeat;
				compressedData[compressedSize + 1] = curR;
				// ���ӱ������ݳ���
				compressedSize += 2;
			}
		}
		else
		{
			// �洢��һ��gֵ��
			compressedData[compressedSize] = repeat;
			compressedData[compressedSize + 1] = curR;
			// ���ӱ������ݳ���
			compressedSize += 2;
			// ����һ��rֵ
			curR = nextR;
			repeat = 1;
			// ��������һ��
			if (i == cDataSize / 3 - 1)
			{
				// �洢���һ��rֵ
				compressedData[compressedSize] = 1;
				compressedData[compressedSize + 1] = curR;
				// ���ӱ������ݳ���
				compressedSize += 2;
			}
		}
	}

	// ȡ��ѹ����Ĵ�����
	cDataSize = compressedSize;
	unsigned char *finalData = new unsigned char[cDataSize];
	for (int i = 0; i < cDataSize; i++)
	{
		unsigned char temp = compressedData[i];
		finalData[i] = temp;
	}
	delete compressedData;
	compressedData = finalData;

	// �����ã�
	int pixelCount = 0;
	for (int i = 0; i < cDataSize; i += 2)
	{
		int curRpeat = compressedData[i];
		pixelCount += curRpeat;
	}

	/******************************************** My Code End ****************************************************/

	return compressedData;		// return the compressed data
}

// This function takes in compressedData with size cDatasize, and decompresses it into 8-8-8 image.
// The decompressed image data should be stored into the uncompressedData buffer, with 8-8-8 image format
void CAppCompress::Decompress(unsigned char *compressedData, int cDataSize, unsigned char *uncompressedData) {

	// You can modify anything within this function, but you cannot change the function prototype.
	//memcpy(uncompressedData, compressedData, cDataSize) ;	// Here, we simply copy the compressedData into the output buffer.

	/******************************************** My Code *********************************************************/
	
	// Ѱ��gͨ����rͨ����ѹ�����������е�ƫ������
	int offset_r = 0, offset_g = 0;
	int pixelCount = 0;
	for (int i = 0; i < cDataSize;)
	{
		int curRpeat = compressedData[i];
		pixelCount += curRpeat;
		i += 2;
		if (pixelCount == width*height)
		{
			offset_g = i;// gͨ���Ŀ�ʼ����
		}
		if (pixelCount == width*height * 2)
		{
			offset_r = i;// rͨ���Ŀ�ʼ����
		}
	}

	unsigned int b, g, r;
	int repeat;
	// 1.��ԭbͨ��
	for (int i = 0, j = 0; i < width*height, j < offset_g; j += 2)
	{
		// �ָ�һ���ظ���bֵ
		repeat = compressedData[j];
		for (int p = 0; p < repeat; p++)
		{
			int d = compressedData[j + 1];
			uncompressedData[i * 3 + p*3 + 0] = compressedData[j + 1];
		}
		i += repeat;
	}

	// 2.��ԭgͨ��
	for (int i = 0, j = offset_g; i < width*height, j < offset_r; j += 2)
	{
		repeat = compressedData[j];
		for (int p = 0; p < repeat; p++)
		{
			int d = compressedData[j + 1];
			uncompressedData[i * 3 + p * 3 + 1] = compressedData[j + 1];
		}
		i += repeat;
	}

	// ��ԭrͨ��
	for (int i = 0, j = offset_r; i < width*height, j < cDataSize; j += 2)
	{
		repeat = compressedData[j];
		for (int p = 0; p < repeat; p++)
		{
			int d = compressedData[j + 1];
			uncompressedData[i * 3 + p * 3 + 2] = compressedData[j + 1];
		}
		i += repeat;
	}
	/******************************************** My Code End *********************************************************/
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
