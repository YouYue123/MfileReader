#pragma once
using namespace std;
#include"Debug.h"
#include"halfEdge.h"
#include"global.h"
#include<vector>
class MFile
{
 public:
	MFile(char * location);//���캯��ֱ�Ӷ�ȡ�ļ��������
	~MFile(void);
	void DrawModel();
 private:
	 void draw_AABB();
	 void draw_axes();
	 void draw_plane();
	 vector<struct HE_vert> verList;//���б�����
	 vector<struct HE_edge*> edgeList;//���б�����
	 vector<struct HE_face> faceList;//���б�����
	 int totalVertex;
	 int totalFace;
	 float minX,maxX,minY,maxY,minZ,maxZ;
};

