#include<easyx.h>
#include<graphics.h>
#include<conio.h>
#include<time.h>
#include<stdio.h>
#include<mmsystem.h>        //多媒体库文件
#pragma comment(lib,"winmm.lib")

HWND hwnd;      //窗口句柄

//定义分数
int score = 0;

int arr[4] = {0};
//初始化一维数组
void initArr() 
{
    //随机函数种子 
    srand((unsigned int)time(NULL));
    for (int i = 0; i < 4; i++)
    {
        arr[i] = rand() % 4;//随机生成一维数组的元素   :伪随机：每次随机的结果都一样
    }
}

//绘制地图
void drawMap()
{
    //设置线的样式
    setlinestyle(PS_SOLID,2);
    //设置线的颜色
    setlinecolor(BLACK);
    for (int i = 0; i < 5; i++)
    {
        //画横线
        line(0, 50 + i * 100, 200, 50 + i * 100);
        //画竖线
        line(i*50,50, i * 50,450);
    }
    //画黑块：填充矩形
    for (int i = 0; i < 4; i++)
    {
        setfillcolor(BLACK);    
        int x = arr[i] * 50;
        int y = 50 + i * 100;
        fillrectangle(x, y, x + 50, y + 100);
    }
}

//游戏过程：鼠标操作
void playGame()
{

    int flag = 0;//游戏结束的标记
    //定义鼠标消息变量
    MOUSEMSG m;
    while (1)
    {
        //设置字体风格
        settextstyle(13, 0, "宋体");
        //设置字体颜色
        settextcolor(RGB(51,201,255));
        //文字输出
        outtextxy(75,5,"别踩白块");

        //获取鼠标消息
        m = GetMouseMsg();

        switch (m.uMsg)//判断鼠标当前消息
        {
        case WM_LBUTTONDOWN:
            int x = arr[3] * 50;
            int y = 350;
            //动起来的条件
            if (m.x > x && m.x < x+50 && m.y > y && m.y < y+100)
            {
                cleardevice();
                //整体移动
                for (int i = 3 ; i >= 1; i--)
                {
                    arr[i] = arr[i-1];
                }
                arr[0] = rand() % 4;

                score += 10;//分数增加
                drawMap();
            }
            //点击白块：游戏结束
            else
            {
                flag = 1;

                //显示分数：格式化打印sprintf
                char grade[20] = "";
                sprintf(grade, "分数：%d分",score);
                outtextxy(25,25,grade);

                break;
            }
            break;
        }
        //游戏结束
        if (flag == 1)
        {
            mciSendString("close M",0,0,0);
            MessageBox(hwnd,"你踩白块了，游戏结束！","GameOver",MB_OK);
            exit(0);
        }
    }
}

int main()
{
    //初始化图形环境
    initgraph(200,450);         //创建图形窗口
    //设置背景颜色
    setbkcolor(WHITE);
    cleardevice();          //清屏

    mciSendString("open 青石巷.mp3 alias M",0,0,0);
    mciSendString("play M repeat",0,0,0);

    initArr();
    drawMap();
    playGame();

    _getch();
    //while (1);        //卡屏
    closegraph();
    return 0;
}