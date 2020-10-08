#include"DrawMunu.h"
#include"DiagnosisMessage.h"
#include"global.h"
#include"TimePassing.h"
#include"ListOperator.h"

//主菜单--时间流逝--子界面
void drawTiming(){
	int thirty_days = 0, day = 0, hour = 0, minute = 0;
	MOUSEMSG m;
	initgraph(500, 700);
	setbkcolor(WHITE);
	cleardevice();
	settextstyle(20, 0, "仿宋");//设置文字大小 格式 
	setbkmode(TRANSPARENT);// 去掉文字背景
	settextcolor(BLACK);

	outtextxy(80, 50, "当前时间：");
	outtextxy(80, 90, "调整时间：");

	outtextxy(80, 230, "+ 30天 :");
	outtextxy(80, 270, "+ 1 天 :");
	outtextxy(80, 310, "+ 1小时:");
	outtextxy(80, 350, "+ 1分钟:");
	TimeRecord temp = currentTime;
	char buf_cur[30];
	char buf_aft[30];
	sprintf_s(buf_cur,"%d月%d日 %02d:%02d",currentTime.month,currentTime.day,currentTime.hour,currentTime.minute);
	sprintf_s(buf_aft, "%d月%d日 %02d:%02d", temp.month, temp.day, temp.hour, temp.minute);
	outtextxy(200, 50, buf_cur);
	outtextxy(200, 90, buf_aft);

	setfillcolor(RGB(210, 210, 210));
	fillrectangle(125, 640, 200, 660);
	fillrectangle(300, 640, 375, 660);

	fillrectangle(280, 230, 330, 250);		//四个选择
	fillrectangle(280, 270, 330, 290);
	fillrectangle(280, 310, 330, 330);
	fillrectangle(280, 350, 330, 370);

	settextstyle(15, 0, "仿宋");
	outtextxy(285, 232, "选择");
	outtextxy(285, 272, "选择");
	outtextxy(285, 312, "选择");
	outtextxy(285, 352, "选择");

	outtextxy(147, 642, "确认");
	outtextxy(322, 642, "返回");

	settextstyle(20, 0, "仿宋");
	while (1)
	{
		
		clearrectangle(200, 30, 500, 120);
		outtextxy(200, 50, buf_cur);
		outtextxy(200, 90, buf_aft);
		m = GetMouseMsg();
		if (m.x >= 125 && m.x <= 200 && m.y >= 640 && m.y <= 660)
		{
			//点击了确认
			if (m.uMsg == WM_LBUTTONDOWN) {
				timePass(InHospitalHead, thirty_days, day, hour, minute);	//流逝
				int cnt = sortInHospitalList(InHospitalHead);				//需要交押金病人数
				drawPatientToDeposit(cnt);									//打印该交押金的住院病人			
				break;
			}
			else {
				continue;
			}
		}
		else if (m.x >= 300 && m.x <= 375 && m.y >= 640 && m.y <= 660)
		{
			//点击了返回
			if (m.uMsg == WM_LBUTTONDOWN) {

				break;
			}
			else {
				continue;
			}
		}
		else if (m.x >= 280 && m.x <= 330 && m.y >= 230 && m.y <= 250)
		{
			//点击 +30天
			if (m.uMsg == WM_LBUTTONDOWN) {
				thirty_days++;
				clearrectangle(200, 230, 270, 250);
				char buf[10];
				itoa(thirty_days, buf, 10);
				outtextxy(200, 230, buf);
				continue;
			}
			else {
				continue;
			}

		}
		else if (m.x >= 280 && m.x <= 330 && m.y >= 270 && m.y <= 290)
		{
			//点击 +1 天
			if (m.uMsg == WM_LBUTTONDOWN) {
				day++;
				clearrectangle(200, 270, 270, 290);
				char buf[10];
				itoa(day, buf, 10);
				outtextxy(200, 270, buf);
				continue;
			}
		}
		else if (m.x >= 280 && m.x <= 330 && m.y >= 310 && m.y <= 330)
		{
			//点击 + 1 小时
			if (m.uMsg == WM_LBUTTONDOWN) {
				hour++;
				clearrectangle(200, 310, 270, 330);
				char buf[10];
				itoa(hour, buf, 10);
				outtextxy(200, 310, buf);
				continue;
			}
		}
		else if (m.x >= 280 && m.x <= 330 && m.y >= 350 && m.y <= 370)
		{
			//点击 + 1分钟
			if (m.uMsg == WM_LBUTTONDOWN) {
				minute++;
				clearrectangle(200, 350, 270, 370);
				char buf[10];
				itoa(minute, buf, 10);
				outtextxy(200, 350, buf);
				continue;
			}
		}

	}

}
//主菜单-->时间流逝-->修改时间-->自动弹出提醒需要缴费的住院患者名单
void drawPatientToDeposit(int cnt)
{
	MOUSEMSG m;
	initgraph(500, 700);
	setbkcolor(WHITE);
	cleardevice();
	settextstyle(20, 0, "仿宋");//设置文字大小 格式 
	setbkmode(TRANSPARENT);// 去掉文字背景
	settextcolor(BLACK);
	outtextxy(30, 30, "姓名");
	outtextxy(200, 30, "挂号号码");
	outtextxy(400, 30, "当前押金");

	setfillcolor(RGB(210, 210, 210));
	fillrectangle(125, 640, 200, 660);
	fillrectangle(300, 640, 375, 660);
	settextstyle(15, 0, "仿宋");
	outtextxy(147, 642, "确认");
	outtextxy(322, 642, "返回");
	char buf_name[30];
	char buf_id[30];
	char buf_deposit[30];
	int y = 60;
	DiagnosisRecord * res = InHospitalHead->next;
	while (cnt--)
	{
		strcpy_s(buf_name, res->patientInfo.name);
		itoa(res->patientInfo.registerId, buf_id, 10);
		SingleCost * temp = &res->diagnosisSituation.diagnosisSituationInfo.inHospitalRecord.deposit;
		sprintf(buf_deposit, "%d元%d角%d分", temp->yuan, temp->jiao, temp->fen);
		outtextxy(30, y, buf_name);
		outtextxy(200, y, buf_id);
		outtextxy(380, y, buf_deposit);
		y += 30;
		res = res->next;
	}
	while (1) {
		m = GetMouseMsg();
		if (m.x >= 125 && m.x <= 200 && m.y >= 640 && m.y <= 660)
		{
			//点击了确认
			if (m.uMsg == WM_LBUTTONDOWN) {
				break;
			}
			else {
				continue;
			}
		}
		else if (m.x >= 300 && m.x <= 375 && m.y >= 640 && m.y <= 660)
		{
			//点击了返回
			if (m.uMsg == WM_LBUTTONDOWN) {

				break;
			}
			else {
				continue;
			}
		}
	}

}