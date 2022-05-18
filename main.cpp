#include <graphics.h>	
#include<windows.h>
#include<iostream>
#include<time.h>
#include<fstream>

using namespace std;

struct blocks
{
	int x;
	int y;
	int x1 = 0;
	int y1 = 0;
} block[4];

struct graphs
{
	int num[4][4];
}graph[19];

int random;//随机数
int graph_num;
int speed_level = 10;
int map[28][12];

void initialize_map()
{
	
	for (int i = 0; i < 28; i++)
	{
		for (int j = 0; j< 12; j++)
		{
			map[i][j] = 0;
		}
	}
}

void draw()
{
	for (int i = 4; i < 28; i++)
	{
		for (int j = 0; j < 12; j++)
		{
			if (map[i][j] == 0)
			{
				setfillcolor(RGB(190, 190, 190));
				fillrectangle(j * 40, (i - 4) * 40, (j + 1) * 40, (i - 3) * 40);
			}
			else
			{
				setfillcolor(RGB(125, 0, 125));
				fillrectangle(j * 40, (i - 4) * 40, (j + 1) * 40, (i - 3) * 40);
			}
			
		}
	}
}

void read_graph()//把所有图形样式读进结构体数组garph[19]
{
	ifstream fp;
	fp.open("file.txt",ios::in);
	if (!fp.is_open())
	{
		cout << "文件打开失败" << endl;
	}
	else
	{
		for (int i = 0; i < 19; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				for (int k = 0; k < 4; k++)
				{
					fp >> graph[i].num[j][k];				
				}
			}
		}
	}
}

void ran_num()
{
	srand((unsigned)time(NULL));
	random = rand() % 19;
}
//获取随机图形样式中四个方块坐标
void get_blocks_XY()
{
	int count = 0;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (graph[random].num[i][j] == 2)
			{
				block[count].x = i;
				block[count].y = j+4;
				block[count].x1 = 0;
				block[count].y1 = 0;
				map[block[count].x][block[count].y] = 2;
				count++;
			}
			
		}
	}
}

void exchange(int x)
{
	int temp = 0;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (graph[x].num[i][j] == 2)
			{
				map[block[temp].x][block[temp].y] = 0;
				block[temp].x = i + block[temp].x1;
				block[temp].y = j + 4 + block[temp].y1;
				map[block[temp].x][block[temp].y] = 2;	
				temp++;
			}
		}
	}
}



void elimate_execude(int x)
{
	for (int i = x; i >=3; i--)
	{
		for (int j = 0; j < 12; j++)
		{
			map[i][j] = map[i - 1][j];
		}
	}
}




int elimiate_judge()
{
	int temp2 = 0;
	for (int i = 4; i < 28; i++)
	{
		for (int j = 0; j < 12; j++)
		{
			if (map[i][j] == 1) temp2++;
		}
		if (temp2 == 12) return i;
		else temp2 = 0;
	}
	return 0;
}
void obstacle_detection()
{

}
void shape_change(int x)
{
	
	switch (x)
	{
		case 0: exchange(1); random = 1; break;
		case 1: exchange(2); random = 2; break;
		case 2: exchange(3); random = 3; break;
		case 3: exchange(0); random = 0; break;
		case 4: exchange(5); random = 5; break;
		case 5: exchange(6); random = 6; break;
		case 6: exchange(7); random = 7; break;
		case 7: exchange(4); random = 4; break;
		case 8: exchange(9); random = 9; break;
		case 9: exchange(8); random = 8; break;
		case 10: exchange(11); random = 11; break;
		case 11: exchange(12); random = 12; break;
		case 12: exchange(13); random = 13; break;
		case 13: exchange(10); random = 10; break;
		case 14: exchange(15); random = 15; break;
		case 15: exchange(14); random = 14; break;
		case 16: exchange(17); random = 17; break;
		case 17: exchange(16);	random = 16; break;
	}
}
void move_left()
{
	for (int i = 0; i < 4; i++)
	{
		if (block[i].y == 0) return;
	}
	for (int j = 0; j < 4; j++)
	{
		if (map[block[j].x][block[j].y - 1] == 1) return;
	}
	for (int k = 0; k < 4; k++)
	{
		map[block[k].x][block[k].y] = 0;
	}
	for (int k = 0; k < 4; k++)
	{
		block[k].y--;
		block[k].y1--;
	}
	for (int k = 0; k < 4; k++)
	{
		map[block[k].x][block[k].y] = 2;
	}


}

void move_right()
{
	for (int i = 0; i < 4; i++)
	{
		if (block[i].y == 11) return;
	}
	for (int j = 0; j < 4; j++)
	{
		if (map[block[j].x][block[j].y + 1] == 1) return;
	}
	for (int k = 0; k < 4; k++)
	{
		map[block[k].x][block[k].y] = 0;
	}
	for (int k = 0; k < 4; k++)
	{
		block[k].y++;
		block[k].y1++;
	}
	for (int k = 0; k < 4; k++)
	{
		map[block[k].x][block[k].y] = 2;
	}
}
int move()
{
		for (int i = 0; i < 4; i++)
		{
			if (block[i].x == 27)
			{
				for (int m = 0; m < 4; m++)//固定已停止方块位置
				{
					map[block[m].x][block[m].y] = 1;
				}
				return 0;
			}
		}
			
		for(int j=0;j<4;j++)
		{
			if (map[block[j].x + 1][block[j].y] == 1)
			{
				for (int m = 0; m < 4; m++)//固定已停止方块位置
				{
					map[block[m].x][block[m].y] = 1;
				}
				return 0;
			}
			
		}
		for (int k = 0; k < 4; k++)
		{
			map[block[k].x][block[k].y] = 0;
		}
		for (int k = 0; k < 4; k++)
		{
			block[k].x++;
			block[k].x1++;
		}
		for (int k = 0; k < 4; k++)
		{
			map[block[k].x][block[k].y] = 2;
		}
		return 1;

}
int main()
{
	
	initgraph(480*0.8, 960*0.8);//创建窗口
	setaspectratio(0.8, 0.8);
	initialize_map();
	read_graph();
	//BeginBatchDraw();
	int count = 0;
	int count2 = 0;
	while (1)
	{
		
		ran_num();
		get_blocks_XY();
		draw();
		while (1)
		{
			
			if (GetAsyncKeyState(65))  move_left();
			if (GetAsyncKeyState(68))  move_right();
			if (GetAsyncKeyState(83))   move();
			BeginBatchDraw();
			if (count2 == 5)
			{
				if (GetAsyncKeyState(32))	shape_change(random);
				count2 = 0;
			}
			else
			{
				count2++;
			}
			if (count ==speed_level)
			{
				if (move() == 0)
				{
					while (elimiate_judge())
					{
						elimate_execude(elimiate_judge());
					}
					ran_num();
					get_blocks_XY();
				}
				move();
				count = 0;
			}
			else
			{
				count++;
			}
			draw();
			FlushBatchDraw();
			
			
			
			Sleep(60);
		    
		}
		EndBatchDraw();

	}
}