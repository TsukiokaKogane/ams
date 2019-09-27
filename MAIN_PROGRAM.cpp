#include "PROGRAM_BASIC_ACTION.h"
#include "PROGRAM_CONFIGURATION.h"
#include "PROGRAM_IO.h"
#include "PRGRAM_SIMULATION.h"
#include "QApplication"
#include "QWidget"
#include "widget.h"
int LANGUAGE;/*����*/
/*
0 Ӣ��
1 ����
*/
int PROGRAM_TIME;/*����ʱ��*/
int PASSENGER_NUMBER;/*�˿ͱ��*/ 
int SORT_MODE;/*�Ŷ�ģʽ*/
int BUFFER_LINE_LEN;/*����������*/
/*
0 ���鳤��
1	Ч��
*/
int WORK_WINDOW_NUM;/*����״̬�������*/
int NORMAL_WORK_WINDOW_NUM;/*����״̬һ�㰲�����*/ 
int DYNAMIC_WINDOW_MANAGEMENT;/*�Ƿ�̬����*/
int MAX_BUFFERLINE_LENGTH;/*����������󳤶�*/
/*
0 ��
1 �� 
*/
int MAX_CUSTSINGLE_LINE;/*�����*/
int MAX_LINES;/*�������*/ 
int MAX_SEQUENCE_LENGTH;/*��������ȴ�����*/ 
int WORK_STATUS;/*����״̬*/
/*
0 ����
1 �°�׼��
2 �°�ȷ�� 
*/
int INPUT_MODE;/*����ģʽ*/ 
/*
0 ���� 
1 �ļ� 
*/ 
int CYCLE=3;/*ˢ����*/
int tot_People_Num;/*������*/
FILE *CONFIG_FILE=NULL;/*�����ļ�ָ��*/ 
FILE *OUTPUT_DETAIL=NULL;/*�б仯ʱ���м�¼*/
FILE *NORMAL_OUTPUT=NULL;/*�����Լ�¼*/
WINDOWLINE_DATA *WINDOW_RESTLINE_PTR=NULL;/*������Ϣ���ж�ָ��*/
PASSENGER_DATA *BUFFER_LINE_HEADPTR=NULL;/*����������*/
PASSENGER_DATA *BUFFER_LINE_TAILPTR=NULL;/*��������β*/
WINDOW_DATA *WINDOW_SET;/*����ڽṹ����*/
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
 LANGUAGE?puts("�ļ�����"):puts("INUPUT BY FILE");
 printf("2--");
 LANGUAGE?puts("��������"):puts("INUPUT BY KEYBORAD");
 printf("3--");
 LANGUAGE?puts("ģ��ģ��"):puts("SIMULATION");
 printf("4--");
 LANGUAGE?puts("ͼ�λ�ģʽ"):puts("GRAPHIC MDOE");
 printf("5--");
 LANGUAGE?puts("�˳�"):puts("EXIT");
}
static void OUTPUT_CHOICE()
{switch(ord)
 {case 0:LANGUAGE?puts("�޸������ļ�"):puts("MODIFY CONFIGURATION DATA");break;
  case 1:LANGUAGE?puts("�ļ�����"):puts("INUPUT BY FILE");break;
  case 2:LANGUAGE?puts("��������"):puts("INUPUT BY KEYBORAD");break;
  case 3:LANGUAGE?puts("ģ��ģ��"):puts("SIMULATION");break;
  case 4:LANGUAGE?puts("ͼ�λ�ģʽ"):puts("GRAPHIC MDOE");break;
  case 5:LANGUAGE?puts("�˳�"):puts("EXIT");break;
 }
}
static int CONFIRMATION()
{ch=getchar();
 LANGUAGE?printf("��ȷ�ϲ��� "):printf("Please confrim your action:");
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
 {puts("��ѡ������");
  puts("Please choose your language");
  puts("1--����");
  puts("2--ENGLISH");
  ord=GET_ORDER();
  if(ord==1){LANGUAGE=1;break;}
  else if(ord==2){LANGUAGE=0;break;}
  else{puts("��Ч���� <(��^��)>");puts("INVAILD INPUT <(��^��)>");continue;}
 }
 ord=0;
 CONFIG_FILE=fopen("configuration.txt","w+");
 if(CONFIG_FILE==NULL){LANGUAGE?puts("�޷��������ļ���"):printf("File could not be opened\n");return 0;}
 LANGUAGE?puts("��ӭ������������ϵͳ!(=���أ�=)"):puts("Welcome to airport security system!(=���أ�=)");
 CONFIGURATION_INITIALIZATION();
 getBasicData();
 output_configuration_data();
 if(CONFIRMATION()){MODIFY_CONFIGURATION();getBasicData();}
 
 while(1)
 {system("cls");
  LANGUAGE?puts("��ѡ�������"):puts("Please choose your action: ");
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
  {if(CONFIRMATION()){LANGUAGE?puts("��лʹ�� �ټ�����=��=��(;�����)�� "):puts("Thanks for using, byebye ��=��=��(;�����)��");break;}
    else continue;
  }
  else {LANGUAGE?puts("��Ч���� <(��^��)>"):puts("INVAILD INPUT <(��^��)>");system("pause");continue;}
 }
 fclose(CONFIG_FILE);
 return 0 ;
}
