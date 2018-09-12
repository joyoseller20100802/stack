
#pragma once
 
#include <stdio.h>  
#include <malloc.h>  
#include <stdlib.h>  
#include <string.h>
typedef int DirectiveType;        //下一个通道方向  
#define RANGE 100                 //迷宫大小  
#define STACK_INIT_SIZE 100
#define STACKINCREMENT    10
//------------  栈的顺序存储实现  ------------------------------
typedef struct 
{
	int row;                     //迷宫中的行
    int col;                     //迷宫中的列
}PosType;                        //坐标(row,col)
 
typedef struct
{
    int step;                    //当前位置在路径上的"序号"
    PosType seat;                //当前的坐标位置
    DirectiveType di;            //往下一个坐标位置的方向
}SElemType;                      //栈的元素类型
typedef struct
{
    SElemType *base;
    SElemType *top;
    int stacksize;
}SqStack;
 
bool InitStack(SqStack &s);          //栈的创建,即构造一个空栈
bool GetTop(SqStack s,SElemType &e); //如栈不为空，用e返回栈顶元素
bool Push(SqStack &s, SElemType e);  //在栈中插入元素
bool Pop(SqStack &s, SElemType &e);  //删除栈顶元素
bool StackEmpty(SqStack s);          //判断栈为不为空
bool DestoryStack(SqStack &s);       //销毁栈
