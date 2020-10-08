#pragma once
#include"DrawMunu.h"
#include"DiagnosisMessage.h"
#include"global.h"
void drawLogMenu() {  //һ���ӽ���--���Ƽ�¼
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

    settextstyle(15, 0, "����");//�������ִ�С ��ʽ 
    setbkmode(TRANSPARENT);// ȥ�����ֱ���
    outtextxy(250, 142, "�������Ƽ�¼");
    outtextxy(250, 202, "��ѯ���Ƽ�¼");
    outtextxy(250, 262, "ɾ�����Ƽ�¼");
    outtextxy(250, 322, "�޸����Ƽ�¼");
    outtextxy(260, 382, "�������˵�");
    while (1) {
        m = GetMouseMsg();
        if (m.x >= 200 && m.x <= 600 && m.y >= 140 && m.y <= 160) {//�������λ�� �Ƿ���������
            setlinecolor(RED);//����� �����µı߿�Ϊ��ɫ
            rectangle(190, 135, 610, 165);//���µı߿�
            //�������� �������Ƽ�¼
            if (m.uMsg == WM_LBUTTONDOWN) {
                drawAddLogRecord();
                goto abcd;//����ʵ�ֺ� ��ת�� �ͷ
            }
        }
        else if (m.x >= 200 && m.x <= 600 && m.y >= 200 && m.y <= 220) {
            setlinecolor(RED);
            rectangle(190, 195, 610, 225);
            //�������˲�ѯ���Ƽ�¼
            if (m.uMsg == WM_LBUTTONDOWN) {
                drawSearchMenu();
                goto abcd;
            }
        }
        else if (m.x >= 200 && m.x <= 600 && m.y >= 260 && m.y <= 280) {
            setlinecolor(RED);
            rectangle(190, 255, 610, 285);
            //�����ɾ�����Ƽ�¼
            if (m.uMsg == WM_LBUTTONDOWN) {
                //����ֱ��ɾ
                char buf[8];
                InputBox(buf, 8, "������7λ���Ƽ�¼���");
                if (IsRegisterId(buf)) {
                    if (deleteDiagnosisList(DiagnosisRecordHead, atoi(buf))) {
                        InputBox(buf, 2, "ɾ���ɹ��������");
                    }
                    else {
                        InputBox(buf, 2, "ɾ��ʧ�ܣ�û���ҵ���¼");
                    }
                }
                //��һ����������,��ʱ��Box����
                break;
            }


        }
        else if (m.x >= 200 && m.x <= 600 && m.y >= 320 && m.y <= 340) {
            setlinecolor(RED);
            rectangle(190, 315, 610, 345);
            //������޸����Ƽ�¼
            if (m.uMsg == WM_LBUTTONDOWN) {
                drawUpdateMenu();
                goto abcd;
            }
        }
        else if (m.x >= 200 && m.x <= 600 && m.y >= 380 && m.y <= 400) {
            setlinecolor(RED);
            rectangle(190, 375, 610, 405);
            //����˷������˵�
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