#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#include <GLFW/glfw3.h>
#include "utils.hpp"
typedef long long lli;
std::vector<std::vector<lli>>gr;
lli curr;
lli fr;
lli t;
lli longest;

void render()
{
	float diff = curr == 0 ? 0 : 1.5 / curr;
	float x = -0.875;
	float y = -0.75;

	if(curr)
	{
		float big = 0;

		for(lli line=0;line<gr.size();line++)
		{
			big = gr[line][curr - 1];
			for(lli i = 0; i < curr; i++)
			{
				DrawLine(x, y, x + diff, big == 0 ? -0.75 : -0.75 + gr[line][i] / big);
				x += diff;
				y = -0.75 + (big == 0 ? 0 : gr[line][i] / big);

				if(curr < 20 || i == curr - 1)
				{
					DrawCircle(x, y, 0.01);
				}
				else if(curr < 50 && i % 2 == 0)
				{
					DrawCircle(x, y, 0.01);
				}
				else if(curr < 200 && i % 6 == 0)
				{
					DrawCircle(x, y, 0.01);
				}
			}
		}

	}

	if(curr < longest - 1 && fr % (t / (curr + 1)) == 0)
	{
		++curr;
		fr = 0;
	}

	++fr;
}

int main(int argl, char**argv)
{
	if(glfwInit())
	{
		GLFWwindow* window = glfwCreateWindow(1024,576,"GLFW",NULL,NULL);
		if(window)
		{
			std::ifstream ifs ("data.txt");
			lli cnt = 0;
			lli len = 0;
			lli tmp = 0;
			ifs >> cnt;

			gr.reserve(cnt);

			for(lli i = 0; i < cnt; i++)
			{
				ifs >> len;
				longest = std::max(longest,len);
				gr.emplace_back();
				gr.back().reserve(len);
				for(lli j=0;j<len;j++)
				{
					ifs >> tmp;
					gr.back().push_back(tmp);
				}
			}

			ifs.close();
			glfwMakeContextCurrent(window);
			t = 240;

			double last = glfwGetTime();
			double now = 0;
			double passed = 0;

			glColor3f(0, 0.5, 0);
			glLineWidth(4);

			while(!glfwWindowShouldClose(window))
			{

				now = glfwGetTime();
				passed += now - last;
				last = now;

				if(passed >= 0.016666667)
				{
					glClear(GL_COLOR_BUFFER_BIT);
					render();
					glfwSwapBuffers(window);
					glfwPollEvents();
					passed = 0;
				}

			}
			glfwTerminate();
		}
	}
	return 0;
}
