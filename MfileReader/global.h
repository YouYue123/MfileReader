#ifndef GLOBAL_H
#define GLOBAL_H
#include<GL/glut.h>
#include<gl/glui.h>
/******���ò���*************/
#define MaxPointNumber 32768//������ɵ����
#define MaxFaceNumber 32768//������������
#define MaxMtlNumber 1024//������ɲ��ʸ���
#define MaxGroupNumber 128//������������
#define MtlFileLength 256//�����ļ�����󳤶�
#define PI 3.14159265359
#define MoveSpeed 1.1//����ƶ��ٶ�
#define SpinSpeed PI/18//��ת�ٶ�
#define ScaleSpeed 0.05//�����ٶ�
#define MaxCommonFace 16
#define checkImageWidth 64
#define checkImageHeight 64
#define MAX 65535
#define MIN -65535
/********** UI�ؼ����õ���ID ********/
#define LIGHT0_ENABLED_ID    200
#define LIGHT1_ENABLED_ID    201
#define LIGHT0_INTENSITY_ID  250
#define LIGHT1_INTENSITY_ID  260
#endif