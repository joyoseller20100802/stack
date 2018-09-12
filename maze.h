
typedef int DirectiveType;        //下一个通道方向  
#define RANGE 100                 //迷宫大小  
#define ROW 10                    //迷宫的行数
#define COL 10                    //迷宫的列数    
typedef struct
{
    int m,n;
    int arr[RANGE][RANGE];
}MazeType;   
   
bool InitMaze(MazeType &maze, int a[ROW][COL], int row, int col);//初始化迷宫
bool Pass(MazeType maze,PosType curpos);                         //判断能否通过
bool FootPrint(MazeType &maze,PosType curpos);                   //留下足迹
bool MarkPrint(MazeType &maze,PosType curpos);                   //留下不能通过的标记
PosType NextPos(PosType curpos, DirectiveType di);               //curpos当前位置
                                                                 //返回当前节点的下一节点	
bool PosEqual(PosType pos1, PosType pos2);                       //判断两节点是否相等
void PrintMaze(MazeType maze,int row,int col);
