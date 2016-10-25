#ifndef RW_BMP_H_INCLUDED
#define RW_BMP_H_INCLUDED


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct tagBITMAPFILEHEADER
{
    /*
    不能用这种方式读取，因为结构体有对齐规则
        fread(&bitp.file, sizeof(BITMAPFILEHEADER), 1, fp);
    */
    uint8_t bfType[2];  // 图像类型
    uint32_t bfSize;  // 文件大小
    uint16_t bfreserved1;  // 保留
    uint16_t bfreserved2;  // 保留
    uint32_t bfOffBits;  //  文件0地址到位图数据的偏移量。即文件头 + 信息头 + 调色板的字节数
} BITMAPFILEHEADER;


typedef struct tagBITMAPINFOHEADER
{
    uint32_t biSize;  // 信息头占有的字节数
    uint32_t biWidth;  // 图像宽
    int32_t biHigh;  // 图像高
    uint16_t biPlanes;  //
    uint16_t biBitCount;  // 每个像素的位数
    uint32_t biCompression;  // 压缩
    uint32_t biSizeImage;  //
    uint32_t biXpelsPerMeter;  // 像素每米
    uint32_t biYpelsPerMeter;  // 像素每米
    uint32_t biClrUsed;  // 调色板
    uint32_t biClrImportant;  // 重要的颜色

} BITMAPINFOHEADER;

/*
lena_512512的前32个16进制

文件头
42 4D 换成ascii是BM
36 00 0C 00 指文件大小, 为0x000c0036 = 786486
00 00 bfreserved1
00 00 bfreserved2
36 00 00 00 bfOffBits，为00 00 00 36h = 54 说明文件头有54字节（文件头 + 信息头）

文件信息头
28 00 00 00 biSize
00 02 00 00 biWidth（512）， 00 00 02 00 h (2^4)^2 * 2
00 02 00 00 biHigh（512）， 00 00 02 00 h (2^4)^2 * 2
01 00 biPlanes
18 00 biBitCount, 每个像素的位数， 00 18 h ?(2^4) + 8 = 24 位
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
    BITMAPFILEHEADER file; //文件头
    BITMAPINFOHEADER info; //文件信息头
    RGBQUAD pColorTable[256]; //256色调色板
    uint8_t *pBmpBuf; //图像位图数据
} bmp;


bmp readbmp(char *path);
bmp writebmp(char *path, bmp bitp);
void free_bmp(bmp bitp);

#endif // RW_BMP_H_INCLUDED
