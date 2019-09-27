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
#define WINDOW_NUMBER 8/*窗口数*/ 
#define NORMAL_WINDOW_NUMBER 4/*一般窗口数*/ 
#define INTERVAL_TIME 0/*从缓冲区到安检口所需时间*/
#define MAX_WAIT_LEN 7 
struct CONFIGURATION_DATA{int data;char name[20];};
struct PASSENGER_DATA
{int arrive_time,num;struct PASSENGER_DATA *nextPtr,*previousPtr;
  QLabel pic;QPoint po;
};
/*到达时间 乘客编号 下一位的指针*/
struct WINDOW_DATA
{int left_time,totrestLen,restLen,servLen,winState,lineLen,lineTime,listState,picnum;double effciency;struct PASSENGER_DATA *headPtr,*tailPtr;
};
/*剩余休息时间   总休息时长 已休息时长  已服务时长  队伍时间 队伍人数 窗口状态 效率 窗口状态 首位的指针 末尾的指针 */
/*
winState 0// 休息
winState 1// 工作
winState 2//休息等待状态
winState 3//特殊的窗口的休息准备
winState 4//特殊的窗口休息
listState 0//NOCHANGED
listState 1//CUSTIN
listState 2//CUSTOUT
*/
struct WINDOWLINE_DATA{int num;struct WINDOWLINE_DATA *nextPtr;};
typedef struct CONFIGURATION_DATA CONFIGURATION_DATA;    
typedef struct PASSENGER_DATA PASSENGER_DATA;
typedef struct WINDOW_DATA WINDOW_DATA;
typedef struct WINDOWLINE_DATA WINDOWLINE_DATA;

extern int LANGUAGE;/*语言*/
/*

0 英语
1 中文
*/
extern int PROGRAM_TIME;/*程序时间*/
extern int PASSENGER_NUMBER;/*乘客编号*/ 
extern int SORT_MODE;/*排队模式*/
extern int BUFFER_LINE_LEN;/*缓冲区长度*/
/*
0 队伍长短
1	效率
*/
extern int WORK_WINDOW_NUM;/*工作状态安检口数*/
extern int NORMAL_WORK_WINDOW_NUM;/*工作状态一般安检口数*/ 
extern int DYNAMIC_WINDOW_MANAGEMENT;/*是否动态窗口*/
extern int MAX_BUFFERLINE_LENGTH;/*缓冲区域最大长度*/ 
/*
0 否
1 是 
*/
extern int MAX_CUSTSINGLE_LINE;/*最长单列*/
extern int MAX_LINES;/*最多行数*/ 
extern int MAX_SEQUENCE_LENGTH;/*安检口最大等待队列*/ 
extern int WORK_STATUS;/*工作状态*/
/*
0 工作
1 下班准备
2 下班确认 
*/
extern int INPUT_MODE;/*输入模式*/ 
/*
0 键盘 
1 文件 
*/
extern int CYCLE;/*刷新率*/
extern int tot_People_Num;/*总人数*/
extern FILE *CONFIG_FILE;/*配置文件指针*/ 
extern FILE *OUTPUT_DETAIL;/*有变化时进行记录*/
extern FILE *NORMAL_OUTPUT;/*周期性记录*/
extern WINDOWLINE_DATA *WINDOW_RESTLINE_PTR;/*窗口休息序列队指针*/
extern PASSENGER_DATA *BUFFER_LINE_HEADPTR;/*缓冲区队首*/
extern PASSENGER_DATA *BUFFER_LINE_TAILPTR;/*缓冲区队尾*/
extern WINDOW_DATA *WINDOW_SET;/*安检口结构数组*/
#endif

