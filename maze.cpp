// maze.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Stack.h"               
#include "Maze.h"    
// 最左边 最右边 分别是进栈出栈是栈操做 对应数据结构栈 中间的为队列 ADD BY LICHAO 20180902
bool InitMaze(MazeType &maze, int a[ROW][COL], int row, int col)
{
	int i,j;//设置迷宫maze的初值,包括加上边缘一圈的值
    for(i=1;i<row-1;i++)
	{
        for(j=1;j<col-1;j++)
		{
            maze.arr[i][j] = a[i][j];
        }
    }
    //加上围墙
    for(j=0;j<row;j++)
	{
        maze.arr[0][j] = maze.arr[row-1][j]=1;
    }
    for(i=0;i<col;i++)
	{
        maze.arr[i][0] = maze.arr[i][col-1]=1;
    }
    return true;
}
 
bool Pass(MazeType maze,PosType curpos)
{ //判断当前节点是否通过
    if(maze.arr[curpos.row][curpos.col] == 0)
	{
		return true;
	}
	else 
	{
		return false;
	}
}
 
bool FootPrint(MazeType &maze,PosType curpos)
{ //留下足迹
    maze.arr[curpos.row][curpos.col]=2;//走过且走得通
    return true;
}
 
bool MarkPrint(MazeType &maze,PosType curpos)
{//留下不能通过的标记
    maze.arr[curpos.row][curpos.col]=3;  //走过但走不通
    return true;
}
 
SElemType CreateSElem(int step, PosType pos, int di)
{   
    SElemType e;
    e.step = step;
    e.seat = pos;
    e.di = di;
    return e;
}
 
PosType NextPos(PosType curpos, DirectiveType di)//curpos当前位置
{//返回当前节点的下一节点
    PosType pos = curpos;
    switch(di)
    {
    case 1:        //右
        pos.col++;
        break;
    case 2:        //下
        pos.row++;
        break;
    case 3:        //左
        pos.col--;
        break;
    case 4:        //上
        pos.row--;
        break;
    }
    return pos;
}
 
bool PosEqual(PosType pos1, PosType pos2)
{//判断是不是出口
    if(pos1.row==pos2.row && pos1.col==pos2.col)
	{
		return true;
	}
	else 
	{
		return false;
	}
}
 
void PrintMaze(MazeType maze,int row,int col)
{//打印路径
	int i,j;
	printf("   ");
	for(i=0;i<col;i++)//打印列数名
	{
		printf("%d ",i);
	}
	printf("\n");
	for(i=0;i<row;i++)
	{
		printf("%d  ",i);//打印行数名
        for(j=0;j<col;j++)
		{
            switch(maze.arr[i][j])
			{
            case 0:
                printf("  ");//没走过，但是通路
                break;
			case 1:
                printf("# ");//障碍
                break;
            case 2:
                printf("* ");//走过且走得通
                break;
            case 3:
                printf("@ ");//走过但走不通
                break;
		    default: 
				break;
			}      
        }
		printf("\n");
    }
}
//这个代码和那个求全排列不同 不同在第一个处理节点是否为根节点 画图可知 ？？这样在先处理儿子还是先处理兄弟上不同？？
int MazePath(MazeType &maze, PosType start, PosType end)
{ //求解迷宫maze中,从入口start到出口end的一条路径
    SqStack s; 
	SElemType e;
    InitStack(s);
    PosType curpos = start;
    int curstep = 1;                              //探索第一步
    do{
        if( Pass(maze,curpos) )   //全排列 看是否存在 这个除了是否存在 还要看是不是坏点
		{    //如果当前位置可以通过,即是未曾走到的通道块
            FootPrint(maze,curpos);               //留下足迹
            e = CreateSElem(curstep,curpos,1);    //创建元素 PUSH进去
            Push(s,e);                             // 如果能PASS说明有儿子向下走 否则横着走
            if( PosEqual(curpos,end) )   
			{
				return curstep;
			}											
            curpos=NextPos(curpos,1);             //W //获得下一节点  // 这里一定有儿子  有儿子 用最左边的  因为没有兄弟所以先处理儿子 ADD BY LICHAO 20180901
            curstep++;                            //探索下一步
        }
		else{                                     //当前位置不能通过
            if(!StackEmpty(s))
			{
                Pop(s,e);           
				while(e.di==4 && !StackEmpty(s) ) //找寻了四个方向   看有没有 右兄弟 ADD BY LICHAO 20180901
				{
                    MarkPrint(maze,e.seat);
					Pop(s,e);                     //留下不能通过的标记,并退回一步 //如果没有右兄弟 也就是空节点 ADD BY LICHAO 20180901
				}
				if(e.di<4)                        //  如果找到右兄弟   // ADD BY LICHAO 20180901
				{
                    e.di++;                       //换一个方向探索  没加之前的DI是横侧前一个节点 
					Push(s,e);            
                    curpos = NextPos(e.seat,e.di); //设定当前位置是该方向上的相邻块  //这一步是可以和W处合并一起的 统一用DI 然后放到开头
													//不过因为和全排列的初始点不同 所以还是要分开不能放到开头
													// 全排列上来不是根 是子节点 要找兄弟的 MAZE一开始就是根所以不用找 其实是一样的
                }
				
            }
        }
    }while(!StackEmpty(s));
    return false;
}

         
void main()
{ 
	char cmd;//命令
	int i,j;
	PosType start,end;
	MazeType maze;
    int a[ROW][COL] = {
		{1,1,1,1,1,1,1,1,1,1},
		{1,0,1,1,1,1,1,0,0,1},
		{1,0,0,1,1,1,0,0,1,1},
		{1,1,0,0,0,0,0,0,1,1},
		{1,1,0,1,1,1,1,0,1,1},
		{1,1,0,0,1,1,1,0,1,1},
		{1,1,1,0,1,1,1,0,0,1},
		{1,1,1,0,0,1,1,1,1,1},
		{1,0,0,0,0,0,0,0,0,1},
		{1,1,1,1,1,1,1,1,1,1}
	};
	printf("\n----------原始迷宫(加外围围墙)(0 表示通路，1 表示障碍)---------\n");
	for(i=0;i<10;i++)
	{
		for(j=0;j<10;j++)
		{
			printf("%d ",a[i][j]);	
		}
		printf("\n");	
	}
    InitMaze(maze,a,ROW,COL);
	do{
		int flag=0;//是不是越界de标志。0即没越界执行下一步，1即循环再次输入
		do{
			printf("\n输入迷宫入口坐标( <0,0>到<9,9>之间 ): ");
			scanf("%d,%d",&start.row,&start.col);
			if(start.col>COL-1 || start.row>ROW-1 ||start.col<0||start.row<0)
			{
				printf("越界!");
				flag=1;
			}
			else
			{
				flag=0;
			}
		}while(flag);
		do{
			printf("输入迷宫出口坐标( <0,0>到<9,9>之间 ): ");
			scanf("%d,%d",&end.row , &end.col);
			if( end.col>COL-1 || end.row>ROW-1 ||end.col<0||end.row<0)
			{
				printf("越界!\n");
				flag=1;
			}
			else 
			{
				flag=0;
			}
		}while(flag);
		int step;
		if(step = MazePath(maze,start,end))//找到一条路径
		{
			printf("\n---------从当前入口到出口有通路 * 组成的路径----------\n");
			PrintMaze(maze,ROW,COL);
		}
		else
		{
			printf("\n---------从入口到出口没有通路!-----\n");
		}
		printf("%d\n",step);
		printf("\n 需要继续吗？: ");
		scanf(" %c",&cmd);
	}while(cmd=='Y'||cmd=='y');
}
