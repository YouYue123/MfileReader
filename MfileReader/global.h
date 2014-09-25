#ifndef GLOBAL_H
#define GLOBAL_H
#include<GL/glut.h>
#include<gl/glui.h>
/******设置参数*************/
#define MaxPointNumber 32768//最大容纳点个数
#define MaxFaceNumber 32768//最大容纳面个数
#define MaxMtlNumber 1024//最大容纳材质个数
#define MaxGroupNumber 128//最大容纳组个数
#define MtlFileLength 256//材质文件名最大长度
#define PI 3.14159265359
#define MoveSpeed 1.1//相机移动速度
#define SpinSpeed PI/18//旋转速度
#define ScaleSpeed 0.05//缩放速度
#define MaxCommonFace 16
#define checkImageWidth 64
#define checkImageHeight 64
#define MAX 65535
#define MIN -65535
/********** UI控件所用到的ID ********/
#define LIGHT0_ENABLED_ID    200
#define LIGHT1_ENABLED_ID    201
#define LIGHT0_INTENSITY_ID  250
#define LIGHT1_INTENSITY_ID  260
#endif