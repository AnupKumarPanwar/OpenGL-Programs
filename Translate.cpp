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


void translate(GLint x, GLint y) {
	int tx=x-vertices[0].x;
	int ty=y-vertices[0].y;

	for (int i = 0; i < V; i++)
	{
		vertices[i].x+=tx;
		vertices[i].y+=ty;	
	}

	drawPolygon();
}

void key(unsigned char key_t, int x, int y){
    if(key_t=='d'){
        drawPolygon();
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
	    glClear(GL_COLOR_BUFFER_BIT);

	    translate(x, 500-y);

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
	glutCreateWindow("Translate");
	init();
	glutDisplayFunc(display);
	glutMouseFunc(onMouseClick);
	glutKeyboardFunc(key);
	glutMainLoop();
	return 0;
}