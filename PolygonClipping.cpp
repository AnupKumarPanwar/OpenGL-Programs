// #include<windows.h>
#include <algorithm>
#include <GL/glut.h>
#include<iostream>
#include<math.h>
#define ROUND(x) ((int)(x+0.5))
int wx = 600, wy = 400;
int xi, yi, xf, yf, r, rx, ry;
bool secondClick = false;
int xmin,xmax,ymin,ymax;
bool firstClick = true;
int c = 1;
//float u1, u2;
using namespace std;

void setPixel(int x, int y)
{
    glColor3f(0.0, 0.0, 0.0);
    glPointSize(1.5f);
    glBegin(GL_POINTS);
    glVertex2i(x,y);
    glEnd();
    glFlush();
    //glFlush();
}

void draw_viewport()
{
    cout<<xmin<<" "<<xmax<<" "<<ymin<<" "<<ymax<<endl;
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.0, 0.0);

	//draw a line
	glLineWidth(1.5f);
	glBegin(GL_LINES);
		glVertex2i(xmin, ymax);
		glVertex2i(xmax, ymax);
		glVertex2i(xmin, ymin);
		glVertex2i(xmax, ymin);
		glVertex2i(xmin, ymin);
		glVertex2i(xmin, ymax);
		glVertex2i(xmax, ymin);
		glVertex2i(xmax, ymax);
	glEnd();
	for(int i= 0; i<=wx ; i++)
     {
        setPixel(i,wy/2);
     }

     for(int i=0; i<=wy ; i++)
     {
        setPixel(wx/2,i);
     }
	glFlush();
}

int check(int x, int y)
{
    if(x>=xmin && x<=xmax && y>=ymin && y<=ymax)
        return 1;
    else
        return 0;
}

void circle_midpoint(int xc,int yc,int r)
{
    int x=0,y=r;
    int p0 = 1-r;
    setPixel(xc+x, yc+y);
    while(x<y)
    {
        x++;
        if(p0<0)
        {
            p0 += 2*x+1;
        }
        else
        {
            y--;
            p0 += 2*x+1-2*y;
        }
        //cout<<x<<" "<<y<<endl;

        if(check(xc+x, yc+y))
            setPixel(xc+x, yc+y);
        if(check(xc-x, yc+y))
            setPixel(xc-x, yc+y);
        if(check(xc+x, yc-y))
            setPixel(xc+x, yc-y);
        if(check(xc-x, yc-y))
            setPixel(xc-x, yc-y);

        if(check(xc+y, yc+x))
            setPixel(xc+y, yc+x);
        if(check(xc-y, yc+x))
            setPixel(xc-y, yc+x);
        if(check(xc+y, yc-x))
            setPixel(xc+y, yc-x);
        if(check(xc-y, yc-x))
            setPixel(xc-y, yc-x);
    }

}

void mouse(int btn, int state, int x, int y)
{
        if( btn == GLUT_LEFT_BUTTON && state == GLUT_UP ) {
        if (firstClick) {
            xi = x;
            yi = (wy - y);
            setPixel(xi,yi);
            firstClick = false;
        }
        else {
            xf = x;
            yf = wy-y;
            //ry = abs((wy-y)-yi);
            //rx = abs(xi-x);
            r = sqrt(((x-xi)*(x-xi))+((wy-y-yi)*(wy-y-yi)));
            firstClick = true;
            setPixel(x, wy-y);
            if(c == 1)
            {

                if(xi<xf){
                    xmin = xi;
                    xmax = xf;
                }
                else{
                    xmin = xf;
                    xmax = xi;
                }
                if(yi<yf){
                    ymin = yi;
                    ymax = yf;
                }
                else{
                    ymin = yf;
                    ymax = yi;
                }
                draw_viewport();
                //choice = 0;
                c++;
            }
            else
                circle_midpoint(xi,yi,r);
        }
    }

    }



    void drawScene()
    {
        glClearColor(1.0, 1.0, 1.0, 1.0); // Set foreground color
    glColor3f(0.2, 0.3, 0.3); // Clear screen to background color.
    glClear(GL_COLOR_BUFFER_BIT);   //Flush created objects to the screen, i.e., force rendering.
     for(int i= 0; i<=wx ; i++)
     {
        setPixel(i,wy/2);
     }

     for(int i=0; i<=wy ; i++)
     {
        setPixel(wx/2,i);
     }
    glFlush();
}

void setup()
{
    glViewport(0, 0, wx, wy);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, (GLdouble)wx, 0.0, (GLdouble)wy);
    glMatrixMode(GL_MODELVIEW);
}



int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(wx, wy);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Curve Clipping");
    glutDisplayFunc(drawScene);
    setup();

    glutMouseFunc(mouse);
    glutMainLoop();
    return 0;
}
