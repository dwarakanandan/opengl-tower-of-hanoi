#include<GL/glut.h>
#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#define LIGHT_ON 0
#define LIGHT_OFF 1
int pos[16] = {10,15,20,25,30,35,40,45,50,55,60,65,70,75,80,85};
int peg[3] = {50,150,250};
int moves[10000][3];
int max_moves;
int POLES[3][10];
int top[3]={-1,-1,-1};
int NUM_DISKS=3;
int cnt,counter,speed=5;
int line1=90,line2=85;
float ycoordinate;
int lightflag=1,animationFlag=1,randomColorFlag=0;

void push(int p,int disk)
{
	POLES[p][++top[p]] = disk;
}

void pop(int p)
{
	top[p]--;
}

void tower(int n,int src,int temp,int dst)
{
	if(n>0)
	{
		tower(n-1,src,dst,temp);
		moves[cnt][0] = n;
		moves[cnt][1] = src;
		moves[cnt][2] = dst;
		cnt++;
		tower(n-1,temp,src,dst);
	}
}

void drawPegs()
{
	int i;
	glColor3f(0.5,0.0,0.1);
	for(i=0;i<3;i++)
	{
		glPushMatrix();
		glTranslatef(peg[i],5,0);
		glRotatef(-90,1,0,0);
		glutSolidCone(2,70,20,20);
		glutSolidTorus(2,45, 20, 20);
		glPopMatrix();
	}
	
}

void printString(char *text)
{
	int len=strlen(text),i;
	for(i=0;i<len;i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,text[i]);
}

void drawText()
{
	glColor3f(1,1,1);
	glRasterPos3f(-70,line1,0);
	printString("Move :");
	char str[5];
	sprintf(str, "%d", counter);
	glRasterPos3f(-40,line1,0);
	printString(str);
	glRasterPos3f(-70,line2,0);
	printString("Disk");
	char str1[10];
	sprintf(str1, "%d", moves[counter][0]);
	glRasterPos3f(-50,line2,0);
	printString(str1);
	glRasterPos3f(-40,line2,0);
	printString("from");
	char src[2];
	if(moves[counter][1]==0)strcpy(src,"A");
	else if(moves[counter][1]==1)strcpy(src,"B");
	else strcpy(src,"C");
	glRasterPos3f(-20,line2,0);
	printString(src);
	glRasterPos3f(-10,line2,0);
	printString("to");
	char dst[2];
	if(moves[counter][2]==0)strcpy(dst,"A");
	else if(moves[counter][2]==1)strcpy(dst,"B");
	else strcpy(dst,"C");
	glRasterPos3f(0,line2,0);
	printString(dst);
	glColor3f(0.6,0.3,0.5);
	glBegin(GL_POLYGON);
		glVertex3f(-75,93,-5);
		glVertex3f(-75,83,-5);
		glVertex3f(10,83,-5);
		glVertex3f(10,93,-5);
	glEnd();
	glColor3f(1,0,0);
	glRasterPos3f(peg[0],70,0);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'A');
	glRasterPos3f(peg[1],70,0);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'B');
	glRasterPos3f(peg[2],70,0);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'C');
}

void drawSolved()
{
	glColor3f(1,1,0);
	glRasterPos3f(-60,87,0);
	printString("Solved !!");
	glColor3f(0.6,0.3,0.5);
	glBegin(GL_POLYGON);
		glVertex3f(-75,93,-5);
		glVertex3f(-75,83,-5);
		glVertex3f(10,83,-5);
		glVertex3f(10,93,-5);
	glEnd();
	glColor3f(1,0,0);
	glRasterPos3f(peg[0],70,0);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'A');
	glRasterPos3f(peg[1],70,0);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'B');
	glRasterPos3f(peg[2],70,0);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,'C');
}

void display()
{
	int i,j,k;
	if(randomColorFlag)
		glClearColor((rand()%100)/100.0,(rand()%100)/100.0,(rand()%100)/100.0,0);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	if(lightflag)glEnable(GL_LIGHTING);	
	glPushMatrix();
	gluLookAt(0,ycoordinate,0,0,0,-1,0,1,0);
	drawPegs();
	for(i=0;i<3;i++)
	{
		k=0;
		for(j=0;j<=top[i];j++)
		{
			glPushMatrix();
			glTranslatef(peg[i],pos[k++],0);
			glRotatef(90,1,0,0);
			glColor3f(0.1*POLES[i][j],0.2*POLES[i][j],0);
			glutSolidTorus(2.0, 4*POLES[i][j], 20, 20);
			glPopMatrix();
		}
	}	
	glPopMatrix();
	glDisable(GL_LIGHTING);	
	if(counter==max_moves)
		drawSolved();
	else
		drawText();
	if(lightflag)glEnable(GL_LIGHTING);
	glutSwapBuffers();
}


void lighting()
{
	GLfloat shininess[] = {50};
	GLfloat white[] = {0.6,0.6,0.6,1};
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
	GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat light_position[] = {100,60, 10, 0.0 };
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, white);
	glMaterialfv(GL_FRONT, GL_SPECULAR, white);
	glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
	glEnable(GL_LIGHT0);
}

void init()
{
	glClearColor(0.0,0.0,0.0,0);
	glColor3f(1,0,0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-80,350,-10,100,-100,100);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);
	lighting();
}

void animate(int n,int src,int dest)
{
	int i;
	if(speed<=0)speed=1;
	for(i=pos[top[src]+1];i<90;i+=speed)
	{
		glPushMatrix();
		glTranslatef(peg[src],i,0);
		glRotatef(85,1,0,0);
		glColor3f(0.1*n,0.2*n,0);
		glutSolidTorus(2.0, 4*n, 20, 20);
		glPopMatrix();
		glutSwapBuffers();
		display();
	}
	if(peg[src]<peg[dest])
		for(i=peg[src];i<=peg[dest];i+=speed)
		{
			glPushMatrix();
			glTranslatef(i,90,0);
			glRotatef(85,1,0,0);
			glColor3f(0.1*n,0.2*n,0);
			glutSolidTorus(2.0, 4*n, 20, 20);
			glPopMatrix();
			glutSwapBuffers();
			display();
		}
	else
		for(i=peg[src];i>=peg[dest];i-=speed)
		{
			glPushMatrix();
			glTranslatef(i,90,0);
			glRotatef(85,1,0,0);
			glColor3f(0.1*n,0.2*n,0);
			glutSolidTorus(2.0, 4*n, 20, 20);
			glPopMatrix();
			glutSwapBuffers();
			display();
		}
	for(i=70;i>pos[top[dest]+1];i-=speed)
	{
		glPushMatrix();
		glTranslatef(peg[dest],i,0);
		glRotatef(85,1,0,0);
		glColor3f(0.1*n,0.2*n,0);
		glutSolidTorus(2.0, 4*n, 20, 20);
		glPopMatrix();
		glutSwapBuffers();
		display();
	}
}

void mouse(int btn,int mode,int x,int y)
{
	if(btn == 4 && mode == GLUT_DOWN)
	{
		if(counter<max_moves)
		{
			pop(moves[counter][1]);
			if(animationFlag)
				animate(moves[counter][0],moves[counter][1],moves[counter][2]);
			push(moves[counter][2],moves[counter][0]);
			counter++;
		}
	}
	if(btn == 3 && mode == GLUT_DOWN)
	{
		if(counter>0)
		{
			counter--;
			pop(moves[counter][2]);
			if(animationFlag)
				animate(moves[counter][0],moves[counter][2],moves[counter][1]);
			push(moves[counter][1],moves[counter][0]);
		}
	}
	glutPostRedisplay();
}

void restart()
{
	int i;
	memset(POLES,0,sizeof(POLES));
	memset(moves,0,sizeof(POLES));
	memset(top,-1,sizeof(top));
	cnt=0,counter=0;
	ycoordinate=0.1;
	max_moves = pow(2,NUM_DISKS)-1;
	for(i=NUM_DISKS;i>0;i--)
	{
		push(0,i);
	}
	tower(NUM_DISKS,0,1,2);
}

void processMenuLighting(int option)
{
	switch(option)
	{
		case LIGHT_OFF:
			glDisable(GL_LIGHTING);
			lightflag=0;
		break;
		case LIGHT_ON:
			glEnable(GL_LIGHTING);
			lightflag=1;
		break;
	}
	glutPostRedisplay();
}
void processMenuMain2(int option)
{
	
}
void processMenuCamera(int option)
{
	switch(option)
	{
		case 0:ycoordinate+=0.1;break;
		case 1:ycoordinate-=0.1;break;
	}
	glutPostRedisplay();
}

void processMenuRestart(int option)
{
	if(option==0)
	{
		restart();
		glutPostRedisplay();
	}
}

void processMenuExit(int option)
{
	if(option==0)exit(0);
}

void processMenuAnimate(int option)
{
	switch(option)
	{
		case 0:
			animationFlag=1;
		break;
		case 1:
			animationFlag=0;
	}
}

void processMenuSolveCompletely(int option)
{
	int temp=animationFlag;
	animationFlag=0;
	int i,j;
	while(counter<max_moves)
	{
		mouse(4,GLUT_DOWN,0,0);
		display();
		for(i=0;i<100000;i++)
			for(j=0;j<100;j++);
	}
	animationFlag=temp;
}

void processMenuBgColor(int option)
{
	switch(option)
	{
		case 0:glClearColor(0,0,0,0);randomColorFlag=0;break;
		case 1:glClearColor(1,1,1,0);randomColorFlag=0;break;
		case 2:glClearColor(1,0,0,0);randomColorFlag=0;break;
		case 3:glClearColor(0,1,0,0);randomColorFlag=0;break;
		case 4:glClearColor(0,0,1,0);randomColorFlag=0;break;
		case 5:randomColorFlag=1;break;
	}
	glutPostRedisplay();
}

void createGLUTMenus2()
{
	int menu = glutCreateMenu(processMenuLighting);
	glutAddMenuEntry("On",LIGHT_ON);
	glutAddMenuEntry("Off",LIGHT_OFF);
	int menuExit = glutCreateMenu(processMenuExit);
	glutAddMenuEntry("Yes",0);
	glutAddMenuEntry("No",1);
	int menuCamera = glutCreateMenu(processMenuCamera);
	glutAddMenuEntry("+0.1",0);
	glutAddMenuEntry("-0.1",1);
	int menuRestart = glutCreateMenu(processMenuRestart);
	glutAddMenuEntry("Yes",0);
	glutAddMenuEntry("No",1);
	int menuAnimate = glutCreateMenu(processMenuAnimate);
	glutAddMenuEntry("On",0);
	glutAddMenuEntry("Off",1);
	int menuBgColor = glutCreateMenu(processMenuBgColor);
	glutAddMenuEntry("Black",0);
	glutAddMenuEntry("White",1);
	glutAddMenuEntry("Red",2);
	glutAddMenuEntry("Green",3);
	glutAddMenuEntry("Blue",4);
	glutAddMenuEntry("Random",5);
	int menuSolveCompletely = glutCreateMenu(processMenuSolveCompletely);
	glutAddMenuEntry("Start",0);
	glutCreateMenu(processMenuMain2);
	glutAddSubMenu("Lighting",menu);
	glutAddSubMenu("Move Camera",menuCamera);
	glutAddSubMenu("Animation",menuAnimate);
	glutAddSubMenu("Background Color",menuBgColor);
	glutAddSubMenu("Solve Completely",menuSolveCompletely);
	glutAddSubMenu("Restart",menuRestart);
	glutAddSubMenu("Exit",menuExit);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void processMenuMain1(int option)
{
}

void processMenuNumDisks(int option)
{
	NUM_DISKS=option;
	restart();
	glutPostRedisplay();
}

void createGLUTMenus1()
{
	int menu = glutCreateMenu(processMenuNumDisks);
	glutAddMenuEntry("3",3);
	glutAddMenuEntry("4",4);
	glutAddMenuEntry("5",5);
	glutAddMenuEntry("6",6);
	glutAddMenuEntry("7",7);
	glutAddMenuEntry("8",8);
	glutAddMenuEntry("9",9);
	glutAddMenuEntry("10",10);
	int menuExit = glutCreateMenu(processMenuExit);
	glutAddMenuEntry("Yes",0);
	glutAddMenuEntry("No",1);
	glutCreateMenu(processMenuMain1);
	glutAddSubMenu("Number of Disks",menu);
	glutAddSubMenu("Exit",menuExit);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void strokeString(float x,float y,float sx,float sy,char *string,int width)
{
	char *c;
	glLineWidth(width);
	glPushMatrix();
	glTranslatef(x,y,0);
	glScalef(sx,sy,0);
	for(c=string; *c != '\0'; c++)
	{
		glutStrokeCharacter(GLUT_STROKE_ROMAN, *c);
	}
	glPopMatrix();
}

void initfirst()
{
	glClearColor(0,0,0,0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0,1000,0,1000,-1,1);
	glMatrixMode(GL_MODELVIEW);
}

void first()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1,0,0);
	strokeString(50,850,0.15,0.15,"BANGALORE INSTITUTE OF TECHNOLOGY",2);
	strokeString(100,750,0.3,0.3,"DEPARTMENT OF COMPUTER SCIENCE",4);
	strokeString(300,670,0.3,0.3,"AND ENGINEERING",4);
	strokeString(200,500,0.3,0.3,"AN OPENGL MINI PROJECT ON",2);
	glColor3f(0,1,1);
	strokeString(250,420,0.4,0.4,"TOWER OF HANOI",6);
	strokeString(150,220,0.2,0.2,"NUMBER OF DISKS:",3);
	glColor3f(1,1,0);
	char str[5];
	sprintf(str, "%d", NUM_DISKS);
	strokeString(450,220,0.2,0.2,str,3);
	glColor3f(1,0,0);
	strokeString(50,100,0.17,0.17,"1 . Set the number of disks using the menu",2);
	strokeString(50,50,0.17,0.17,"2 . Press (Enter) to start the simulation",2);
	strokeString(650,200,0.15,0.15,"By:",2);
	glColor3f(1,1,0);
	strokeString(650,160,0.18,0.18,"Dwarakanandan.B.M",2);
	strokeString(650,30,0.2,0.2,"Girija.J(Associate Professor)",2);
	glColor3f(1,0,0);
	strokeString(650,120,0.18,0.18,"1BI13CS052",2);
	strokeString(650,60,0.15,0.15,"Under the guidance of.",2);	
	glutSwapBuffers();
}

void keyboard2(unsigned char c, int x, int y){}
void keyboard(unsigned char c, int x, int y)
{
	switch(c)
	{
		case 13:
			restart();
			init();
			glutDisplayFunc(display);
			createGLUTMenus2();
			glutKeyboardFunc(keyboard2);
			glutMouseFunc(mouse);
		break;
	}
	glutPostRedisplay();
}

int main(int argc,char** argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
	glutInitWindowSize(1024,720);
	glutInitWindowPosition(100,100);
	glutCreateWindow("tower of hannoi");
	initfirst();
	glutDisplayFunc(first);
	createGLUTMenus1();
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;
}
