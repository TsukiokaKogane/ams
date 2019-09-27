#ifndef  PROGRAM_BASIC_ACTION_H
#define  PROGRAM_BASIC_ACTION_H
#include<stdio.h>
#include<time.h>
#include<math.h>
#include<string.h>
#include<stdlib.h>
#include<windows.h> 
#include "QLabel"
#define ENGLISH 0
#define CHINIESE 1 
#define CONFIGURATION_LENGTH 7
#define WINDOW_NUMBER 8/*������*/ 
#define NORMAL_WINDOW_NUMBER 4/*һ�㴰����*/ 
#define INTERVAL_TIME 0/*�ӻ����������������ʱ��*/
#define MAX_WAIT_LEN 7 
struct CONFIGURATION_DATA{int data;char name[20];};
struct PASSENGER_DATA
{int arrive_time,num;struct PASSENGER_DATA *nextPtr,*previousPtr;
  QLabel pic;QPoint po;
};
/*����ʱ�� �˿ͱ�� ��һλ��ָ��*/
struct WINDOW_DATA
{int left_time,totrestLen,restLen,servLen,winState,lineLen,lineTime,listState,picnum;double effciency;struct PASSENGER_DATA *headPtr,*tailPtr;
};
/*ʣ����Ϣʱ��   ����Ϣʱ�� ����Ϣʱ��  �ѷ���ʱ��  ����ʱ�� �������� ����״̬ Ч�� ����״̬ ��λ��ָ�� ĩβ��ָ�� */
/*
winState 0// ��Ϣ
winState 1// ����
winState 2//��Ϣ�ȴ�״̬
winState 3//����Ĵ��ڵ���Ϣ׼��
winState 4//����Ĵ�����Ϣ
listState 0//NOCHANGED
listState 1//CUSTIN
listState 2//CUSTOUT
*/
struct WINDOWLINE_DATA{int num;struct WINDOWLINE_DATA *nextPtr;};
typedef struct CONFIGURATION_DATA CONFIGURATION_DATA;    
typedef struct PASSENGER_DATA PASSENGER_DATA;
typedef struct WINDOW_DATA WINDOW_DATA;
typedef struct WINDOWLINE_DATA WINDOWLINE_DATA;

extern int LANGUAGE;/*����*/
/*

0 Ӣ��
1 ����
*/
extern int PROGRAM_TIME;/*����ʱ��*/
extern int PASSENGER_NUMBER;/*�˿ͱ��*/ 
extern int SORT_MODE;/*�Ŷ�ģʽ*/
extern int BUFFER_LINE_LEN;/*����������*/
/*
0 ���鳤��
1	Ч��
*/
extern int WORK_WINDOW_NUM;/*����״̬�������*/
extern int NORMAL_WORK_WINDOW_NUM;/*����״̬һ�㰲�����*/ 
extern int DYNAMIC_WINDOW_MANAGEMENT;/*�Ƿ�̬����*/
extern int MAX_BUFFERLINE_LENGTH;/*����������󳤶�*/ 
/*
0 ��
1 �� 
*/
extern int MAX_CUSTSINGLE_LINE;/*�����*/
extern int MAX_LINES;/*�������*/ 
extern int MAX_SEQUENCE_LENGTH;/*��������ȴ�����*/ 
extern int WORK_STATUS;/*����״̬*/
/*
0 ����
1 �°�׼��
2 �°�ȷ�� 
*/
extern int INPUT_MODE;/*����ģʽ*/ 
/*
0 ���� 
1 �ļ� 
*/
extern int CYCLE;/*ˢ����*/
extern int tot_People_Num;/*������*/
extern FILE *CONFIG_FILE;/*�����ļ�ָ��*/ 
extern FILE *OUTPUT_DETAIL;/*�б仯ʱ���м�¼*/
extern FILE *NORMAL_OUTPUT;/*�����Լ�¼*/
extern WINDOWLINE_DATA *WINDOW_RESTLINE_PTR;/*������Ϣ���ж�ָ��*/
extern PASSENGER_DATA *BUFFER_LINE_HEADPTR;/*����������*/
extern PASSENGER_DATA *BUFFER_LINE_TAILPTR;/*��������β*/
extern WINDOW_DATA *WINDOW_SET;/*����ڽṹ����*/
#endif

