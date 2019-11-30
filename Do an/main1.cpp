#include <iostream>
#include <graphics.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <math.h>
#include <fstream>
#include "define.h"
using namespace std;

struct toado
{
	int x,y;
};
struct Dinh
{
	char ten[100];
};
struct Graph
{
	int n;
	toado td[MAX];
	Dinh Tendinh[MAX];
	int MTTS[MAX][MAX];
};
Graph G;
void trangthai();
void trogiup();

double lenghLine(int x1, int y1, int x2, int y2){//tinh ban kinh vong tron
	return sqrt(double(pow(x2 - x1, 2) + pow(y2 - y1, 2)));
}
void textWrite(int &x, int &y, char s[],int color){//viet tiep
	setcolor(WHITE);
	setbkcolor(color);
	outtextxy(x, y, s);
	x += textwidth(s);
}

void textWriteRemove(int &x, int &y, char s[]){//lui lai khi xoa
	setcolor(GREEN);
	setbkcolor(GREEN);
	x -= textwidth(s);
	outtextxy(x, y, s);
}

void textReadword(int x, int y, char s[]){//dua du lieu kieu ky tu vao
	char ch[2];
	char temp;
	ch[1] = 0;
	int i = 0;
	settextstyle(0,0,1);

	while (1){
		fflush(stdin);
		temp = getch();
		
		if (temp >= '0' && temp <= '9'||temp >= 'A' && temp <= 'Z'||temp >= 'a' && temp <= 'z'){
			 if (i<4)
			{
			settextstyle(0,0,1);			
			ch[0] = temp;
			textWrite(x, y, ch,GREEN);
			s[i++] = ch[0];
			}
			else {
			settextstyle(8,0,1);
			outtextxy(5,520,"Do dai cua ten dinh da dat gioi han");
			
			}
		 }
	    else if (temp == 8){
	    	trangthai();
			if(i>0)
			{
			settextstyle(0,0,1);
			textWriteRemove(x, y, ch);
			i--;
			}
		}
		else if (temp == 13)
		{
			trangthai();
			break;
		}
	}
s[i] = 0;
}

void textReadnumber(int &x, int &y, char s[]){//dua du lieu kieu so vao
	char ch[2];
	char temp;
	ch[1] = 0;
	int i = 0;
	while (1){
		fflush(stdin);
		temp = getch();
		if (temp >= '0' && temp <= '9'){
			ch[0] = temp;
			textWrite(x, y, ch,GREEN);
			s[i++] = ch[0];
		}
		else if (temp == 8){
			textWriteRemove(x, y, ch);
			i--;
			setcolor(WHITE);
		}
		else if (temp == 13) break;
	}
	s[i] = 0;
}
void textWriteln(int &x, int &y, char s[]){//xuong hang
	outtextxy(x, y, s);
	x = 0;
	y += 20;
}
void veMuiTen(double start_x, double start_y, double end_x, double end_y, int color){
	double x1, x2, y1, y2, x3, y3;
	double arrow_lenght_(30), arrow_degrees_(0.3);
	double angle = atan2(end_y - start_y, end_x - start_x) + M_PI;

	x1 = end_x + arrow_lenght_ * cos(angle - arrow_degrees_);
	y1 = end_y + arrow_lenght_ * sin(angle - arrow_degrees_);
	x2 = end_x + arrow_lenght_ * cos(angle + arrow_degrees_);
	y2 = end_y + arrow_lenght_ * sin(angle + arrow_degrees_);

	x3 = end_x + 20 * cos(angle);
	y3 = end_y + 20 * sin(angle);

	int x4 = end_x + 23 * cos(angle);
	int y4 = end_y + 23 * sin(angle);

	//to mau 
	setcolor(color);
	setfillstyle(SOLID_FILL,color);
	line(x1, y1, x3, y3);
	line(x2, y2, x3, y3);
	line(x1, y1, x2, y2);

}

// ve cung

void veCung( Graph G, int dinhdau, int dinhcuoi, int color){
	int x1 = G.td[dinhdau].x, y1 = G.td[dinhdau].y;
	int x2 = G.td[dinhcuoi].x, y2 = G.td[dinhcuoi].y;
	settextstyle(0,0,1);
	if(G.MTTS[dinhdau][dinhcuoi]==0)
	{
		settextstyle(0,0,1);
		char trongSo[4];
		setcolor(15);
		line(x2, y2, x1, y1);
		veMuiTen(x1, y1, x2, y2,15);
		_itoa(G.MTTS[dinhdau][dinhcuoi], trongSo, 10);
		setbkcolor(WHITE);
		outtextxy((x1 + x2) / 2 + 15, (y1 + y2) / 2 + 5, trongSo);

		double arrow_lenght_(8), arrow_degrees_(M_PI/2);
		double angle = atan2(y2 - y1, x2 - x1) + M_PI;
		int xtemp1 = x1 + arrow_lenght_ * cos(angle - arrow_degrees_);
		int ytemp1 = y1 + arrow_lenght_ * sin(angle - arrow_degrees_);
		int xtemp2 = x2 + arrow_lenght_ * cos(angle - arrow_degrees_);
		int ytemp2 = y2 + arrow_lenght_ * sin(angle - arrow_degrees_);

		//ve lai dinh cuoi-> dinh dau
		setcolor(WHITE);
		line(xtemp2, ytemp2, xtemp1, ytemp1);
		veMuiTen(xtemp2, ytemp2, xtemp1, ytemp1,WHITE);
		_itoa(G.MTTS[dinhcuoi][dinhdau], trongSo, 10);
		outtextxy((xtemp1 + xtemp2) / 2, (ytemp1 + ytemp2) / 2, trongSo);

		// Ve lai mui ten tu Dau -> cuoi
		xtemp1 = x1 + arrow_lenght_ * cos(angle + arrow_degrees_);
		ytemp1 = y1 + arrow_lenght_ * sin(angle + arrow_degrees_);
		xtemp2 = x2 + arrow_lenght_ * cos(angle + arrow_degrees_);
		ytemp2 = y2 + arrow_lenght_ * sin(angle + arrow_degrees_);
		line(xtemp1, ytemp1, xtemp2, ytemp2);
		veMuiTen(xtemp1, ytemp1, xtemp2, ytemp2,WHITE);
		_itoa(G.MTTS[dinhdau][dinhcuoi], trongSo, 10);
		outtextxy((xtemp1 + xtemp2) / 2, (ytemp1 + ytemp2) / 2, trongSo);

		// to lai mau cho 2 dinh
		setfillstyle(SOLID_FILL, GREEN);
		// dinh 1
		setcolor(YELLOW);
		circle(x1, y1, R);
		floodfill(x1, y1, YELLOW);
		setcolor(GREEN);
		circle(x1, y1, R);
		floodfill(x1, y1, GREEN);
		setcolor(RED);
		setbkcolor(GREEN);
		outtextxy(x1 - 15, y1 - 5, G.Tendinh[dinhdau].ten);

		// dinh 2
		setcolor(YELLOW);
		circle(x2, y2, R);
		floodfill(x2, y2, YELLOW);
		setcolor(GREEN);
		circle(x2, y2, R);
		floodfill(x2, y2, GREEN);
		setcolor(RED);
		setbkcolor(GREEN);
		outtextxy(x2 - 15, y2 - 5, G.Tendinh[dinhcuoi].ten);
	
			if(G.MTTS[dinhcuoi][dinhdau]!=0)
			{
				char trongSo[4];
				setcolor(color);
				line(x1, y1, x2, y2);
				veMuiTen(x2, y2, x1, y1, color);

				setfillstyle(SOLID_FILL, GREEN);
				// to lai hai hinh vi khi ve no bi che mat
				// hinh 1
				setcolor(WHITE);
				circle(x1, y1, R);
				floodfill(x1, y1, WHITE);

				setcolor(GREEN);
				circle(x1, y1, R);
				floodfill(x1, y1, GREEN);
				setcolor(RED);
				setbkcolor(GREEN);
				outtextxy(x1 - 15, y1 - 5, G.Tendinh[dinhdau].ten);

				// hinh 2
				setcolor(WHITE);
				circle(x2, y2, R);
				floodfill(x2, y2, WHITE);

				setcolor(GREEN);
				circle(x2, y2, R);
				floodfill(x2, y2, GREEN);
				setcolor(RED);
				setbkcolor(GREEN);
				outtextxy(x2 - 15, y2 - 5, G.Tendinh[dinhcuoi].ten);

				// in mau trang
				setbkcolor(15);
				setcolor(color);
				_itoa(G.MTTS[dinhcuoi][dinhdau], trongSo, 10);
				outtextxy((x1 + x2) / 2 + 15, (y1 + y2) / 2 + 5, trongSo);
			}
	} 
	else{
	
	if (G.MTTS[dinhcuoi][dinhdau] == 0){
		char trongSo[4];
		setcolor(color);
		line(x1, y1, x2, y2);
		veMuiTen(x1, y1, x2, y2, color);

		setfillstyle(SOLID_FILL, GREEN);
		// to lai hai hinh vi khi ve no bi che mat
		// hinh 1
		setcolor(WHITE);
		circle(x1, y1, R);
		floodfill(x1, y1, WHITE);

		setcolor(GREEN);
		circle(x1, y1, R);
		floodfill(x1, y1, GREEN);
		setcolor(RED);
		setbkcolor(GREEN);
		outtextxy(x1 - 15, y1 - 5, G.Tendinh[dinhdau].ten);

		// hinh 2
		setcolor(WHITE);
		circle(x2, y2, R);
		floodfill(x2, y2, WHITE);

		setcolor(GREEN);
		circle(x2, y2, R);
		floodfill(x2, y2, GREEN);
		setcolor(RED);
		setbkcolor(GREEN);
		outtextxy(x2 - 15, y2 - 5, G.Tendinh[dinhcuoi].ten);

		// in mau trang
		setbkcolor(15);
		setcolor(color);
		_itoa(G.MTTS[dinhdau][dinhcuoi], trongSo, 10);
		outtextxy((x1 + x2) / 2 + 15, (y1 + y2) / 2 + 5, trongSo);
	} 
	else{
		settextstyle(0,0,1);
		char trongSo[4];
		setcolor(WHITE);
		line(x2, y2, x1, y1);
		veMuiTen(x2, y2, x1, y1, WHITE);
		_itoa(G.MTTS[dinhcuoi][dinhdau], trongSo, 10);
		setbkcolor(WHITE);
		outtextxy((x1 + x2) / 2 + 15, (y1 + y2) / 2 + 5, trongSo);
		
		double arrow_lenght_(8), arrow_degrees_(M_PI/2);
		double angle = atan2(y2 - y1, x2 - x1) + M_PI;
		int xtemp1 = x1 + arrow_lenght_ * cos(angle - arrow_degrees_);
		int ytemp1 = y1 + arrow_lenght_ * sin(angle - arrow_degrees_);
		int xtemp2 = x2 + arrow_lenght_ * cos(angle - arrow_degrees_);
		int ytemp2 = y2 + arrow_lenght_ * sin(angle - arrow_degrees_);

		//ve lai dinh cuoi-> dinh dau
		setcolor(0);
		line(xtemp2, ytemp2, xtemp1, ytemp1);
		veMuiTen(xtemp2, ytemp2, xtemp1, ytemp1, 0);
		_itoa(G.MTTS[dinhcuoi][dinhdau], trongSo, 10);
		outtextxy((xtemp1 + xtemp2) / 2, (ytemp1 + ytemp2) / 2, trongSo);

		// Ve lai mui ten tu Dau -> cuoi
		xtemp1 = x1 + arrow_lenght_ * cos(angle + arrow_degrees_);
		ytemp1 = y1 + arrow_lenght_ * sin(angle + arrow_degrees_);
		xtemp2 = x2 + arrow_lenght_ * cos(angle + arrow_degrees_);
		ytemp2 = y2 + arrow_lenght_ * sin(angle + arrow_degrees_);
		line(xtemp1, ytemp1, xtemp2, ytemp2);
		veMuiTen(xtemp1, ytemp1, xtemp2, ytemp2, 0);
		_itoa(G.MTTS[dinhdau][dinhcuoi], trongSo, 10);
		outtextxy((xtemp1 + xtemp2) / 2, (ytemp1 + ytemp2) / 2, trongSo);
		// to lai mau cho 2 dinh
		setfillstyle(SOLID_FILL, GREEN);
		// dinh 1
		setcolor(BLACK);
		circle(x1, y1, R);
		floodfill(x1, y1, BLACK);
		setcolor(WHITE);
		circle(x1, y1, R);
		floodfill(x1, y1, WHITE);
		setcolor(RED);
		setbkcolor(GREEN);
		outtextxy(x1 - 15, y1 - 5, G.Tendinh[dinhdau].ten);

		// dinh 2
		setcolor(BLACK);
		circle(x2, y2, R);
		floodfill(x2, y2, BLACK);
		setcolor(WHITE);
		circle(x2, y2, R);
		floodfill(x2, y2, WHITE);
		setcolor(RED);
		setbkcolor(15);
		outtextxy(x2 - 15, y2 - 5, G.Tendinh[dinhcuoi].ten);	
	}
}
}
// ve cung demo
void veCungdemo( Graph G, int dinhdau, int dinhcuoi, int color){
	int x1 = G.td[dinhdau].x, y1 = G.td[dinhdau].y;
	int x2 = G.td[dinhcuoi].x, y2 = G.td[dinhcuoi].y;
	settextstyle(0,0,1);
	if(G.MTTS[dinhdau][dinhcuoi]==0)
	{
		settextstyle(0,0,1);
		char trongSo[4];
		setcolor(WHITE);
		line(x2, y2, x1, y1);
		veMuiTen(x1, y1, x2, y2, WHITE);
		_itoa(G.MTTS[dinhdau][dinhcuoi], trongSo, 10);
		setbkcolor(WHITE);
		outtextxy((x1 + x2) / 2 + 15, (y1 + y2) / 2 + 5, trongSo);
		double arrow_lenght_(8), arrow_degrees_(M_PI/2);
		double angle = atan2(y2 - y1, x2 - x1) + M_PI;
		int xtemp1 = x1 + arrow_lenght_ * cos(angle - arrow_degrees_);
		int ytemp1 = y1 + arrow_lenght_ * sin(angle - arrow_degrees_);
		int xtemp2 = x2 + arrow_lenght_ * cos(angle - arrow_degrees_);
		int ytemp2 = y2 + arrow_lenght_ * sin(angle - arrow_degrees_);

		//ve lai dinh cuoi-> dinh dau
		setcolor(WHITE);
		line(xtemp2, ytemp2, xtemp1, ytemp1);
		veMuiTen(xtemp2, ytemp2, xtemp1, ytemp1,WHITE);
		_itoa(G.MTTS[dinhcuoi][dinhdau], trongSo, 10);
		outtextxy((xtemp1 + xtemp2) / 2, (ytemp1 + ytemp2) / 2, trongSo);

		// Ve lai mui ten tu Dau -> cuoi
		xtemp1 = x1 + arrow_lenght_ * cos(angle + arrow_degrees_);
		ytemp1 = y1 + arrow_lenght_ * sin(angle + arrow_degrees_);
		xtemp2 = x2 + arrow_lenght_ * cos(angle + arrow_degrees_);
		ytemp2 = y2 + arrow_lenght_ * sin(angle + arrow_degrees_);
		line(xtemp1, ytemp1, xtemp2, ytemp2);
		veMuiTen(xtemp1, ytemp1, xtemp2, ytemp2,WHITE);
		_itoa(G.MTTS[dinhdau][dinhcuoi], trongSo, 10);
		outtextxy((xtemp1 + xtemp2) / 2, (ytemp1 + ytemp2) / 2, trongSo);

		// to lai mau cho 2 dinh
		setfillstyle(SOLID_FILL, GREEN);
		// dinh 1
		setcolor(YELLOW);
		circle(x1, y1, R);
		floodfill(x1, y1, YELLOW);
		setcolor(GREEN);
		circle(x1, y1, R);
		floodfill(x1, y1, GREEN);
		setcolor(RED);
		setbkcolor(GREEN);
		outtextxy(x1 - 15, y1 - 5, G.Tendinh[dinhdau].ten);

		// dinh 2
		setcolor(YELLOW);
		circle(x2, y2, R);
		floodfill(x2, y2, YELLOW);
		setcolor(GREEN);
		circle(x2, y2, R);
		floodfill(x2, y2, GREEN);
		setcolor(RED);
		setbkcolor(GREEN);
		outtextxy(x2 - 15, y2 - 5, G.Tendinh[dinhcuoi].ten);	
		if(G.MTTS[dinhcuoi][dinhdau]!=0)
		{
			char trongSo[4];
			setcolor(color);
			line(x1, y1, x2, y2);
			veMuiTen(x2, y2, x1, y1, color);

			setfillstyle(SOLID_FILL, 1);
		// to lai hai hinh vi khi ve no bi che mat
		// hinh 1
			setcolor(WHITE);
			circle(x1, y1, R);
			floodfill(x1, y1, WHITE);

		setcolor(1);
		circle(x1, y1, R);
		floodfill(x1, y1, 1);
		setcolor(RED);
		setbkcolor(1);
		outtextxy(x1 - 15, y1 - 5, G.Tendinh[dinhdau].ten);

		// hinh 2
		setcolor(WHITE);
		circle(x2, y2, R);
		floodfill(x2, y2, WHITE);

		setcolor(1);
		circle(x2, y2, R);
		floodfill(x2, y2, 1);
		setcolor(RED);
		setbkcolor(1);
		outtextxy(x2 - 15, y2 - 5, G.Tendinh[dinhcuoi].ten);

		// in mau trang
		setbkcolor(15);
		setcolor(0);
		_itoa(G.MTTS[dinhcuoi][dinhdau], trongSo, 10);
		outtextxy((x1 + x2) / 2 + 15, (y1 + y2) / 2 + 5, trongSo);
		}
	}
	else {
	
	if (G.MTTS[dinhcuoi][dinhdau] == 0){
		char trongSo[4];
		setcolor(color);
		line(x1, y1, x2, y2);
		veMuiTen(x1, y1, x2, y2, color);

		setfillstyle(SOLID_FILL, 1);
		// to lai hai hinh vi khi ve no bi che mat
		// hinh 1
		setcolor(WHITE);
		circle(x1, y1, R);
		floodfill(x1, y1, WHITE);

		setcolor(1);
		circle(x1, y1, R);
		floodfill(x1, y1, 1);
		setcolor(RED);
		setbkcolor(1);
		outtextxy(x1 - 15, y1 - 5, G.Tendinh[dinhdau].ten);

		// hinh 2
		setcolor(WHITE);
		circle(x2, y2, R);
		floodfill(x2, y2, WHITE);

		setcolor(1);
		circle(x2, y2, R);
		floodfill(x2, y2, 1);
		setcolor(RED);
		setbkcolor(1);
		outtextxy(x2 - 15, y2 - 5, G.Tendinh[dinhcuoi].ten);

		// in mau trang
		setbkcolor(15);
		setcolor(0);
		_itoa(G.MTTS[dinhdau][dinhcuoi], trongSo, 10);
		outtextxy((x1 + x2) / 2 + 15, (y1 + y2) / 2 + 5, trongSo);
	} 
	else{
			settextstyle(0,0,1);
		char trongSo[4];
		setcolor(WHITE);
		line(x2, y2, x1, y1);
		veMuiTen(x2, y2, x1, y1, WHITE);
		_itoa(G.MTTS[dinhcuoi][dinhdau], trongSo, 10);
		setbkcolor(WHITE);
		outtextxy((x1 + x2) / 2 + 15, (y1 + y2) / 2 + 5, trongSo);

		double arrow_lenght_(8), arrow_degrees_(M_PI/2);
		double angle = atan2(y2 - y1, x2 - x1) + M_PI;
		int xtemp1 = x1 + arrow_lenght_ * cos(angle - arrow_degrees_);
		int ytemp1 = y1 + arrow_lenght_ * sin(angle - arrow_degrees_);
		int xtemp2 = x2 + arrow_lenght_ * cos(angle - arrow_degrees_);
		int ytemp2 = y2 + arrow_lenght_ * sin(angle - arrow_degrees_);

		//ve lai dinh cuoi-> dinh dau
		setcolor(color);
		line(xtemp2, ytemp2, xtemp1, ytemp1);
		veMuiTen(xtemp2, ytemp2, xtemp1, ytemp1, color);
		_itoa(G.MTTS[dinhcuoi][dinhdau], trongSo, 10);
		setbkcolor(15);
		outtextxy((xtemp1 + xtemp2) / 2, (ytemp1 + ytemp2) / 2, trongSo);
		setbkcolor(WHITE);

		// Ve lai mui ten tu Dau -> cuoi
		xtemp1 = x1 + arrow_lenght_ * cos(angle + arrow_degrees_);
		ytemp1 = y1 + arrow_lenght_ * sin(angle + arrow_degrees_);
		xtemp2 = x2 + arrow_lenght_ * cos(angle + arrow_degrees_);
		ytemp2 = y2 + arrow_lenght_ * sin(angle + arrow_degrees_);
		line(xtemp1, ytemp1, xtemp2, ytemp2);
		veMuiTen(xtemp1, ytemp1, xtemp2, ytemp2, color);
		_itoa(G.MTTS[dinhdau][dinhcuoi], trongSo, 10);
		setbkcolor(15);
		outtextxy((xtemp1 + xtemp2) / 2, (ytemp1 + ytemp2) / 2, trongSo);
		setbkcolor(WHITE);

		// to lai mau cho 2 dinh
		setfillstyle(SOLID_FILL,1);
		// dinh 1
		setcolor(BLACK);
		circle(x1, y1, R);
		floodfill(x1, y1, BLACK);
		setcolor(WHITE);
		circle(x1, y1, R);
		floodfill(x1, y1, WHITE);
		setcolor(RED);
		setbkcolor(GREEN);
		outtextxy(x1 - 15, y1 - 5, G.Tendinh[dinhdau].ten);

		// dinh 2
		setcolor(BLACK);
		circle(x2, y2, R);
		floodfill(x2, y2,BLACK);
		setcolor(WHITE);
		circle(x2, y2, R);
		floodfill(x2, y2, WHITE);
		setcolor(RED);
		setbkcolor(GREEN);
		outtextxy(x2 - 15, y2 - 5, G.Tendinh[dinhcuoi].ten);	
	}
	}
}

void veCungTron(int x1, int y1, int x2, int y2)
{
	double angle = atan2(y2 - y1, x2 - x1);
	angle = angle*(180 / M_PI);
	arc((x1 + x2) / 2, (y1 + y2) / 2, -angle + 180, 180 - angle + 180, lenghLine(x1, y1, x2, y2) / 2);
}

void vehinhchunhatvien(int x,int y,int z,int b,int color)
{
	setfillstyle(SOLID_FILL,color);	
	setcolor(BLACK);
	rectangle(x,y,z,b);//ve hinh chu nhat rong
	setbkcolor(color);
	bar(x+1,y+1,z,b);// ve hcn dac
}
void trangthai()
{
	settextstyle(8,0,1);
	setcolor(BLACK);
	vehinhchunhatvien(kqx,kqy,getmaxx(),getmaxy(),7);
	outtextxy(10,485,"RESULT");
}
void trogiup()
{
	settextstyle(8,0,1);
	setcolor(BLACK);
}
void matran(Graph&G)
{
	vehinhchunhatvien(0,210,295,480,7);
	settextstyle(8,0,1);
	outtextxy(10,205,"ADJACENCY MATRIX");
	int max;
	int a6=5;
	int b6=225;
	int temp1=a6;
	int temp2=b6;
	char a[50];
	settextstyle(8,0,1);
	for(int i=1;i<=G.n;i++)
	{
		max=0;
		textWrite(a6,b6,G.Tendinh[i].ten,7);
		textWrite(a6,b6," ",7);
		temp2=225+20;
	
		for(int j=1;j<=G.n;j++)
		{
			if(G.MTTS[j][i]!=0)
			{
			_itoa(G.MTTS[j][i],a,10);
			
			outtextxy(temp1,temp2,a);
			if(textwidth(a)>textwidth(G.Tendinh[i].ten))
			{
				max=textwidth(a);
			}
			
		}
		temp2=temp2+20;
		}
		if(max!=0)
		{
			temp1=temp1+max+textwidth(" ");
			a6=a6+(max-textwidth(G.Tendinh[i].ten));
		}
		else{
			temp1=temp1+textwidth(G.Tendinh[i].ten)+textwidth(" ");
		}
		
	}
	
	
}

void vedinh(Graph& G)
{
	int x2,y2;
	char s[100];
	int chophep;
	while(1)
	{
		delay(0.0001);
		if(ismouseclick(WM_LBUTTONDOWN))
		{
	
			getmouseclick(WM_LBUTTONDOWN,x2,y2);
			chophep=1;
			// kiem tra 
				for(int a5=1;a5<=G.n;a5++)
				{
					
					if ((lenghLine(G.td[a5].x,G.td[a5].y,x2,y2)<=R+R))
					{
						settextstyle(8,0,1);
					    outtextxy(5,520,"DINH BI CHONG LEN NHAU VUI LONG CHON DINH KHAC");
						chophep=0;
					}
				
					
				}
			if(x2<getmaxx()&&x2>435&&y2>20&&y2<480&&chophep==1)
			{
						
				chophep=0;
						
					G.n++;
					setfillstyle(SOLID_FILL, GREEN);
					G.td[G.n].x=x2;
					G.td[G.n].y=y2;
					setcolor(GREEN);
					setbkcolor(GREEN);
					circle(G.td[G.n].x,G.td[G.n].y, R);
					floodfill(G.td[G.n].x, G.td[G.n].y, GREEN);
					settextstyle(0,0,1);
	
					textReadword(G.td[G.n].x-15, G.td[G.n].y-5, s);
					int k=0;
					while(1)
					{
						k++;
						if(strcmp((G.Tendinh[k].ten),s)==0)
						{
							settextstyle(8,0,1);
							setbkcolor(YELLOW);setcolor(RED);
							outtextxy(5,520,"TEN TRUNG VUI LONG NHAP LAI!");
							setcolor(GREEN);
							setbkcolor(GREEN);
						
							settextstyle(0,0,1);
							outtextxy(G.td[G.n].x-15, G.td[G.n].y-5,"abcd");
							strcpy(s,"");
							textReadword(G.td[G.n].x-15, G.td[G.n].y-5, s);
							k=0;
						}
						if(k>=G.n)
						{
							break;
						}
					}
					strcpy(G.Tendinh[G.n].ten,s);
					
			}
			if(x2>335&&x2<435&&y2>20&&y2<70)
			{
				break;
			}
		}
	}
	matran(G);
}
void trongso(Graph& G)
{
	settextstyle(0,0,1);
	int dinhdau=0;
	int dinhcuoi=0; 
	int kiemtraclickright=0;	
	int textX=2;
	int textY=530;
	char s[100];
	int xtemp,ytemp;
	while(1)
	{
		delay(0.0001);
		
		if(kiemtraclickright==2)
        {
        	setbkcolor(15);
			setcolor(0);
			settextstyle(8,0,1);
			textWrite(textX, textY, "MOI NHAP TRONG SO ",GREEN);
			char *a = new char[6];
			strcpy(a, "");
			strcat(a, G.Tendinh[dinhdau].ten);
			strcat(a, "->");
			strcat(a, G.Tendinh[dinhcuoi].ten);
			strcat(a, ":");
			textWrite(textX, textY, a,GREEN);
			
			textReadnumber(textX, textY, s);
			textX=2;textY=530;
			
			G.MTTS[dinhdau][dinhcuoi]=atoi(s);
			
			veCung( G, dinhdau, dinhcuoi, 0);
		
        	kiemtraclickright=0;
        	dinhdau=0;
        	dinhcuoi=0;
        	
        	trangthai();
        	
		}
		
		 if (ismouseclick(WM_LBUTTONDOWN)){
        	
            getmouseclick(WM_LBUTTONDOWN, xtemp, ytemp);
            
           
           
           for (int i=1;i<=G.n;i++)
            {
            	
            	if (lenghLine(G.td[i].x,G.td[i].y,xtemp,ytemp)<=R)// kiem tra lick chuot phai co ngay vong tron hay khong de ve cung
            	{
            		
            		kiemtraclickright++;
            		if (dinhdau == 0) 
					{
						setfillstyle(SOLID_FILL, 10);
						setcolor(RED);
						setbkcolor(10);
						circle(G.td[i].x,G.td[i].y, R);
						
							settextstyle(0,0,1);
						outtextxy(G.td[i].x - 15, G.td[i].y - 5, G.Tendinh[i].ten);
						dinhdau = i;
						
					}
					else if (i != dinhdau) dinhcuoi = i;
					else if (dinhdau == i) { kiemtraclickright--;}
            	
				}
			}
			
        }
        if(xtemp>335&xtemp<435&&ytemp>134&&ytemp<205)
        {
        	break;
		}
	}
	matran(G);
}

void luu(Graph & G)
{
	fstream fs;
	fs.open("Dothi.txt",ios::out);
	fs<<G.n<<endl;
	for(int i=1;i<=G.n;i++)
	{
		fs<<G.Tendinh[i].ten<<"\t\t"<<G.td[i].x<<"  "<<G.td[i].y<<endl;
	}
	for(int a1=1;a1<=G.n;a1++)
	{
		for(int a2=1;a2<=G.n;a2++)
		{
			fs<<G.MTTS[a1][a2]<<" ";
		}
		fs<<endl;
	}
	fs.close();
}
//doc file
int Doc(Graph & G)
{
	fstream fs;
	fs.open("Dothi.txt",ios::in);
	if (!fs) return -1;
	fs>>G.n;
	for(int i=1;i<=G.n;i++)
	{
		fs>>G.Tendinh[i].ten>>G.td[i].x>>G.td[i].y;
	}
	for(int a1=1;a1<=G.n;a1++)
	{
		for(int a2=1;a2<=G.n;a2++)
		{
			fs>>G.MTTS[a1][a2];
		}
	}
	fs.close(); return 0;
}
void velaidothi(Graph & G)
{
		for(int i=1;i<=G.n;i++)
		{
			setfillstyle(SOLID_FILL, GREEN);
			setcolor(YELLOW);
			circle(G.td[i].x, G.td[i].y, R);
			floodfill(G.td[i].x, G.td[i].y, YELLOW);
			setcolor(GREEN);
			circle(G.td[i].x, G.td[i].y, R);
			floodfill(G.td[i].x, G.td[i].y, GREEN);
			setcolor(RED);
			setbkcolor(GREEN);
			settextstyle(0,0,1);
			outtextxy(G.td[i].x - 15, G.td[i].y - 5, G.Tendinh[i].ten);
		}
		for(int a1=1;a1<=G.n;a1++)
		{
			for(int a2=1;a2<=G.n;a2++)
			{
				if(G.MTTS[a1][a2]!=0)
				{
					veCung(G,a1,a2,0);
				}
			}
		}
		
}
// nut load
void clear(Graph & G);
void load(Graph & G)
{
	clear(G);
	Doc(G);
	velaidothi(G);
	matran(G);
}
// nut clear
void clear(Graph & G)
{
	setfillstyle(SOLID_FILL,15);
	setbkcolor(WHITE);
	setcolor(15);
	bar(getmaxx(),11,470,480);
	vehinhchunhatvien(0,210,295,480,7);
	settextstyle(8,0,1);
	outtextxy(10,205,"ADJACENCY MATRIX");
	for(int i=1;i<=G.n;i++)
	{
		for (int j=1;j<=G.n;j++)
		{
			G.MTTS[i][j]=0;
		}
		strcpy(G.Tendinh[i].ten,"");
		G.td[i].x=0;
		G.td[i].y=0;
	}
	G.n=0;
}
// nut xoa dinh

void xoa(Graph&G,int vitri)
{
	for(int i=1;i<=G.n;i++)
	{
		if(G.MTTS[vitri][i]!=0)
		{
			veCung(G,vitri,i,15);
			G.MTTS[vitri][i]==0;
		}
		else {
			if(G.MTTS[i][vitri]!=0)
			{
				veCung(G,i,vitri,15);
				G.MTTS[i][vitri]==0;
			}
		}
	}
		setcolor(15);
	setfillstyle(SOLID_FILL, 15);
	setcolor(15);
	circle(G.td[vitri].x, G.td[vitri].y, R);
	floodfill(G.td[vitri].x, G.td[vitri].y, 15);
	setcolor(15);
	setbkcolor(15);
	settextstyle(0,0,1);
	outtextxy(G.td[vitri].x - 15, G.td[vitri].y - 5, G.Tendinh[vitri].ten);
	// cap nhat ten dinh voi toa do moi trong MTTS
	for(int i=vitri;i<G.n;i++)
	{
		strcpy(G.Tendinh[i].ten,G.Tendinh[i+1].ten);
		G.td[i].x=G.td[i+1].x;G.td[i].y=G.td[i+1].y;
		
	}
	strcpy(G.Tendinh[G.n].ten,"");
	// thay doi ma tran
	// thay doi dong
	for(int a1=vitri;a1<G.n;a1++)
	{
		for(int a2=1;a2<=G.n;a2++)
		{
			G.MTTS[a1][a2]=G.MTTS[a1+1][a2];
		}
	}
	//thay doi cot
	for(int a1=1;a1<=G.n;a1++)
	{
		for(int a2=vitri;a2<G.n;a2++)
		{
			G.MTTS[a1][a2]=G.MTTS[a1][a2+1];
		}
	}
	for(int an=1;an<=G.n;an++)
	{
		G.MTTS[an][G.n]=G.MTTS[G.n][an]=0;
	}
	G.n--;
	setcolor(0);
	velaidothi(G);
}

void xoadinh(Graph & G)
{
	int xtemp,ytemp;
	while(1)
	{
		delay(0.001);
		if(ismouseclick(WM_LBUTTONDOWN))
		{
			getmouseclick(WM_LBUTTONDOWN,xtemp,ytemp);
			if(xtemp>335&&xtemp<435&&ytemp>75&&ytemp<125) break;
			for(int i=1;i<=G.n;i++)
			{
				if(lenghLine(G.td[i].x,G.td[i].y,xtemp,ytemp)<=R)
				{
					xoa(G,i);
				}
			}
			
		}
	}
	matran(G);
}
// nut di chuyen dinh
void chuottraidichuyen(Graph & G, int i,int & buong)
{

	int textX,textY;
		while(2)
			{
				
					delay(0.001);
					if(ismouseclick(WM_LBUTTONUP))
					{
						getmouseclick(WM_LBUTTONUP,textX,textY);
						
						if(buong==2)
						{
							break;
						}
							buong=2;
						
					}
					if(ismouseclick(WM_MOUSEMOVE))
					{
						getmouseclick(WM_MOUSEMOVE,textX,textY);
						if(textX<getmaxx()&&textX>470+R&&textY>11+R&&textY<480-R)// gioi han di chuyen
						{
						
						G.td[i].x=textX;
						G.td[i].y=textY;
						//to lai khung nguoi dung
						setfillstyle(SOLID_FILL,15);
						setbkcolor(15);
						setcolor(0);
						bar(getmaxx(),11,470,480);
						// dua do thi toa do moi vao
						velaidothi(G);
					
						}
					}
					
			}
}

void dichuyen(Graph&G,int buong)
{
	int a,b;
	int stop;

	while (1)
	{
		delay(0.0001);
		stop=1;
		if(ismouseclick(WM_LBUTTONDOWN))
		{
			getmouseclick(WM_LBUTTONDOWN,a,b);
			if(stop==1)
			{
					for(int i=1;i<=G.n;i++)
					{
					
						if(lenghLine(G.td[i].x,G.td[i].y,a,b)<=R)
						{
						
							chuottraidichuyen(G,i,buong);
							
							break;
						}
					}
				stop=0;
			}	
			if(a>335&&a<435&&b>185&&b<235)
			{
				break;
			}
			
		}
	}
}

int congcu(int x2,int y2,Graph& G,int & stop)
{
	int x3=x2;
	int y3=y2;

			//them dinh
			if(x3>335&&x3<435&&y3>20&&y3<70)
			{
				vehinhchunhatvien(335,20,435,70,11);
            	outtextxy(350,35,"INSERT");
				settextstyle(8,0,1);
				
				// co su kien moi
				vedinh(G);
	
				vehinhchunhatvien(335,20,435,70,9);
            	outtextxy(350,35,"INSERT");
				settextstyle(8,0,1);
				return 0;
			}
			// xoa dinh
			if(x3>335&&x3<435&&y3>75&&y3<125)
			{
				settextstyle(8,0,1);
				vehinhchunhatvien(335,75,435,125,11);
				outtextxy(350,90,"DELETE");
				xoadinh(G);
				vehinhchunhatvien(335,75,435,125,9);
				settextstyle(8,0,1);
				outtextxy(350,90,"DELETE");
				return 0;
			}
			// them trong so
			if(x3>335&&x3<435&&y3>130&&y3<180)
			{
					settextstyle(8,0,1);
				    vehinhchunhatvien(335,130,435,180,11);
                	outtextxy(350,145,"WEIGHT");
					trongso(G);
					vehinhchunhatvien(335,130,435,180,9);
					settextstyle(8,0,1);
                	outtextxy(350,145,"WEIGHT");
				return 0;
	
			}
			//nut di chuyen
			if(x3>335&&x3<435&&y3>185&&y3<235)
			{
				settextstyle(8,0,1);
				vehinhchunhatvien(335,185,435,235,11);
	            outtextxy(360,200,"MOVE");
				int buong=1;
				dichuyen(G,buong);
			    vehinhchunhatvien(335,185,435,235,9);
		    	settextstyle(8,0,1);
            	outtextxy(360,200,"MOVE");
			}
			//nut save
			if(x3>335&&x3<435&&y3>240&&y3<290)
			{
				vehinhchunhatvien(335,240,435,290,11);
				settextstyle(8,0,1);
				outtextxy(360,255,"SAVE");
				luu(G);
				delay(10);
				vehinhchunhatvien(335,240,435,290,9);
				outtextxy(360,255,"SAVE");
				return 0;
				
			}
			//nut load
			if(x3>335&&x3<435&&y3>295&&y3<345)
			{
				vehinhchunhatvien(335,295,435,345,11);
				settextstyle(8,0,1);
	            outtextxy(360,310,"LOAD");
				load(G);
				delay(20);
		        vehinhchunhatvien(335,295,435,345,9);
				settextstyle(8,0,1);
	            outtextxy(360,310,"LOAD");
				return 0;
			}
			//nut clear
			if (x3>335&&x3<435&&y3>350&&y3<400)
			{
				vehinhchunhatvien(335,350,435,400,11);
				settextstyle(8,0,1);
            	outtextxy(360,365,"CLEAR");
				clear(G);
				vehinhchunhatvien(335,350,435,400,9);
				settextstyle(8,0,1);
            	outtextxy(360,365,"CLEAR");
				return 0;
	
			}
			//nut exit
			if((335<x3)&&(x3<435)&&(405<y3)&&(y3<455))
			{
					closegraph();
					stop=0;
					return 0;
			}
			
}

// nut DFS

void DFS1in(int i,int tham[],Graph G,int &dfsx,int &dfsy){
	char a[100];
	int cd=0;
	int top=0;
	a[top++]=i;
	tham[i]=1;
	int z=0;
	while(top!=0)
	{
		if(top!=0&&z==1){
			settextstyle(8,0,1);
			textWrite(dfsx,dfsy,"->",10);
		
		}
		i=a[--top];
		settextstyle(8,0,1);
		textWrite(dfsx,dfsy,G.Tendinh[i].ten,10);
		
		for(int k=G.n;k>=1;k--)
		{
			if(G.MTTS[i][k]!=0&&tham[k]==0)
			{
				cd=cd+G.MTTS[i][k];
				delay(300);
				veCungdemo(G,i,k,4);
				tham[k]=1;
				a[top++]=k;
				z=1;
			}
		}
	}
	char k[100];
	_itoa(cd,k,10);
	settextstyle(8,0,1);
	textWrite(dfsx,dfsy,"  Chieu dai: ",10);
	textWrite(dfsx,dfsy,k,10);
	
}
void DFS(Graph G){
	int x6,y6;
	
	while(1)
	{
		delay(0.0001);
		if(ismouseclick(WM_LBUTTONDOWN))
		{
			getmouseclick(WM_LBUTTONDOWN,x6,y6);
			for(int k=1;k<=G.n;k++)
			{
				if(lenghLine(G.td[k].x,G.td[k].y,x6,y6)<=R)
				{
					int dfsx=10;
					int dfsy=525;
					int tham[100];
					for(int i=1;i<=G.n;i++) tham[i]=0;
				
					 DFS1in(k,tham,G,dfsx,dfsy);
					 settextstyle(8,0,1);
					 textWriteln(dfsx,dfsy,"");
					 textWrite(dfsx,dfsy,"NHAN ENTER DE CHUONG TRINH DUOC TIEP TUC !",RED);
					 while(1)
					 {
					 	delay(0.0001);
					 	char c;
					 	c=getch();
					 	if(c==13)
					 	{
					 		trangthai();
					 		velaidothi(G);
					 		break;
						}
					}				
				}
			
			}
			if(x6>5&&x6<85&&y6>25&&y6<65)
			{
				break;
			}
		}
	}

}

void ketthuc(int x, int y)
{
	textWriteln(x,y,"");
	textWrite(x,y,"NHAN ENTER DE CHUONG TRINH DUOC TIEP TUC !",RED);
	while(1)
	{
		delay(0.0001);
		char c;
		c=getch();
		if(c==13)
		{
			trangthai();
			velaidothi(G);
			break;
		}
	}				
}
//BFS
void BFS(Graph G)
{
	int x,y;
	while (1)
	{
		delay(0.0001);
		if(ismouseclick(WM_LBUTTONDOWN))
		{
			getmouseclick(WM_LBUTTONDOWN,x,y);
			for(int i=1;i<=G.n;i++)
			{
				if(lenghLine(G.td[i].x,G.td[i].y,x,y)<=R)
				{
					
					int queue[MAX],d,c,tham[MAX],cd;
					cd=d=c=0;
					int u,v;
					for(int h=1;h<=MAX;h++)tham[h]=0;
					int bfsx=10;
					int bfsy=525;
					settextstyle(8,0,1);
					textWrite(bfsx,bfsy,G.Tendinh[i].ten,10);
					queue[c++]=i;tham[i]=1;
					while(d!=c)
						{
							u=queue[d++];tham[u]=1;
							for(v=1;v<=G.n;v++)
							{
									if(G.MTTS[u][v]!=0&&tham[v]==0)
								{
									delay(300);
									settextstyle(8,0,1);
									textWrite(bfsx,bfsy,"->",10);
									textWrite(bfsx,bfsy,G.Tendinh[v].ten,10);
									veCungdemo(G,u,v,RED);
									cd=cd+G.MTTS[u][v];
									tham[v]=1;
									queue[c++]=v;
								}
							}
						}
					char z[100];
					_itoa(cd,z,10);
					settextstyle(8,0,1);
					textWrite(bfsx,bfsy,"  Chieu dai: ",10);
					textWrite(bfsx,bfsy,z,10);
					ketthuc(bfsx,bfsy);
				}
			}
			if(x>90&&x<195&&y>25&&y<65)
			{
				break;
			}
		}
	}
}

// lien thong
void DFS1(int i,int tham[],Graph G){
	int top=0;
	int a[MAX];
	a[top++]=i;// cau truc stack
	tham[i]=1;
	while(top!=0)
	{
		i=a[--top];	
		for(int k=G.n;k>=1;k--)
		{
			if(G.MTTS[i][k]!=0&&tham[k]==0)
			{
				tham[k]=1;
				a[top++]=k;
			}
		}
	}
}
int kiemtralienthong(Graph G)
{
	int tham[MAX],br[MAX],sxbr[MAX];
	int stplt=0;
	for (int i=1;i<=G.n;i++)  sxbr[i]=br[i]=tham[i]=0;
	int temp=0;
	for(int k1=1;k1<=G.n;k1++)
	{
		sxbr[k1]=k1;
		for(int k2=1;k2<=G.n;k2++)
		{
			if(G.MTTS[k1][k2]!=0)
			{
				br[k1]++;
			}
		}
	}
	for(int c1=1;c1<=G.n-1;c1++)
	{
		for(int c2=c1+1;c2<=G.n;c2++)
		{
			if(br[c1]<br[c2])
			{
				int temp1=br[c1];
                br[c1]=br[c2];
                br[c2]=temp1;
                temp=sxbr[c1];
                sxbr[c1]=sxbr[c2];
                sxbr[c2]=temp;
			}
		}
	}
		for(int n1=1;n1<=G.n;n1++)
	{
		if(tham[sxbr[n1]]==0)
		{
			
			for(int j1=1;j1<=G.n;j1++)
			{
				if(tham[sxbr[j1]]==1&&G.MTTS[sxbr[n1]][sxbr[j1]]!=0)
				{
					int ltn1[MAX],ltj1[MAX];
					int stop=0;
					for(int t1=1;t1<=G.n;t1++) ltn1[t1]=ltj1[t1]=0;
					for(int z1=1;z1<=G.n;z1++)
					{
						if(tham[sxbr[z1]]==1&&sxbr[z1]!=sxbr[n1])
						{
							DFS1(sxbr[z1],ltn1,G);
							if(ltn1[sxbr[j1]]==1)
							{
								for(int z2=1;z2<=G.n;z2++)ltn1[z2]=0;
								DFS1(sxbr[n1],ltn1,G);ltn1[sxbr[n1]]=0;
								DFS1(sxbr[z1],ltj1,G);
								for(int ss=1;ss<=G.n;ss++)
								{
									if(ltn1[ss]!=ltj1[ss])
									{
										stop=1;
									}
									else
									{
										if(ltn1[ss]==ltj1[ss]&&ltn1[ss]==1)
										{
											tham[ss]=0;
										}
									}
								}
								if(stop==0)
								{
									stplt--;
								}
							}
						}
					}
				}
			}
			stplt++;
			DFS1(sxbr[n1],tham,G);
		}
	}
	return stplt;

}
void lienthong(Graph G)
{
	int stplt=kiemtralienthong(G);
	char v[100];
	_itoa(stplt,v,10);
	int lx=5;
	int ly=525;
	settextstyle(8,0,1);
	textWrite(lx,ly,"Do thi co ",10);
	textWrite(lx,ly,v,10);
	textWrite(lx,ly," thanh phan lien thong:",10);
	int tham[MAX],br[MAX],sxbr[MAX];
	for (int m=1;m<=G.n;m++) sxbr[m]=br[m]=tham[m]=0;
	int temp=0;
	for(int k1=1;k1<=G.n;k1++)
	{
		sxbr[k1]=k1;
		for(int k2=1;k2<=G.n;k2++)
		{
			if(G.MTTS[k1][k2]!=0)
			{
				br[k1]++;
			}
		}
	}
	for(int c1=1;c1<=G.n-1;c1++)
	{
		for(int c2=c1+1;c2<=G.n;c2++)
		{
			if(br[c1]<br[c2])
			{
				int temp1=br[c1];
                br[c1]=br[c2];
                br[c2]=temp1;
                temp=sxbr[c1];
                sxbr[c1]=sxbr[c2];
                sxbr[c2]=temp;
			}
		}
	}
		for(int n1=1;n1<=G.n;n1++)
	{
		if(tham[sxbr[n1]]==0)
		{
			for(int j1=1;j1<=G.n;j1++)
				{
					if(tham[sxbr[j1]]==1&&G.MTTS[sxbr[n1]][sxbr[j1]]!=0)
					{
						int ltn1[MAX],ltj1[MAX];
						int stop=0;
						for(int t1=1;t1<=G.n;t1++) ltn1[t1]=ltj1[t1]=0;
						for(int z1=1;z1<=G.n;z1++)
						{
							if(tham[sxbr[z1]]==1&&sxbr[z1]!=sxbr[n1])
							{
								DFS1(sxbr[z1],ltn1,G);
								if(ltn1[sxbr[j1]]==1)
								{
									for(int z2=1;z2<=G.n;z2++)ltn1[z2]=0;
									DFS1(sxbr[n1],ltn1,G);ltn1[sxbr[n1]]=0;
									DFS1(sxbr[z1],ltj1,G);
									for(int ss=1;ss<=G.n;ss++)
									{
										if(ltn1[ss]!=ltj1[ss])
										{
											stop=1;
										}
										else
										{
											if(ltn1[ss]==ltj1[ss]&&ltn1[ss]==1)
											{
												tham[ss]=0;
											}
										}
									}
									if(stop==0)
									{
										ly=ly-20;
									}
								}
							}
						}
					}					
				}
			textWriteln(lx,ly,"");
			DFS1in(sxbr[n1],tham,G,lx,ly);
		}
	}

	ketthuc(lx,ly);
}
// tim duong di nho nhat 
void Dijkstra1(Graph G, int s, int t,int &dx,int &dy)
{
	int tham[MAX],truoc[MAX];
	int d[MAX];
	for(int k=1;k<=G.n;k++) tham[k]=0;
	DFS1(t,tham,G);
	if (tham[s]==1)
	{
			settextstyle(8,0,1);
			textWrite(dx,dy,"Duong di ngan nhat tu ",10);
			textWrite(dx,dy,G.Tendinh[t].ten,10);
			textWrite(dx,dy," den ",10);
			textWrite(dx,dy,G.Tendinh[s].ten,10);
			textWrite(dx,dy," la: ",10);
			textWriteln(dx,dy,"");
			for (int i=1;i<=G.n;i++)
			for (int j=1;j<=G.n;j++)
				{
					if (G.MTTS[i][j]==0)
					{
						G.MTTS[i][j]=10000;
					}
					tham[i]=0;
				}		
		//khoi tao truoc
		for (int i=1;i<=G.n;i++)
		{
			d[i]=G.MTTS[t][i];truoc[i]=t;
		}
		tham[t]=1;
		// duyet tim duong di ngan nhat
		for(int m=1;m<G.n;m++)
		{
			int temp=10000;
			int c;
			int u=0;
			for (c=1;c<=G.n;c++)
			{
				if(tham[c]==0&&d[c]<temp)
				{
					u=c;temp=d[c];
				}
			}
			tham[u]=1;
			if(u==s)
			{
				break;
			}
			for (int v=1;v<=G.n;v++)
			{
				if(tham[v]==0&&d[v]>d[u]+G.MTTS[u][v])
				{
					d[v]=d[u]+G.MTTS[u][v];
					truoc[v]=u;
				}
			}
		}
		//tra ma tran ve gia tri 0 thay cho 10000 nay tao de ve cung dc 
		for (int i1=1;i1<=G.n;i1++)
		{
					for(int j1=1;j1<=G.n;j1++) 
				{
					if(G.MTTS[i1][j1]==10000)
					{
							G.MTTS[i1][j1]=0;
					}
				}
		}
		
		// in duong di nho nhat ra
		int z=s;
		int stack[MAX];
		int top=-1;
		stack[top++]=s;
		do
		{ 
			veCungdemo(G,s,truoc[s],RED);
			settextstyle(8,0,1);
			s=truoc[s];
			stack[top++]=s;
		}while(s!=t);
		while(top!=-1)
		{
			textWrite(dx,dy,G.Tendinh[stack[--top]].ten,10);
			if(top!=-1)
			{
				textWrite(dx,dy,"->",10);
			}
		}
		textWriteln(dx,dy,"");
		textWrite(dx,dy,"chieu dai la : ",10);
		char f[600];
		_itoa(d[z],f,10);
		textWrite(dx,dy,f,10);
		
	}
	else  {
		settextstyle(8,0,1);
			textWrite(dx,dy,"KHONG CO DUONG DI TU ",10);
			textWrite(dx,dy,G.Tendinh[s].ten,10);
			textWrite(dx,dy," den ",10);
			textWrite(dx,dy,G.Tendinh[t].ten,10);
	}

}
void Dijkstra(Graph G)
{
	int kiemtraclick=0;
	int s,t,x3,y3;
	s=t=0;
	while(1)
	{
		delay(0.0001);
		if(kiemtraclick==2)
		{
			int tham[MAX],truoc[MAX];
			for(int j=1;j<=G.n;j++)
			{
				tham[j]=truoc[j]=0;
			}
			int dx=5;
			int dy=525;
			Dijkstra1(G,t,s,dx,dy);
			ketthuc(dx,dy);
			s=0;t=0;kiemtraclick=0;
		}
		if(ismouseclick(WM_LBUTTONDOWN))
		{
			getmouseclick(WM_LBUTTONDOWN,x3,y3);
			for(int i=1;i<=G.n;i++)
			{
				if(lenghLine(x3,y3,G.td[i].x,G.td[i].y)<=R)
				{
					kiemtraclick++;
					if (s == 0) 
					{
						setfillstyle(SOLID_FILL, 10);
						setcolor(RED);
						setbkcolor(10);
						circle(G.td[i].x,G.td[i].y, R);
						
							settextstyle(0,0,1);
						outtextxy(G.td[i].x - 15, G.td[i].y - 5, G.Tendinh[i].ten);
						s = i;
						
					}
					else if (i != s) t = i;
					else if (s == i) { kiemtraclick--;}
					cout<<kiemtraclick<<endl;
				}
			}
			if(x3>90&&x3<170&&y3>70&&y3<110)
			{
					break;
			}
		}
	}
}
//dinh tru
// xoa 1 dinh demo tim dinh tru
//xoa 1 dinh
int dinhtru1(Graph G,int vitri)
{
	int bd=kiemtralienthong(G);
	for(int i=1;i<=G.n;i++)
	{
		if(G.MTTS[vitri][i]!=0)
		{
			G.MTTS[vitri][i]==0;
		}
		else {
			if(G.MTTS[i][vitri]!=0)
			{
				G.MTTS[i][vitri]==0;
			}
		}
	}
	// cap nhat ten voi tao do lai
	for(int a1=vitri;a1<G.n;a1++)
	{
		for(int a2=1;a2<=G.n;a2++)
		{
			G.MTTS[a1][a2]=G.MTTS[a1+1][a2];
		}
	}
	//thay doi cot
	for(int a1=1;a1<=G.n;a1++)
	{
		for(int a2=vitri;a2<G.n;a2++)
		{
			G.MTTS[a1][a2]=G.MTTS[a1][a2+1];
		}
	}
	G.n--;
	if(bd<kiemtralienthong(G))
	{
		return 1;
	} 
	return 0;
}
//ta xet tung dinh xem dinh nao la dinh tru roi xuat ra

void dinhtru(Graph G, int &tx, int &ty)
{
	textWrite(tx,ty,"Dinh tru gom: ",10);
	int dem=0;
	for(int i=1;i<=G.n;i++)
	{
		if(dinhtru1(G,i)==1)
		{
			
			if(dem!=0)
			{
				textWrite(tx,ty,", ",10);
			}
				textWrite(tx,ty,G.Tendinh[i].ten,10);
				dem++;
			setfillstyle(SOLID_FILL, 1);
			// to mau dinh tru
				settextstyle(0,0,1);
				setcolor(BLACK);
				circle(G.td[i].x,G.td[i].y, R);
				floodfill(G.td[i].x, G.td[i].y, BLACK);

				setcolor(1);
				circle(G.td[i].x, G.td[i].y, R);
				floodfill(G.td[i].x, G.td[i].y, 1);
				setcolor(RED);
				setbkcolor(1);
				outtextxy(G.td[i].x - 15, G.td[i].y - 5, G.Tendinh[i].ten);
				settextstyle(8,0,1);

		}
	}
}
// canh cau cua do thi
void canhcau(Graph G,int &cx,int &cy)
{
	textWrite(cx,cy,"Cac canh cau la: ",10);
	int ts=0;
	int bd=kiemtralienthong(G);
	int dauphay=0;
	for (int i=1;i<=G.n;i++)
	{
		for (int j=1;j<=G.n;j++)
		{
			ts=G.MTTS[i][j];
			G.MTTS[i][j]=0;
			if(bd<kiemtralienthong(G))
			{
				// xuat ket qua ra thanh trang thai
							if(dauphay!=0)
						{
								textWrite(cx,cy,", ",10);
						}
						textWrite(cx,cy,G.Tendinh[i].ten,10);
						textWrite(cx,cy,"->",10);
						textWrite(cx,cy,G.Tendinh[j].ten,10);
						dauphay++;
					// ta de mo canh len do thi;	
				G.MTTS[i][j]=ts;
				veCung(G,i,j,4);
				settextstyle(8,0,1);
			}
			G.MTTS[i][j]=ts;
		}
	}
}
//dinh tru trong ccau
void CCau(Graph)
{
	int tx=5;
	int ty=525;
	// dua canh cau ra truoc
	canhcau(G,tx,ty);
	textWriteln(tx,ty,"");
	// xuat dinh tru sau
	dinhtru(G,tx,ty);
	ketthuc(tx,ty);
	
}
// euler
void DDELUER(Graph &G,int b[MAX], int m,int i,int &dx, int &dy)// thuat toan nay co nhiem vu de quy tim ra duong di euler
{
	int l=0;// co nhiem vu luu lai trong so
	for(int j=1;j<=G.n;j++)
	{
		if(G.MTTS[b[i-1]][j]!=0)// tai sao b-1 vi b day co nhiem vu nhu 1 mang truoc nhu stack luu lai cac dinh da qua
		{
			b[i]=j;
			l=G.MTTS[b[i-1]][j];//luu lai trong so lat tra ve nhu cu khi no quay lui
			G.MTTS[b[i-1]][j]=0;// danh dau no khi da di qua tuc la cho no ve 0
			if(i==m)
			{
				textWriteln(dx,dy,"");
				for(int k=0;k<=m;k++)
				{
					textWrite(dx,dy,G.Tendinh[b[k]].ten,10);
					if(k!=m)
					{
						textWrite(dx,dy,"->",10);
					}

				}
				if(dy>650)
				{
					ketthuc(dx,dy);
					dy=510;
					settextstyle(8,0,1);
				}
				G.MTTS[b[i-1]][j]=l;
			} 
			else {
				DDELUER(G,b,m,i+1,dx,dy);// de quy tim dinh ke tiep theo
			 	G.MTTS[b[i-1]][j]=l;//tra lai trong so neu quay lui				
			}
		}
	}
}
void Euler(Graph G,int hx,int hy)
{
	if(kiemtralienthong(G)==1)// kiem tra do thi co 1 thanh phan lien thong moi co the tim euler duoc
	{
		textWrite(hx,hy,"Duong di Euler gom: ",10);
		int m=0;// m la so canh cua do thi
		int b[MAX];
		for(int i=1;i<=G.n;i++)
		{
			for(int j=1;j<=G.n;j++)
				{
					if(G.MTTS[i][j]!=0)m++;
				}
		}
		for(int u=1;u<=G.n;u++)
		{
			b[0]=u;
			DDELUER(G,b,m,1,hx,hy);//
		}
	}
	else
	{
		textWrite(hx,hy,"Do thi khong phai la do thi euler",10);
	}
	ketthuc(hx,hy);
}
//Hamilton
void DDHAMILTON(Graph G,int tham[MAX],int b[MAX],int i,int &dx, int &dy)// gan giong voi EULER sua lai tu do
{ 
	for(int k1=1;k1<=G.n;k1++)
	{
		if(G.MTTS[b[i-1]][k1]!=0&&tham[k1]==0)
		{
			b[i]=k1; tham[k1]=1;
			if(i<G.n)
			  DDHAMILTON(G,tham,b,i+1,dx,dy);
			else
			{
				textWriteln(dx,dy,"");
				for(int k2=0;k2<=G.n;k2++)
					{
						textWrite(dx,dy,G.Tendinh[b[k2]].ten,10);
						if(k2!=G.n)
						{
							textWrite(dx,dy,"->",10);
						}
					}
				
				if(dy>650)
				{
					ketthuc(dx,dy);
					dy=510;
					settextstyle(8,0,1);
				}
			
			}
			tham[k1]=0;
		
		}
	}
}
void Hamilton(Graph G, int hx,int hy)
{
	if(kiemtralienthong(G)==1)
	{
		textWrite(hx,hy,"Duong di hamilton gom: ",10);
			int tham[MAX],b[MAX];
			for(int k2=1;k2<=G.n;k2++)tham[k2]=b[k2]=0;
			for(int k3=1;k3<=G.n;k3++)
			{
				b[0]=k3;
				DDHAMILTON(G,tham,b,1,hx,hy);
			}
		
	}
	else
	{
		textWrite(hx,hy,"Day khong phai la do thi hamiton",10);
	}
	ketthuc(hx,hy);
}
// hamilton(G);//tong hop
void hamilton(Graph G)// muc nay gom 2 cong cu gom co tim Euler va hamilton
{
	int hx=5;
	int hy=525;
	Euler(G,hx,hy);
	settextstyle(8,0,1);
	Hamilton(G,hx,hy);
}
// topo sort 
struct node
{
	int dinh_ke;
	struct node*next;
};
typedef struct node*NODEPTR;
struct phantu_ke
{
	int count;// dung de chi so ban bac vao cua no
	NODEPTR pF;// fist phan tu dau tien cua no
};
typedef struct phantu_ke Dothi[100]; //cung gan giong voi G
Dothi G1;
void Init_graph(Dothi G1)// tao 1 do thi trong graphic
{
	for (int i=0;i<=MAX;G1[i++].pF=NULL);
	
}
void DSLKD(Graph G,Dothi &G1)
{
	NODEPTR p;
	Init_graph(G1);
	// tim ban bac ra cua tung dinh
	for(int j=1;j<=G.n;j++)
	{
		G1[j].count=0;// cho ban bac ra bang 0 truoc
		for(int i=1;i<=G.n;i++)
		{
			if(G.MTTS[i][j]!=0)
			{
				G1[j].count++;// co ban bac vao
			}
		}
	}
	// tao danh sach lien ket don cho moi phan tu
	for(int i1=1;i1<=G.n;i1++)
	{
		for (int j1=1;j1<=G.n;j1++)
		{
			if(G.MTTS[i1][j1]!=0)
			{
				p=new node();
				p->next=NULL;
				p->dinh_ke=j1;
				if(G1[i1].pF==NULL)G1[i1].pF=p;
				else
				{
					p->next=G1[i1].pF;
					G1[i1].pF=p;
				}				
			}
		}
	}
}
void Topo_Sort(Graph G,Dothi &G1)
{
	int sx=10;
	int sy=525;
	int stack[100];
	int sp=-1;
	NODEPTR p;
	textWrite(sx,sy,"Sap sep topo: ",10);
	textWriteln(sx,sy,"");
	// ta tien hanh dua cac dinh khong phu thoc dinh nao lam truoc vao do thi
	for(int i=G.n;i>0;i--)
	{
		if(G1[i].count==0)
		{
			stack[++sp]=i;
		}
	}
	int h1,k1;
	for(int i=1;i<=G.n;i++)
	{
		if(sp==-1)
		{
			textWrite(sx,sy,"Day la do thi dinh huong co chu trinh -> khong the sap sep topo duoc",10);
			break;
		}
		h1=stack[sp--];
		delay(500);
		// to mau dinh duoc chon 
		setfillstyle(SOLID_FILL, 1);
		settextstyle(0,0,1);
		setcolor(BLACK);
		circle(G.td[h1].x,G.td[h1].y, R);
		floodfill(G.td[h1].x, G.td[h1].y, BLACK);

		setcolor(1);
		circle(G.td[h1].x, G.td[h1].y, R);
		floodfill(G.td[h1].x, G.td[h1].y, 1);
		setcolor(RED);
		setbkcolor(1);
		outtextxy(G.td[h1].x - 15, G.td[h1].y - 5, G.Tendinh[h1].ten);
		settextstyle(8,0,1);
		textWrite(sx,sy,G.Tendinh[h1].ten,10);
		if(i!=G.n) textWrite(sx,sy,"->",10);
		p=G1[h1].pF;
		while(p!=NULL)
		{
			k1=p->dinh_ke;
			G1[k1].count--;
			if(G1[k1].count==0)// da thuc hien cac cong viec truoc thoa
			{
				stack[++sp]=k1;
			}
			p=p->next;
		}
	}
	ketthuc(sx,sy);
}
//xuly()
void xuly(int a[100][100],int m[100],int &sm, int n){ //Xu ly de cho ra ket qua vao mang m[]
    int kt;
    for(int i=1;i<=n;i++)
        if(!m[i]) {
            sm++; //Dem so mau
            m[i]=sm;
            for(int j=i+1;j<=n;j++) //Kiem tra xem nhung dinh nao co the gan bang mau sm nua khong
                if((a[i][j]==0)&&(m[j]==0)){
                    kt=1;
                    for(int k=i+1;k<j;k++)
                        if((a[k][j]==1)&&(m[i]==m[k])){
                            kt=0;
                            break;
                        }
                    if(kt==1) m[j]=sm;
                }                   
        }
}
//To mau
void Tomau(Graph G)
{
	int  a[100][100]={0},sm=0,m[100]={0};
	for (int i=1;i<=G.n;i++)// ta chuyen ma tran trong so ve dang vo huong de to mau
	{
		for (int j=1;j<=G.n;j++)
		{
			if (G.MTTS[i][j]!=0)
			{
				a[i][j]=1;
				a[j][i]=1;
			}
		}
	}
	
	xuly(a,m,sm,G.n);// xu ly de lay mau vao
	int MAU[15]={22,2,3,13,5,6,7,8,9,10,11,12,1,14};
 	for(int i=1;i<=sm;i++){
        setfillstyle(SOLID_FILL, MAU[i]); 
        for(int j=1;j<=G.n;j++) if(m[j]==i) 
		{
			settextstyle(0,0,1);//  to mau dinh
			setcolor(MAU[i]);
			circle(G.td[j].x, G.td[j].y, R);
			floodfill(G.td[j].x, G.td[j].y, MAU[i]);
			setcolor(RED);
			setbkcolor(MAU[i]);
			outtextxy(G.td[j].x - 15, G.td[j].y - 5, G.Tendinh[j].ten);
			cout << j << " ";
        	cout << endl;
		}
    }
    settextstyle(8,0,1);
    int hx=5;
	int hy=500;
	ketthuc(hx,hy);
	velaidothi(G);
}
int menu(Graph G,int x1, int y1)
{
	while(1)
	{
		delay(0.0001);
	
		if(x1>5&&x1<85&&y1>25&&y1<65)
		{
			settextstyle(8,0,1);
			vehinhchunhatvien(5,25,85,65,11);
			outtextxy(30,35,"DFS");
			DFS(G);
			settextstyle(8,0,1);
			vehinhchunhatvien(5,25,85,65,9);
			outtextxy(30,35,"DFS");
			return 0;
		}
		if(x1>90&&x1<195&&y1>25&&y1<65)
		{
			settextstyle(8,0,1);
			vehinhchunhatvien(90,25,195,65,11);
			outtextxy(125,35,"BFS");
			BFS(G);
			settextstyle(8,0,1);
			vehinhchunhatvien(90,25,195,65,9);
			outtextxy(125,35,"BFS");
			return 0;
		}
		if(x1>200&&x1<280&&y1>25&&y1<65)
		{
			settextstyle(8,0,1);
			vehinhchunhatvien(200,25,280,65,11);
			outtextxy(205,35,"To mau");
			Tomau(G);
			settextstyle(8,0,1);
			vehinhchunhatvien(200,25,280,65,9);
			outtextxy(205,35,"To mau");
			return 0;
		}
		if(x1>5&&x1<85&&y1>70&&y1<110)
		{
			settextstyle(8,0,1);
			vehinhchunhatvien(5,70,85,110,11);
	    	outtextxy(20,80,"TPLT");
			lienthong(G);
			settextstyle(8,0,1);
			vehinhchunhatvien(5,70,85,110,9);
	    	outtextxy(20,80,"TPLT");
			return 0;
		}
		if(x1>90&&x1<195&&y1>70&&y1<110)
		{
			settextstyle(8,0,1);
			vehinhchunhatvien(90,70,195,110,11);
			outtextxy(125,80,"DDNN");
			settextstyle(8,0,1);
			Dijkstra(G);
			settextstyle(8,0,1);
			vehinhchunhatvien(90,70,195,110,9);
			outtextxy(125,80,"DDNN");
			settextstyle(8,0,1);
			return 0;
		}
		if(x1>200&&x1<280&&y1>70&&y1<110)
		{
				settextstyle(8,0,1);
				vehinhchunhatvien(200,70,280,110,11);
				outtextxy(220,80,"CCAU");
				CCau(G);
				settextstyle(8,0,1);
				vehinhchunhatvien(200,70,280,110,9);
				outtextxy(220,80,"CCAU");
				return 0;
		}
		if(x1>90&&x1<195&&y1>115&&y1<155)
		{
			settextstyle(8,0,1);
			vehinhchunhatvien(90,115,195,155,11);
         	outtextxy(100,125,"Hamilton");
			hamilton(G);
			settextstyle(8,0,1);
			vehinhchunhatvien(90,115,195,155,9);
        	outtextxy(100,125,"Hamilton");
			return 0;
		}
		if(x1>5&&x1<85&&y1>115&&y1<155)
		{
			settextstyle(8,0,1);
    		vehinhchunhatvien(5,115,85,155,11);
        	outtextxy(25,116,"Topo");
        	outtextxy(25,134,"Sort");
        	DSLKD(G,G1);
			Topo_Sort(G,G1);
			settextstyle(8,0,1);
			vehinhchunhatvien(5,115,85,155,9);
        	outtextxy(25,116,"Topo");
        	outtextxy(25,134,"Sort");
			return 0;
		}
	}
}
void giaodien()// man hinh chinh giao tiep voi nguoi dung
{
	settextstyle(8,0,1);
	//khung danh cho nguoi dung tuong tac voi do thi
	setcolor(BLACK);
	setfillstyle(SOLID_FILL,WHITE);
	setbkcolor(WHITE);
	rectangle(300,10,getmaxx(),480);
	bar(getmaxx(),11,301,480);
	
	// duong lam thanh tinh chinh trong khung
	moveto(getmaxx()-900,10);
	lineto(getmaxx()-900,480);
	
	//chuc nang them dinh
	vehinhchunhatvien(335,20,435,70,9);
	outtextxy(350,35,"INSERT");
	
	//chuc nang xoa dinh
	vehinhchunhatvien(335,75,435,125,9);
	outtextxy(350,90,"DELETE");
	
	//chuc nang them trong so
	vehinhchunhatvien(335,130,435,180,9);
	outtextxy(350,145,"WEIGHT");
	
	//chuc nang di chuyen
	vehinhchunhatvien(335,185,435,235,9);
	outtextxy(360,200,"MOVE");
	
	// chuc nang luu
	vehinhchunhatvien(335,240,435,290,9);
	outtextxy(360,255,"SAVE");
	
	// load
	vehinhchunhatvien(335,295,435,345,9);
	outtextxy(360,310,"LOAD");
	
	// clear
	vehinhchunhatvien(335,350,435,400,9);
	outtextxy(360,365,"CLEAR");
	
	// nut exit
	vehinhchunhatvien(335,405,435,455,9);
	outtextxy(360,420,"EXIT");
	
	//man hinh menu
	vehinhchunhatvien(0,10,295,200,7);
	outtextxy(10,5,"MENU");
	//nut DFS
	vehinhchunhatvien(5,25,85,65,9);
	outtextxy(30,35,"DFS");
	
	// nut BFS
	vehinhchunhatvien(90,25,195,65,9);
	outtextxy(125,35,"BFS");
	
	//nut to mau
	vehinhchunhatvien(200,25,280,65,9);
	outtextxy(205,35,"To mau");
	
	// nut lien thong
	vehinhchunhatvien(5,70,85,110,9);
	outtextxy(20,80,"TPLT");
	
    // nut DDNN
	vehinhchunhatvien(90,70,195,110,9);
	outtextxy(125,80,"DDNN");
	settextstyle(8,0,1);
	
	//nut CCau
	vehinhchunhatvien(200,70,280,110,9);
	outtextxy(220,80,"Ccau");
	
	//nut Hamilton
	vehinhchunhatvien(90,115,195,155,9);
	outtextxy(100,125,"Hamilton");
	
	// nut Topo Sort
	vehinhchunhatvien(5,115,85,155,9);
	outtextxy(25,116,"Topo");
	outtextxy(25,134,"Sort");
	//matran
	vehinhchunhatvien(0,210,295,480,7);
	settextstyle(8,0,1);//8,11
	outtextxy(10,205,"ADJACENCY MATRIX");
		trangthai();
	trogiup();
}

int main()
{
	initwindow(winx,winy);
	setbkcolor(7);
	cleardevice();
	giaodien();
	int stop=1;
	// ham bat su kien click
	while(stop!=0)
	{
		delay(0.0001);
		int x1,y1;
		
		// kiem tra click chuot trai
		if(ismouseclick(WM_LBUTTONDOWN))
		{
			
			// lay toa do click chuot gan vao bien x1 va y1
			getmouseclick(WM_LBUTTONDOWN,x1,y1);
			if(x1>335&&x1<435)
			{
				congcu(x1,y1,G,stop);
			} else 
			if(x1>0&&x1<330&&y1>20&&y1<200)
			{
				menu(G,x1,y1);
			} 	
		}
			
		if(ismouseclick(WM_MOUSEMOVE))
		{
			getmouseclick(WM_MOUSEMOVE,x1,y1);
			
				cout<<x1<<"  "<<y1<<endl;
			
		}
		if(ismouseclick(WM_LBUTTONDBLCLK))
		{
			getmouseclick(WM_LBUTTONDBLCLK,x1,y1);
			
		}
	
	}
	system("pause");
	return 0;
}
