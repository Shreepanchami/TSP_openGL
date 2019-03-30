#include<GL/glut.h>
#include<math.h>
#include<stdio.h>
int w = 2000, h = 2000;
int costmatrix[100][100];
int nodes;
float node_x_y[100][2];
void myinit()
{
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1, 0, 0);
	gluOrtho2D(-1000, 1000, -1000, 1000);
}

void plot_point(int x, int y)
{
	glColor3f(1, 0, 0);
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
	glFlush();
}

void circ_draw(int xc, int yc, int r)
{
	glBegin(GL_POINTS);
	glColor3f(1, 0, 0);
	int t = 0;
	for (int i = 0; i < 360; i++)
	{
		glVertex2f(xc + r * cos(t), yc + r * sin(t));
		t = t + 1;
	}
	glEnd();
	glFlush();

}
void find_nodes()
{


	float teta = 0;
	float r = 400;
	for (int i = 0; i < nodes; i++)
	{
		node_x_y[i][0] = r * cos(teta*3.14 / 180);
		node_x_y[i][1] = r * sin(teta*3.14 / 180);

		teta = teta + (360 / nodes);

	}
}
void matrix()
{

	printf("Enter the number of nodes");
	scanf_s("%d", &nodes);
	printf("Enter the cost matrix");
	for (int row = 0; row < nodes; row++)
		for (int column = 0; column < nodes; column++)
			scanf_s("%d", &costmatrix[row][column]);
	find_nodes();


	for (int i = 0; i < nodes; i++)
	{

		circ_draw((int)node_x_y[i][0], (int)node_x_y[i][1], 50);
	}



}
void display()
{
	int choice;
	printf("Enter 1.If u want to insert cost as Matrix OR 2.If u want to add costs using mouse");
	scanf_s("%d", &choice);
	if (choice == 1)
		matrix();
	//else
		//usingmouse();
}
int main(int argc, char *argv[])
{

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(2000, 2000);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("dda");
	myinit();
	glutDisplayFunc(display);
	glutMainLoop();
}