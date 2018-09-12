#include "stdafx.h"
#include "Stack.h"               
#include "Maze.h"    
 
bool InitStack(SqStack &s)
{ //栈的初始化
    s.base = (SElemType * ) malloc(STACK_INIT_SIZE * sizeof(SElemType));
    if(!s.base) 
	{
		exit(-2);
	}
    s.top=s.base;
    s.stacksize=STACK_INIT_SIZE;
    return true;
}
 
bool GetTop(SqStack s, SElemType &e )
{
    if( s.top == s.base) 
	{
		return false;
	}
    e = *(s.top-1);
    return true;
}
 
bool Push(SqStack &s, SElemType e)
{
    if(s.top-s.base >= s.stacksize)
	{    //栈满，追加存储空间
        s.base = (SElemType *)realloc(s.base,(s.stacksize+STACKINCREMENT)*sizeof(SElemType));
        if(!s.base) 
		{
			exit(-2);
		}
        s.top = s.base + s.stacksize;
        s.stacksize += STACKINCREMENT;
    }
    *s.top++ = e;
    return true;
}
 
bool Pop(SqStack &s, SElemType &e)
{
    if(s.top==s.base)
		return false;
    e = * --s.top;
    return true;
}
 
bool StackEmpty(SqStack s)
{
    return s.base == s.top;
}
 
bool DestoryStack(SqStack &s)
{
	free(&s);
	return true;
}
