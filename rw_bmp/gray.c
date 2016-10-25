#include"gray.h"

bmp gray(bmp bitp, int method)
{
    bmp grayp = {.pBmpBuf = NULL};
    grayp.file = bitp.file;
    grayp.info = bitp.info;
    // 像素的位数变化了
    grayp.info.biBitCount = 8;
    // 考虑到行的字节数是4的倍数，重新计算行大小
    int LineByte1=(grayp.info.biWidth*grayp.info.biBitCount+31)/32*4;
    // 因为有调色板，重新偏移量
    grayp.file.bfOffBits = grayp.file.bfOffBits + 256*4;
    // 计算文件大小
    grayp.file.bfSize = grayp.file.bfOffBits + LineByte1 * grayp.info.biHigh;

    grayp.pBmpBuf=(uint8_t*)malloc(sizeof(uint8_t)*LineByte1*grayp.info.biHigh);

    int rowSize_24=(bitp.info.biWidth*bitp.info.biBitCount+31)/32*4;
    int rowSize_8=LineByte1;
    int rth = 0;
    for(rth=0; rth<grayp.info.biHigh; rth++)
    {
        int cth = 0;
        int gray_cth = 0;
        for (cth = 0; cth<rowSize_24; cth+=3)
        {
            uint8_t b = bitp.pBmpBuf[rth*rowSize_24 + cth + 0];
            uint8_t g = bitp.pBmpBuf[rth*rowSize_24 + cth + 1];
            uint8_t r = bitp.pBmpBuf[rth*rowSize_24 + cth + 2];
            uint8_t tmp = 0;
            if(method == 1)
            {
                tmp = (b+g+r)/3;
            }else if(method == 2)
            {
                tmp = 0.3*r + 0.59*g + 0.11*b;
            }else
            {
                tmp = b>g?b:g;
                tmp = tmp>r?tmp:r;
            }
            grayp.pBmpBuf[rth*rowSize_8 + gray_cth++] = tmp;
        }
    }


    //写调色板
    unsigned int i = 0;
    for(i=0; i<256; i++)
    {
        grayp.pColorTable[i].rgbBlue = i;
        grayp.pColorTable[i].rgbGreen = i;
        grayp.pColorTable[i].rgbRed = i;
        grayp.pColorTable[i].rgbReserved = 0;
    }

    return grayp;
}

