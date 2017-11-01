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



int clickNo = 1;
int tx1 = 0, ty1 = 0;

void onMouseClick(int button, int state, int x, int y)
{

	switch (button) {
	case GLUT_LEFT_BUTTON:
	        if (state == GLUT_DOWN) {
	        if (clickNo == 1) {
	            tx1 = x;
	            ty1 = 500 - y;
	            clickNo = 2;
	        }
	        else if (clickNo == 2) {
	            int yc = 500 - y; 
	            LineWithDDA(tx1, ty1, x, yc);
	            clickNo=1;
	        }
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
	glutCreateWindow("4 Fill Boundary Fill");
	init();
	glutDisplayFunc(display);
	glutMouseFunc(onMouseClick);
	glutMainLoop();
	return 0;
}