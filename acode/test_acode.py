# -*- coding:utf-8 -*-

from myacode import *
import time

if __name__ == "__main__":
    # 读入图像, test2.bmp
    while(True):
        filename = input("请输入文件名\n")
        im = cv.imread(filename, 0)
        if im is None: print("文件不存在, 请重新输入")
        else: break

    # 新建窗口
    cv.namedWindow('origin', cv.WINDOW_NORMAL)
    cv.namedWindow('recover', cv.WINDOW_NORMAL)

    shape = im.shape

    time1 = time.time()
    # 统计像素出现的频率
    acpro = static(im.reshape(-1))
    time2 = time.time()
    print("static {0} image cost time {1} s".format(shape, time2-time1))

    time1 = time.time()
    # 算术编码压缩42x42的图像
    code = compress(im.reshape(-1), acpro, 100000)
    time2 = time.time()
    print("encode {0} image cost time {1} s".format(shape, time2-time1))

    time1 = time.time()
    # 算术编码解压数据
    result = decompress(len(im.reshape(-1)), acpro, code, 100000)
    time2 = time.time()
    print("decode {0} image cost time {1} s".format(shape, time2-time1))

    im2 = np.array(result, dtype=np.uint8).reshape(shape)

    # 显示图片
    cv.imshow('origin', im)
    cv.imshow('recover', im2)

    # 等待键盘输入
    cv.waitKey(0)

    # 释放窗口
    cv.destroyWindow('recover')
    cv.destroyWindow('origin')
