#include <stdio.h>
#include <math.h>
#include <GL/glut.h>

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

void init() {
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glColor3f(0.0, 0.0, 0.0);
	glPointSize(1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 500, 0, 500);
}

Color getPixelColor(GLint x, GLint y) {
	Color color;
	glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, &color);
	return color;
}

void setPixelColor(GLint x, GLint y, Color color) {
	glColor3f(color.r, color.g, color.b);
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
	glFlush();
}


int V = 0;

struct Vertex
{
	int x;
	int y;	
};

Vertex vertices[10];


void boundaryFill(GLint x, GLint y, Color oldColor, Color newColor) {
	Color color;
	color = getPixelColor(x, y);

	if(color.r == newColor.r && color.g == newColor.g && color.b == newColor.b)
	{
		return;
	}
	else
	{
		setPixelColor(x, y, newColor);
		boundaryFill(x+1, y, oldColor, newColor);
		boundaryFill(x, y+1, oldColor, newColor);
		boundaryFill(x-1, y, oldColor, newColor);
		boundaryFill(x, y-1, oldColor, newColor);
	}
	return;
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


void drawCircle(int cx, int cy, int r)
{
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 360; i++)
	{
		float radians=i*3.14159/180;
		glVertex2f(cx+cos(radians)*r, cy+sin(radians)*r);
		glVertex2f(cx+cos(radians)*r+1, cy+sin(radians)*r);
		glVertex2f(cx+cos(radians)*r-1, cy+sin(radians)*r);
		glVertex2f(cx+cos(radians)*r, cy+sin(radians)*r+1);
		glVertex2f(cx+cos(radians)*r, cy+sin(radians)*r-1);
	}
	glEnd();
}


void drawEllipse(int cx, int cy, int rx, int ry)
{
	glBegin(GL_LINE_LOOP);
	
	  for(int i=0;i<360;i++)
	  {
	     float rad = i*3.14159/180;
	     glVertex2f(cx+cos(rad)*rx, cy+sin(rad)*ry);
	  }
	
	  glEnd();
}

int clickNo = 1;
int tx1 = 0, ty1 = 0;

int dc=0, dp=0;

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

	    boundaryFill(x, 500-y, oldColor, newColor);

	    break;

	default:
	    break;
	}
	fflush(stdout); 

}


void drawPolygon()
{
	for (int i = 0; i < V; i++)
	{
		LineWithDDA(vertices[i].x, vertices[i].y, vertices[(i+1)%V].x, vertices[(i+1)%V].y);
	}
}


void key(unsigned char key_t, int x, int y){
    if(key_t=='d'){
            drawPolygon();
        }

        if(key_t=='c'){
        	int dx=vertices[1].x-vertices[0].x;
        	int dy=vertices[1].y-vertices[0].y;
            drawCircle(vertices[0].x, vertices[0].y, sqrt(dx*dx+dy*dy));
        }



        if(key_t=='e'){
        	int rx=vertices[1].x-vertices[0].x;
        	int ry=vertices[1].y-vertices[0].y;
            drawEllipse(vertices[0].x, vertices[0].y, rx, ry);
        }

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
	glutCreateWindow("Flood Fill");
	init();
	glutDisplayFunc(display);
	glutMouseFunc(onMouseClick);

	glutKeyboardFunc(key);
	glutMainLoop();
	return 0;
}