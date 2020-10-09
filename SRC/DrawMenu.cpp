#include"DrawMunu.h"
void drawMenu() {  //主菜单绘制函数
abcd:;
	MOUSEMSG m;
	//菜单
	initgraph(600, 700);
	setbkcolor(WHITE);
	cleardevice();  //刷新一次 略等于那个system(cls)
	setfillcolor(GREEN);
	//          左x1 高y1 右x2 高y2
	fillrectangle(10, 10, 395, 140);
	setfillcolor(LIGHTBLUE);
	fillrectangle(405, 10, 590, 140);
	setfillcolor(LIGHTRED);
	fillrectangle(10, 150, 190, 280);
	setfillcolor(LIGHTBLUE);
	fillrectangle(200, 150, 395, 280);
	setfillcolor(BLUE);
	fillrectangle(405, 150, 590, 280);
	setfillcolor(BLUE);
	fillrectangle(10, 290, 190, 420);
	setfillcolor(GREEN);
	fillrectangle(200, 290, 590, 420);
	setfillcolor(GREEN);
	fillrectangle(10, 430, 190, 560);
	setfillcolor(LIGHTRED);
	fillrectangle(200, 430, 380, 560);

	settextstyle(25, 0, "楷体");	//设置文字格式
	setbkmode(TRANSPARENT);			//去掉文字背景

	outtextxy(150, 60, "诊疗记录");
	outtextxy(440, 60, "医院营业额");
	outtextxy(50, 205, "医生情况");
	outtextxy(240, 205, "时间流逝");


	outtextxy(445, 205, "患者就诊");
	outtextxy(50, 350, "床位情况");
	outtextxy(350, 350, "住院缴费");
	outtextxy(50, 480, "住院报表");
	outtextxy(265, 480, "退出");



	settextcolor(BLACK);
	settextstyle(20, 0, "楷体");
	outtextxy(350, 660, "医院诊疗管理系统V1.0");

	while (1) {
		m = GetMouseMsg();
		if (m.x >= 10 && m.x <= 395 && m.y >= 10 && m.y <= 140) {
			setlinecolor(RED);
			rectangle(5, 5, 400, 145);
			//如果点击了诊疗记录
			if (m.uMsg == WM_LBUTTONDOWN) {
				drawLogMenu();
				goto abcd;
			}
		}
		else if (m.x >= 405 && m.x <= 590 && m.y >= 10 && m.y <= 140) {
			setlinecolor(RED);
			rectangle(400, 5, 595, 145);
			//如果点击了医院营业额
			if (m.uMsg == WM_LBUTTONDOWN) {
				drawHospitalIncome();
				goto abcd;
			}
		}
		else if (m.x >= 5 && m.x <= 190 && m.y >= 150 && m.y <= 280) {
			setlinecolor(RED);
			rectangle(5, 145, 195, 285);
			//点击了 医生情况
			if (m.uMsg == WM_LBUTTONDOWN) {
				drawDocSituation();
				goto abcd;
			}
		}
		else if (m.x >= 200 && m.x <= 395 && m.y >= 150 && m.y <= 280) {
			setlinecolor(RED);
			rectangle(195, 145, 400, 285);
			//点击了 时间流逝
			if (m.uMsg == WM_LBUTTONDOWN) {
				drawTiming();
				goto abcd;
			}
		}
		//
		else if (m.x >= 405 && m.x <= 590 && m.y >= 150 && m.y <= 280) {//
			setlinecolor(RED);
			rectangle(400, 145, 595, 285);
			//点击了 患者就诊
			if (m.uMsg == WM_LBUTTONDOWN) {
				drawPatientToTreat();
				goto abcd;
			}
		}
		else if (m.x >= 10 && m.x <= 190 && m.y >= 290 && m.y <= 420) {//
			setlinecolor(RED);
			rectangle(5, 285, 195, 425);
			//点击了 床位情况
			if (m.uMsg == WM_LBUTTONDOWN) {
				drawBedSituation();
				goto abcd;
			}
		}
		else if (m.x >= 200 && m.x <= 590 && m.y >= 290 && m.y <= 420) {
			setlinecolor(RED);
			rectangle(195, 285, 595, 425);
			//点击了 住院缴费
			if (m.uMsg == WM_LBUTTONDOWN) {
				drawToHandDeposit();
				goto abcd;
			}
		}
		else if (m.x >= 10 && m.x <= 190 && m.y >= 430 && m.y <= 560) {
			setlinecolor(RED);
			rectangle(5, 425, 195, 565);
			//点击了 住院报表
			if (m.uMsg == WM_LBUTTONDOWN) {
				drawInHospitalPatient();
				goto abcd;
			}

		}
		else if (m.x >= 200 && m.x <= 380 && m.y >= 430 && m.y <= 560) {
			setlinecolor(RED);
			rectangle(195, 425, 385, 565);
			//点击了 退出
			if (m.uMsg == WM_LBUTTONDOWN) {
				return;

			}

		}



		else {
			setlinecolor(WHITE);
			rectangle(5, 5, 400, 145);
			rectangle(400, 5, 595, 145);
			rectangle(5, 145, 195, 285);
			rectangle(195, 145, 400, 285);
			rectangle(400, 145, 595, 285);
			rectangle(5, 285, 195, 425);
			rectangle(195, 285, 595, 425);
			rectangle(5, 425, 195, 565);
			rectangle(195, 425, 385, 565);

		}
	}
	getchar();
	closegraph();
}