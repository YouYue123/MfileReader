#include "MFile.h"
using namespace std;
#include<fstream>
#include<iostream>
/********* UI所用到的控件指针*******/
 extern GLUI *glui, *glui2;
 extern GLUI_Spinner    *light0_spinner, *light1_spinner;
  extern GLUI_RadioGroup *radio;
  extern GLUI_Panel      *obj_panel;
  extern GLUI_FileBrowser *fb,*ft;
  extern GLUI_EditText *camera_info[9];
  extern GLUI_EditText *obj_info[9];
  extern GLUI_Listbox *list;
/********相机位置信息*************/
extern GLfloat center[3];/// 看向的点 
extern GLfloat eye[3];//位置 
extern GLfloat HeadDirection[3];//头顶朝向
/********球坐标信息*************/
extern GLfloat theta;
extern GLfloat phi;
extern GLfloat r;
/********物体变换信息**********/
extern GLfloat ScaleX,ScaleY,ScaleZ;//缩放变换
extern float view_rotate[16];//旋转变换
extern float obj_pos[] ;//位置变换
/**********定义四种材质*****************/
extern GLfloat BrassA[];
extern GLfloat BrassD[];
extern GLfloat BrassS[];
extern GLfloat BrassNs; 


extern GLfloat GoldA[];
extern GLfloat GoldD[];
extern GLfloat GoldS[];
extern GLfloat GoldNs;

extern GLfloat EmeraldA[];
extern GLfloat EmeraldD[];
extern GLfloat EmeraldS[];
extern GLfloat EmeraldNs;

extern GLfloat VioletA[];
extern GLfloat VioletD[];
extern GLfloat VioletS[];
extern GLfloat VioletNs;
/********窗口信息*****/
extern int   width,height;//初始窗口长宽
extern float xy_aspect;//窗口比例
extern int main_window;//主窗口ID
extern int window_x;//窗口中心
extern int window_y;//窗口中心
/********UI所用到的开关量******/
extern int   FillMode;//填充模式开关
extern int   normal;//法线计算开关
extern float scale ;//缩放比例
extern int UseOtherMtl ;//使用系统模型开关
void MFile::draw_axes()
{
  glDisable(GL_LIGHTING);
  glPushMatrix();


  glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
  
  glColor3f( 1.0f, 1.0f, 1.0f );
  glTranslated(0.0f,0.0f,100.0f);
  glutSolidCone(0.6f,3.0,20.0,1);

  glLoadIdentity();
  glColor3f( 1.0f, 1.0f, 1.0f );
  glTranslated(0.0f,100.0f,0.0f);
  glRotated(90.f,-1.0f,0.0f,0.0f);
  glutSolidCone(0.6f,3.0,20.0,1);

  glLoadIdentity();
  glColor3f( 1.0f, 1.0f, 1.0f );
  glTranslated(100.0f,0.0f,0.0f);
  glRotated(90.f,0.0f,1.0f,0.0f);
  glutSolidCone(0.6f,3.0,20.0,1);
  
  GLUquadricObj *quadratic;
  quadratic=gluNewQuadric();

  glLoadIdentity();
  glColor3f( 1.0, 0.0, 0.0 );
  gluCylinder(quadratic,0.6f,0.6f,100.0f,32,32);//画圆柱

  glLoadIdentity();
  glRotated(90.f,-1.0f,0.0f,0.0f);
  glColor3f( 0.0, 1.0, 0.0 );
  gluCylinder(quadratic,0.6f,0.6f,100.0f,32,32);//画圆柱

  glLoadIdentity();
  glRotated(90.f,0.0f,1.0f,0.0f);
  glColor3f( 0.0, 0.0, 1.0 );
  gluCylinder(quadratic,0.6f,0.6f,100.0f,32,32);//画圆柱

  glPopMatrix();
  glEnable(GL_LIGHTING);
}
void MFile::draw_plane()
{
	 glDisable(GL_LIGHTING);
     int i;
	 glPushMatrix();
     glColor3f( 1.0f, 1.0f, 1.0f );
	 for(i=0;i<31;i++)
	 {
       glBegin( GL_LINES );
	   glVertex3f( -150.0, 0.0, 150.0 - i*10 );  glVertex3f( 150.0, 0.0, 150 - i* 10 );
	   glVertex3f( 150.0 - i*10, 0.0, -150.0 );  glVertex3f( 150.0 - i*10, 0.0, 150.0 );
       glEnd();
	 }
	 glPopMatrix();
	 glEnable(GL_LIGHTING);
}
void MFile::draw_AABB()
{
   glDisable(GL_LIGHTING);
     int i;
	 glPushMatrix();
     glColor3f( 1.0f, 1.0f, 1.0f );
	 //glLineWidth(1.0f);//设置线的粗细
	 glPolygonMode (GL_FRONT_AND_BACK, GL_LINE);	
    glBegin(GL_QUADS);
       glVertex3f( minX,minY,minZ ); 
	   glVertex3f( minX,minY,maxZ );
	   glVertex3f( minX,maxY,maxZ);
	   glVertex3f( minX,maxY,minZ);
    glEnd();
	glBegin(GL_QUADS);
	   glVertex3f( minX,maxY,maxZ);
	   glVertex3f( minX,maxY,minZ);
	   glVertex3f( maxX,maxY,minZ);
	   glVertex3f( maxX,maxY,maxZ);
    glEnd();
	glBegin(GL_QUADS);
	   glVertex3f( maxX,maxY,minZ);
	   glVertex3f( maxX,maxY,maxZ);
	   glVertex3f( maxX,minY,maxZ);
	   glVertex3f( maxX,minY,minZ);
    glEnd();
	glBegin(GL_QUADS);
	   glVertex3f( maxX,minY,minZ);
	   glVertex3f( maxX,minY,maxZ);
	   glVertex3f( minX,minY,maxZ);
	   glVertex3f( minX,minY,minZ);
    glEnd();
	glBegin(GL_QUADS);
	   glVertex3f( minX,maxY,maxZ);
	    glVertex3f( maxX,maxY,maxZ);
		glVertex3f( maxX,minY,maxZ);
	   glVertex3f( minX,minY,maxZ);
    glEnd();  
	glBegin(GL_QUADS);
	   glVertex3f( minX,maxY,minZ);
	   glVertex3f( minX,maxY,maxZ);
	   glVertex3f( maxX,maxY,maxZ);
	   glVertex3f( maxX,maxY,minZ);
    glEnd();  
	 printf("%f %f %f\n%f %f %f\n",minX,minY,minZ,maxX,maxY,maxZ);
	 glPopMatrix();
	 glEnable(GL_LIGHTING);
}
MFile::MFile(char* location)
{ 
	minX = MAX;maxX = MIN;minY = MAX; maxY = MIN; minZ = MAX; maxZ = MIN;
	char content[1024],temp[1024];
	bool normalCal=true;
	int i,j,k,tempData1,tempData2,tempData3;
    vector<vector<int>> tempFaceInfo;
	ifstream F(location);
	if(!F.is_open())
       {
          cout<<"Error in opening File\n";
          exit(1);
       }
	while(!F.eof())
	{
		memset(content,0,sizeof(content));
		F.getline(content,1024);
		switch (content[0])
		{
		 case '#':
			 break;
		 case 'V':
			 struct HE_vert temp_vert;
			 sscanf(content,"%s %d  %f %f %f",temp,&totalVertex,&temp_vert.x,&temp_vert.y,&temp_vert.z);
			 temp_vert.edge = NULL;
			 if(temp_vert.x < minX) minX = temp_vert.x;if(temp_vert.x > maxX) maxX = temp_vert.x;
			 if(temp_vert.y < minY) minY = temp_vert.y;if(temp_vert.y > maxY) maxY = temp_vert.y;
			 if(temp_vert.z < minZ) minZ = temp_vert.z;if(temp_vert.z > maxZ) maxZ = temp_vert.z;
			 verList.push_back(temp_vert);//存入点数据集合
#ifdef TestInputFile
			 printf("V: %d %f %f %f\n",totalVertex,temp_vert.x,temp_vert.y,temp_vert.z);
#endif
			 break;
		 case 'F':
			  vector<int> temp_face;
			  sscanf(content,"%s %d %d %d %d",temp,&totalFace,&tempData1,&tempData2,&tempData3);
			  temp_face.push_back(tempData1-1);
			  temp_face.push_back(tempData2-1);
			  temp_face.push_back(tempData3-1);
#ifdef TestInputFile
			  printf("F: %d %d %d %d\n",totalFace,tempData1,tempData2,tempData3);
#endif
			  tempFaceInfo.push_back(temp_face);
			  break;
		 }
	}//文件读取完毕
	  printf("Finished reading file...V:%d F:%d",verList.size(),tempFaceInfo.size());
	//根据上方读取得到的临时面数据构建半边结构的面集以及边集的部分数据，并同时补全点集中缺失的数据
    for(std::vector<vector<int>>::iterator iter = tempFaceInfo.begin(); iter != tempFaceInfo.end(); iter ++)
	{ 
        HE_face f;
        HE_edge * edges = new HE_edge[3];//新建一组边
        for(i = 0; i < 3; i ++)
		{//填充该边集
            edges[i].next = &edges[(i+1)%3];
            edges[i].vert = &verList.at(iter->at(i));
			edges[i].prev = &edges[(i+2)%3];
			edges[i].pair = NULL;
            edges[i].face = &f;
			edgeList.push_back(&edges[i]);//存入这个指针
			if((verList.begin()+iter->at(i))->edge == NULL) 
			 (verList.begin()+iter->at(i))->edge = &edges[i];//将点指向引用他的第一条边
        }
        f.edge = &edges[0];//面指向第一个 
		//printf("%f %f %f\n",f.edge->vert->x,f.edge->vert->y,f.edge->vert->z);
        faceList.push_back(f);
    }
	printf("E:%d\n",edgeList.size());
	//两层循环，根据上面构建得到的边集数据来补全边集自身缺失的数据
    //具体做法是嵌套两层遍历边集数据的循环，根据半边结构的特性来找出每条边对应的另一条边半边，并补全其缺失对边的数据
	for(vector<struct HE_edge*>::iterator iter = edgeList.begin(); iter != edgeList.end(); iter ++)
	{
	    
		if((*iter)->pair!=NULL) 
			 continue;
		for(vector<struct HE_edge*>::iterator iter2 = iter; iter2 != edgeList.end(); iter2++)
		{
			if((*iter)->next->vert->x == (*iter2)->vert->x && (*iter)->next->vert->y == (*iter2)->vert->y && (*iter)->next->vert->z == (*iter2)->vert->z
                &&(*iter2)->next->vert->x == (*iter)->vert->x && (*iter2)->next->vert->y == (*iter)->vert->y && (*iter2)->next->vert->z == (*iter)->vert->z)
			{
				(*iter)->pair = &*(*iter2);
                (*iter2)->pair = &*(*iter);
				break;
			}
		}
		if((*iter)->pair==NULL)
		{
			printf("模型不规范！\n");
			normalCal = false;
		}
		//if((*iter)==(*iter)->vert->edge)
		 // printf("%x %x\n",(*iter),(*iter)->vert->edge);
	}//半边数据结构数据填充完毕
	/*
	for(vector<struct HE_edge*>::iterator iter = edgeList.begin(); iter != edgeList.end(); iter ++)
	{
		if((*iter)->next->pair==NULL)
			 printf("hello\n");
	}
	*/
	/*
	for(vector<HE_vert>::iterator iter = verList.begin();iter!=verList.end();iter++)
	{
		if(iter->edge->pair == NULL)
			printf("hello!\n");
	}
	*/
  if(normalCal)
  {
    //根据半边数据结构的信息来计算法线（只计算完全包围图形的法线）
	HE_edge *curEdge;
	for(vector<HE_vert>::iterator iter = verList.begin();iter!=verList.end();iter++)//计算每个点的法线
	{
		float x1,y1,z1,x2,y2,z2,x3,y3,z3,resultx,resulty,resultz,Vnx,Vny,Vnz,L,tempx1,tempx2,tempy1,tempy2,tempz1,tempz2;
		float xn,yn,zn;
		curEdge = iter->edge;
		Vnx = 0,Vny = 0;Vnz = 0;
		while(1)
		{	
			x1 = curEdge->vert->x;
			y1 = curEdge->vert->y;
			z1 = curEdge->vert->z;

			x2 = curEdge->next->vert->x;
			y2 = curEdge->next->vert->y;
			z2 = curEdge->next->vert->z;
			
			x3 = curEdge->next->next->vert->x;
			y3 = curEdge->next->next->vert->y;
			z3 = curEdge->next->next->vert->z;
			
			tempx1 = x2 -x1; tempy1 = y2 - y1; tempz1 = z2 - z1;
			tempx2 = x3 -x2; tempy2 = y3 - y2; tempz2 = z3 - z2;

			resultx = tempy1 * tempz2 - tempz1 * tempy2;
            resulty = tempz1 * tempx2 - tempx1 * tempz2;
            resultz = tempx1 * tempy2 - tempy1 * tempx2;
			//printf("点未归一化%f %f %f\n",resultx,resulty,resultz);
			L = sqrt(resultx*resultx+resulty*resulty+resultz*resultz);
			resultx /= L; resulty /= L; resultz /= L;
			//printf("点归一化 %f %f %f\n",resultx,resulty,resultz);
			//resultx = (y2-y1) * (z3-z2) - (z2-z1) * (y3-y2);//叉乘算出法向量
			//resulty = (z2-z1) * (x3-x2) - (x2-x1) * (z3-z2);
			//resultz = (x2-x1) * (y3-y2) - (y2-y1) * (x3-x2);

			Vnx +=resultx; Vny += resulty; Vnz += resultz;//累加起来
			curEdge = curEdge->pair->next;//取下一个面
			
			if(curEdge == iter->edge)
				break;
		}//遍历所有邻接面
		  //printf("Normal 未归一化\n:%f %f %f",Vnx,Vny,Vnz);
		  L = sqrt(Vnx*Vnx+Vny*Vny+Vnz*Vnz);
		  Vnx /= L;Vny /= L;Vnz /= L;//归一化
		  iter->nx = Vnx; iter->ny = Vny; iter->nz = Vnz;
		  //printf("Normal: %f %f %f\n",iter->nx,iter->ny,iter->nz);
	 }//for
   }//if
}
MFile::~MFile(void)
{
}
void MFile::DrawModel(void)
{
	 int i,j;
     char temp[32];
	 HE_edge *cur;
	 glClearColor(0.0, 0.0, 0.0, 0.0);
     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
     glColor3f(1.0,1.0,1.0);
	 glViewport(window_x,window_y,(GLsizei)width,(GLsizei)height);
	 eye[0] = r*sin(theta)*sin(phi);
     eye[1] = r*cos(theta);
     eye[2] = r*sin(theta)*cos(phi);
     //HeadDirection[0] =  sin(phi);
     HeadDirection[1] = sin(theta);
	 //HeadDirection[2] = 1/sin(phi);
	 sprintf(temp,"%lf",eye[0]);camera_info[0]->text = temp;camera_info[0]->redraw();
	 sprintf(temp,"%lf",eye[1]);camera_info[1]->text = temp;camera_info[1]->redraw();
	 sprintf(temp,"%lf",eye[2]);camera_info[2]->text = temp;camera_info[2]->redraw();
	 sprintf(temp,"%lf",center[0]);camera_info[3]->text = temp;camera_info[3]->redraw();
	 sprintf(temp,"%lf",center[1]);camera_info[4]->text = temp;camera_info[4]->redraw();
	 sprintf(temp,"%lf",center[2]);camera_info[5]->text = temp;camera_info[5]->redraw();
	 sprintf(temp,"%lf",HeadDirection[0]);camera_info[6]->text = temp;camera_info[6]->redraw();
	 sprintf(temp,"%lf",HeadDirection[1]);camera_info[7]->text = temp;camera_info[7]->redraw();
	 sprintf(temp,"%lf",HeadDirection[2]);camera_info[8]->text = temp;camera_info[8]->redraw();

	 sprintf(temp,"%lf",obj_pos[0]);obj_info[0]->text = temp;obj_info[0]->redraw();
	 sprintf(temp,"%lf",obj_pos[1]);obj_info[1]->text = temp;obj_info[1]->redraw();
	 sprintf(temp,"%lf",-obj_pos[2]);obj_info[2]->text = temp;obj_info[2]->redraw();
	  glMatrixMode(GL_PROJECTION);
	  glLoadIdentity();
	  gluPerspective(60, xy_aspect, 0.001,30000);
	  gluLookAt(eye[0],eye[1],eye[2],
               center[0],center[1],center[2],
               HeadDirection[0],HeadDirection[1],HeadDirection[2]);
	  glMatrixMode(GL_MODELVIEW);
	  glLoadIdentity();
	  switch(UseOtherMtl)
		{
		case 0 :
			 break;
		case 1:;
			glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,BrassA);//环境反射
			glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE, BrassD);//漫反射
			glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,BrassS);//镜面反射
			glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,BrassNs);//高光
			UseOtherMtl = 0;
			break;
		case 2:
			glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,GoldA);//环境反射
			glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE, GoldD);//漫反射
			glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,GoldS);//镜面反射
			glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,GoldNs);//高光
			UseOtherMtl = 0;
			break;
		case 3:
			glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,EmeraldA);//环境反射
			glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE, EmeraldD);//漫反射
			glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,EmeraldS);//镜面反射
			glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,EmeraldNs);//高光
			UseOtherMtl = 0;
			break;
		case 4:
			glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,VioletA);//环境反射
			glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE, VioletD);//漫反射
			glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,VioletS);//镜面反射
			glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,VioletNs);//高光
			UseOtherMtl = 0;
			break;
		default:
			UseOtherMtl = 0;
			 break;
		}
	  draw_axes();
	  draw_plane();
	  //glEnable(GL_NORMALIZE);
	  glPushMatrix();
	   //glEnable(GL_CULL_FACE);
	  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);//设置混合方式
	  glEnable(GL_BLEND);//启用混合
      glTranslatef( obj_pos[0], obj_pos[1], -obj_pos[2] ); 
      glScaled(ScaleX,ScaleY,ScaleZ);
	  glMultMatrixf( view_rotate );
	  draw_AABB();
	   if(FillMode==0)
	{
	  glPolygonMode (GL_FRONT_AND_BACK, GL_LINE);	
	}
	 else
	 {
	   glPolygonMode (GL_FRONT_AND_BACK, GL_FILL);	
	 }
	 for(vector<HE_face>::iterator iter= faceList.begin();iter!=faceList.end();iter++)
      {
		  glBegin(GL_POLYGON);
		  cur = iter->edge;
		  do
		  {
			  if(normal==1)//开启法线
			  {
			   glNormal3f(cur->vert->nx,cur->vert->ny,cur->vert->nz);
			   //printf("%f %f %f\n",cur->vert->nx,cur->vert->ny,cur->vert->nz);
			  }
 			  glVertex3f(cur->vert->x,cur->vert->y,cur->vert->z);
			  cur = cur->next;
		  }while(cur!=iter->edge);
		  glEnd();
		 
	 }
	 glDisable(GL_BLEND);//禁止混合
	 glPopMatrix();
	 glFlush();
     glutSwapBuffers();
	 return;
}