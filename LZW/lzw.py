# -*- coding:utf-8 -*-

def encode(dataSet):
    """
    lzw编码, 只能对0~255之间的数据或者字符串数据进行编码
    input
    dataSet: list或者1维numpy array。元素的类型是char或者uint8
    return
    inv_lzwDict: dict，键值分别代表码字值（int型），原始子串（str类型）
    code: list，元素类型是int，代表编码（码字）。
    """

    # 将数据转换为字符型
    dataSet = [item if type(item)==str else chr(item) for item in dataSet]

    # 初始字典化字典
    lzwDict = {}
    for i, c in enumerate(set(dataSet)):
        lzwDict[c] = i

    # lzw编码
    code = []
    p = ''
    for c in dataSet:
        if p+c in lzwDict:
            p = p+c
        else:
            code.append(lzwDict[p])
            lzwDict[p+c] = len(lzwDict) + 1
            p = c

    code.append(lzwDict[p])

    # 将键值位置转换生成新的字典
    inv_lzwDict = {}
    for key in lzwDict:
        inv_lzwDict[lzwDict[key]] = key

    return inv_lzwDict, code


def decode(inv_lzwDict, code):
    """
    解码
    Input
    inv_lzwDict: 键值分别代表码字值（int型），原始子串（str类型）
    code: list，元素类型是int，代表编码（码字）。

    Return
    s，字符串。如果原始数据是0~255的数据，那么每个字符的assci码表示原始数据。如果是字符则s便是原始数据
    """

    s = []
    for cc in code:
        s.extend(inv_lzwDict[cc])
    "".join(s)
    return s


