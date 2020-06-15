#include <cmath>
#include <GLFW/glfw3.h>
#include "utils.hpp"
void DrawLine(float p, float q, float r, float s)
{
	glBegin(GL_LINES);
	glVertex2f(p, q);
	glVertex2f(r, s);
	glEnd();
}
void DrawCircle(float x, float y, float r)
{
	using std::cos;
	using std::sin;

	float theta = 0;
	glBegin(GL_POLYGON);
	for(int i = 0; i < 60; i++)
	{
		theta = i * 3.1415926535897932 / 30;
		glVertex2f(x + r * cos(theta), y + r * sin(theta));
	}
	glEnd();
}
