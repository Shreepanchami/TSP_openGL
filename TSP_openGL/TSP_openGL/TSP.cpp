#include<GL/glut.h>
#include<math.h>
#include<stdio.h>
int radius = 50;
int w = 2000, h = 2000;
int costmatrix[100][100];
int nodes;
float node_x_y[100][2];
int completed[100];
int cost = 0;
int path[100];


//////following 2 are used for tsp
int glob = 0;;
int firstcity = 0;

void myinit()
{
	
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	gluOrtho2D(-1000, 1000, -1000, 1000);
}
void  write_node_num(float x,float y,int i)
{
	char n1[10];

	glRasterPos2f(x,y);
	_itoa_s(i + 1, n1, 10);
	for (int i = 0; i < strlen(n1); i++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, n1[i]);
	glFlush();
}
void circ_draw(int xc, int yc, int r)
{	
	glPointSize(3);
	glBegin(GL_POINTS);

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
void connect_nodes(float x1,float y1,float x2, float y2)
{
	
	float t = (y2 - y1) / (x2 - x1);
	t = t*(3.14 / 180);
	glBegin(GL_LINES);
	glVertex2f(x1,y1);
	glVertex2f(x2,y2);
	glEnd();
	glFlush();

}

/////following two are TSP function "REPLACE IT WITH A PROPER ONE" which stores path values int path[] array;
int least(int c)
{
	int i, nc = 999;
	int min = 999, kmin;

	for (i = 0; i < nodes; i++)
	{
		if ((costmatrix[c][i] != 0) && (completed[i] == 0))
			if (costmatrix[c][i] + costmatrix[i][c] < min)
			{
				min = costmatrix[i][0] + costmatrix[c][i];
				kmin = costmatrix[c][i];
				nc = i;
			}
	}

	if (min != 999)
		cost += kmin;

	return nc;
}
void mincost(int city)
	{
	 
	int ncity;
		completed[city] = 1;

		printf("%d--->", city + 1);
		path[glob] = city ;
		glob++;
		ncity = least(city);

		if (ncity == 999)
		{
			
			printf("%d", firstcity);
			path[glob] = firstcity-1;
			glob++;
			cost += costmatrix[city][firstcity-1];

			return;
		}

		mincost(ncity);
	}



void matrix_input()
{
	int city;
	printf("Enter the number of nodes");
	scanf_s("%d", &nodes);
	printf("Enter the cost matrix");
	for (int row = 0; row < nodes; row++)
		for (int column = 0; column < nodes; column++)
			scanf_s("%d", &costmatrix[row][column]);
	printf("Enter the first node");
	scanf_s("%d", &city);

	/////frstcity variable used in tsp;
	firstcity = city;

	find_nodes();
	for (int i = 0; i < nodes; i++)
	{
		glColor3f(1, 0, 0);
		circ_draw((int)node_x_y[i][0], (int)node_x_y[i][1], radius);
		glColor3f(0, 0, 0);
		write_node_num(node_x_y[i][0] - 12, node_x_y[i][1]-18 ,i);
		for (int j = 0; j < nodes; j++)
			if (costmatrix[i][j] > 0)
			{
				glColor3f(1, 0, 0);
				connect_nodes(node_x_y[i][0], node_x_y[i][1], node_x_y[j][0], node_x_y[j][1]);
			}
		
	}


	//calling tsp
	mincost(city-1);
	

	for (int i = 0; i < nodes; i++)
	{
		
		glLineWidth(5);
		glColor3f(0, 1, 0);

		connect_nodes(node_x_y[path[i]][0], node_x_y[path[i]][1], node_x_y[path[i+1]][0], node_x_y[path[i+1]][1]);
			

	}
	printf("The least cost is %d\n\n\n", &cost);
	
		
}
void display()
{
	//int choice;
	//printf("Enter 1.If u want to insert cost as Matrix OR 2.If u want to add costs using mouse");
	//scanf_s("%d", &choice);
	//if (choice == 1)
		matrix_input();
	//else
		//usingmouse();
}
int main(int argc, char *argv[])
{

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(1000, 1000);
	glutInitWindowPosition(200, 200);
	glutCreateWindow("dda");
	myinit();
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}