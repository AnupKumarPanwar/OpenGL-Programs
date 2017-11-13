
#include <GL/glut.h>
#include<iostream>
#include<math.h>

int wx = 600, wy = 400;
int xi, yi, xf, yf, xm, ym;
int xmin,xmax,ymin,ymax;
bool firstClick = true;
int c = 1;
float u1, u2;
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

float maximum(float a, float b, float c)
{
    if(a>b && a>c)
        return a;
    else if(b>a && b>c)
        return b;
    else if(c>a && c>b)
        return c;
}

float minimum(float a, float b, float c)
{
    if(a<b && a<c)
        return a;
    else if(b<c && b<a)
        return b;
    else if(c<a && c<b)
        return c;
}

//1 for +ve and -1 for -ve
float p[4], q[4];
void line_clipping()
{
    cout<<"minimum point:"<<xi<<" "<<yi<<endl;
    cout<<"maximum point:"<<xf<<" "<<yf<<endl;
    // glClear(GL_COLOR_BUFFER_BIT);
	// glColor3f(1.0, 0.0, 0.0);
    draw_viewport();

    float dx, dy, p1, p2, p3, p4, q1, q2, q3, q4;
    dx = (xf-xi);
    dy = (yf-yi);
    p[1] = -(dx);
    p[2] = dx;
    p[3] = -(dy);
    p[4] = dy;
    q[1] = xi - xmin;
    q[2] = xmax - xi;
    q[3] = yi - ymin;
    q[4] = ymax - yi;

    bool flag = true;
    for(int i=1;i<=4;i++)
    {
        if(p[i]==0 && q[i]<0)
        {
            flag = false;
            cout<<"line outside the region"<<endl;
            break;
        }
    }

    if(flag)
    {
        if(p[1]<0)
        {
            if(p[3]<0)
            {
                u1 = maximum(0,(q[1]/p[1]), (q[3]/p[3]));
            }
            else
            {
                u1 = maximum(0, (q[1]/p[1]), (q[4]/p[4]));
            }
        }
        else{
            if(p[3]<0)
            {
                u1 = maximum(0, (q[2]/p[2]), (q[3]/p[3]));
            }
            else
            {
                u1 = maximum(0, (q[2]/p[2]), (q[4]/p[4]));
            }
        }
        if(p[1]>0)
        {
            if(p[3]>0)
            {
                u2 = minimum(1,(q[1]/p[1]), (q[3]/p[3]));
            }
            else
            {
                u2 = minimum(1, (q[1]/p[1]), (q[4]/p[4]));
            }
        }
        else{
            if(p[3]>0)
            {
                u2 = minimum(1, (q[2]/p[2]), (q[3]/p[3]));
            }
            else
            {
                u2 = minimum(1, (q[2]/p[2]), (q[4]/p[4]));
            }
        }
        cout<<u1<<" "<<u2<<endl;
        float x1, y1, x2, y2;
        x1 = xi + u1*dx;
        y1 = yi + u1*dy;
        x2 = xi + u2*dx;
        y2 = yi + u2*dy;
        cout<<x1<<" "<<y1<<" "<<x2<<" "<<y2<<endl;
        if((u1>=0 && u1 <=1) && (u2>=0 && u2<=1))
        {
           glLineWidth(1.5f);
            glBegin(GL_LINES);
            glVertex2f(x1, y1);
            glVertex2f(x2, y2);
            glEnd();
            glFlush();
        }
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
            yf = (wy - y);
            setPixel(xf, yf);
            firstClick = true;
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
                c++;
            }
            else
            {
                line_clipping();
            }
        }
    }
    }


void drawScene(void)
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
    glutCreateWindow("Line Clipping");
    glutDisplayFunc(drawScene);
    setup();

    glutMouseFunc(mouse);
    glutMainLoop();
    return 0;
}
