
#include<stdio.h>
#include<unistd.h>//#include<process.h>
#include<windows.h>
#include<conio.h>
#include<time.h>
#include<stdlib.h>
#define WIDTH 40
#define HEIGH 12
enum direction{//方向
LEFT,
RIGHT,
UP,
DOWN
};
struct Food{//食物
int x;
int y;
};
struct Node{//画蛇身
int x;
int y;
struct Node *next;
};
struct Snake{//蛇属性
int lenth;//长度
enum direction dir;//方向
};
struct Food *food; //食物
struct Snake *snake;//蛇属性
struct Node *snode,*tail;//蛇身
int SPEECH=200;
int score=0;//分数
int smark=0;//吃食物标记
int times=0;
int STOP=0;
void Initfood();//产生食物
void Initsnake();//构造snake
void Eatfood();//头部前进
void Addnode(int x, int y);//增加蛇身
void display(struct Node *shead);//显示蛇身坐标
void move();//蛇移动
void draw();//画蛇
void Homepage();//主页
void keybordhit();//监控键盘按键
void Addtail();//吃到食物
void gotoxy(int x, int y)//定位光标
{ 
    COORD pos; 
    pos.X = x - 1; 
    pos.Y = y - 1;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos); 
}
void Initsnake()//构造snake
{
int i;
snake=(struct Snake*)malloc(sizeof(struct Snake));
tail=(struct Node*)malloc(sizeof(struct Node));
food = (struct Food*)malloc(sizeof(struct Food));
snake->lenth=5;//初始长度 5
snake->dir=RIGHT;//初始蛇头方向 右
for(i=2;i<=snake->lenth+2;i++)//增加 5 个结点
{
Addnode(i,2);
}
}
void Initfood()//产生食物
{
struct Node *p=snode;
int mark=1;
srand((unsigned)time(NULL));//以时间为种子产生随机数
while(1)
{
food->x=rand()%(WIDTH-2)+2;//食物X坐标
food->y=rand()%(HEIGH-2)+2;//食物Y坐标
while(p!=NULL)
{
if((food->x==p->x)&&(food->y==p->y))//如果食物产生在蛇身上
{//则重新生成食物
mark=0;//食物生成无效
break;
}
p=p->next;
}
if(mark==1)//如果食物不在蛇身上,生成食物,否则重新生成食物
{
gotoxy(food->x,food->y);
printf("%c",3);
break;
}
mark=1;
p=snode;
}
}
void move()//移动
{
struct Node *q, *p=snode;
if(snake->dir==RIGHT)
{
Addnode(p->x+1,p->y);
if(smark==0)
{
while(p->next!=NULL)
{
q=p;
p=p->next;
}
q->next=NULL;
free(p);
}
}
if(snake->dir==LEFT)
{
Addnode(p->x-1,p->y);
if(smark==0)
{
while(p->next!=NULL)
{
q=p;
p=p->next;
}
q->next=NULL;
free(p);
}
}
if(snake->dir==UP)
{
Addnode(p->x,p->y-1);
if(smark==0)
{
while(p->next!=NULL)
{
q=p;
p=p->next;
}
q->next=NULL;
free(p);
}
}
if(snake->dir==DOWN)
{
Addnode(p->x,p->y+1);
if(smark==0)
{
while(p->next!=NULL)
{
q=p;
p=p->next;
}
q->next=NULL;
free(p);
}
}
}
void Addnode(int x, int y)//增加蛇身
{
struct Node *newnode=(struct Node *)malloc(sizeof(struct Node));
struct Node *p=snode;
newnode->next=snode;
newnode->x=x;
newnode->y=y;
snode=newnode;//结点加到蛇头
if(x<2||x>=WIDTH||y<2||y>=HEIGH)//碰到边界
{
STOP=1;
gotoxy(10,19);
printf("撞墙,游戏结束,任意键退出!\n");//失败
_getch();
free(snode);//释放内存
free(snake);
exit(0);
}
while(p!=NULL)//碰到自身
{
if(p->next!=NULL)
if((p->x==x)&&(p->y==y))
{
STOP=1;
gotoxy(10,19);
printf("撞到自身,游戏结束,任意键退出!\n");//失败
_getch();
free(snode);//释放内存
free(snake);
exit(0);
}
p=p->next;
}
}
void Eatfood()//吃到食物
{
Addtail();
score++;
}
void Addtail()//增加蛇尾
{
struct Node *newnode=(struct Node *)malloc(sizeof(struct Node));
struct Node *p=snode;
tail->next=newnode;
newnode->x=50;
newnode->y=20;
newnode->next=NULL;//结点加到蛇头
tail=newnode;//新的蛇尾
}
void draw()//画蛇
{
struct Node *p=snode;
int i,j;
while(p!=NULL)
{
gotoxy(p->x,p->y);
printf("%c",2);
tail=p;
p=p->next;
}
if(snode->x==food->x&&snode->y==food->y)//蛇头坐标等于食物坐标
{
smark=1;
Eatfood();//增加结点
Initfood();//产生食物
}
if(smark==0)
{
gotoxy(tail->x,tail->y);//没吃到食物清除之前的尾结点
printf("%c",' ');//如果吃到食物,不清楚尾结点
}
else
{
times=1;
}
if((smark==1)&&(times==1))
{
gotoxy(tail->x,tail->y);//没吃到食物清除之前的尾结点
printf("%c",' ');//如果吃到食物,不清楚尾结点
smark=0;
}
gotoxy(50,12);
printf("食物: %d,%d",food->x,food->y);
gotoxy(50,5);
printf("分数: %d",score);
gotoxy(50,7);
printf("速度: %d",SPEECH);
gotoxy(15,14);
printf("按o键加速");
gotoxy(15,15);
printf("按p键减速");
gotoxy(15,16);
printf("按空格键暂停");
}
void HideCursor()//隐藏光标
{
 CONSOLE_CURSOR_INFO cursor_info = {1, 0}; 
 SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}
void Homepage()//绘主页
{
int x,y;
HideCursor();//隐藏光标
printf("----------------------------------------\n");
printf("|\t\t\t\t       |\n");
printf("|\t\t\t\t       |\n");
printf("|\t\t\t\t       |\n");
printf("|\t\t\t\t       |\n");
printf("|\t\t\t\t       |\n");
printf("|\t\t\t\t       |\n");
printf("|\t\t\t\t       |\n");
printf("|\t\t\t\t       |\n");
printf("|\t\t\t\t       |\n");
printf("|\t\t\t\t       |\n");
printf("----------------------------------------\n");
gotoxy(5,13);
printf("任意键开始游戏!按W.A.S.D控制方向");
_getch();
Initsnake();
Initfood();
gotoxy(5,13);
printf("                                ");
}
void keybordhit()//监控键盘
{
char ch;
if(_kbhit())
{
ch=getch();
switch(ch)
{
case 'W':
case 'w':if(snake->dir==DOWN)//如果本来方向是下,而按相反方向无效
{
 break;
}
else
snake->dir=UP;break;
case 'A':
case 'a':if(snake->dir==RIGHT)//如果本来方向是右,而按相反方向无效
{
 break;
}
else
snake->dir=LEFT;break;
case 'S':
case 's':if(snake->dir==UP)//如果本来方向是上,而按相反方向无效
{
 break;
}
else
snake->dir=DOWN;break;
case 'D':
case 'd':if(snake->dir==LEFT)//如果本来方向是左,而按相反方向无效
{
 break;
}
else
snake->dir=RIGHT;break;
case 'O':
case 'o':
if(SPEECH>=150)//速度加快
{
SPEECH=SPEECH-50;
}
break;
case 'P':
case 'p':
if(SPEECH<=400)//速度减慢
{
SPEECH=SPEECH+50;
}
break;
case ' '://暂停
gotoxy(15,18);
printf("游戏已暂停,按任意键恢复游戏");
system("pause>nul");
gotoxy(15,18);
printf("                           ");
break;
default:break;
}
}
}
int main(void)//程序入口
{
Homepage();
while(!STOP)
{
keybordhit();//监控键盘按键
move();//蛇的坐标变化
draw();//蛇的重绘
Sleep(SPEECH);//暂时挂起线程
}
return 0;
}
