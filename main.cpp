/*All copyrights reversed by KenLee@2015, SS, SYSU*/
#include "main.h"
cTexture tex;
cTexture tex2;
array<float,4> a={0.8,0,0.8,1.0};
array<float,4> d={0.8,0,0.8,1.0};
array<float,4> s={1,0,1,1};
array<float,4> e={0,0,0,1};
float fs=50;
float ft=1;
cMaterial mat(a,d,s,e,fs,ft);
cMaterial mat2(a,d,s,e,fs,ft);
/*glut DisplayFunc*/
void scene(){
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);


	cOBJ OBJ;
	OBJ.loadObjFromFile("one_colunm.obj");
	OBJ.render();
	/*
	//glColor3f(1,1,1);
	mat.setMaterial();
	//glutSolidSphere( 0.5f, 50, 50 ); 
	
	//tex.bindTexutre();
	glBegin(GL_QUADS);{
		glTexCoord2f(0.0f, 0.0f);glVertex3f(-2,0,0.0);
		glTexCoord2f(1.0f, 0.0f);glVertex3f(0,0,0.0);
		glTexCoord2f(1.0f, 1.0f);glVertex3f(0,2,0.0);
		glTexCoord2f(0.0f, 1.0f);glVertex3f(-2,2,0.0);
	}
	*/
	//mat2.setMaterial();
	glutSolidSphere( 0.5f, 50, 50 ); 
	glutSwapBuffers();
}
/*初始化*/
void initWindow(int argc,char* argv[]){
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_RGB|GLUT_DOUBLE);
	glutInitWindowSize(500,500);
	glutInitWindowPosition(200,200);
	glDepthMask(GL_TRUE);
	glutCreateWindow("3D Cube");
	glEnable(GL_TEXTURE_2D);
	//光源
	GLfloat light_position[]={1.0,1.0,1.0,0.0};
	glLightfv(GL_LIGHT0,GL_POSITION,light_position);

	//将光源设置应用
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	//着色消隐
	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);
}
//reshape funx
void reshape(GLsizei w,GLsizei h)
{
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if(w<=h)
		glOrtho(-2.0,2.0,-2.0*(GLfloat)h/(GLfloat)w,
		2.0*(GLfloat)h/(GLfloat)w,-10.0,10.0);
	else
		glOrtho(-2.0*(GLfloat)h/(GLfloat)w,
		2.0*(GLfloat)h/(GLfloat)w,-2.0,2.0,-10.0,10.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


/*你可以在这里添加你的测试函数*/
int main(int argc, char* argv[]){
	initWindow(argc,argv);

	//test source ..
	//tex.loadTexture("Resources/mc.jpg");
	//tex2.loadTexture("Resources/a.png");
	//cOBJ obj;

	
	//mat.setTexturePath("Resources/mc.jpg");
	//mat.initTexture();
	glutReshapeFunc(reshape);
	glutDisplayFunc(scene);
	glutMainLoop();
	
	return 0;
}