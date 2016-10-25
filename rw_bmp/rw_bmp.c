#include"rw_bmp.h"

bmp readbmp(char *path)
{
    bmp bitp = {.pBmpBuf = NULL};
    FILE *fp;
    fp = fopen(path, "rb");
    if(fp == NULL)
    {
        printf("can't open the bmp image.\n");
        exit(0);
    }

//    /*--------------------------读取文件头--------------------------*/
    // read B
    fread(&bitp.file.bfType[0], sizeof(uint8_t), 1, fp);
    // read M
    fread(&bitp.file.bfType[1], sizeof(uint8_t), 1, fp);

    if(bitp.file.bfType[0] != 0x42 || bitp.file.bfType[1] != 0x4D)
    {
        printf("this file is not bmp file.\n");
        exit(0);
    }

    fread(&bitp.file.bfSize, sizeof(int32_t), 1, fp);
    fread(&bitp.file.bfreserved1, sizeof(int16_t), 1, fp);
    fread(&bitp.file.bfreserved2, sizeof(int16_t), 1, fp);
    fread(&bitp.file.bfOffBits, sizeof(int32_t), 1, fp);

    printf("--------------------------文件头--------------------------\n");
    printf("bfType : %c%c\n", bitp.file.bfType[0],bitp.file.bfType[1]);
    printf("bfSize : %x\n", bitp.file.bfSize);
    printf("bfreserved1 : %x\n", bitp.file.bfreserved1);
    printf("bfreserved2 : %x\n", bitp.file.bfreserved2);
    printf("bfOffBits : %x\n", bitp.file.bfOffBits);

    /*--------------------------读取信息头--------------------------*/
    fread(&bitp.info.biSize, sizeof(int32_t), 1, fp);
    fread(&bitp.info.biWidth, sizeof(int32_t), 1, fp);
    fread(&bitp.info.biHigh, sizeof(int32_t), 1, fp);
    fread(&bitp.info.biPlanes, sizeof(int16_t), 1, fp);
    fread(&bitp.info.biBitCount, sizeof(int16_t), 1, fp);
    fread(&bitp.info.biCompression, sizeof(int32_t), 1, fp);
    fread(&bitp.info.biSizeImage, sizeof(int32_t), 1, fp);
    fread(&bitp.info.biXpelsPerMeter, sizeof(int32_t), 1, fp);
    fread(&bitp.info.biYpelsPerMeter, sizeof(int32_t), 1, fp);
    fread(&bitp.info.biClrUsed, sizeof(int32_t), 1, fp);
    fread(&bitp.info.biClrImportant, sizeof(int32_t), 1, fp);


    printf("--------------------------文件信息头--------------------------\n");
    printf("biSize : %x\n", bitp.info.biSize);
    printf("biWidth : %x\n", bitp.info.biWidth);
    printf("biHigh : %x\n", bitp.info.biHigh);
    printf("biPlanes : %x\n", bitp.info.biPlanes);
    printf("biBitCount : %x\n", bitp.info.biBitCount);
    printf("biCompression : %x\n", bitp.info.biCompression);
    printf("biSizeImage : %x\n", bitp.info.biSizeImage);
    printf("biXpelsPerMeter : %x\n", bitp.info.biXpelsPerMeter);
    printf("biYpelsPerMeter : %x\n", bitp.info.biYpelsPerMeter);
    printf("biClrUsed : %x\n", bitp.info.biClrUsed);
    printf("biClrImportant : %x\n", bitp.info.biClrImportant);


    /*--------------------------------图像数据------------------------------------*/
    int rowSize=(bitp.info.biWidth*bitp.info.biBitCount+31)/32*4;
    //读取调色板
    unsigned int nCounti = 0;
    for(nCounti=0; nCounti<bitp.info.biClrUsed; nCounti++)
    {
        //存储的时候，一般去掉保留字rgbReserved??
        fread(&bitp.pColorTable[nCounti].rgbBlue,1,sizeof(uint8_t),fp);
        fread(&bitp.pColorTable[nCounti].rgbGreen,1,sizeof(uint8_t),fp);
        fread(&bitp.pColorTable[nCounti].rgbRed,1,sizeof(uint8_t),fp);
    }


    bitp.pBmpBuf=(uint8_t*)malloc(sizeof(uint8_t)*rowSize*bitp.info.biHigh);
    fread(bitp.pBmpBuf,1,rowSize*bitp.info.biHigh,fp);

    fclose(fp);
    return bitp;
}



bmp writebmp(char *path, bmp bitp)
{
    FILE *fp;
    fp = fopen(path, "wb");
    if(fp == NULL)
    {
        printf("can't open the bmp image.\n");
        exit(0);
    }

//    /*--------------------------读取文件头--------------------------*/
    // read B
    fwrite(&bitp.file.bfType[0], sizeof(uint8_t), 1, fp);
    // read M
    fwrite(&bitp.file.bfType[1], sizeof(uint8_t), 1, fp);

    if(bitp.file.bfType[0] != 0x42 || bitp.file.bfType[1] != 0x4D)
    {
        printf("this file is not bmp file.\n");
        exit(0);
    }

    fwrite(&bitp.file.bfSize, sizeof(int32_t), 1, fp);
    fwrite(&bitp.file.bfreserved1, sizeof(int16_t), 1, fp);
    fwrite(&bitp.file.bfreserved2, sizeof(int16_t), 1, fp);
    fwrite(&bitp.file.bfOffBits, sizeof(int32_t), 1, fp);

    /*--------------------------读取信息头--------------------------*/
    fwrite(&bitp.info.biSize, sizeof(int32_t), 1, fp);
    fwrite(&bitp.info.biWidth, sizeof(int32_t), 1, fp);
    fwrite(&bitp.info.biHigh, sizeof(int32_t), 1, fp);
    fwrite(&bitp.info.biPlanes, sizeof(int16_t), 1, fp);
    fwrite(&bitp.info.biBitCount, sizeof(int16_t), 1, fp);
    fwrite(&bitp.info.biCompression, sizeof(int32_t), 1, fp);
    fwrite(&bitp.info.biSizeImage, sizeof(int32_t), 1, fp);
    fwrite(&bitp.info.biXpelsPerMeter, sizeof(int32_t), 1, fp);
    fwrite(&bitp.info.biYpelsPerMeter, sizeof(int32_t), 1, fp);
    fwrite(&bitp.info.biClrUsed, sizeof(int32_t), 1, fp);
    fwrite(&bitp.info.biClrImportant, sizeof(int32_t), 1, fp);


    /*--------------------------------图像数据------------------------------------*/
    int rowSize=(bitp.info.biWidth*bitp.info.biBitCount+31)/32*4;

    if (bitp.info.biBitCount == 8)
    {
        //写调色板
        unsigned int j = 0;
        for(j=0; j<256; j+=1)
        {
            fwrite(&bitp.pColorTable[j].rgbBlue,1,sizeof(uint8_t),fp);
            fwrite(&bitp.pColorTable[j].rgbGreen,1,sizeof(uint8_t),fp);
            fwrite(&bitp.pColorTable[j].rgbRed,1,sizeof(uint8_t),fp);
            fwrite(&bitp.pColorTable[j].rgbReserved,1,sizeof(uint8_t),fp);
        }
    }

    fwrite(bitp.pBmpBuf,1,rowSize*bitp.info.biHigh,fp);

    fclose(fp);
    return bitp;
}



void free_bmp(bmp bitp)
{
    if (bitp.pBmpBuf != NULL)
    {
        free(bitp.pBmpBuf);
        bitp.pBmpBuf = NULL;
    }
}
