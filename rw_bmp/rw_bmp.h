#ifndef RW_BMP_H_INCLUDED
#define RW_BMP_H_INCLUDED


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct tagBITMAPFILEHEADER
{
    /*
    ���������ַ�ʽ��ȡ����Ϊ�ṹ���ж������
        fread(&bitp.file, sizeof(BITMAPFILEHEADER), 1, fp);
    */
    uint8_t bfType[2];  // ͼ������
    uint32_t bfSize;  // �ļ���С
    uint16_t bfreserved1;  // ����
    uint16_t bfreserved2;  // ����
    uint32_t bfOffBits;  //  �ļ�0��ַ��λͼ���ݵ�ƫ���������ļ�ͷ + ��Ϣͷ + ��ɫ����ֽ���
} BITMAPFILEHEADER;


typedef struct tagBITMAPINFOHEADER
{
    uint32_t biSize;  // ��Ϣͷռ�е��ֽ���
    uint32_t biWidth;  // ͼ���
    int32_t biHigh;  // ͼ���
    uint16_t biPlanes;  //
    uint16_t biBitCount;  // ÿ�����ص�λ��
    uint32_t biCompression;  // ѹ��
    uint32_t biSizeImage;  //
    uint32_t biXpelsPerMeter;  // ����ÿ��
    uint32_t biYpelsPerMeter;  // ����ÿ��
    uint32_t biClrUsed;  // ��ɫ��
    uint32_t biClrImportant;  // ��Ҫ����ɫ

} BITMAPINFOHEADER;

/*
lena_512512��ǰ32��16����

�ļ�ͷ
42 4D ����ascii��BM
36 00 0C 00 ָ�ļ���С, Ϊ0x000c0036 = 786486
00 00 bfreserved1
00 00 bfreserved2
36 00 00 00 bfOffBits��Ϊ00 00 00 36h = 54 ˵���ļ�ͷ��54�ֽڣ��ļ�ͷ + ��Ϣͷ��

�ļ���Ϣͷ
28 00 00 00 biSize
00 02 00 00 biWidth��512���� 00 00 02 00 h (2^4)^2 * 2
00 02 00 00 biHigh��512���� 00 00 02 00 h (2^4)^2 * 2
01 00 biPlanes
18 00 biBitCount, ÿ�����ص�λ���� 00 18 h ?(2^4) + 8 = 24 λ
00 00 biCompression
00 00 00 00 biSizeImage
0C 00 00 00 biXpelsPerMeter
00 00 00 00 biYpelsPerMeter
00 00 00 00 biClrUsed
00 00 00 00 biClrImportant
*/


typedef struct tagRGBQUAD
{
    uint8_t rgbBlue; // 0-255
    uint8_t rgbGreen; // 0-255
    uint8_t rgbRed;  // 0-255
    uint8_t rgbReserved; // 0
} RGBQUAD;


typedef struct tagBMP
{
    BITMAPFILEHEADER file; //�ļ�ͷ
    BITMAPINFOHEADER info; //�ļ���Ϣͷ
    RGBQUAD pColorTable[256]; //256ɫ��ɫ��
    uint8_t *pBmpBuf; //ͼ��λͼ����
} bmp;


bmp readbmp(char *path);
bmp writebmp(char *path, bmp bitp);
void free_bmp(bmp bitp);

#endif // RW_BMP_H_INCLUDED
