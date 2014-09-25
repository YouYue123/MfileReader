// MfileReader.cpp : 定义控制台应用程序的入口点。
//
#define GLUT_DISABLE_ATEXIT_HACK 
#include "stdafx.h"
#include"MFile.h"
MFile *M = NULL;
/********* UI所用到的控件指针*******/
 GLUI *glui, *glui2;
 GLUI_Spinner    *light0_spinner, *light1_spinner;
 GLUI_RadioGroup *radio;
 GLUI_Panel      *obj_panel;
 GLUI_FileBrowser *fb,*ft;
 GLUI_EditText *camera_info[9];
 GLUI_EditText *obj_info[9];
 GLUI_Listbox *list;
/********** 全局灯光信息 **********/
 GLfloat LightAmbient[]= { 1.0f, 1.0f, 1.0f, 1.0f };//环境光反射 	
 GLfloat LightDiffuse[]= { 1.0f, 1.0f, 1.0f, 1.0f };	//漫反射
 GLfloat LightSpecular[] = {1.0f,1.0f,1.0f,1.0f};//镜面反射
 GLfloat LightPosition[]= { 0.0f, 0.0f, 1000.0f, 1.0f };//灯光位置

 GLfloat Light1Ambient[]= { 1.0f, 1.0f, 1.0f, 1.0f }; 	
 GLfloat Light1Diffuse[]= { 1.0f, 1.0f, 1.0f, 1.0f };
 GLfloat Light1Specular[] = {1.0f,1.0f,1.0f,1.0f};
 GLfloat Light1Position[] = { 0.0f, 0.0f, -1000.0f, 1.0f };
/********鼠标信息全局变量********/
 GLboolean MouseLDown = GL_FALSE;
 GLboolean MouseRDown = GL_FALSE;
 GLboolean MouseMDown = GL_FALSE;
 GLint mousex = 0, mousey = 0;//鼠标位置
 int LastP[2];//记录鼠标之前的位置
/********相机位置信息*************/
 GLfloat center[3] = {0.0f, 0.0f, 0.0f};/// 看向的点 
 GLfloat eye[3];//位置 
 GLfloat HeadDirection[3]={0.0f,1.0f,0.0f};//头顶朝向
/********球坐标信息*************/
 GLfloat theta = 0.5 * PI;
 GLfloat phi = 0.0;
 GLfloat r = 100.0;
/********物体变换信息**********/
 GLfloat ScaleX=1.0f,ScaleY=1.0f,ScaleZ=1.0f;//缩放变换
 float view_rotate[16] = { 1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1 };//旋转变换
 float obj_pos[] = { 0.0, 0.0, 0.0 };//位置变换
/**********定义四种材质*****************/
 GLfloat BrassA[] = {0.329412f, 0.223529f, 0.027451f, 1.000000f};
 GLfloat BrassD[] = {0.780392f, 0.568627f, 0.113725f, 1.000000f};
 GLfloat BrassS[] = {0.992157f, 0.941176f, 0.807843f, 1.000000f};
 GLfloat BrassNs = 27.897400f;


 GLfloat GoldA[] = {0.247250f, 0.199500f, 0.074500f, 1.000000f};
 GLfloat GoldD[] = {0.751640f, 0.606480f, 0.226480f, 1.000000f};
 GLfloat GoldS[] = {0.628281f, 0.555802f, 0.366065f, 1.000000f};
 GLfloat GoldNs = 51.200001f;

 GLfloat EmeraldA[] = {0.021500f, 0.174500f, 0.021500f, 0.550000f};
 GLfloat EmeraldD[] = {0.075680f, 0.614240f, 0.075680f, 0.550000f};
 GLfloat EmeraldS[] = {0.633000f, 0.727811f, 0.633000f, 0.550000f};
 GLfloat EmeraldNs = 76.800003f;

 GLfloat VioletA[] = {0.110000f, 0.060000f, 0.090000f, 1.000000f};
 GLfloat VioletD[] = {0.430000f, 0.470000f, 0.540000f, 1.000000f};
 GLfloat VioletS[] = {0.330000f, 0.330000f, 0.520000f, 1.000000f};
 GLfloat VioletNs = 22.0000f;
/********窗口信息*****/
 int   width = 1366,height = 768;//初始窗口长宽
 float xy_aspect = 1366/768;//窗口比例
 int main_window;//主窗口ID
 int window_x = (glutGet (GLUT_SCREEN_WIDTH) - width)/2;//窗口中心
 int window_y = (glutGet (GLUT_SCREEN_HEIGHT) - height)/2;//窗口中心
/********UI所用到的开关量******/
 int   FillMode = 0;//填充模式开关
 int   normal = 0;//法线计算开关
 int   light0_enabled = 1;//光源开关
 int   light1_enabled = 1;
 float light0_intensity = 1.0;//光源强度
 float light1_intensity = 1.0;
 float scale = 1.0;//缩放比例
 float smooth = 1.0;//平滑程度
 int UseOtherMtl = 0;//使用系统模型开关
 char FileName[128];//文件名
 int shade_type=1;
/***************Texture**************/
 GLubyte checkImage[checkImageHeight][checkImageWidth][4];
void control_cb( int control)
{
  if(control == 4)
  {
	  switch(radio->get_int_val())
	  {
	  case 0:
		  glShadeModel(GL_FLAT);//设置Shade的方式GL_SMOOTH或者GL_FLAT;
		  break;
	  case 1:
		  glShadeModel(GL_SMOOTH);//设置Shade的方式GL_SMOOTH或者GL_FLAT
		  break;
	  }
	  glutPostRedisplay();
	  return;
  }
  if(control == 7)
  {
	  if(!strstr(fb->get_file(),".m"))
	{
		printf("File Type Error!\n");
		return;
	}
	else
	{
	   strcpy(FileName,fb->get_file());
	   if(M)
		  delete(M);
	    M = new MFile(FileName);	
		glutPostRedisplay();
		 return;
	}
  }
  if(control == 8)
  {
	     ScaleX = scale;
         ScaleY = scale;
         ScaleZ = scale;
         glutPostRedisplay();
		 return;
  }
  if(control == 9)
  {
	   glutPostRedisplay();
		 return;
  }
   if(control == 10)
  {      
		 UseOtherMtl = list->get_int_val();
	     glutPostRedisplay();
		 return;  
  }
  if(control==16)
  {
	    glutPostRedisplay();
		return;
  }
  if(control==21)
  {
	  glutPostRedisplay();
	  return;
  }
  if ( control == LIGHT0_ENABLED_ID ) 
  {
    if ( light0_enabled ) 
	{
      glEnable( GL_LIGHT0 );
      light0_spinner->enable();
    }
    else 
	{
      glDisable( GL_LIGHT0 ); 
      light0_spinner->disable();
    }
  }
  else if ( control == LIGHT1_ENABLED_ID ) 
  {
    if ( light1_enabled ) 
	{
      glEnable( GL_LIGHT1 );
      light1_spinner->enable();
    }
    else 
	{
      glDisable( GL_LIGHT1 ); 
      light1_spinner->disable();
    }
  }
  else if ( control == LIGHT0_INTENSITY_ID ) 
  {
    float v[] = 
	{ 
      LightDiffuse[0],  LightDiffuse[1],
      LightDiffuse[2],  LightDiffuse[3] 
	};
    
    v[0] *= light0_intensity;
    v[1] *= light0_intensity;
    v[2] *= light0_intensity;

    glLightfv(GL_LIGHT0, GL_DIFFUSE, v );
  }
  else if ( control == LIGHT1_INTENSITY_ID ) 
  {
    float v[] = 
	{ 
      Light1Diffuse[0],   Light1Diffuse[1],
       Light1Diffuse[2],   Light1Diffuse[3] 
	};
    
    v[0] *= light1_intensity;
    v[1] *= light1_intensity;
    v[2] *= light1_intensity;

    glLightfv(GL_LIGHT1, GL_DIFFUSE, v );
  }
  glutPostRedisplay();
  return;
}
void Display()
{
	if(M)
	M->DrawModel();
}
void myGlutReshape( int x, int y )
{
  int tx, ty, tw, th;

  GLUI_Master.reshape();
  GLUI_Master.get_viewport_area( &tx, &ty, &tw, &th );
  glViewport( tx, ty, tw, th );

  window_x = tx;window_y = ty;
  width = tw;height = th;

  xy_aspect = (float)tw / (float)th;
  glutPostRedisplay();
}
void InputKey(unsigned char key, int x, int y)
{
   float x1,x2,y1,y2,z1,z2;
   x1 = eye[0];y1 = eye[1];z1 = eye[2];
   x2 = center[0];y2 = center[1]; z2 = center[2];
   if(key=='s'||key=='S')
    {
        r *= MoveSpeed;
		printf("r:%f\n",r);
    }
   if(key=='w'||key=='W')
    {
        r /= MoveSpeed;  
    }
   if(key=='d'||key=='D')
    {
         phi += SpinSpeed;
    }
   if(key=='a'||key=='A')
    {
         phi -= SpinSpeed;
    } 
   if(key=='=')
    {
         ScaleX += ScaleSpeed;
         ScaleY += ScaleSpeed;
         ScaleZ += ScaleSpeed;
         glutPostRedisplay();   
		 return;
    } 
   if(key=='-')
   {
         ScaleX -= ScaleSpeed;
         ScaleY -= ScaleSpeed;
         ScaleZ -= ScaleSpeed;
         glutPostRedisplay();
		 return;
   }
   glutPostRedisplay();
   return;
} 
void MouseClick(int button,int state,int x,int y)
{
    if(button == GLUT_RIGHT_BUTTON)
           MouseRDown = !MouseRDown;
    if(button == GLUT_LEFT_BUTTON)
           MouseLDown = !MouseRDown;
    if(MouseRDown)
     {
       LastP[0] = x;
       LastP[1] = y;
     }
    if(MouseLDown)
    {
      LastP[0] = x;
      LastP[1] = y;             
    }     
}
void MouseMove(int x,int y)
{
     if(MouseRDown)
       {
           phi   += (LastP[0]-x)*PI/720;
           theta += (LastP[1]-y)*PI/720;
           LastP[0] = x;
           LastP[1] = y;
           glutPostRedisplay();
       }
     if(MouseLDown)
      {
         obj_pos[0] += cos(phi) *  (x - LastP[0])/10;
         obj_pos[1] += sin(theta)* (LastP[1] - y)/10;
         obj_pos[2] -= cos(theta)*(LastP[1] - y)/5 + sin(phi) * (LastP[0] - x)/5;
         LastP[0] = x;
         LastP[1] = y;
         glutPostRedisplay();
      }
}
void Init()
{
	/*
	 glClearColor (0.0, 0.0, 0.0, 0.0); //设置背景
    glClearDepth(1.0f);	//设置深度缓冲的值
    //设置光照
    glLightfv(GL_LIGHT1, GL_AMBIENT, Light1Ambient); //设置环境光颜色	
	glLightfv(GL_LIGHT1, GL_DIFFUSE, Light1Diffuse); //设置漫反射光颜色
	glLightfv(GL_LIGHT1,GL_SPECULAR,Light1Specular);
	glLightfv(GL_LIGHT1, GL_POSITION,Light1Position);//设置光源位置

    glLightfv(GL_LIGHT0, GL_AMBIENT, LightAmbient); //设置环境光颜色	
	glLightfv(GL_LIGHT0, GL_DIFFUSE, LightDiffuse); //设置漫反射光颜色
	glLightfv(GL_LIGHT0,GL_SPECULAR,LightSpecular);
	glLightfv(GL_LIGHT0, GL_POSITION,LightPosition);//设置光源位置

	glEnable(GL_LIGHT1);//启用光照LIGHT1
	glEnable(GL_LIGHT0);//启用光照LIGHT2
    glEnable(GL_LIGHTING);//启用光照

    glDepthFunc(GL_LEQUAL);//设置深度测试函数
    glEnable(GL_DEPTH_TEST);//启用深度测试
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	*/
	glShadeModel(GL_SMOOTH);//设置Shade的方式GL_SMOOTH或者GL_FLAT
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    GLfloat ambient[] = {1.0f, 1.0f, 1.0f, 0.0f};
    GLfloat diffuse[] = {1.0f, 1.0f, 1.0f, 0.0f};
    GLfloat specular[] = {1.0f, 1.0f, 1.0f, 0.0f};
    GLfloat position[] = {-300.0f, 300.0f, 300.0f, 0.0f};
    //glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glEnable(GL_DEPTH_TEST);
    //glDepthFunc(GL_LESS);//指定深度比较中使用的数值
    glShadeModel(GL_SMOOTH);
    
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
    
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    
    GLfloat light_position[] = { 0.0, 50.0, 300.0, 0.0 };
    glLightfv(GL_LIGHT1, GL_POSITION, light_position);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT1);
}
void myGlutIdle( void )
{
  /* According to the GLUT specification, the current window is 
     undefined during an idle callback.  So we need to explicitly change
     it if necessary */
  if ( glutGetWindow() != main_window ) 
    glutSetWindow(main_window);  

  //glutPostRedisplay();
}
int main(int argc,char** argv)	
{
	M = new MFile("knot.m");
	glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
    glutInitWindowPosition(window_x,window_y);
    glutInitWindowSize(width,height);
    main_window = glutCreateWindow("M File Reader");
   
	Init();
	
    GLUI_Master.set_glutReshapeFunc( myGlutReshape ); 
    GLUI_Master.set_glutSpecialFunc( NULL );

    /****************************************/
    /*         Here's the GLUI code         */
    /****************************************/

	glui = GLUI_Master.create_glui_subwindow( main_window,GLUI_SUBWINDOW_RIGHT );
	obj_panel = new GLUI_Rollout(glui, "Properties", true);
    
	new GLUI_Checkbox( obj_panel, "FillMode", &FillMode,1,control_cb);//线框模式checkbox
	new GLUI_Checkbox( obj_panel, "Normalization", &normal,16,control_cb);//法线模式checkbox

    new GLUI_Separator( obj_panel);
	
	GLUI_Panel *type_panel = new GLUI_Panel( obj_panel, "Render Mode" );
    radio = new GLUI_RadioGroup(type_panel,&shade_type,4,control_cb);
    new GLUI_RadioButton( radio, "Flat" );
    new GLUI_RadioButton( radio, "Smooth" );


	new GLUI_Separator( obj_panel);

	list =new GLUI_Listbox(obj_panel,"Material",(int*)0,10,control_cb);  
	list->add_item(1,"Brass");
	list->add_item(2,"Gold");
	list->add_item(3,"Emerald");
	list->add_item(4,"Violet");
	list->set_alignment(GLUI_ALIGN_RIGHT);

	new GLUI_Separator( obj_panel);

    GLUI_Spinner *scale_spinner = new GLUI_Spinner( obj_panel, "Scale:", &scale,8,control_cb);
    scale_spinner->set_float_limits( .2f, 4.0 );
    scale_spinner->set_alignment( GLUI_ALIGN_RIGHT);
	
	new GLUI_Separator(glui);
    GLUI_Panel *control_panel = new GLUI_Rollout(glui, "Control", true );
	GLUI_Rotation *view_rot = new GLUI_Rotation(control_panel, "Rotate Objects", view_rotate,9,control_cb);
    view_rot->set_spin( 1.0 ); 
	GLUI_Translation *trans_xy = new GLUI_Translation(control_panel, "Objects XY", GLUI_TRANSLATION_XY, obj_pos );
	new GLUI_Column(control_panel,false);
	 GLUI_Translation *trans_x = new GLUI_Translation(control_panel, "Objects X", GLUI_TRANSLATION_X, obj_pos );
     trans_x->set_speed( .05 );
    GLUI_Translation *trans_y = new GLUI_Translation( control_panel, "Objects Y", GLUI_TRANSLATION_Y, &obj_pos[1] );
    trans_y->set_speed( .05 );
    GLUI_Translation *trans_z = new GLUI_Translation( control_panel, "Objects Z", GLUI_TRANSLATION_Z, &obj_pos[2] );
    trans_z->set_speed( .05 );
	
	new GLUI_Separator(glui);

    GLUI_Panel *camera_panel = new GLUI_Rollout( glui, "Camera Information" );
	camera_info[0] = new GLUI_EditText(camera_panel,"PositionX: ");
	camera_info[1] = new GLUI_EditText(camera_panel,"PositionY: ");
	camera_info[2] = new GLUI_EditText(camera_panel,"PositionZ: ");
	new GLUI_Separator(camera_panel);
	camera_info[3] = new GLUI_EditText(camera_panel,"LookAtX: ");
	camera_info[4] = new GLUI_EditText(camera_panel,"LookAtY: ");
	camera_info[5] = new GLUI_EditText(camera_panel,"LookAtZ: ");
	new GLUI_Separator(camera_panel);
	camera_info[6] = new GLUI_EditText(camera_panel,"HeadX: ");
	camera_info[7] = new GLUI_EditText(camera_panel,"HeadY: ");
	camera_info[8] = new GLUI_EditText(camera_panel,"HeadZ: ");
	new GLUI_Separator(camera_panel);

    new GLUI_Column( glui, false );
    GLUI_Rollout *roll_lights = new GLUI_Rollout(glui, "Lights", true );

    GLUI_Panel *light0 = new GLUI_Panel( roll_lights, "Light 1" );
    GLUI_Panel *light1 = new GLUI_Panel( roll_lights, "Light 2" );

  new GLUI_Checkbox( light0, "Enabled", &light0_enabled,
                     LIGHT0_ENABLED_ID, control_cb );
  light0_spinner = 
    new GLUI_Spinner( light0, "Intensity:", 
                      &light0_intensity, LIGHT0_INTENSITY_ID,
                      control_cb );
  light0_spinner->set_float_limits( 0.0, 1.0 );
  GLUI_Scrollbar *sb;
  sb = new GLUI_Scrollbar( light0, "Red",GLUI_SCROLL_HORIZONTAL,
                           &LightDiffuse[0],LIGHT0_INTENSITY_ID,control_cb);
  sb->set_float_limits(0,1);
  sb = new GLUI_Scrollbar( light0, "Green",GLUI_SCROLL_HORIZONTAL,
                           &LightDiffuse[1],LIGHT0_INTENSITY_ID,control_cb);
  sb->set_float_limits(0,1);
  sb = new GLUI_Scrollbar( light0, "Blue",GLUI_SCROLL_HORIZONTAL,
                           &LightDiffuse[2],LIGHT0_INTENSITY_ID,control_cb);
  sb->set_float_limits(0,1);
  new GLUI_Checkbox( light1, "Enabled", &light1_enabled,
                     LIGHT1_ENABLED_ID, control_cb );
  light1_spinner = 
    new GLUI_Spinner( light1, "Intensity:",
                      &light1_intensity, LIGHT1_INTENSITY_ID,
                      control_cb );
  light1_spinner->set_float_limits( 0.0, 1.0 );
  sb = new GLUI_Scrollbar( light1, "Red",GLUI_SCROLL_HORIZONTAL,
                           &Light1Diffuse[0],LIGHT1_INTENSITY_ID,control_cb);
  sb->set_float_limits(0,1);
  sb = new GLUI_Scrollbar( light1, "Green",GLUI_SCROLL_HORIZONTAL,
                           &Light1Diffuse[1],LIGHT1_INTENSITY_ID,control_cb);
  sb->set_float_limits(0,1);
  sb = new GLUI_Scrollbar( light1, "Blue",GLUI_SCROLL_HORIZONTAL,
                           &Light1Diffuse[2],LIGHT1_INTENSITY_ID,control_cb);
  sb->set_float_limits(0,1);
  trans_xy->set_speed( .05 );
  
   fb = new GLUI_FileBrowser(glui, "",1, 7, control_cb);
   fb->set_h(150);
    new GLUI_Separator(glui);
    GLUI_Panel *object_panel = new GLUI_Rollout( glui, "Object Information");
	obj_info[0] = new GLUI_EditText(object_panel,"PositionX: ");
	obj_info[1] = new GLUI_EditText(object_panel,"PositionY: ");
	obj_info[2] = new GLUI_EditText(object_panel,"PositionZ: ");
	new GLUI_Separator(glui);

    new GLUI_Button( glui, "Quit", 0,(GLUI_Update_CB)exit );


   /**** Link windows to GLUI, and register idle callback ******/
  
    glui->set_main_gfx_window( main_window );

    /* We register the idle callback with GLUI, *not* with GLUT */
    GLUI_Master.set_glutIdleFunc( myGlutIdle ); 
   /*End of GLUI code*************************/
	glutKeyboardFunc(InputKey);//WASD设置位置 
    glutMouseFunc(MouseClick);//右键设置朝向，左键调整模型位置 
    glutMotionFunc(MouseMove);//鼠标移动 
	glutReshapeFunc(myGlutReshape);
	glutDisplayFunc(Display);
    glutMainLoop();
    return 0;
}

