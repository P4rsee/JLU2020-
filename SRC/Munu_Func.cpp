#pragma once
#include"DrawMunu.h"
#include"DiagnosisMessage.h"
#include"ListOperator.h"
#include"DoctorInfoProcessor.h"
#include"global.h"

//主菜单---->住院报表
void drawInHospitalPatient() {
	MOUSEMSG m;
	initgraph(500, 700);
	setbkcolor(WHITE);
	cleardevice();
	settextstyle(20, 0, "仿宋");//设置文字大小 格式 
	setbkmode(TRANSPARENT);// 去掉文字背景
	settextcolor(BLACK);

	outtextxy(210, 15, "住院报表");
	outtextxy(40, 50, "挂号");
	outtextxy(100, 50, "患者姓名");
	outtextxy(200, 50, "年龄");
	outtextxy(265, 50, "预出院时间");
	outtextxy(390, 50, "押金");

	setfillcolor(RGB(210, 210, 210));  //按钮灰色底色
	fillrectangle(125, 640, 200, 660);  //返回和确认
	fillrectangle(300, 640, 375, 660);

	settextstyle(15, 0, "仿宋");
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);

	outtextxy(147, 642, "确认");
	outtextxy(322, 642, "返回");

	DiagnosisRecord* nowRecord = DiagnosisRecordHead->next;
	int sx = 30, y = 80;
	while (nowRecord != NULL) {
		if (!IsInHospital(nowRecord)) {
			nowRecord = nowRecord->next; continue;
		}
		char buf[100]; int x = sx;
		settextstyle(15, 0, "仿宋");
		sprintf(buf, "%07d", nowRecord->patientInfo.registerId);
		outtextxy(x, y, buf);

		settextstyle(18, 0, "仿宋");
		x = x + 85;
		outtextxy(x, y, nowRecord->patientInfo.name);
		x = x + 95;
		sprintf(buf, "%d", nowRecord->patientInfo.age);
		outtextxy(x, y, buf);
		x = x + 60;
		TimeRecord p_time = nowRecord->diagnosisSituation.
			diagnosisSituationInfo.inHospitalRecord.predictedLeaveDate;
		sprintf(buf, "%02d-%02d %02d:%02d",
			p_time.month, p_time.day, p_time.hour, p_time.hour);
		settextstyle(15, 0, "仿宋");
		outtextxy(x, y, buf);
		x = x + 110;
		sprintf(buf, "%d.00", nowRecord->diagnosisSituation.
			diagnosisSituationInfo.inHospitalRecord.deposit.yuan);
		outtextxy(x, y, buf);

		y += 25;
		nowRecord = nowRecord->next;
	}

	while (1) {
		m = GetMouseMsg();
		if (m.x >= 125 && m.x <= 200 && m.y >= 640 && m.y <= 660) {  //确认
			setfillcolor(RGB(220, 140, 140));
			fillrectangle(125, 640, 200, 660);
			outtextxy(147, 642, "确认");
			if (m.uMsg == WM_LBUTTONDOWN) {

				break;
			}
		}
		else if (m.x >= 300 && m.x <= 375 && m.y >= 640 && m.y <= 660) {  //返回
			setfillcolor(RGB(220, 140, 140));
			fillrectangle(300, 640, 375, 660);
			outtextxy(322, 642, "返回");
			if (m.uMsg == WM_LBUTTONDOWN) {

				break;
			}
		}
		else {
			setfillcolor(RGB(210, 210, 210));  //灰色
			settextstyle(15, 0, "仿宋");

			fillrectangle(125, 640, 200, 660);  //返回和修改
			fillrectangle(300, 640, 375, 660);

			outtextxy(147, 642, "确认");
			outtextxy(322, 642, "返回");

		}
	}
}
//主菜单---->医院营业额
void drawHospitalIncome() {
	MOUSEMSG m;
	initgraph(500, 700);
	setbkcolor(WHITE);
	cleardevice();
	settextstyle(20, 0, "仿宋");//设置文字大小 格式 
	setbkmode(TRANSPARENT);// 去掉文字背景
	settextcolor(BLACK);
	//outtextxy(40, 40, "检查收入");
	//outtextxy(200, 40, "药品收入");
	//outtextxy(360, 40, "住院收入");
	outtextxy(65, 60, "检查收入:");
	outtextxy(65, 110, "药品收入:");
	outtextxy(65, 160, "住院收入:");
	outtextxy(65, 210, "全部收入:");

	FundPushUp();
	outtextxy(200, 60, hospitalFund.stringOfCheck);
	outtextxy(200, 110, hospitalFund.stringOfDrug);
	outtextxy(200, 160, hospitalFund.stringOfInHospital);
	outtextxy(200, 210, hospitalFund.stringOfAll);

	setfillcolor(RGB(210, 210, 210));  //按钮灰色底色
	fillrectangle(125, 640, 200, 660);  //返回和确认
	fillrectangle(300, 640, 375, 660);

	settextstyle(15, 0, "仿宋");
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);

	outtextxy(147, 642, "确认");
	outtextxy(322, 642, "返回");
	while (1) {
		m = GetMouseMsg();
		if (m.x >= 125 && m.x <= 200 && m.y >= 640 && m.y <= 660) {  //确认
			setfillcolor(RGB(220, 140, 140));
			fillrectangle(125, 640, 200, 660);
			outtextxy(147, 642, "确认");
			if (m.uMsg == WM_LBUTTONDOWN) {

				break;
			}
		}
		else if (m.x >= 300 && m.x <= 375 && m.y >= 640 && m.y <= 660) {  //返回
			setfillcolor(RGB(220, 140, 140));
			fillrectangle(300, 640, 375, 660);
			outtextxy(322, 642, "返回");
			if (m.uMsg == WM_LBUTTONDOWN) {

				break;
			}
		}
		else {
			setfillcolor(RGB(210, 210, 210));  //灰色
			settextstyle(15, 0, "仿宋");

			fillrectangle(125, 640, 200, 660);  //返回和修改
			fillrectangle(300, 640, 375, 660);

			outtextxy(147, 642, "确认");
			outtextxy(322, 642, "返回");

		}
	}

}
//主菜单---->床位情况
void drawBedSituation() {
abcd:;
	MOUSEMSG m;
	initgraph(500, 700);
	setbkcolor(WHITE);
	cleardevice();
	settextstyle(20, 0, "仿宋");//设置文字大小 格式 
	setbkmode(TRANSPARENT);// 去掉文字背景
	settextcolor(BLACK);
	outtextxy(40, 40, "病房号码");
	outtextxy(200, 40, "病房类型");
	outtextxy(360, 40, "占用情况");

	setfillcolor(RGB(210, 210, 210));  //按钮灰色底色
	fillrectangle(125, 640, 200, 660);  //返回和确认
	fillrectangle(300, 640, 375, 660);

	settextstyle(15, 0, "仿宋");
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);

	outtextxy(147, 642, "修改");
	outtextxy(322, 642, "返回");
	int y = 70;
	int x = 40;
	Ward* temp = WardHead->next;
	char buf_wid[6];
	char buf_occu[3];
	char buf_total[3];
	while (temp) {
		itoa(temp->wardId, buf_wid, 10);
		outtextxy(x+30, y, buf_wid);
		outtextxy(x + 160, y, nursingType[temp->nursingType]);
		outtextxy(x + 190, y, bedType[temp->bedType]);
		itoa(temp->occupiedBedNum, buf_occu, 10);
		itoa(temp->totalBedNum, buf_total, 10);
		outtextxy(x + 330, y, buf_occu);
		outtextxy(x + 345, y, "/");
		outtextxy(x + 360, y, buf_total);
		temp = temp->next;
		y += 30;
	}
	while (1) {
		m = GetMouseMsg();
		if (m.x >= 125 && m.x <= 200 && m.y >= 640 && m.y <= 660) {  //修改
			setfillcolor(RGB(220, 140, 140));
			fillrectangle(125, 640, 200, 660);
			outtextxy(147, 642, "修改");
			if (m.uMsg == WM_LBUTTONDOWN) {
				char buf_wid[8];
				char buf_ntype[8];
				char buf_btype[8];
				char buf_bed[3];
				InputBox(buf_wid,3,"请输入病房号码(两位数字,补零)");
				InputBox(buf_ntype, 2, "请输入护理类型(特殊：1  普通：2)");
				InputBox(buf_btype, 2, "请输入病床位数(1,2,3)");
				InputBox(buf_bed, 2, "请输入增加床位数");
				if (LEGAL_DATA == IsWardId(buf_wid)
					&& LEGAL_DATA == IsOneDigitNumber(buf_ntype)
					&& LEGAL_DATA == IsOneDigitNumber(buf_btype)
					&& LEGAL_DATA == IsOneDigitNumber(buf_bed)) {
					Ward * res = modifyWard(WardHead,atoi(buf_wid));
					if (res){
						res->nursingType = atoi(buf_ntype);
						res->bedType = atoi(buf_btype);
						int pos = res->totalBedNum;
						res->totalBedNum += atoi(buf_bed);
						for (int i = pos; i < res->totalBedNum; i++){
							res->bedSituation[i] = 0;
						}
						InputBox(buf_bed, 2, "修改成功！");
					}
					else {
						InputBox(buf_bed, 2, "未查到此病房！");
					}
					
				}
				break;
			}
		}
		else if (m.x >= 300 && m.x <= 375 && m.y >= 640 && m.y <= 660) {  //返回
			setfillcolor(RGB(220, 140, 140));
			fillrectangle(300, 640, 375, 660);
			outtextxy(322, 642, "返回");
			if (m.uMsg == WM_LBUTTONDOWN) {

				break;
			}
		}
		else {
			setfillcolor(RGB(210, 210, 210));  //灰色
			settextstyle(15, 0, "仿宋");

			fillrectangle(125, 640, 200, 660);  //返回和修改
			fillrectangle(300, 640, 375, 660);

			
			outtextxy(147, 642, "修改");
			outtextxy(322, 642, "返回");

		}
	}

}
//主菜单---->患者就诊
void drawPatientToTreat() {
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
	fillrectangle(200, 440, 600, 460);

	settextstyle(15, 0, "楷体");//设置文字大小 格式 
	setbkmode(TRANSPARENT);// 去掉文字背景
	outtextxy(250, 142, "我要挂号");
	outtextxy(250, 202, "我要开药");
	outtextxy(250, 262, "我要检查");
	outtextxy(250, 322, "我要住院");
	outtextxy(250, 382, "我要出院");
	outtextxy(250, 442, "返回主菜单");
	while (1) {
		m = GetMouseMsg();
		if (m.x >= 200 && m.x <= 600 && m.y >= 140 && m.y <= 160) {
			setlinecolor(RED);//满足后 设置新的边框为红色
			rectangle(190, 135, 610, 165);//画新的边框
			//如果点击了 我要挂号
			if (m.uMsg == WM_LBUTTONDOWN) {
				//生成挂号界面，填写姓名年龄，（挂什么科室） 挂号号码自动生成并弹出告示患者
				drawToRegister();
				goto abcd;//功能实现后 跳转到 最开头
			}
		}
		else if (m.x >= 200 && m.x <= 600 && m.y >= 200 && m.y <= 220) {
			setlinecolor(RED);
			rectangle(190, 195, 610, 225);
			//如果点击了 我要开药
			if (m.uMsg == WM_LBUTTONDOWN) {
				//生成开药界面，先让患者输入自己的挂号号码，检查号码合法后，录入药单
				drawToPrescribe();
				goto abcd;
			}
		}
		else if (m.x >= 200 && m.x <= 600 && m.y >= 260 && m.y <= 280) {
			setlinecolor(RED);
			rectangle(190, 255, 610, 285);
			//点击了 我要检查
			if (m.uMsg == WM_LBUTTONDOWN) {
				//生成检查界面，先让患者输入自己的挂号号码，检查号码合法后，填写检查报表
				drawToCheck();
				goto abcd;
			}


		}
		else if (m.x >= 200 && m.x <= 600 && m.y >= 320 && m.y <= 340) {
			setlinecolor(RED);
			rectangle(190, 315, 610, 345);
			//点击了 我要住院
			if (m.uMsg == WM_LBUTTONDOWN) {
				//生成住院界面，先让患者输入自己的挂号号码，检查号码合法后，填写入院/期望出院日期/押金
				drawToHospital();
				goto abcd;
			}

		}
		else if (m.x >= 200 && m.x <= 600 && m.y >= 380 && m.y <= 400) {
			setlinecolor(RED);
			rectangle(190, 375, 610, 405);
			//点击了 我要出院
			if (m.uMsg == WM_LBUTTONDOWN) {
				//生成出院界面，先让患者输入自己的挂号号码，检查号码合法后，（填）出院日期，记录转入历史txt，退还押金
				drawOutHospital();
				goto abcd;
			}

		}
		else if (m.x >= 200 && m.x <= 600 && m.y >= 440 && m.y <= 460) {
			setlinecolor(RED);
			rectangle(190, 435, 610, 465);
			//点击了 返回主菜单
			if (m.uMsg == WM_LBUTTONDOWN) {


				break;
			}

		}
		else {
			setlinecolor(WHITE);
			rectangle(190, 135, 610, 165);
			rectangle(190, 195, 610, 225);
			rectangle(190, 255, 610, 285);
			rectangle(190, 315, 610, 345);
			rectangle(190, 375, 610, 405);
			rectangle(190, 435, 610, 465);
		}
	}

}
//主菜单---->住院缴费(押金)
void drawToHandDeposit() 
{
	MOUSEMSG m;
	initgraph(500, 700);
	setbkcolor(WHITE);
	cleardevice();
	char buf[8];
	DiagnosisRecord* res = NULL;
	settextstyle(20, 0, "仿宋");//设置文字大小 格式 
	setbkmode(TRANSPARENT);// 去掉文字背景
	settextcolor(BLACK);
	outtextxy(30, 50, "挂号号码：");
	outtextxy(30, 80, "患者姓名：");
	outtextxy(30, 110, "患者年龄：");
	outtextxy(30, 140, "医生姓名：");
	outtextxy(30, 170, "医生级别：");
	outtextxy(30, 200, "医生科室：");
	outtextxy(30, 230, "医生工号：");
	outtextxy(30, 260, "至少缴费：");
	setfillcolor(RGB(210, 210, 210));  //按钮灰色底色

	fillrectangle(300, 50, 380, 70);
	fillrectangle(125, 640, 200, 660);  //返回和确认
	fillrectangle(300, 640, 375, 660);
	settextstyle(15, 0, "仿宋");
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	outtextxy(305, 53, "添加/修改");
	outtextxy(147, 642, "确认");
	outtextxy(322, 642, "返回");
	while (1) {
		m = GetMouseMsg();
		if (m.x >= 300 && m.x <= 380 && m.y >= 50 && m.y <= 70) {  //挂号号码
			clearrectangle(300, 50, 380, 70);
			setfillcolor(RGB(220, 140, 140));
			fillrectangle(300, 50, 380, 70);
			settextstyle(15, 0, "仿宋");
			outtextxy(305, 53, "添加/修改");

			if (m.uMsg == WM_LBUTTONDOWN) {
				char buf[8];
				InputBox(buf, 8, "请输入7位挂号号码");
				res = findModifiedNode(DiagnosisRecordHead, atoi(buf));
				if (res) {
					clearrectangle(150, 50, 290, 280);				//刷新显示区域
					outtextxy(150, 50, buf);
					outtextxy(150, 80, res->patientInfo.name);		//患者姓名
					char buf_age[4];
					itoa(res->patientInfo.age, buf_age, 10);
					outtextxy(150, 110, buf_age);					//患者年龄
					outtextxy(150, 140, res->doctorInfo.name);		//医生姓名
					char buf_leval[2];
					itoa(res->doctorInfo.level, buf_leval, 10);
					outtextxy(150, 170, doctorType[res->doctorInfo.level]);					//医生级别
					char buf_section[3];
					itoa(res->doctorInfo.sectionId, buf_section, 10);
					outtextxy(150, 200, buf_section);				//医生科室
					char buf_Doctorid[6];
					itoa(res->doctorInfo.id, buf_Doctorid, 10);
					outtextxy(150, 230, buf_Doctorid);				//医生工号
					char buf_CDate[20];
					char buf_PLDate[21];
					char buf_Deposit[20];
					InHospitalRecord*temp = &(res->diagnosisSituation.
						diagnosisSituationInfo.inHospitalRecord);
					sprintf(buf_PLDate, "%d月%d日%d点%d分"
							, temp->predictedLeaveDate.month
							, temp->predictedLeaveDate.day
							, temp->predictedLeaveDate.hour
							, temp->predictedLeaveDate.minute
						);
						//入院日期
						sprintf(buf_CDate, "%d月%d日%d点%d分"
							, temp->hospitalizedDate.month
							, temp->hospitalizedDate.day
							, temp->hospitalizedDate.hour
							, temp->hospitalizedDate.minute
						);
					
					sprintf(buf_Deposit, "%d元%d角%d分"
							, temp->deposit.yuan
							, temp->deposit.jiao
							, temp->deposit.fen
						);
						clearrectangle(30, 320, 450, 600);
						settextstyle(20, 0, "仿宋");
						outtextxy(30, 320, "入院日期：");
						outtextxy(10, 350, "预计出院日期：");
						outtextxy(30, 380, "当前押金：");
						settextstyle(15, 0, "仿宋");
						outtextxy(150, 320, buf_CDate);
						outtextxy(150, 350, buf_PLDate);
						outtextxy(150, 380, buf_Deposit);
						InputBox(buf_Deposit, 10, "请输入缴纳押金金额");
					if (LEGAL_DATA == IsDeposit(buf_Deposit)) {
						temp->deposit = costAdd(temp->deposit,constructSingleCost(buf_Deposit));
						clearrectangle(150, 380, 500, 400);
						sprintf(buf_Deposit, "%d元%d角%d分"
							, temp->deposit.yuan
							, temp->deposit.jiao
							, temp->deposit.fen
						);
						outtextxy(150, 380, buf_Deposit);
						continue;
					}
					
				}
			}
		}
		else if (m.x >= 125 && m.x <= 200 && m.y >= 640 && m.y <= 660) {  //确认
			setfillcolor(RGB(220, 140, 140));
			fillrectangle(125, 640, 200, 660);
			outtextxy(147, 642, "确认");
			if (m.uMsg == WM_LBUTTONDOWN) {
				break;  
			}

		}
		else if (m.x >= 300 && m.x <= 375 && m.y >= 640 && m.y <= 660) {  //返回
			setfillcolor(RGB(220, 140, 140));
			fillrectangle(300, 640, 375, 660);
			outtextxy(322, 642, "返回");
			if (m.uMsg == WM_LBUTTONDOWN) {
				break;
			}

		}
		else {
			setfillcolor(RGB(210, 210, 210));  //灰色
			settextstyle(15, 0, "仿宋");

			fillrectangle(300, 50, 380, 70);

			fillrectangle(125, 640, 200, 660);  //返回和确认
			fillrectangle(300, 640, 375, 660);

			outtextxy(305, 53, "添加/修改");

			outtextxy(147, 642, "确认");
			outtextxy(322, 642, "返回");

		}

	}
}
//患者就诊-->我要出院
void drawOutHospital() {
	MOUSEMSG m;
	initgraph(500, 700);
	setbkcolor(WHITE);
	cleardevice();
	//
	char buf[8];
	//DiagnosisRecord* res = NULL;
	settextstyle(20, 0, "仿宋");//设置文字大小 格式 
	setbkmode(TRANSPARENT);// 去掉文字背景
	settextcolor(BLACK);
	outtextxy(30, 50, "挂号号码：");
	outtextxy(30, 80, "患者姓名：");
	outtextxy(30, 110, "患者年龄：");
	outtextxy(30, 140, "医生姓名：");
	outtextxy(30, 170, "医生级别：");
	outtextxy(30, 200, "医生科室：");
	outtextxy(30, 230, "医生工号：");
	outtextxy(30, 260, "诊疗日期：");
	setfillcolor(RGB(210, 210, 210));  //按钮灰色底色

	fillrectangle(300, 50, 380, 70);
	fillrectangle(125, 640, 200, 660);  //返回和确认
	fillrectangle(300, 640, 375, 660);
	settextstyle(15, 0, "仿宋");
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	outtextxy(305, 53, "添加/修改");
	outtextxy(147, 642, "确认");
	outtextxy(322, 642, "返回");
	while (1) {
		m = GetMouseMsg();
		if (m.x >= 300 && m.x <= 380 && m.y >= 50 && m.y <= 70) {  //挂号号码
			clearrectangle(300, 50, 380, 70);
			setfillcolor(RGB(220, 140, 140));
			fillrectangle(300, 50, 380, 70);
			settextstyle(15, 0, "仿宋");
			outtextxy(305, 53, "添加/修改");

			if (m.uMsg == WM_LBUTTONDOWN) {
				char buf[8];
				InputBox(buf, 8, "请输入7位挂号号码");
				if (IsRegisterId(buf)) { //测试					
					DiagnosisRecord* res =
						findModifiedNode(DiagnosisRecordHead, atoi(buf));
					clearrectangle(150, 50, 290, 280);				//刷新显示区域
					outtextxy(150, 50, buf);
					outtextxy(150, 80, res->patientInfo.name);	//患者姓名
					char buf_age[4];
					itoa(res->patientInfo.age, buf_age, 10);
					outtextxy(150, 110, buf_age);					//患者年龄
					outtextxy(150, 140, res->doctorInfo.name);	//医生姓名
					char buf_leval[2];
					itoa(res->doctorInfo.level, buf_leval, 10);
					outtextxy(150, 170, doctorType[res->doctorInfo.level]);		//医生级别
					char buf_section[3];
					itoa(res->doctorInfo.sectionId, buf_section, 10);
					outtextxy(150, 200, buf_section);				//医生科室
					char buf_Doctorid[6];
					itoa(res->doctorInfo.id, buf_Doctorid, 10);
					outtextxy(150, 230, buf_Doctorid);			//医生工号
					//诊疗日期
					char buf_date[30];
					sprintf(buf_date, "%d月%d日 %02d ：%02d",
						currentTime.month, currentTime.day, currentTime.hour, currentTime.minute);
					outtextxy(150, 260, buf_date);
					if (res->diagnosisSituation.setFlag == 2) {
						char buf_CDate[30];
						char buf_LDate[31];
						char buf_Deposit[30];
						//代码合并后 改为获取当前时间
						InputBox(buf_LDate, 2, "确认要出院吗？（填 1）");
						if (1 == atoi(buf_LDate)) {
							//InputBox(buf_LDate, 9, "请输入出院日期:");
							//if (!IsDate(buf_LDate))continue;
							TimeRecord* timeRecord = &(res->diagnosisSituation.
								diagnosisSituationInfo.inHospitalRecord.predictedLeaveDate);
							timeRecord->month = timeRecord->day =
								timeRecord->hour = timeRecord->minute = -1;
							//if (LEGAL_DATA == IsDate(buf_LDate)) {
							InHospitalRecord*temp = &(res->diagnosisSituation.
								diagnosisSituationInfo.inHospitalRecord);
							temp->leaveDate = currentTime;
							
							sprintf(buf_CDate, "%d月%d日%d点%d分"
								, temp->hospitalizedDate.month
								, temp->hospitalizedDate.day
								, temp->hospitalizedDate.hour
								, temp->hospitalizedDate.minute
							);
							sprintf(buf_Deposit, "%d元%d角%d分"
								, temp->deposit.yuan
								, temp->deposit.jiao
								, temp->deposit.fen
							);
							sprintf(buf_LDate, "%d月%d日%d点%d分"
								, currentTime.month, currentTime.day, currentTime.hour, currentTime.minute);
							clearrectangle(30, 320, 450, 600);
							settextstyle(20, 0, "仿宋");
							outtextxy(30, 320, "入院日期：");
							outtextxy(30, 350, "出院日期：");
							outtextxy(30, 380, "退还押金：");
							settextstyle(15, 0, "仿宋");
							outtextxy(150, 320, buf_CDate);
							outtextxy(150, 350, buf_LDate);
							outtextxy(150, 380, buf_Deposit);
							temp->deposit.yuan = temp->deposit.jiao
								= temp->deposit.fen = 0;
							int WardId = temp->sickBedNumber;
							int BedId = WardId % 100;
							WardId /= 100;
							//出院走人，床位置空
							freeWardBed(WardId,BedId);

						}
					}
				}
			}
		}
		else if (m.x >= 125 && m.x <= 200 && m.y >= 640 && m.y <= 660) {  //确认
			setfillcolor(RGB(220, 140, 140));
			fillrectangle(125, 640, 200, 660);
			outtextxy(147, 642, "确认");
			if (m.uMsg == WM_LBUTTONDOWN) {
				//删除原来不完整的结点
				//提交完整结点，加入链表
				//return;
				break;  //函数结束会free掉res
			}

		}
		else if (m.x >= 300 && m.x <= 375 && m.y >= 640 && m.y <= 660) {  //返回
			setfillcolor(RGB(220, 140, 140));
			fillrectangle(300, 640, 375, 660);
			outtextxy(322, 642, "返回");
			if (m.uMsg == WM_LBUTTONDOWN) {
				break;
			}

		}
		else {
			setfillcolor(RGB(210, 210, 210));  //灰色
			settextstyle(15, 0, "仿宋");

			fillrectangle(300, 50, 380, 70);

			fillrectangle(125, 640, 200, 660);  //返回和确认
			fillrectangle(300, 640, 375, 660);

			outtextxy(305, 53, "添加/修改");

			outtextxy(147, 642, "确认");
			outtextxy(322, 642, "返回");

		}

	}
	//free(res);

}
//患者就诊-->我要住院
void drawToHospital() {
	MOUSEMSG m;
	initgraph(500, 700);
	setbkcolor(WHITE);
	cleardevice();
	//
	char buf[8];
	DiagnosisRecord* res = NULL;
	settextstyle(20, 0, "仿宋");//设置文字大小 格式 
	setbkmode(TRANSPARENT);// 去掉文字背景
	settextcolor(BLACK);
	outtextxy(30, 50, "挂号号码：");
	outtextxy(30, 80, "患者姓名：");
	outtextxy(30, 110, "患者年龄：");
	outtextxy(30, 140, "医生姓名：");
	outtextxy(30, 170, "医生级别：");
	outtextxy(30, 200, "医生科室：");
	outtextxy(30, 230, "医生工号：");
	outtextxy(30, 260, "诊疗日期：");
	setfillcolor(RGB(210, 210, 210));  //按钮灰色底色

	fillrectangle(300, 50, 380, 70);
	fillrectangle(125, 640, 200, 660);  //返回和确认
	fillrectangle(300, 640, 375, 660);
	settextstyle(15, 0, "仿宋");
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	outtextxy(305, 53, "添加/修改");
	outtextxy(147, 642, "确认");
	outtextxy(322, 642, "返回");
	while (1) {
		m = GetMouseMsg();
		if (m.x >= 300 && m.x <= 380 && m.y >= 50 && m.y <= 70) {  //挂号号码
			clearrectangle(300, 50, 380, 70);
			setfillcolor(RGB(220, 140, 140));
			fillrectangle(300, 50, 380, 70);
			settextstyle(15, 0, "仿宋");
			outtextxy(305, 53, "添加/修改");

			if (m.uMsg == WM_LBUTTONDOWN) {
				char buf[8];
				InputBox(buf, 8, "请输入7位挂号号码");
				
				if (IsRegisterId(buf)) { //测试
					res = findModifiedNode(DiagnosisRecordHead, atoi(buf));		//测试

					res->diagnosisSituation.setFlag = 2;
					clearrectangle(150, 50, 290, 280);					//刷新显示区域
					outtextxy(150, 50, buf);
					outtextxy(150, 80, res->patientInfo.name);			//患者姓名
					char buf_age[4];
					itoa(res->patientInfo.age, buf_age, 10);
					outtextxy(150, 110, buf_age);						//患者年龄
					outtextxy(150, 140, res->doctorInfo.name);			//医生姓名
					char buf_leval[2];
					itoa(res->doctorInfo.level, buf_leval, 10);
					outtextxy(150, 170, doctorType[res->doctorInfo.level]);	//医生级别
					char buf_section[3];
					itoa(res->doctorInfo.sectionId, buf_section, 10);
					outtextxy(150, 200, buf_section);					//医生科室
					char buf_Doctorid[6];
					itoa(res->doctorInfo.id, buf_Doctorid, 10);
					outtextxy(150, 230, buf_Doctorid);					//医生工号
					//诊疗日期
					char buf_date[30];
					sprintf(buf_date, "%d月%d日 %02d ：%02d",
						currentTime.month, currentTime.day, currentTime.hour, currentTime.minute);
					outtextxy(150, 260, buf_date);
					res->diagnosisSituation.setFlag = 2;
					char buf_CDate[30];
					char buf_PLDate[30];
					char buf_Deposit[30];
					//InputBox(buf_CDate, 9, "请输入入院日期");
					InputBox(buf_PLDate, 9, "请输入预计出院日期");
					InputBox(buf_Deposit, 9, "请输入入院押金");
					if (LEGAL_DATA == IsDate(buf_PLDate) &&
						LEGAL_DATA == IsDeposit(buf_Deposit)) {
						InHospitalRecord*temp = &(res->diagnosisSituation.
							diagnosisSituationInfo.inHospitalRecord);
						temp->costByNow = StrToCost("0");			//刚入院，初始化开销为 0
						temp->hospitalizedDate = currentTime;
						temp->deposit = StrToCost(buf_Deposit);
						SetDate(buf_PLDate, &(temp->predictedLeaveDate.month)
							, &(temp->predictedLeaveDate.day)
							, &(temp->predictedLeaveDate.hour)
							, &(temp->predictedLeaveDate.minute)
						);
						sprintf(buf_CDate, "%d月%d日 %02d : %02d"
							, currentTime.month, currentTime.day, currentTime.hour, currentTime.minute);
						sprintf(buf_PLDate, "%d月%d日 %02d : %02d"
							, temp->predictedLeaveDate.month
							, temp->predictedLeaveDate.day
							, temp->predictedLeaveDate.hour
							, temp->predictedLeaveDate.minute
						);
						getSickBedNum(res);
						
						clearrectangle(30, 320, 450, 600);
						settextstyle(20, 0, "仿宋");
						outtextxy(30, 320, "入院日期：");
						outtextxy(30, 350, "预计出院：");
						outtextxy(30, 380, "缴纳押金：");
						outtextxy(30, 410, "病房病床:");
						settextstyle(15, 0, "仿宋");
						outtextxy(150, 320, buf_CDate);
						outtextxy(150, 350, buf_PLDate);
						outtextxy(150, 380, buf_Deposit);
						char buf_bedNum[30];
						int WardId = res->diagnosisSituation.diagnosisSituationInfo.inHospitalRecord.sickBedNumber;
						int BedId = WardId % 100;
						WardId /= 100;
						sprintf(buf_bedNum, "%d号病房 %d号病床", WardId, BedId);
						outtextxy(150, 410, buf_bedNum);

					}
				}

			}
		}
		else if (m.x >= 125 && m.x <= 200 && m.y >= 640 && m.y <= 660) {  //确认
			setfillcolor(RGB(220, 140, 140));
			fillrectangle(125, 640, 200, 660);
			outtextxy(147, 642, "确认");
			if (m.uMsg == WM_LBUTTONDOWN) {
				//删除原来不完整的结点
				//提交完整结点，加入链表
				//return;
				break;  //函数结束会free掉res
			}

		}
		else if (m.x >= 300 && m.x <= 375 && m.y >= 640 && m.y <= 660) {  //返回
			setfillcolor(RGB(220, 140, 140));
			fillrectangle(300, 640, 375, 660);
			outtextxy(322, 642, "返回");
			if (m.uMsg == WM_LBUTTONDOWN) {
				break;
			}

		}
		else {
			setfillcolor(RGB(210, 210, 210));  //灰色
			settextstyle(15, 0, "仿宋");

			fillrectangle(300, 50, 380, 70);

			fillrectangle(125, 640, 200, 660);  //返回和确认
			fillrectangle(300, 640, 375, 660);

			outtextxy(305, 53, "添加/修改");

			outtextxy(147, 642, "确认");
			outtextxy(322, 642, "返回");

		}

	}
	//free(res);

}
//患者就诊-->我要检查
void drawToCheck() {
	MOUSEMSG m;
	initgraph(500, 700);
	setbkcolor(WHITE);
	cleardevice();
	//
	char buf[8];
	DiagnosisRecord* res = NULL;
	settextstyle(20, 0, "仿宋");//设置文字大小 格式 
	setbkmode(TRANSPARENT);// 去掉文字背景
	settextcolor(BLACK);
	outtextxy(30, 50, "挂号号码：");
	outtextxy(30, 80, "患者姓名：");
	outtextxy(30, 110, "患者年龄：");
	outtextxy(30, 140, "医生姓名：");
	outtextxy(30, 170, "医生级别：");
	outtextxy(30, 200, "医生科室：");
	outtextxy(30, 230, "医生工号：");
	outtextxy(30, 260, "诊疗日期：");
	setfillcolor(RGB(210, 210, 210));  //按钮灰色底色

	fillrectangle(300, 50, 380, 70);
	fillrectangle(125, 640, 200, 660);  //返回和确认
	fillrectangle(300, 640, 375, 660);
	settextstyle(15, 0, "仿宋");
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	outtextxy(305, 53, "添加/修改");
	outtextxy(147, 642, "确认");
	outtextxy(322, 642, "返回");
	SingleCost temp;
	temp.yuan = 0;
	temp.jiao = 0;
	temp.fen = 0;
	while (1) {
		m = GetMouseMsg();
		if (m.x >= 300 && m.x <= 380 && m.y >= 50 && m.y <= 70) {  //挂号号码
			clearrectangle(300, 50, 380, 70);
			setfillcolor(RGB(220, 140, 140));
			fillrectangle(300, 50, 380, 70);
			settextstyle(15, 0, "仿宋");
			outtextxy(305, 53, "添加/修改");

			if (m.uMsg == WM_LBUTTONDOWN) {
				char buf[8];
				InputBox(buf, 8, "请输入7位挂号号码");
				if (IsRegisterId(buf)) {
					res = findModifiedNode(DiagnosisRecordHead, atoi(buf));
					if (res) {
						res->diagnosisSituation.setFlag = 1;
						clearrectangle(150, 50, 290, 280);				//刷新显示区域
						outtextxy(150, 50, buf);
						outtextxy(150, 80, res->patientInfo.name);	//患者姓名
						char buf_age[4];
						itoa(res->patientInfo.age, buf_age, 10);
						outtextxy(150, 110, buf_age);					//患者年龄
						outtextxy(150, 140, res->doctorInfo.name);	//医生姓名
						char buf_leval[2];
						itoa(res->doctorInfo.level, buf_leval, 10);
						outtextxy(150, 170, doctorType[res->doctorInfo.level]);	//医生级别
						char buf_section[3];
						itoa(res->doctorInfo.sectionId, buf_section, 10);
						outtextxy(150, 200, buf_section);				//医生科室
						char buf_Doctorid[6];
						itoa(res->doctorInfo.id, buf_Doctorid, 10);
						outtextxy(150, 230, buf_Doctorid);			//医生工号
						res->diagnosisSituation.setFlag = 0;
						char buf_date[30];
						sprintf(buf_date, "%d月%d日 %02d ：%02d", 
							currentTime.month, currentTime.day, currentTime.hour, currentTime.minute);
						outtextxy(150, 260, buf_date);
						res->recordTime = currentTime;
						char buf_num[3];
						InputBox(buf_num, 3, "请输入检查种类数");
						if (LEGAL_DATA == IsDrugKindNum(buf_num)) {

							clearrectangle(30, 320, 450, 600);
							settextstyle(20, 0, "仿宋");
							outtextxy(30, 320, "检查编号");
							outtextxy(230, 320, "检查费用");

							int x = 30;
							int y = 350;
							int num = atoi(buf_num);
							CheckInfo* head = (CheckInfo*)malloc(sizeof(CheckInfo));
							head->next = NULL;
							CheckInfo* rear = head;
							for (int i = 0; i < num; i++) {
								char buf_CheckId[3];
								InputBox(buf_CheckId, 3, "请输入检查编号");
								if (LEGAL_DATA == IsDrugId(buf_CheckId)) {
									outtextxy(x, y, buf_CheckId);
									
									char temp_t[10];
									itoa(checkPriceList[atoi(buf_CheckId)], temp_t, 10);
									temp.yuan += checkPriceList[atoi(buf_CheckId)];
									outtextxy(x + 200, y, temp_t);
									y += 30;
									rear->next = (CheckInfo*)malloc(sizeof(CheckInfo));
									rear->next->next = NULL;
									rear->next->checkId = atoi(buf_CheckId);
									rear->next->singleCost = constructSingleCost(temp_t);
									rear = rear->next;
								}
								else {
									i--;
								}

							}
		
							
							res->diagnosisSituation.diagnosisSituationInfo
								.checkRecord.typeNumber = atoi(buf_num);
							res->diagnosisSituation.diagnosisSituationInfo
								.checkRecord.checkInfoHead = head;

						}

					}
				}
			}
		}
		else if (m.x >= 125 && m.x <= 200 && m.y >= 640 && m.y <= 660) {  //确认
			setfillcolor(RGB(220, 140, 140));
			fillrectangle(125, 640, 200, 660);
			outtextxy(147, 642, "确认");
			if (m.uMsg == WM_LBUTTONDOWN) {
				hospitalFund.checkCost.yuan += temp.yuan;
				hospitalFund.allCost.yuan += temp.yuan;
				res->diagnosisSituation.diagnosisSituationInfo.checkRecord.totalCost = temp;
				break;  
			}

		}
		else if (m.x >= 300 && m.x <= 375 && m.y >= 640 && m.y <= 660) {  //返回
			setfillcolor(RGB(220, 140, 140));
			fillrectangle(300, 640, 375, 660);
			outtextxy(322, 642, "返回");
			if (m.uMsg == WM_LBUTTONDOWN) {
				break;
			}

		}
		else {
			setfillcolor(RGB(210, 210, 210));  //灰色
			settextstyle(15, 0, "仿宋");

			fillrectangle(300, 50, 380, 70);

			fillrectangle(125, 640, 200, 660);  //返回和确认
			fillrectangle(300, 640, 375, 660);

			outtextxy(305, 53, "添加/修改");

			outtextxy(147, 642, "确认");
			outtextxy(322, 642, "返回");

		}
		
	}

}
//患者就诊-->我要开药
void drawToPrescribe() {
	//DiagnosisRecord* queryDiagnosisByRegisterId(DiagnosisRecord* head,*int* registerId)
	MOUSEMSG m;
	initgraph(500, 700);
	setbkcolor(WHITE);
	cleardevice();
	//
	char buf[8];
	DiagnosisRecord* res = NULL;
	settextstyle(20, 0, "仿宋");//设置文字大小 格式 
	setbkmode(TRANSPARENT);// 去掉文字背景
	settextcolor(BLACK);
	outtextxy(30, 50, "挂号号码：");
	outtextxy(30, 80, "患者姓名：");
	outtextxy(30, 110, "患者年龄：");
	outtextxy(30, 140, "医生姓名：");
	outtextxy(30, 170, "医生级别：");
	outtextxy(30, 200, "医生科室：");
	outtextxy(30, 230, "医生工号：");
	outtextxy(30, 260, "诊疗日期：");
	setfillcolor(RGB(210, 210, 210));  //按钮灰色底色

	fillrectangle(300, 50, 380, 70);
	fillrectangle(125, 640, 200, 660);  //返回和确认
	fillrectangle(300, 640, 375, 660);
	settextstyle(15, 0, "仿宋");
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	outtextxy(305, 53, "添加/修改");
	outtextxy(147, 642, "确认");
	outtextxy(322, 642, "返回");
	SingleCost temp;
	while (1) {
		m = GetMouseMsg();
		if (m.x >= 300 && m.x <= 380 && m.y >= 50 && m.y <= 70) {  //挂号号码
			clearrectangle(300, 50, 380, 70);
			setfillcolor(RGB(220, 140, 140));
			fillrectangle(300, 50, 380, 70);
			settextstyle(15, 0, "仿宋");
			outtextxy(305, 53, "添加/修改");

			if (m.uMsg == WM_LBUTTONDOWN) {
				char buf[8];
				InputBox(buf, 8, "请输入7位挂号号码");
				

				if (IsRegisterId(buf)) { //测试
					res = findModifiedNode(DiagnosisRecordHead, atoi(buf));
					if (res == NULL)continue;
					res->diagnosisSituation.setFlag = 1;
					clearrectangle(150, 50, 290, 280);				//刷新显示区域
					outtextxy(150, 50, buf);
					outtextxy(150, 80, res->patientInfo.name);	//患者姓名
					char buf_age[4];
					itoa(res->patientInfo.age, buf_age, 10);
					outtextxy(150, 110, buf_age);					//患者年龄
					outtextxy(150, 140, res->doctorInfo.name);	//医生姓名
					char buf_leval[2];
					itoa(res->doctorInfo.level, buf_leval, 10);
					outtextxy(150, 170, doctorType[res->doctorInfo.level]);	//医生级别
					char buf_section[3];
					itoa(res->doctorInfo.sectionId, buf_section, 10);
					outtextxy(150, 200, buf_section);				//医生科室
					char buf_Doctorid[6];
					itoa(res->doctorInfo.id, buf_Doctorid, 10);
					outtextxy(150, 230, buf_Doctorid);			//医生工号
					//诊疗日期
					char buf_date[30];
					sprintf(buf_date, "%d月%d日 %02d ：%02d",
						currentTime.month, currentTime.day, currentTime.hour, currentTime.minute);
					res->recordTime = currentTime;
					outtextxy(150, 260, buf_date);
					char buf_num[3];
					InputBox(buf_num, 2, "请输入药品种类数");
					if (LEGAL_DATA == IsDrugKindNum(buf_num)) {

						clearrectangle(30, 320, 450, 600);
						settextstyle(20, 0, "仿宋");
						outtextxy(30, 320, "药品编号");
						outtextxy(130, 320, "药品数目");
						outtextxy(230, 320, "药品单价");
						outtextxy(330, 320, "药品费用");
						int x = 30;
						int y = 350;

						int num = atoi(buf_num);
						PrescribeInfo* head = (PrescribeInfo*)malloc(sizeof(PrescribeInfo));
						head->next = NULL;
						PrescribeInfo* rear = head;
						
						temp.yuan = 0;
						temp.jiao = 0;
						temp.fen = 0;
						for (int i = 0; i < num; i++) {
							char buf_DrugId[3];
							char buf_DrugNum[4];
							InputBox(buf_DrugId, 3, "请输入药品编号");
							InputBox(buf_DrugNum, 4, "请输入药品数量");
							if (LEGAL_DATA == IsDrugId(buf_DrugId) &&
								LEGAL_DATA == IsDrugNum(buf_DrugNum)) {
								outtextxy(x, y, buf_DrugId);
								outtextxy(x + 100, y, buf_DrugNum);
								
								char temp_p[10];
								itoa(drugPriceList[atoi(buf_DrugId)], temp_p, 10);
								outtextxy(x + 200, y, temp_p);

								char temp_t[10];
								itoa(drugPriceList[atoi(buf_DrugId)] * atoi(buf_DrugNum), temp_t, 10);
								outtextxy(x + 300, y, temp_t);
								temp.yuan += drugPriceList[atoi(buf_DrugId)] * atoi(buf_DrugNum);
								y += 30;
								rear->next = (PrescribeInfo*)malloc(sizeof(PrescribeInfo));
								rear->next->next = NULL;
								rear->next->drugId = atoi(buf_DrugId);
								rear->next->drugNumber = atoi(buf_DrugNum);
								rear = rear->next;
							}
							else {
								i--;
							}
						}

						//free(rear);
						res->diagnosisSituation.diagnosisSituationInfo
							.prescribeRecord.typeNumber = atoi(buf_num);
						res->diagnosisSituation.diagnosisSituationInfo
							.prescribeRecord.prescribeInfoHead = head;

					}
					else {
						continue;
					}
				}
			}

		}
		else if (m.x >= 125 && m.x <= 200 && m.y >= 640 && m.y <= 660) {  //确认
			setfillcolor(RGB(220, 140, 140));
			fillrectangle(125, 640, 200, 660);
			outtextxy(147, 642, "确认");
			if (m.uMsg == WM_LBUTTONDOWN) {
				hospitalFund.drugCost.yuan += temp.yuan;
				hospitalFund.allCost.yuan += temp.yuan;
				res->diagnosisSituation.diagnosisSituationInfo.prescribeRecord.totalCost = temp;
				break;  //函数结束会free掉res
			}

		}
		else if (m.x >= 300 && m.x <= 375 && m.y >= 640 && m.y <= 660) {  //返回
			setfillcolor(RGB(220, 140, 140));
			fillrectangle(300, 640, 375, 660);
			outtextxy(322, 642, "返回");
			if (m.uMsg == WM_LBUTTONDOWN) {
				break;
			}

		}
		else {
			setfillcolor(RGB(210, 210, 210));  //灰色
			settextstyle(15, 0, "仿宋");

			fillrectangle(300, 50, 380, 70);
			fillrectangle(125, 640, 200, 660);  //返回和确认
			fillrectangle(300, 640, 375, 660);

			outtextxy(305, 53, "添加/修改");
			outtextxy(147, 642, "确认");
			outtextxy(322, 642, "返回");
		}
	}
	//free(res);
}
//患者就诊-->我要挂号--插入到DiagnogsisRecordHead链表
void drawToRegister() {
	DiagnosisRecord* res = initDiagnosisRecord();
	//初始化节点所有信息
	int flag = 0;
	MOUSEMSG m;
	initgraph(500, 700);
	setbkcolor(WHITE);
	cleardevice();
	settextstyle(20, 0, "仿宋");//设置文字大小 格式 
	setbkmode(TRANSPARENT);// 去掉文字背景
	settextcolor(BLACK);
	
	outtextxy(30, 80, "患者姓名：");
	outtextxy(30, 110, "患者年龄：");
	outtextxy(30, 140, "选择科室：");
	//settextstyle(15, 0, "仿宋");//设置文字大小 格式 
	outtextxy(50, 200, "妇科 01 -- 内科 02 --皮肤科 03");
	outtextxy(50, 230, "眼科 04 -- 骨科 05 --儿童科 06");
	setfillcolor(RGB(210, 210, 210));  //按钮灰色底色
	//settextstyle(20, 0, "仿宋");//设置文字大小 格式 
	fillrectangle(300, 80, 380, 100);
	fillrectangle(300, 110, 380, 130);
	fillrectangle(300, 140, 380, 160);

	fillrectangle(125, 640, 200, 660);  //返回和确认
	fillrectangle(300, 640, 375, 660);

	settextstyle(15, 0, "仿宋");
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	outtextxy(305, 83, "添加/修改");
	outtextxy(305, 113, "添加/修改");
	outtextxy(305, 143, "添加/修改");
	outtextxy(147, 642, "确认");
	outtextxy(322, 642, "返回");
	while (1) {
		m = GetMouseMsg();
		if (m.x >= 300 && m.x <= 380 && m.y >= 80 && m.y <= 100) {  //患者姓名
		setfillcolor(RGB(220, 140, 140));
		fillrectangle(300, 80, 380, 100);
		outtextxy(305, 83, "添加/修改");
		if (m.uMsg == WM_LBUTTONDOWN) {
			char buf[50];
			InputBox(buf, 41, "请输入患者姓名(20字以内)");
			if (LEGAL_DATA == IsName(buf)) {
				strcpy(res->patientInfo.name, buf);		// 存储到内存
				clearrectangle(150, 80, 290, 100);		// 刷新显示区域
				outtextxy(150, 80, buf);				//显示

			}
			else {
				continue;
			}

		}
		}
		else if (m.x >= 300 && m.x <= 380 && m.y >= 110 && m.y <= 130) {  //患者年龄
			setfillcolor(RGB(220, 140, 140));
			fillrectangle(300, 110, 380, 130);
			outtextxy(305, 113, "添加/修改");
			if (m.uMsg == WM_LBUTTONDOWN) {
			char buf[5];
			InputBox(buf, 4, "请输入患者年龄");
			if (LEGAL_DATA == IsAge(buf)) {
				res->patientInfo.age = atoi(buf);
				clearrectangle(150, 110, 290, 130);
				outtextxy(150, 110, buf);

			}
			else {
				continue;
			}

			}

		}
		else if (m.x >= 300 && m.x <= 380 && m.y >= 140 && m.y <= 160) {  //医生科室
			setfillcolor(RGB(220, 140, 140));
			fillrectangle(300, 140, 380, 160);
			outtextxy(305, 143, "添加/修改");
			if (m.uMsg == WM_LBUTTONDOWN) {
				char buf[4];
				InputBox(buf, 3, "请输入科室");
				if (LEGAL_DATA == IsSection(buf)) {
					res->doctorInfo.sectionId = atoi(buf);
					clearrectangle(150, 140, 290, 160);
					outtextxy(150, 140, buf);

				}
				else {
					continue;
				}

			}


		}
		else if (m.x >= 125 && m.x <= 200 && m.y >= 640 && m.y <= 660) {  //确认
			setfillcolor(RGB(220, 140, 140));
			fillrectangle(125, 640, 200, 660);
			outtextxy(147, 642, "确认");
			if (m.uMsg == WM_LBUTTONDOWN) {
				settextstyle(20, 0, "仿宋");
				clearrectangle(50, 390, 500, 430);
				//生成挂号ID函数
				generateRegisterID(res);
				//推荐医生函数
				DoctorNode * List = getRecommendedDoctors(DoctorHead, res->doctorInfo.sectionId);
				char buf_doc[70];
				char buf_id[30];
				sprintf(buf_id,"您的挂号ID为 : %d",res->patientInfo.registerId);
				outtextxy(50, 400, buf_id);
				DoctorNode * temp = List->next;
				int cnt = 1;
				int y = 440;
				while(temp)
				{
					sprintf(buf_doc, "为您推荐的第%d位医生: %d 工号 %s 医师",cnt, temp->doctorInfo.id, temp->doctorInfo.name);
					outtextxy(50, y,buf_doc);
					y += 30;
					flag = 1;
					cnt++;
					temp = temp->next;
				}
				//选择完医生后把node的医生信息更新
				InputBox(buf_doc, 2, "您要选择第几位医生？");
				if (IsOneDigitNumber(buf_doc)) {
					temp = List;
					int cct = atoi(buf_doc);
					while (cct--){
						temp = temp->next;
					}
					combineDoctorIntoDiagnosisRecord(DiagnosisRecordHead, res, temp);
					sprintf(buf_doc,"请记好您的挂号：%s，以及医师：%s",
						buf_id, res->doctorInfo.name);
					InputBox(buf_doc, 2, buf_doc);
					//这里res后期可能要free ，但要改pushBack的浅拷贝
					break;
				}
				else {
					InputBox(buf_doc, 2, "您的输入有误");
					break;
				}
				//提交结点函数
			}
		}
		else if (m.x >= 300 && m.x <= 375 && m.y >= 640 && m.y <= 660) {  //返回
			setfillcolor(RGB(220, 140, 140));
			fillrectangle(300, 640, 375, 660);
			outtextxy(322, 642, "返回");
			if (m.uMsg == WM_LBUTTONDOWN) {
				if(!flag)
					free(res);
				break;
			}
		}
		else {
			setfillcolor(RGB(210, 210, 210));  //灰色
			settextstyle(15, 0, "仿宋");
			fillrectangle(300, 80, 380, 100);
			fillrectangle(300, 110, 380, 130);
			fillrectangle(300, 140, 380, 160);
			fillrectangle(125, 640, 200, 660);  //返回和确认
			fillrectangle(300, 640, 375, 660);
			outtextxy(305, 83, "添加/修改");
			outtextxy(305, 113, "添加/修改");
			outtextxy(305, 143, "添加/修改");
			outtextxy(147, 642, "确认");
			outtextxy(322, 642, "返回");
		}
	}

}
//主菜单-- 医生情况 -- 子界面
void drawDocSituation()
{
refresh:;
	MOUSEMSG m;
	initgraph(500, 700);
	setbkcolor(WHITE);
	cleardevice();
	settextstyle(20, 0, "仿宋");//设置文字大小 格式 
	setbkmode(TRANSPARENT);// 去掉文字背景
	settextcolor(BLACK);

	outtextxy(80, 50, "当前时间");
	outtextxy(35, 90, "医生姓名");
	outtextxy(155, 90, "医生工号");
	outtextxy(275, 90, "繁忙程度");
	outtextxy(395, 90, "状态");

	//打印医生信息情况 姓名 工号 繁忙程度因子
	settextstyle(17, 0, "仿宋");//设置文字大小 格式 
	DoctorNode* nowNode = DoctorHead->next;
	int y = 113;
	char _buf[200];
	while (nowNode != NULL) {
		outtextxy(45, y, nowNode->doctorInfo.name);
		sprintf(_buf, "%04d          %d",
			nowNode->doctorInfo.id,
			nowNode->doctorInfo.busyDegree);
		outtextxy(175, y, _buf);
		if (nowNode->doctorInfo.doctorStatus == 0)
			outtextxy(397, y, "在职");
		else if (nowNode->doctorInfo.doctorStatus == 1)
			outtextxy(397, y, "请假");
		else if (nowNode->doctorInfo.doctorStatus == 2)
			outtextxy(397, y, "离职");
		nowNode = nowNode->next;
		y += 23;
	}

	setfillcolor(RGB(210, 210, 210));
	fillrectangle(125, 600, 200, 620);
	fillrectangle(300, 600, 375, 620);
	fillrectangle(125, 640, 200, 660);
	fillrectangle(300, 640, 375, 660);
	settextstyle(15, 0, "仿宋");
	outtextxy(147, 602, "请假");
	outtextxy(322, 602, "离职");
	outtextxy(147, 642, "新聘");
	outtextxy(322, 642, "返回");

	
	char buf_cur[30];
	sprintf_s(buf_cur, "%d月%d日 %02d:%02d", currentTime.month, currentTime.day, currentTime.hour, currentTime.minute);
	outtextxy(200, 50, buf_cur);
	while (1)
	{
		//获取当前时间(测试)
		setfillcolor(RGB(255, 255, 255));
		fillrectangle(200, 50, 390, 70);
		outtextxy(200, 50, buf_cur);
		m = GetMouseMsg();
		if (m.x >= 125 && m.x <= 200 && m.y >= 640 && m.y <= 660) {
			setfillcolor(RGB(220, 140, 140));
			fillrectangle(125, 640, 200, 660);
			outtextxy(147, 642, "新聘");
			//点击了新聘
			if (m.uMsg == WM_LBUTTONDOWN) {
				//进入新聘界面	
				char buf_name[50], buf_sectionId[10];
				char buf_level[5], buf_workTime[8];
				InputBox(buf_name, 41, "请输入姓名");
				InputBox(buf_sectionId, 3, "请输入科室");
				InputBox(buf_level, 2, "请输入医生级别");
				InputBox(buf_workTime, 8, "请输入出诊时间");
				if (!IsName(buf_name))continue;
				if (!IsSection(buf_sectionId))continue;
				if (!IsDoctorLevel(buf_level))continue;
				if (strlen(buf_workTime) != 7)continue;
				int flag = 0;
				for (int i = 0; i < 7; i++)
					if (buf_workTime[i] < '0' || buf_workTime[i]>'1') {
						flag = 1; break;
					}
				if (flag)continue;
				int secId = atoi(buf_sectionId);
				DoctorNode* newNode = (DoctorNode*)malloc(sizeof(DoctorNode));
				strcpy(newNode->doctorInfo.name, buf_name);
				newNode->doctorInfo.busyDegree = 0;
				newNode->doctorInfo.doctorStatus = 0;
				newNode->doctorInfo.sectionId = secId;
				for (int i = 0; i < 7; i++)
					newNode->doctorInfo.consultTime[i] =
					buf_workTime[i] == '1' ? true : false;
				newNode->doctorInfo.level = buf_level[0] - '0';
				newNode->doctorInfo.vacationLeft = 0;
				newNode->next = NULL;
				// 哨兵结点
				DoctorNode* tempHead = queryDoctorBySectionId(DoctorHead, secId);
				int doctorIdOfLastTwo = 0;
				while (1) {
					doctorIdOfLastTwo++;
					if (tempHead == NULL)break;
					DoctorNode* t_Node = tempHead->next;
					int flag = 0;
					while (t_Node != NULL) {
						if (t_Node->doctorInfo.id % 100 == doctorIdOfLastTwo) {
							flag = 1; break;
						}
						t_Node = t_Node->next;
					}
					if (!flag)break;
				}
				newNode->doctorInfo.id = secId * 100 + doctorIdOfLastTwo;
				pushBackDoctorList(DoctorHead, newNode);
				goto refresh;
			}
		}
		else if (m.x >= 300 && m.x <= 375 && m.y >= 640 && m.y <= 660) {
			setfillcolor(RGB(220, 140, 140));
			fillrectangle(300, 640, 375, 660);
			outtextxy(322, 642, "返回");
			//点击了返回
			if (m.uMsg == WM_LBUTTONDOWN) {
				break;
			}
		}
		else if (m.x >= 125 && m.x <= 200 && m.y >= 600 && m.y <= 620) {
			setfillcolor(RGB(220, 140, 140));
			fillrectangle(125, 600, 200, 620);
			outtextxy(147, 602, "请假");
			//点击了请假
			if (m.uMsg == WM_LBUTTONDOWN) {
				//进入界面
				char buf_id[10], buf_day[10];
				InputBox(buf_id, 5, "请输入医生工号");
				InputBox(buf_day, 3, "请输入请假天数");
				if (!IsDoctorId(buf_id))continue;
				if (!IsNumber(buf_day))continue;
				DoctorNode* nowNode = queryDoctorByDoctorId(DoctorHead, atoi(buf_id));
				nowNode->doctorInfo.doctorStatus = 1;
				nowNode->doctorInfo.vacationLeft = atoi(buf_day);
				goto refresh;
			}
		}
		else if (m.x >= 300 && m.x <= 375 && m.y >= 600 && m.y <= 620) {
			setfillcolor(RGB(220, 140, 140));
			fillrectangle(300, 600, 375, 620);
			outtextxy(322, 602, "离职");
			//点击了离职
			if (m.uMsg == WM_LBUTTONDOWN) {
				//进入界面
				char buf_id[10];
				InputBox(buf_id, 5, "请输入医生工号");
				if (!IsDoctorId(buf_id))continue;
				int id = atoi(buf_id);
				DoctorNode* nowNode = DoctorHead->next;
				while (nowNode != NULL) {
					if (nowNode->doctorInfo.id == id) {
						nowNode->doctorInfo.doctorStatus = 2;
						break;
					}
					nowNode = nowNode->next;
				}
				goto refresh;
			}
		}
		else {
			setfillcolor(RGB(210, 210, 210));  //灰色
			settextstyle(15, 0, "仿宋");

			fillrectangle(125, 600, 200, 620);
			fillrectangle(300, 600, 375, 620);
			fillrectangle(125, 640, 200, 660);
			fillrectangle(300, 640, 375, 660);

			outtextxy(147, 602, "请假");
			outtextxy(322, 602, "离职");
			outtextxy(147, 642, "新聘");
			outtextxy(322, 642, "返回");
		}

	}


}

