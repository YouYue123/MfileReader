#pragma once
using namespace std;
#include"Debug.h"
#include"halfEdge.h"
#include"global.h"
#include<vector>
class MFile
{
 public:
	MFile(char * location);//构造函数直接读取文件填充容器
	~MFile(void);
	void DrawModel();
 private:
	 void draw_AABB();
	 void draw_axes();
	 void draw_plane();
	 vector<struct HE_vert> verList;//点列表容器
	 vector<struct HE_edge*> edgeList;//边列表容器
	 vector<struct HE_face> faceList;//面列表容器
	 int totalVertex;
	 int totalFace;
	 float minX,maxX,minY,maxY,minZ,maxZ;
};

