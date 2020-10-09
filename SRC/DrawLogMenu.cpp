#pragma once
#include"DrawMunu.h"
#include"DiagnosisMessage.h"
#include"global.h"
void drawLogMenu() {  //一级子界面--诊疗记录
abcd:;
	MOUSEMSG m;
	initgraph(800, 600);
	setbkcolor(WHITE);
	cleardevice();
	setfillcolor(LIGHTBLUE);

	fillrectangle(200, 140, 600, 160);
	fillrectangle(200, 200, 600, 220);
	fillrectangle(200, 260, 600, 280);
	fillrectangle(200, 320, 600, 340);
	fillrectangle(200, 380, 600, 400);

	settextstyle(15, 0, "楷体");//设置文字大小 格式 
	setbkmode(TRANSPARENT);// 去掉文字背景
	outtextxy(250, 142, "增加诊疗记录");
	outtextxy(250, 202, "查询诊疗记录");
	outtextxy(250, 262, "删除诊疗记录");
	outtextxy(250, 322, "修改诊疗记录");
	outtextxy(260, 382, "返回主菜单");
	while (1) {
		m = GetMouseMsg();
		if (m.x >= 200 && m.x <= 600 && m.y >= 140 && m.y <= 160) {//检测鼠标的位置 是否满足条件
			setlinecolor(RED);//满足后 设置新的边框为红色
			rectangle(190, 135, 610, 165);//画新的边框
			//如果点击了 增加诊疗记录
			if (m.uMsg == WM_LBUTTONDOWN) {
				drawAddLogRecord();
				goto abcd;//功能实现后 跳转到 最开头
			}
		}
		else if (m.x >= 200 && m.x <= 600 && m.y >= 200 && m.y <= 220) {
			setlinecolor(RED);
			rectangle(190, 195, 610, 225);
			//如果点击了查询诊疗记录
			if (m.uMsg == WM_LBUTTONDOWN) {
				drawSearchMenu();
				goto abcd;
			}
		}
		else if (m.x >= 200 && m.x <= 600 && m.y >= 260 && m.y <= 280) {
			setlinecolor(RED);
			rectangle(190, 255, 610, 285);
			//点击了删除诊疗记录
			if (m.uMsg == WM_LBUTTONDOWN) {
				//输入直接删
				char buf[8];
				InputBox(buf, 8, "请输入7位诊疗记录编号");
				if (IsRegisterId(buf)) {
					if (deleteDiagnosisList(DiagnosisRecordHead, atoi(buf))) {
						InputBox(buf, 2, "删除成功，请继续");
					}
					else {
						InputBox(buf, 2, "删除失败，没有找到记录");
					}
				}
				//弹一个反馈窗口,暂时用Box代替
				break;
			}


		}
		else if (m.x >= 200 && m.x <= 600 && m.y >= 320 && m.y <= 340) {
			setlinecolor(RED);
			rectangle(190, 315, 610, 345);
			//点击了修改诊疗记录
			if (m.uMsg == WM_LBUTTONDOWN) {
				drawUpdateMenu();
				goto abcd;
			}
		}
		else if (m.x >= 200 && m.x <= 600 && m.y >= 380 && m.y <= 400) {
			setlinecolor(RED);
			rectangle(190, 375, 610, 405);
			//点击了返回主菜单
			if (m.uMsg == WM_LBUTTONDOWN) {

				return;
			}


		}
		else {
			setlinecolor(WHITE);
			rectangle(190, 135, 610, 165);
			rectangle(190, 195, 610, 225);
			rectangle(190, 255, 610, 285);
			rectangle(190, 315, 610, 345);
			rectangle(190, 375, 610, 405);
		}
	}
}