#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#include <iostream>

using namespace std;

struct Point {
	GLint x;
	GLint y;
};

struct Color {
	GLfloat r;
	GLfloat g;
	GLfloat b;
};

Color newColor = {1.0f, 0.0f, 0.0f};
Color oldColor = {1.0f, 1.0f, 1.0f};


int V = 0;

struct Vertex
{
	int x;
	int y;	
};

Vertex vertices[10];



void init() {
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glColor3f(0.0, 0.0, 0.0);
	glPointSize(1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 500, 0, 500);
}



void setPixelColor(GLint x, GLint y, Color color) {
	glColor3f(color.r, color.g, color.b);
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
	// glFlush();
}





void LineWithDDA(int x0, int y0, int x1, int y1)
{
    int dy = y1 - y0;
    int dx = x1 - x0;
    int steps, i;
    float xinc, yinc, x = x0, y = y0;
    if (abs(dx) > abs(dy)) {
        steps = abs(dx);
    }
    else {
        steps = abs(dy);
    }
    xinc = (float)dx / (float)steps;
    yinc = (float)dy / (float)steps;
    setPixelColor(int(x), int(y), newColor);
    for (i = 0; i < steps; i++) {
        x += xinc;
        y += yinc;
        setPixelColor(int(x), int(y), newColor);
    }
    glutSwapBuffers();
}



void drawPolygon()
{
	for (int i = 0; i < V; i++)
	{
		LineWithDDA(vertices[i].x, vertices[i].y, vertices[(i+1)%V].x, vertices[(i+1)%V].y);
	}
}






// void drawCircle(int cx, int cy, int r)
// {
// 	glBegin(GL_LINE_LOOP);
// 	for (int i = 0; i < 360; i++)
// 	{
// 		float radians=i*3.14159/180;
// 		glVertex2f(cx+cos(radians)*r, cy+sin(radians)*r);
// 		glVertex2f(cx+cos(radians)*r+1, cy+sin(radians)*r);
// 		glVertex2f(cx+cos(radians)*r-1, cy+sin(radians)*r);
// 		glVertex2f(cx+cos(radians)*r, cy+sin(radians)*r+1);
// 		glVertex2f(cx+cos(radians)*r, cy+sin(radians)*r-1);
// 	}
// 	glEnd();
// 	glutSwapBuffers();
// }


void drawEllipse(int cx, int cy, int rx, int ry)
{
	glBegin(GL_LINE_LOOP);
	
	  for(int i=0;i<360;i++)
	  {
	     float rad = i*3.14159/180;
	     glVertex2f(cx+cos(rad)*rx, cy+sin(rad)*ry);
	  }
	
	  glEnd();
	  glutSwapBuffers();
}




float sx=1;
float sy=1;

void scale() {

	int tx=vertices[0].x;
	int ty=vertices[0].y;

	for (int i = 0; i < V; i++)
	{
		vertices[i].x-=tx;
		vertices[i].y-=ty;	
	}

	for (int i = 0; i < V; i++)
	{
		vertices[i].x*=sx;
		vertices[i].y*=sy;	
	}

	for (int i = 0; i < V; i++)
	{
		vertices[i].x+=tx;
		vertices[i].y+=ty;	
	}

	glClear(GL_COLOR_BUFFER_BIT);
	drawPolygon();
}


float rx;
float ry;


void scaleEllipse() {

	glClear(GL_COLOR_BUFFER_BIT);
	drawEllipse(vertices[0].x, vertices[0].y, rx, ry);
}

int SE=0;


void key(unsigned char key_t, int x, int y){
    if(key_t=='d'){
        drawPolygon();
    }

    // if(key_t=='c'){
    // 	int dx=vertices[1].x-vertices[0].x;
    // 	int dy=vertices[1].y-vertices[0].y;
    //     drawCircle(vertices[0].x, vertices[0].y, sqrt(dx*dx+dy*dy));
    // }



    if(key_t=='e'){
    	SE=1;
    	rx=vertices[1].x-vertices[0].x;
    	ry=vertices[1].y-vertices[0].y;
        drawEllipse(vertices[0].x, vertices[0].y, rx, ry);
    }


    else if (key_t=='8')
    {
    	sx=1;
    	sy+=0.2;
    	
    	ry+=2;
    	if (SE==1)
    	{
    		scaleEllipse();
    	}
    	else
    	{
    		scale();    		
    	}
    	sy=1;
    }
    else if (key_t=='2')
    {
    	sx=1;
    	sy-=0.2;
    	
    	ry-=2;
    	if (SE==1)
    	{
    		scaleEllipse();
    	}
    	else
    	{
    		scale();    		
    	}    	
    	sy=1;
    }
    else if (key_t=='6')
    {
    	sy=1;
    	sx+=0.2;

    	rx+=2;
    	if (SE==1)
    	{
    		scaleEllipse();
    	}
    	else
    	{
    		scale();    		
    	}    	
    	sx=1;
    }
    else if (key_t=='4')
    {
    	sy=1;
    	sx-=0.2;

    	rx-=2;
    	if (SE==1)
    	{
    		scaleEllipse();
    	}
    	else
    	{
    		scale();    		
    	}    	
    	sx=1;
    }

}




void onMouseClick(int button, int state, int x, int y)
{

	switch (button) {
	case GLUT_LEFT_BUTTON:
	    printf(" LEFT ");
	    if (state == GLUT_DOWN) {
	    	vertices[V].x=x;
	    	vertices[V].y=500-y;
	    	setPixelColor(x, 500-y, newColor);
	    	V++;
	    }


	    else if (state == GLUT_UP)
	    {
	        printf("UP\n");
	    }
	    break;

	    case GLUT_RIGHT_BUTTON:
	    printf("RIGHT");
	    // glClear(GL_COLOR_BUFFER_BIT);

	    // scale(x, 500-y);

	    break;

	default:
	    break;
	}
	fflush(stdout); 

}
void display(void) {
	Point pt = {320, 240};
	GLfloat radius = 50;

	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POINTS);
	glEnd();
	glFlush();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(200, 200);
	glutCreateWindow("Scale");
	init();
	glutDisplayFunc(display);
	glutMouseFunc(onMouseClick);
	glutKeyboardFunc(key);
	glutMainLoop();
	return 0;
}