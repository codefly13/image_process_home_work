# -*- coding:utf-8 -*-

import cv2 as cv
import numpy as np
from collections import defaultdict
from bigfloat import *

def static(dataSet):
    """
    统计像素的(累积)分布

    Input
    dataSet: 整型或字符型列表或者numpy 1d array

    return:
    acpro， 字典，键值分别表示一个字符（或数字）和相应的概率（累积）分别区间。如{'a', [0, 0.5]}
    """
    # 初始化
    length,dataDict=float(len(dataSet)),defaultdict(lambda : 0)

    # 统计出现次数
    acpro = []
    for data in dataSet:
        dataDict[data]+=1

    # 计算概率
    for key in dataDict:
        dataDict[key] /= length

    # 计算累积分布
    for key in dataDict:
         acpro.append([key, [0.0, dataDict[key]]])
    for i in range(len(acpro)-1):
        [low ,high] = acpro[i][1]
        acpro[i+1][1] = [high, high+acpro[i+1][1][1]]

    # 将列表转化为字典
    acpro = dict(acpro)
    return acpro


def compress(dataSet, acpro, prs):
    """
    算术编码压缩数据

    Input
    dataSet: 字符串或者整型列表
    acpro: 字典，键值分别表示一个字符（或数字）和相应的概率（累积）分别区间。如{'a', [0, 0.5]}
    prs: 精度

    return
    code，float, 编码
    """

    # 生成prs精度的类型
    low = BigFloat.exact('0.0', precision=prs)
    rg = BigFloat.exact('1.0', precision=prs)

    print("压缩")
    # 运算过程中设置浮点运算精度为prs
    with precision(prs):
        for c in dataSet:
            rl, rh = acpro[c]
            low2 = low + rg*rl
            high2 = low + rg*rh
            low, high = low2, high2
            rg = high - low

    code = low
    print("code：", code)
    return code


def decompress(length, acpro, code, prs):
    """
    算术编码解压数据

    Input
    dataSet: 字符串或者整型列表
    acpro: 字典，键值分别表示一个字符（或数字）和相应的概率（累积）分别区间。如{'a', [0, 0.5]}
    prs: 精度

    return
    code，float, 编码
    """

    # 生成prs精度的类型
    low = BigFloat.exact('0.0', precision=prs)
    rg = BigFloat.exact('1.0', precision=prs)

    # 解压
    data = []
    number = code
    print("解码开始")

    # 运算过程中设置浮点运算精度为prs
    with precision(prs):
        flag = 0
        for i in range(int(length)):
            if i % 200 == 0 and flag == 0:
                print('{0}%'.format(int(i/length*100)))
            elif (length - i - 1 < 100) and (flag == 0):
                flag += 1
                print("100%")
            number = (number - low)/rg
            for key in acpro:
                ll, hh = acpro[key]
                if ll<=number and number<hh:
                    low = ll
                    rg = hh - ll
                    data.append(key)
                    break
    print("解码结束")
    return data



