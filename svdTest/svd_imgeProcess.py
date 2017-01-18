"""reference
http://www.cnblogs.com/LeftNotEasy/archive/2011/01/19/svd-and-applications.html
"""

import numpy as np
import cv2

def svd(c):
    """list of 2d array. a = U S V.H,
    The v return this functions is u = U, t = S, v = V.H"""
    c = c.astype(np.float)
    namuda, v = np.linalg.eig(np.dot(c.T, c))
    theta = np.sqrt(namuda)
    u = np.dot(c, v)/theta
    idx = np.argsort(namuda)[::-1]
    return [u[:, idx], theta[idx], v[:, idx].T]


def SVD_inverse(u, namuda, v, k):
    namuda = np.array(namuda)
    tmp = np.dot(u[:, :k], np.diag(namuda[:k]))
    # 注意， 这里的v在函数外已经转置过了。每行都是一个特征向量
    new_c = np.dot(tmp, v[:k, :])
    return new_c


if __name__ == "__main__":
    img = cv2.imread("Lena_512512.bmp")
    channels = cv2.split(img)
    for k in list(range(5, min(50, len(channels[0])), 5)) + list(range(50, len(channels[0]), 50)):
        new_img = []
        for c in channels:
            [u, theta, v] = svd(c)
            # print([[len(w), v.shape], [len(theta), u.shape], b.shape])
            new_img.append(SVD_inverse(u, theta, v, k).astype(np.uint8))
        new_img = cv2.merge(new_img)
        cv2.imwrite("result\\new{0}.jpg".format(k), new_img)