#ifndef GRAY_H_INCLUDED
#define GRAY_H_INCLUDED

#include"rw_bmp.h"

/*
① 最大值法：这种方法原理是使RGB的值等于三个色彩分量中最大的一个分量，即：R=G=B=max（R、G、B）。
使用最大值法处理后的灰度图像亮度会偏高。
② 平均值法：这种方法的原理是使R、G、B的值等于三个色彩分量的平均值，即：R=G=B（R+G+B）/3。
使用平均值法处理后的灰度图像亮度较为柔和。
③ 加权平均值法：这种方法是根据重要性或其他指标给R、G、B赋予不同的权值，并使R、G、B等于它们的加权值，即R=G=B=aR+bG+cB，
其中，a、b、c分别是R、G、B的权值。当其权值a、b、c取不同的值时，加权法能够形成不同灰度的灰度图像。
由于人眼对绿色的敏感度最高，红色次之，对蓝色的敏感度最低，因此，当权值b>a>c时，所生成的灰度图像更符合人眼的视觉感受。
通常，当a=30%,b=59%,c=11%时，这种图像的灰度最为合理。上述三种方法形成的灰度图像各不相同，
通常，使用加权平均法进行灰度处理后的灰度图像最为符合视觉享受。
*/

// 取值可以是1,2,3,对应的方法分别是最大值法，平均值法，加权法
bmp gray(bmp bitp, int method);

#endif // GRAY_H_INCLUDED
