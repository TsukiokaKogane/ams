#include "PROGRAM_BASIC_ACTION.h"
#include "PROGRAM_CONFIGURATION.h"
#include "PROGRAM_IO.h"
#include "PRGRAM_SIMULATION.h"
#include "QApplication"
#include "QWidget"
#include "widget.h"
int LANGUAGE;/*语言*/
/*
0 英语
1 中文
*/
int PROGRAM_TIME;/*程序时间*/
int PASSENGER_NUMBER;/*乘客编号*/ 
int SORT_MODE;/*排队模式*/
int BUFFER_LINE_LEN;/*缓冲区长度*/
/*
0 队伍长短
1	效率
*/
int WORK_WINDOW_NUM;/*工作状态安检口数*/
int NORMAL_WORK_WINDOW_NUM;/*工作状态一般安检口数*/ 
int DYNAMIC_WINDOW_MANAGEMENT;/*是否动态窗口*/
int MAX_BUFFERLINE_LENGTH;/*缓冲区域最大长度*/
/*
0 否
1 是 
*/
int MAX_CUSTSINGLE_LINE;/*最长单列*/
int MAX_LINES;/*最多行数*/ 
int MAX_SEQUENCE_LENGTH;/*安检口最大等待队列*/ 
int WORK_STATUS;/*工作状态*/
/*
0 工作
1 下班准备
2 下班确认 
*/
int INPUT_MODE;/*输入模式*/ 
/*
0 键盘 
1 文件 
*/ 
int CYCLE=3;/*刷新率*/
int tot_People_Num;/*总人数*/
FILE *CONFIG_FILE=NULL;/*配置文件指针*/ 
FILE *OUTPUT_DETAIL=NULL;/*有变化时进行记录*/
FILE *NORMAL_OUTPUT=NULL;/*周期性记录*/
WINDOWLINE_DATA *WINDOW_RESTLINE_PTR=NULL;/*窗口休息序列队指针*/
PASSENGER_DATA *BUFFER_LINE_HEADPTR=NULL;/*缓冲区队首*/
PASSENGER_DATA *BUFFER_LINE_TAILPTR=NULL;/*缓冲区队尾*/
WINDOW_DATA *WINDOW_SET;/*安检口结构数组*/
static char ch;
static int ord;
static int GET_ORDER()
{int ret=0;
 ch=getchar();
 while(ch<'0'||ch>'9')ch=getchar();
 ret=ch-'0';
 return ret;
}
static void OUTPUT_ACTION()
{printf("1--");
 LANGUAGE?puts("文件输入"):puts("INUPUT BY FILE");
 printf("2--");
 LANGUAGE?puts("键盘输入"):puts("INUPUT BY KEYBORAD");
 printf("3--");
 LANGUAGE?puts("模型模拟"):puts("SIMULATION");
 printf("4--");
 LANGUAGE?puts("图形化模式"):puts("GRAPHIC MDOE");
 printf("5--");
 LANGUAGE?puts("退出"):puts("EXIT");
}
static void OUTPUT_CHOICE()
{switch(ord)
 {case 0:LANGUAGE?puts("修改配置文件"):puts("MODIFY CONFIGURATION DATA");break;
  case 1:LANGUAGE?puts("文件输入"):puts("INUPUT BY FILE");break;
  case 2:LANGUAGE?puts("键盘输入"):puts("INUPUT BY KEYBORAD");break;
  case 3:LANGUAGE?puts("模型模拟"):puts("SIMULATION");break;
  case 4:LANGUAGE?puts("图形化模式"):puts("GRAPHIC MDOE");break;
  case 5:LANGUAGE?puts("退出"):puts("EXIT");break;
 }
}
static int CONFIRMATION()
{ch=getchar();
 LANGUAGE?printf("请确认操作 "):printf("Please confrim your action:");
 OUTPUT_CHOICE();
 puts("<Y/N>");
 while(ch!='Y'&&ch!='N')ch=getchar();
 if(ch=='Y'){ch=getchar();return 1;}
   else {ch=getchar();return 0;}
}
int main(int argc, char *argv[])
{CONFIG_FILE=NULL;
 QApplication AGW(argc,argv);/*Airport Graphic Window*/
 //QCoreApplication::addLibraryPath("./");
 while(1)
 {puts("请选择语言");
  puts("Please choose your language");
  puts("1--中文");
  puts("2--ENGLISH");
  ord=GET_ORDER();
  if(ord==1){LANGUAGE=1;break;}
  else if(ord==2){LANGUAGE=0;break;}
  else{puts("无效操作 <(￣^￣)>");puts("INVAILD INPUT <(￣^￣)>");continue;}
 }
 ord=0;
 CONFIG_FILE=fopen("configuration.txt","w+");
 if(CONFIG_FILE==NULL){LANGUAGE?puts("无法打开配置文件！"):printf("File could not be opened\n");return 0;}
 LANGUAGE?puts("欢迎来到机场安检系统!(=￣ω￣=)"):puts("Welcome to airport security system!(=￣ω￣=)");
 CONFIGURATION_INITIALIZATION();
 getBasicData();
 output_configuration_data();
 if(CONFIRMATION()){MODIFY_CONFIGURATION();getBasicData();}
 
 while(1)
 {system("cls");
  LANGUAGE?puts("请选择操作："):puts("Please choose your action: ");
  OUTPUT_ACTION();
  ord=GET_ORDER();
  if(ord==1){if(CONFIRMATION())INPUT_BY_FILE();else continue;}
  else if(ord==2){if(CONFIRMATION())INUPUT_BY_KEYBORAD();else continue;}
  else if(ord==3){if(CONFIRMATION())INUPUT_BY_SIMULATION();else continue;}
  else if(ord==4){if(CONFIRMATION())
      {INPUT_MODE=3;
          system("cls");
        BASIC_INITIALIZATION();
        OUTPUT_ADVANCED_SETTING();
        MODIFY_ADVANCED_SETTING();
        Widget w;
        w.resize(1366,768);
        w.show();AGW.exec();
       FREE_SPACE();
      }else continue;}
  else if(ord==5)
  {if(CONFIRMATION()){LANGUAGE?puts("感谢使用 再见！ε=ε=┌(;￣◇￣)┘ "):puts("Thanks for using, byebye ε=ε=┌(;￣◇￣)┘");break;}
    else continue;
  }
  else {LANGUAGE?puts("无效操作 <(￣^￣)>"):puts("INVAILD INPUT <(￣^￣)>");system("pause");continue;}
 }
 fclose(CONFIG_FILE);
 return 0 ;
}
