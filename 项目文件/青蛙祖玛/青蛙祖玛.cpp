#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <graphics.h>
#include <conio.h>
#define py 650
#define px 950
#define frogx px/2
#define frogy py/2
#pragma comment(lib,"Winmm.lib")
int shootball[1000], flagball[1000], color[1100], frogcx, frogcy;
int t, a, i, j, k, score = 0, length, condition;
double x[1100], y[1100], Vx[1100], Vy[1100], r, dxfrog, dyfrog, dfrog, angle;
double p1_x0, p1_y0, p1_x[1000], p1_y[1000], p1_vx[1000], p1_vy[1000], dxball, dyball, dball;
char name[10][10], key[20][20], s[5], q[10];
MOUSEMSG m;
IMAGE ºì, »Æ, À¶, ÂÌ, ×Ï, frog1, frog2, bk2, caidan, heidong, °ïÖú, defen;
FILE* fp1;
clock_t begin, end;
struct Node
{
	int color;
	double x, y, Vx, Vy;
	Node *last; Node *next;
	Node() {};
	Node(int color1, double x1, double y1, double Vx1, double Vy1) :color(color1), x(x1), y(y1), Vx(Vx1), Vy(Vy1){};
}*head, *tail;
void create(int *color, double *x, double *y, double *Vx, double *Vy, int length);
void initialize();
void play();
void shoot();
void insert(Node *p, Node *p1);
void clear(Node *p1);
void start();
void pause();
void win();
void fail();
int main()
{
	int i = 0;
	if (condition == 0)
		initialize();
	fp1 = fopen("C:\\record.txt", "a");
	if (fp1 == NULL)
	{
		puts("´ò¿ªÊ§°Ü");
		exit(1);
	}
	else
	{
		InputBox(name[i], 10, "ÇëÊäÈëÐÕÃû");
		InputBox(key[i], 20, "ÇëÊäÈë6-12Î»ÃÜÂë");
		fprintf(fp1, "%s\n", name);
	}
	fclose(fp1);

	mciSendString("stop mymusic", 0, 0, 0);
	mciSendString("close mymusic", 0, 0, 0);
	mciSendString("open C:\\ÒôÀÖ\\gulu.wav alias mymusic", 0, 0, 0);
	mciSendString("play mymusic", 0, 0, 0);
	loadimage(&frog1, _T("C:\\Í¼Æ¬\\frog1.jpg"));
	loadimage(&»Æ, _T("C:\\Çò\\»Æ.jpg"));
	loadimage(&ºì, _T("C:\\Çò\\ºì.jpg"));
	loadimage(&ÂÌ, _T("C:\\Çò\\ÂÌ.jpg"));
	loadimage(&À¶, _T("C:\\Çò\\À¶.jpg"));
	loadimage(&×Ï, _T("C:\\Çò\\×Ï.jpg"));
	begin = clock();
	while (condition != 2)
	{
		play();
		if (_kbhit())
		{
			if (_getch() == 32)
			{
				condition = 3;
			}
		}
	}
	if (condition == 2)
	{
		fail();
	}
	return 0;
}
void create(int *color, double *x, double *y, double *Vx, double *Vy, int length)
{
	head =new Node();
	head->last = NULL;
	Node *p1 = head;
	Node *p = NULL;
	for (i = 0; i < length; i++)
	{
		p = new Node(color[i], x[i], y[i], Vx[i], Vy[i]);
		p1->next = p;
		p->last = p1;
		p1 = p;
	}
	tail =new Node();
	p->next = tail;
	tail->last = p;
	tail->next = NULL;
}
void initialize()
{
	condition = 0;
	length = 100;
	a = 80;
	initgraph(px, py);
	loadimage(&caidan, _T("C:\\Í¼Æ¬\\caidan.jpg"));
	putimage(0, 0, &caidan);
	loadimage(&heidong, _T("C:\\Í¼Æ¬\\heidong.jpg"));
	BeginBatchDraw();
	angle = 0;
	t = 1;
	flagball[0] = 1;
	for (i = 2; i<1000; i++)
		flagball[i] = 0;
	x[0] = 40;
	for (i = 1; i<100; i++)
		x[i] = x[i - 1] - 40;
	y[0] = 80;
	for (i = 1; i<100; i++)
		y[i] = y[i - 1];
	for (i = 0; i<100; i++)
	{
		Vx[i] = 0.1, Vy[i] = 0;
	}
	int ColorRGB[5];
	ColorRGB[0] = RGB(255, 255, 0);
	ColorRGB[1] = RGB(255, 0, 0);
	ColorRGB[2] = RGB(0, 255, 0);
	ColorRGB[3] = RGB(0, 0, 255);
	ColorRGB[4] = RGB(255, 0, 255);
	srand(time(NULL));
	for (i = 0; i < 100; i++)
	{
		color[i] = ColorRGB[rand() % 5];
	}
	frogcx = frogx + 38;
	frogcy = frogy + 38;
	shootball[0] = RGB(109, 121, 133);
	for (i = 1; i<1000; i++)
	{
		p1_x[i] = p1_x0, p1_y[i] = p1_y0;
		p1_vx[i] = 0, p1_vy[i] = 0;
		shootball[i] = ColorRGB[rand() % 5];
	}
	create(color, x, y, Vx, Vy, 100);
	while (condition == 0)
		start();
}
void play()
{
	Node *p;
	p = head;
	int ColorRGB[5];
	ColorRGB[0] = RGB(255, 255, 0);
	ColorRGB[1] = RGB(255, 0, 0);
	ColorRGB[2] = RGB(0, 255, 0);
	ColorRGB[3] = RGB(0, 0, 255);
	ColorRGB[4] = RGB(255, 0, 255);
	while (condition == 3)
		pause();
	while (condition == 0)
	{
		initialize();
		loadimage(&caidan, _T("C:\\Í¼Æ¬\\caidan.jpg"));
		putimage(0, 0, &caidan);
	}
	putimage(0, 0, &bk2);
	putimage(60, 200, &heidong);
	switch (shootball[t])
	{
	case RGB(255, 255, 0): putimage(p1_x0, p1_y0, &»Æ); break;
	case RGB(255, 0, 0): putimage(p1_x0, p1_y0, &ºì); break;
	case RGB(0, 255, 0):putimage(p1_x0, p1_y0, &ÂÌ); break;
	case RGB(0, 0, 255): putimage(p1_x0, p1_y0, &À¶); break;
	case RGB(255, 0, 255): putimage(p1_x0, p1_y0, &×Ï); break;
	}
	if (MouseHit())
	{
		m = GetMouseMsg();
		if (m.uMsg == WM_MOUSEMOVE)
		{
			dxfrog = m.x - frogx;
			dyfrog = m.y - frogy;
			if (m.x<frogx)
			{
				angle = atan(-dyfrog / dxfrog) + 3.1415926;
				rotateimage(&frog2, &frog1, angle, RGB(109, 121, 133), 0, 0);
				p1_x0 = frogcx + 70 * cos(angle);
				p1_y0 = frogcy - 70 * sin(angle);
			}
			else if (m.x>frogx)
			{
				angle = atan(-dyfrog / dxfrog);
				rotateimage(&frog2, &frog1, angle, RGB(109, 121, 133), 0, 0);
				p1_x0 = frogcx + 70 * cos(angle);
				p1_y0 = frogcy - 70 * sin(angle);
			}
		}
	}
	putimage(frogx + 17, frogy + 17, &frog2);
	shoot();
	FlushMouseMsgBuffer();
	if (flagball[t - 2] == 1 && flagball[t - 1] != 1)
	{
		setcolor(WHITE);
		setfillcolor(shootball[t - 1]);
		fillcircle((int)p1_x[t - 1], (int)p1_y[t - 1], r);
	}

	while (p->next != tail&&p->Vy != 0.1)
	{
		if ((p->x <= px - a && p->y == 80))
		{
			p->Vx = 1; p->Vy = 0;
		}
		else if ((p->x >= px - a && p->y <= py - a && p->y >= a))
		{
			p->Vx = 0; p->Vy = 0.1;
		}
		else if (p->x >= px - a&& p->x >= a && p->y >= py - a)
		{
			p->Vx = -0.1; p->Vy = 0;
		}
		else if (p->x <= a&& p->y >= 3 * a && p->y <= py)
		{
			p->Vx = 0; p->Vy = -0.1;
		}
		else if (p->Vx == 0 && p->Vy == -0.1)
		{
			condition = 2;
		}
		if (!(p->x>40 && (abs(p->x - (p->next->x))>40 || abs(p->y - (p->next->y))>40) && p->next != tail->last))
		{
			p->x += p->Vx; p->y += p->Vy;
		}
		switch (p->color)
		{
		case RGB(255, 255, 0): putimage(p->x - 15, p->y - 15, &»Æ); break;
		case RGB(255, 0, 0):  putimage(p->x - 15, p->y - 15, &ºì); break;
		case RGB(0, 255, 0): putimage(p->x - 15, p->y - 15, &ÂÌ); break;
		case RGB(0, 0, 255): putimage(p->x - 15, p->y - 15, &À¶); break;
		case RGB(255, 0, 255): putimage(p->x - 15, p->y - 15, &×Ï); break;
		}
		p = p->next;
	}
	while (p->next != tail)
	{
		if ((p->x <= px - a && p->y == 80))
		{
			p->Vx = 0.1; p->Vy = 0;
		}
		else if ((p->x >= px - a && p->y <= py - a && p->y >= a))
		{
			p->Vx = 0; p->Vy = 0.1;
		}
		else if (p->x >= px - a && p->x >= a && p->y >= py - a)
		{
			p->Vx = -0.1; p->Vy = 0;
		}
		else if (p->x <= a && p->y >= 3 * a && p->y <= py)
		{
			p->Vx = 0; p->Vy = -0.1;
		}
		else if (p->Vx == 0 && p->Vy == -0.1)
		{
			condition = 2;
		}
		if (!(p->x>40 && (abs(p->x - (p->next->x))>40 || abs(p->y - (p->next->y))>40) && p->next != tail->last))
		{
			p->x += p->Vx; p->y += p->Vy;
		}
		switch (p->color)
		{
		case RGB(255, 255, 0): putimage(p->x - 15, p->y - 15, &»Æ); break;
		case RGB(255, 0, 0):  putimage(p->x - 15, p->y - 15, &ºì); break;
		case RGB(0, 255, 0): putimage(p->x - 15, p->y - 15, &ÂÌ); break;
		case RGB(0, 0, 255): putimage(p->x - 15, p->y - 15, &À¶); break;
		case RGB(255, 0, 255): putimage(p->x - 15, p->y - 15, &×Ï); break;
		}
		p = p->next;
	}
	FlushBatchDraw();
}
void shoot()
{
	Node *p, *p2;
	Node *p3 = new Node(shootball[t - 1], p1_x[t - 1], p1_y[t - 1], p1_vx[t - 1], p1_vy[t - 1]);
	if (MouseHit())
	{
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN&&flagball[t - 1] == 1)
		{
			
			mciSendString("stop mymusic", 0, 0, 0);
			mciSendString("close mymusic", 0, 0, 0);
			mciSendString("open C:\\ÒôÀÖ\\ÍÂÇò1.wav alias mymusic", 0, 0, 0);
			mciSendString("play mymusic", 0, 0, 0);
			t++;
			dxball = m.x - p1_x0;
			dyball = m.y - p1_y0;
			dball = sqrt((m.x - p1_x0)* (m.x - p1_x0) + (m.y - p1_y0) * (m.y - p1_y0));
			p1_vx[t - 1] = dxball / dball;
			p1_vy[t - 1] = dyball / dball;
			p1_x[t - 1] = p1_x0;
			p1_y[t - 1] = p1_y0;
		}
		if (m.uMsg == WM_RBUTTONDOWN)
		{
			t++;
			p1_x[t - 1] = p1_x0;
			p1_y[t - 1] = p1_y0;
			flagball[t - 1] = 1;
		}
	}
	if (flagball[t - 2] == 1 && flagball[t - 1] != 1)
	{
		setcolor(RGB(109, 121, 133));
		setbkmode(TRANSPARENT);
		p1_x[t - 1] = p1_x[t - 1] + p1_vx[t - 1];
		p1_y[t - 1] = p1_y[t - 1] + p1_vy[t - 1];
		switch (shootball[t - 1])
		{
		case RGB(255, 255, 0):putimage(p1_x[t - 1], p1_y[t - 1], &»Æ); break;
		case RGB(255, 0, 0): putimage(p1_x[t - 1], p1_y[t - 1], &ºì); break;
		case RGB(0, 255, 0): putimage(p1_x[t - 1], p1_y[t - 1], &ÂÌ); break;
		case RGB(0, 0, 255): putimage(p1_x[t - 1], p1_y[t - 1], &À¶); break;
		case RGB(255, 0, 255):putimage(p1_x[t - 1], p1_y[t - 1], &×Ï); break;
		}
	}
	if (p1_x[t - 1]>950 || p1_x[t - 1]<0 || p1_y[t - 1]>650 || p1_y[t - 1]<0)
	{
		flagball[t - 1] = 1;
	}
	p = head;
	while (p->next != tail)
	{
		if (sqrt((p1_x[t - 1] - p->x)*(p1_x[t - 1] - p->x) + (p1_y[t - 1] - p->y)*(p1_y[t - 1] - p->y))<20 && flagball[t - 1] != 1)
		{
			flagball[t - 1] = 1;
			p1_x[t - 1] = p->next->x;
			p1_y[t - 1] = p->next->y;
			p1_vx[t - 1] = p->next->Vx;
			p1_vy[t - 1] = p->next->Vy;
			insert(p, p3);
			p2 = p->next;
			while (p2->next != tail->last)
			{
				p2->x = p2->next->x;
				p2->y = p2->next->y;
				p2 = p2->next;
			}
			p2->x -= 300 * p2->Vx;
			p2->y -= 300 * p2->Vy;
			clear(p3);
			if (head->next == tail->last || head->next == tail)
				win();
			break;
		}
		else
			p = p->next;
	}
}
void insert(Node *p, Node *p1)
{
	if (p->next != NULL)
	{
		p1->last = p;
		p1->next = p->next;
		p->next->last = p1;
		p->next = p1;
	}
	else
	{
		p1->last = p;
		p1->next = NULL;
		p->next = p1;
	}
	length++;
}
void clear(Node *p1)
{
	while (1)
	{
		Node *p2 = p1->next;
		Node *p3 = p1;
		
		int n = 0;
		while (p3 != head && p3->color == p1->color)
		{
			p3 = p3->last;
			n++;
		}
		while (p2 != tail && p2->color == p1->color)
		{
			p2 = p2->next;
			n++;
		}
		if (n >= 3)
		{
			mciSendString("stop mymusic", 0, 0, 0);
			mciSendString("close mymusic", 0, 0, 0);
			mciSendString("open C:\\ÒôÀÖ\\ÏûÇò1.wav alias mymusic", 0, 0, 0);
			mciSendString("play mymusic", 0, 0, 0);
			length -= n;
			score += n;
			fopen("C:\\record.txt", "w");
			if (fp1 == NULL)
			{
				puts("´ò¿ªÊ§°Ü");
				exit(1);
			}
			else
			{
				fprintf(fp1, "%s\n%d\n", name, score);
			}
			fclose(fp1);
			Node *p = p1->next, *p4;
			while (p1 != p2)
			{
				p4 = p1->next;
				free(p1);
				p1 = p4;
			}
			p3->next = p2;
			if (p2 != NULL)
				p2->last = p3;
			if (length <= 1)
				win();
			p1 = p3;
		}
		else
		{
			mciSendString("stop mymusic", 0, 0, 0);
			mciSendString("close mymusic", 0, 0, 0);
			mciSendString("open C:\\ÒôÀÖ\\peng.wav alias mymusic", 0, 0, 0);
			mciSendString("play mymusic", 0, 0, 0);
		}
		break;
	}
}
void start()
{
	loadimage(&bk2, _T("C:\\Í¼Æ¬\\bk2.jpg"));
	putimage(0, 0, &bk2);
	setbkmode(TRANSPARENT);
	settextcolor(WHITE);
	if (MouseHit())
	{
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN && m.x >= px*0.75 && m.x <= px*0.96 && m.y >= py*0.2 && m.y <= py*0.3)
		{
			condition = 1;
			cleardevice();
			putimage(0, 0, &bk2);
		}
		else if (m.uMsg == WM_LBUTTONDOWN && m.x >= px*0.55 && m.x <= px*0.9 && m.y >= py*0.4 && m.y <= py*0.5)
		{
			cleardevice();
			loadimage(&°ïÖú, _T("C:\\Í¼Æ¬\\°ïÖú.jpg"));
			putimage(0, 0, &°ïÖú);
			settextcolor(BLACK);
			settextstyle(40, 0, _T("ËÎÌå"));
			outtextxy(px*0.2, py*0.2, "ÓÎÏ·Íæ·¨£º");
			settextcolor(RED);
			settextstyle(30, 0, _T("ºÚÌå"));
			outtextxy(px*0.28, py*0.3, "1.ÓÃÊó±ê¿ØÖÆÐ¡ÇòµÄ·¢Éä·½Ïò");
			outtextxy(px*0.28, py*0.35, "2.µ¥»÷Êó±ê×ó¼ü£º·¢Éäµ±Ç°Ð¡Çò");
			outtextxy(px*0.28, py*0.4, "3.µ¥»÷Êó±êÓÒ¼ü£º¸ü»»Ð¡ÇòµÄÑÕÉ«");
			outtextxy(px*0.28, py*0.45, "4.ÏàÁÚÈý¸ö¼°ÒÔÉÏÑÕÉ«ÏàÍ¬µÄÐ¡Çò¿ÉÏû³ý");
			outtextxy(px*0.28, py*0.5, "5.Ïû³ýËùÓÐµÄÐ¡Çò¼´ÓÎÏ·Ê¤Àû");
			outtextxy(px*0.28, py*0.55, "6.Ð¡ÇòË³Ê±ÕëÔË¶¯£¬µôÈëºÚ¶´¼´ÓÎÏ·Ê§°Ü");
			outtextxy(px*0.28, py*0.6, "7.°´¿Õ¸ñ¼ü£ºÔÝÍ£ÓÎÏ·");
			settextcolor(BLUE);
			settextstyle(50, 0, _T("ºÚÌå"));
			outtextxy(px*0.75, py*0.2, "¿ªÊ¼ÓÎÏ·");
			setlinecolor(BLUE);
			rectangle(px*0.75, py*0.2, px*0.96, py*0.3);
			FlushBatchDraw();
		}
		else if (m.uMsg == WM_LBUTTONDOWN && m.x >= px * 0.55 && m.x <= px * 0.9 && m.y >= py * 0.55 && m.y <= py * 0.7)
			exit(1);
		else if (m.uMsg == WM_LBUTTONDOWN && m.x >= px * 0.86 && m.x <= px * 0.99 && m.y >= py * 0.86 && m.y <= py * 0.99)
		{
			cleardevice();
			loadimage(&defen, _T("C:\\Í¼Æ¬\\defen.jpg"));
			putimage(0, 0, &defen);
			settextcolor(BLUE);
			settextstyle(40, 0, _T("ºÚÌå"));
			outtextxy(px*0.28, py*0.29, "ÀúÊ·¼ÇÂ¼£º");
			settextcolor(BLACK);
			settextstyle(30, 0, _T("ËÎÌå"));
			outtextxy(px*0.28, py*0.4, "ÐÕÃû");
			outtextxy(px*0.5, py*0.4, "µÃ·Ö");
			fp1 = fopen("C:\\record.txt", "r");
			if (fp1 == NULL)
			{
				puts("´ò¿ªÊ§°Ü");
				exit(1);
			}
			else
			{
				fscanf(fp1, "%s%d", name, &score);
			}
			fclose(fp1);
			settextcolor(BLACK);
			settextstyle(30, 0, _T("ËÎÌå"));
			sprintf(s, "%d", score);
			outtextxy(px*0.28, py*0.5, *name);
			outtextxy(px*0.5, py*0.5, s);
			FlushBatchDraw();
		}
	}FlushMouseMsgBuffer();
}
void pause()
{
	putimage(0, 0, &bk2);
	setbkmode(TRANSPARENT);
	settextcolor(BROWN);
	settextstyle(80, 0, _T("ËÎÌå"));
	outtextxy(px*0.1, py*0.1, "ÓÎÏ·ÒÑÔÝÍ£");
	settextcolor(WHITE);
	settextstyle(50, 0, _T("ËÎÌå"));
	outtextxy(px*0.3, py*0.3, "¼ÌÐøÓÎÏ·");
	outtextxy(px*0.3, py*0.5, "ÍË³öÓÎÏ·");
	setlinecolor(WHITE);
	rectangle(px*0.3, py*0.3, px*0.51, py*0.38);
	setlinecolor(WHITE);
	rectangle(px*0.3, py*0.5, px*0.51, py*0.58);
	FlushBatchDraw();
	Sleep(2);
	if (MouseHit())
	{
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN && m.x >= px*0.3 && m.x <= px*0.5 && m.y >= py*0.3 && m.y <= py*0.38)
		{
			condition = 1;
		}
		else if (m.uMsg == WM_LBUTTONDOWN && m.x >= px*0.3 && m.x <= px*0.5 && m.y >= py*0.5 && m.y <= py*0.58)
		{
			condition = 2;
			exit(0);
		}
	}
	FlushMouseMsgBuffer();
}
void win()
{
	end = clock();
	mciSendString("stop mymusic", 0, 0, 0);
	mciSendString("close mymusic", 0, 0, 0);
	mciSendString("open C:\\ÒôÀÖ\\³É¹¦.mp3 alias mymusic", 0, 0, 0);
	mciSendString("play mymusic", 0, 0, 0);
	loadimage(&bk2, _T("C:\\Í¼Æ¬\\bk2.jpg"));
	putimage(0, 0, &bk2);
	setbkmode(TRANSPARENT);
	settextcolor(RED);
	settextstyle(40, 0, _T("ºÚÌå"));
	outtextxy(px*0.7, py*0.7, "°´ESC¼üÍË³ö");
	settextcolor(WHITE);
	settextstyle(50, 0, _T("ºÚÌå"));
	outtextxy(px*0.2, py*0.2, "´³¹ØÊ§°Ü£¬ÄúµÄµÃ·ÖÊÇ£º");
	outtextxy(px*0.2, py*0.4, "ÄúµÄÓÃÊ±ÊÇ£º        Ãë");
	sprintf(s, "%d", score);
	outtextxy(px*0.8, py*0.2, s);
	sprintf(q, "%5f", ((double)(end - begin) / CLOCKS_PER_SEC));
	outtextxy(px*0.5, py*0.4, q);
	if (_kbhit())
	{
		if (_getch() == 27)
		{
			begin = clock();
			exit(1);
		}

	}
	FlushBatchDraw();
	system("pause");
}
void fail()
{
	end = clock();
	mciSendString("stop mymusic", 0, 0, 0);
	mciSendString("close mymusic", 0, 0, 0);
	mciSendString("open C:\\ÒôÀÖ\\Ê§°Ü.mp3 alias mymusic", 0, 0, 0);
	mciSendString("play mymusic", 0, 0, 0);
	loadimage(&bk2, _T("C:\\Í¼Æ¬\\bk2.jpg"));
	putimage(0, 0, &bk2);
	setbkmode(TRANSPARENT);
	settextcolor(RED);
	settextstyle(40, 0, _T("ºÚÌå"));
	outtextxy(px*0.7, py*0.7, "°´ESC¼üÍË³ö");
	settextcolor(WHITE);
	settextstyle(50, 0, _T("ºÚÌå"));
	outtextxy(px*0.2, py*0.2, "´³¹ØÊ§°Ü£¬ÄúµÄµÃ·ÖÊÇ£º ·Ö");
	outtextxy(px*0.2, py*0.4, "ÄúµÄÓÃÊ±ÊÇ£º        Ãë");
	sprintf(s, "%d", score);
	outtextxy(px*0.75, py*0.2, s);
	sprintf(q, "%5f", ((double)(end - begin) / CLOCKS_PER_SEC));
	outtextxy(px*0.5, py*0.4, q);
	if (_kbhit())
	{
		if (_getch() == 27)
		{
			begin = clock();
			exit(1);
		}
	}
	FlushBatchDraw();
	system("pause");
}
