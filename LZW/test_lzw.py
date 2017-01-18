# -*- coding:utf-8 -*-

import cv2 as cv
import numpy as np
from lzw import *
import time


if __name__ == '__main__':
    # Lena_512512.bmp
    # 读入图片
    while(True):
        filename = input("请输入文件名\n")
        im = cv.imread(filename, 0)
        if im is None: print("文件不存在, 请重新输入")
        else: break

    shape = im.shape

    time1 = time.time()
    inv_lzwDict, code = encode(im.reshape(-1))
    time2 = time.time()
    print("encode {0} image cost time {1} s".format(shape, time2-time1))

    time1 = time.time()
    result = decode(inv_lzwDict, code)
    time2 = time.time()
    print("encode {0} image cost time {1} s".format(shape, time2-time1))

    # print(inv_lzwDict)

    result = [ord(s) for s in result]
    im2 = np.array(result, dtype=np.uint8).reshape(shape)
    cv.imshow('origin', im)
    cv.imshow('recover', im2)
    cv.waitKey(0)
    cv.destroyWindow('origin')
    cv.destroyWindow('recover')
