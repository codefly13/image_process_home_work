'''
Created on 2016-12-6
@author: gavin
'''

#import cv module
import cv2 as cv
import sys
 
if __name__ == '__main__':
    # Declare the IplImage
    pImg = None
    pContourImg = None
 
    contour = None
    mode = cv.RETR_EXTERNAL
 
    # Create Windows
 
    cv.namedWindow("src", 1)
    cv.namedWindow("gray", 2)
    cv.namedWindow("binary", 3)
    cv.namedWindow("contour", 4)
 
    # Load Image, Convert to Gray by force
 
    pImg = cv.imread("test2.jpg") # A image in the same directory of the file.
    cv.imshow("src", pImg)

    """ cvtColor(src, code[, dst[, dstCn]]) -> dst
        src：原图像。
        code：颜色空间装换编码。
            COLOR_RGB2BGRA
            COLOR_BGRA2RGB
            ...
        dst：目标图像。
        dstCn：目标图像的通道数。如果是0，则根据code和dst推导出来。
    """
    gray_pImg = cv.cvtColor(pImg, cv.COLOR_RGB2GRAY)
    cv.imshow("gray", gray_pImg)

    # 转换成2值图像
    """ threshold(src, thresh, maxval, type[, dst]) -> retval, dst
        type:
            HRESH_BINARY: dist(x,y) = [maxval if src(x,y) > thresh else 0][0]
            THRESH_BINARY_INV: dist(x,y) = [0 if src(x,y) > thresh else maxval][0]
            THRESH_TRUNC: dist(x,y) = [thresh if src(x,y) > thresh else src(x,y)][0]
            THRESH_TOZERO: dist(x,y) = [src(x,y) if src(x,y) > thresh else 0][0]
            THRESH_TOZERO_INV: dist(x,y) = [0 if src(x,y) > thresh else src(x,y)][0]
    """
    ret, binary = cv.threshold(gray_pImg, 180, 255, cv.THRESH_BINARY)
    # 黑白转换
    binary = 255 - binary
    cv.imshow("binary", binary)

    # Find contours
    """ findContours(image, mode, method[, contours[, hierarchy[, offset]]]) -> image, contours, hierarchy
        image： 二值图像，原图会被改变。
        contours： contours[i]存放第i个轮廓的点。
        hiararchy: 存放轮廓的层次结构。hiararchy[0][i][0], hiararchy[0][i][1], hiararchy[0][i][2], hiararchy[0][i][3]。分别表示
                    轮廓的下一个轮廓，上一个轮廓， 上一层轮廓，下一层轮廓。
        mode：
            RETR_EXTERNAL 只检测出外轮廓。
            RETR_LIST 检出所有的轮廓，并将它们保存到list中。
            RETR_CCOMP 检出所有的轮廓并将它们组织成双层结构，顶层是外层边界，第二层是空的边界。
            RETR_TREE 检出所有的轮廓并且重新建立网状结构。
        method:
            CHAIN_APPROX_NONE 存储所有的轮廓点，轮廓点间距离不超过1。
            CHAIN_APPROC_SAMPLE 压缩水平，垂直或斜的部分，只保存最后一个点。
            CV_CHAIN_APPROX_TC89_L1,CV_CHAIN_APPROX_TC89_KCOS 使用Teh-Chin逼近算法的一个。
        offset: 相对位置，使用ROI时候很有用。
    """
    image, contours, hierarchy = cv.findContours(binary, cv.RETR_CCOMP, cv.CHAIN_APPROX_SIMPLE)

    """ drawContours(image, contours, contourIdx, color[, thickness[, lineType[, hierarchy[, maxLevel[, offset]]]]]) -> image
        image：目标图像
        contours：轮廓数据
        contourIdx：轮廓的索引，如果为-1，则绘制所有轮廓。
        color：轮廓的颜色
        thickness：轮廓的厚度。-1时候为填充模式。
        lineType：
            8 (or 0) - 8-connected line（8邻接)连接线。
            4 - 4-connected line(4邻接)连接线。
            CV_AA - 抗锯齿线条。
        hierarchy：轮廓的网络结构。
        maxLevel：遍历轮廓的最大层次。-1时候，只有输入轮廓会被画出，-2时候输入轮廓及其子节点会被画出。
        offset：轮廓的相对位置。
    """
    cv.drawContours(pImg, contours, 0, (255, 0, 0), 1, 8, hierarchy=hierarchy, maxLevel=-1, offset=(10,0))
    cv.drawContours(pImg, contours, 1, (255, 0, 0), 4, 4, hierarchy=hierarchy, maxLevel=-1, offset=(10,0))
    cv.drawContours(pImg, contours, 2, (0, 255, 0), 4, 8, hierarchy=hierarchy, maxLevel=-1, offset=(0,0))
    cv.drawContours(pImg, contours, 3, (0, 255, 0), 8, 4, hierarchy=hierarchy, maxLevel=-1, offset=(0,0))
    cv.drawContours(pImg, contours, 4, (0, 255, 0), 6, 4, hierarchy=hierarchy, maxLevel=-1, offset=(0,0))
    cv.drawContours(pImg, contours, 5, (0, 0, 255), 2, cv.LINE_AA, hierarchy=hierarchy, maxLevel=-1, offset=(0,0))
    cv.drawContours(pImg, contours, 6, (0, 0, 255), 8, 4, hierarchy=hierarchy, maxLevel=-1, offset=(0,0))
    cv.imshow("contour", pImg)

    # 等待按键
    cv.waitKey(0)
    # Destory Windows
    cv.destroyWindow("src")
    cv.destroyWindow("binary")
    cv.destroyWindow("gray")
    cv.destroyWindow("contour")
    sys.exit(0)