#include"DrawMunu.h"
void drawMenu() {  //���˵����ƺ���
abcd:;
	MOUSEMSG m;
	//�˵�
	initgraph(600, 700);
	setbkcolor(WHITE);
	cleardevice();  //ˢ��һ�� �Ե����Ǹ�system(cls)
	setfillcolor(GREEN);
	//          ��x1 ��y1 ��x2 ��y2
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

	settextstyle(25, 0, "����");	//�������ָ�ʽ
	setbkmode(TRANSPARENT);			//ȥ�����ֱ���

	outtextxy(150, 60, "���Ƽ�¼");
	outtextxy(440, 60, "ҽԺӪҵ��");
	outtextxy(50, 205, "ҽ�����");
	outtextxy(240, 205, "ʱ������");


	outtextxy(445, 205, "���߾���");
	outtextxy(50, 350, "��λ���");
	outtextxy(350, 350, "סԺ�ɷ�");
	outtextxy(50, 480, "סԺ����");
	outtextxy(265, 480, "�˳�");



	settextcolor(BLACK);
	settextstyle(20, 0, "����");
	outtextxy(350, 660, "ҽԺ���ƹ���ϵͳV1.0");

	while (1) {
		m = GetMouseMsg();
		if (m.x >= 10 && m.x <= 395 && m.y >= 10 && m.y <= 140) {
			setlinecolor(RED);
			rectangle(5, 5, 400, 145);
			//�����������Ƽ�¼
			if (m.uMsg == WM_LBUTTONDOWN) {
				drawLogMenu();
				goto abcd;
			}
		}
		else if (m.x >= 405 && m.x <= 590 && m.y >= 10 && m.y <= 140) {
			setlinecolor(RED);
			rectangle(400, 5, 595, 145);
			//��������ҽԺӪҵ��
			if (m.uMsg == WM_LBUTTONDOWN) {
				drawHospitalIncome();
				goto abcd;
			}
		}
		else if (m.x >= 5 && m.x <= 190 && m.y >= 150 && m.y <= 280) {
			setlinecolor(RED);
			rectangle(5, 145, 195, 285);
			//����� ҽ�����
			if (m.uMsg == WM_LBUTTONDOWN) {
				drawDocSituation();
				goto abcd;
			}
		}
		else if (m.x >= 200 && m.x <= 395 && m.y >= 150 && m.y <= 280) {
			setlinecolor(RED);
			rectangle(195, 145, 400, 285);
			//����� ʱ������
			if (m.uMsg == WM_LBUTTONDOWN) {
				drawTiming();
				goto abcd;
			}
		}
		//
		else if (m.x >= 405 && m.x <= 590 && m.y >= 150 && m.y <= 280) {//
			setlinecolor(RED);
			rectangle(400, 145, 595, 285);
			//����� ���߾���
			if (m.uMsg == WM_LBUTTONDOWN) {
				drawPatientToTreat();
				goto abcd;
			}
		}
		else if (m.x >= 10 && m.x <= 190 && m.y >= 290 && m.y <= 420) {//
			setlinecolor(RED);
			rectangle(5, 285, 195, 425);
			//����� ��λ���
			if (m.uMsg == WM_LBUTTONDOWN) {
				drawBedSituation();
				goto abcd;
			}
		}
		else if (m.x >= 200 && m.x <= 590 && m.y >= 290 && m.y <= 420) {
			setlinecolor(RED);
			rectangle(195, 285, 595, 425);
			//����� סԺ�ɷ�
			if (m.uMsg == WM_LBUTTONDOWN) {
				drawToHandDeposit();
				goto abcd;
			}
		}
		else if (m.x >= 10 && m.x <= 190 && m.y >= 430 && m.y <= 560) {
			setlinecolor(RED);
			rectangle(5, 425, 195, 565);
			//����� סԺ����
			if (m.uMsg == WM_LBUTTONDOWN) {
				drawInHospitalPatient();
				goto abcd;
			}

		}
		else if (m.x >= 200 && m.x <= 380 && m.y >= 430 && m.y <= 560) {
			setlinecolor(RED);
			rectangle(195, 425, 385, 565);
			//����� �˳�
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