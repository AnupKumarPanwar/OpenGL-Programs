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

int selectedCP=0;



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



void drawCircle(int cx, int cy, int r)
{
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 360; i++)
	{
		float radians=i*3.14159/180;
		glVertex2f(cx+cos(radians)*r, cy+sin(radians)*r);
	}
	glEnd();
    glutSwapBuffers();

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


int factorial(int n)
{
    if (n<=1)
        return(1);
    else
        n=n*factorial(n-1);
    return n;
}


float binomial_coff(float n,float k)
{
    float ans;
    ans = factorial(n) / (factorial(k)*factorial(n-k));
    return ans;
}




Vertex drawBezier(double t) {
    Vertex P;
    P.x = 0;P.y=0;
    for (int i = 0; i<V; i++)
        {
            P.x = P.x + binomial_coff((float)(V - 1), (float)i) * pow(t, (double)i) * pow((1 - t), (V - 1 - i)) * vertices[i].x;
            P.y = P.y + binomial_coff((float)(V - 1), (float)i) * pow(t, (double)i) * pow((1 - t), (V - 1 - i)) * vertices[i].y;
        }

    return P;
}





void drawCurve()
{
	Vertex p1 = vertices[0];
	for(double t = 0.0;t <= 1.0; t += 0.01)
	{
	    Vertex p2 = drawBezier(t);
	    LineWithDDA(p1.x, p1.y, p2.x, p2.y);
	    p1 = p2;
	}
}




void key(unsigned char key_t, int x, int y){
    if(key_t=='d'){
        drawCurve();
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
	    	drawCircle(x, 500-y, 5);
	    	V++;
    		glutSwapBuffers();

	    }


	    else if (state == GLUT_UP)
	    {
	        printf("UP\n");
	    }
	    break;

	    case GLUT_RIGHT_BUTTON:
	    printf("RIGHT");
	    glClear(GL_COLOR_BUFFER_BIT);

	    	    if (state == GLUT_DOWN) {
	    	    	
	    	    	for (int i = 0; i < V; i++)
	    	    	{
	    	    		float dx=vertices[i].x-x;
	    	    		float dy=vertices[i].y-(500-y);

	    	    		float dr=sqrt(dx*dx+dy*dy);

	    	    		if (dr<5.0)
	    	    		{
	    	    			selectedCP=i;
	    	    			break;
	    	    		}

	    	    	}

	    	    }

	    // translate(x, 500-y);

	    break;

	default:
	    break;
	}
	fflush(stdout); 

}


void cp_drag(GLint x, GLint y){

	vertices[selectedCP].x=x;
	vertices[selectedCP].y=500-y;

	glClear(GL_COLOR_BUFFER_BIT);

	for (int i = 0; i < V; i++)
	{
		x=vertices[i].x;
    	y=vertices[i].y;
    	setPixelColor(x, y, newColor);
    	drawCircle(x, y, 5);
	}
	
	glutSwapBuffers();

	drawCurve();

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
	glutMotionFunc(cp_drag);
	glutKeyboardFunc(key);
	glutMainLoop();
	return 0;
}