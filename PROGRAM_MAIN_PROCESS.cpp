#include "PROGRAM_BASIC_ACTION.h"
#include "PROGRAM_LINEANDWINDOW_SCAN.h"
int ENTER_BUFFER_AREA()/*进入缓冲区*/
{PASSENGER_NUMBER++;
 if(BUFFER_LINE_LEN==MAX_BUFFERLINE_LENGTH)
 {LANGUAGE?fputs("排队缓冲区已满\n",NORMAL_OUTPUT):fputs("BUFFER LINE IS FULL\n",NORMAL_OUTPUT);
 LANGUAGE?puts("抱歉！ 排队缓冲区已满 Σ( ° △ °|||)︴\n"):puts("SORRY BUFFER LINE IS FULL Σ( ° △ °|||)︴\n");
  return 0;
 }
 if(WORK_STATUS>1)
 {
  LANGUAGE?puts(" 非常抱歉地告诉您我们即将下班。无法进入 ! Σ( ° △ °|||)︴"):puts("I'm sorry to tell you that we are about to off duty. You can't get in ! Σ( ° △ °|||)︴");
  LANGUAGE?fputs("非常抱歉地告诉您我们即将下班。无法进入 ! Σ( ° △ °|||)n",NORMAL_OUTPUT):fputs("I'm sorry to tell you that we are about to off duty. You can't get in ! Σ( ° △ °|||)n",NORMAL_OUTPUT);
  return 0;
 }
 /*LANGUAGE?puts("乘客进入排队缓冲区"):puts("PASSENGER ENTER THE BUFFER LINE");*/
 LANGUAGE?printf("编号为%d的乘客于%d 进入排队缓冲区\n",PASSENGER_NUMBER,PROGRAM_TIME):printf("PASSENGER No.%d ENTER THE BUFFER LINE AT %d\n",PASSENGER_NUMBER,PROGRAM_TIME);
 LANGUAGE?fprintf(NORMAL_OUTPUT,"编号为%d的乘客于%d 进入排队缓冲区\n",PASSENGER_NUMBER,PROGRAM_TIME):fprintf(NORMAL_OUTPUT,"PASSENGER No.%d ENTER THE BUFFER LINE AT %d\n",PASSENGER_NUMBER,PROGRAM_TIME);
 BUFFER_LINE_LEN++;tot_People_Num++;
 PASSENGER_DATA *NEW_PASSENGER=new PASSENGER_DATA;
 if(NEW_PASSENGER==NULL){puts("UNKNOWN ERROR");system("pause");}
 NEW_PASSENGER->num=PASSENGER_NUMBER;

 if(INPUT_MODE==3)
  { QString str=QStringLiteral("乘客编号:"),str1="";
     int x=PASSENGER_NUMBER;
     if(x==0)str1="0";
     while(x)
     {str1=(char)(x%10+'0')+str1;
      x/=10;
     }
     NEW_PASSENGER->pic.setToolTip(str+str1);
 }

 NEW_PASSENGER->nextPtr=NULL;
 NEW_PASSENGER->previousPtr=NULL;
 /*
 printf("（新乘客到来）NEW_PASSENGER_NUM=%d TIME=%d LienLen=%d\n",NEW_PASSENGER->num,PROGRAM_TIME,BUFFER_LINE_LEN);
 */

 if(BUFFER_LINE_HEADPTR==NULL){BUFFER_LINE_HEADPTR=BUFFER_LINE_TAILPTR=NEW_PASSENGER;return 1;}
 BUFFER_LINE_TAILPTR->nextPtr=NEW_PASSENGER;
 NEW_PASSENGER->previousPtr=BUFFER_LINE_TAILPTR;
 BUFFER_LINE_TAILPTR=NEW_PASSENGER;
 NEW_PASSENGER=NULL;
  return 1;
}
void REST_REQUIREMENT(int WINDOW_NUM)/*要求休息*/ 
{if(WORK_STATUS==1||WORK_STATUS==2)
 {LANGUAGE?puts("已收到下班指令 不再执行休息业务"):puts("RECIVED OFFDUTY ORDER ALREADY NO LONGER PROCESS REST WORK");
  LANGUAGE?fputs("已收到下班指令 不再执行休息业务",NORMAL_OUTPUT):fputs("RECIVED OFFDUTY ORDER ALREADY NO LONGER PROCESS REST WORK",NORMAL_OUTPUT);
  return; 
 }
 if(WINDOW_SET[WINDOW_NUM].winState==0)
 {LANGUAGE?puts("正在执行休息业务 逻辑错误"):puts("ALREADY PROCESSING REST WORK LOGICAL ERROR");
  LANGUAGE?fputs("正在执行休息业务 逻辑错误",NORMAL_OUTPUT):fputs("ALREADY PROCESSING REST WORK LOGICAL ERROR",NORMAL_OUTPUT);
  return;
 }
 WINDOWLINE_DATA *TEMP_PTR=(WINDOWLINE_DATA *)malloc(sizeof(WINDOWLINE_DATA));
 TEMP_PTR->num=WINDOW_NUM;
 TEMP_PTR->nextPtr=NULL;
 if(WINDOW_RESTLINE_PTR==NULL)
 {WINDOW_RESTLINE_PTR=TEMP_PTR;
  return; 
 }
 if(WINDOW_RESTLINE_PTR->num==WINDOW_NUM)
 {LANGUAGE?puts("正在休息队列里 请不要急躁 ヽ（゜ロ゜；）ノ"):puts("already in rest line Please don't get rashヽ（゜ロ゜；）ノ");
  return;
 }
 if(WINDOW_SET[WINDOW_NUM].restLen<WINDOW_SET[WINDOW_RESTLINE_PTR->num].restLen)
 {TEMP_PTR->nextPtr=WINDOW_RESTLINE_PTR;
  WINDOW_RESTLINE_PTR=TEMP_PTR;
  return;
 }
 WINDOWLINE_DATA *currentPtr=WINDOW_RESTLINE_PTR->nextPtr,*previousPtr=WINDOW_RESTLINE_PTR;
 while(currentPtr!=NULL)
 {if(WINDOW_SET[WINDOW_NUM].restLen<WINDOW_SET[WINDOW_RESTLINE_PTR->num].restLen)break;
  if(currentPtr->num==WINDOW_NUM)
  {LANGUAGE?puts("正在休息队列里 请不要急躁 ヽ（゜ロ゜；）ノ"):puts("already in rest line Please don't get rashヽ（゜ロ゜；）ノ");
   previousPtr=currentPtr=NULL;
   return;
  }
  previousPtr=currentPtr;
  currentPtr=currentPtr->nextPtr;
 }
 TEMP_PTR->nextPtr=currentPtr;
 previousPtr->nextPtr=TEMP_PTR;
  return;
}
static void INCREASE_WINDOW()
{int i;
 for(i=NORMAL_WINDOW_NUMBER;i<WINDOW_NUMBER;i++)
 {if(BUFFER_LINE_LEN<WORK_WINDOW_NUM*3)return;
  if(WINDOW_SET[i].winState==4)
  {WINDOW_SET[i].winState=1;
   WINDOW_SET[i].picnum=rand()%3;
   LANGUAGE?printf("编号为%d的动态窗口于T=%d打开\n",i+1,PROGRAM_TIME):printf("dynamic window No. %d open at T=%d\n",i+1,PROGRAM_TIME);
   LANGUAGE?fprintf(NORMAL_OUTPUT,"编号为%d的动态窗口于T=%d打开\n",i+1,PROGRAM_TIME):fprintf(NORMAL_OUTPUT,"dynamic window No. %d open at T=%d\n",i+1,PROGRAM_TIME);
   WORK_WINDOW_NUM++;
  }
 }
 if(BUFFER_LINE_LEN<WORK_WINDOW_NUM*3)return;
 for(i=NORMAL_WINDOW_NUMBER;i<WINDOW_NUMBER;i++)
 {if(BUFFER_LINE_LEN<WORK_WINDOW_NUM*3)return;
  if(WINDOW_SET[i].winState==3)
  {WINDOW_SET[i].winState=1;
  // WINDOW_SET[i].picnum=rand()%3;
   LANGUAGE?printf("编号为%d的动态窗口于T=%d取消预备休息计划\n",i+1,PROGRAM_TIME):printf("dynamic window No. %d cancel rest plan at T=%d\n",i+1,PROGRAM_TIME); 
   LANGUAGE?fprintf(NORMAL_OUTPUT,"编号为%d的动态窗口于T=%d取消预备休息计划\n",i+1,PROGRAM_TIME):fprintf(NORMAL_OUTPUT,"dynamic window No. %d cancel rest plan at T=%d\n",i+1,PROGRAM_TIME); 
   WORK_WINDOW_NUM++;
  }
 }
 return;
}
static void DECREASE_WINDOW()
{int i;
 for(i=NORMAL_WINDOW_NUMBER;i<WINDOW_NUMBER;i++)
 {if(BUFFER_LINE_LEN>=WORK_WINDOW_NUM*2)return;
  if(WINDOW_SET[i].winState==1&&WINDOW_SET[i].lineLen==0)
  {WINDOW_SET[i].winState=4;
    WINDOW_SET[i].picnum=3;
   LANGUAGE?printf("编号为%d的动态窗口于T=%d\n",i+1,PROGRAM_TIME):printf("dynamic window No. %d rest at T=%d\n",i+1,PROGRAM_TIME);
   LANGUAGE?fprintf(NORMAL_OUTPUT,"编号为%d的动态窗口于T=%d休息\n",i+1,PROGRAM_TIME):fprintf(NORMAL_OUTPUT,"dynamic window No. %d rest at T=%d\n",i+1,PROGRAM_TIME); 
   WORK_WINDOW_NUM--;
  }
 }
 if(BUFFER_LINE_LEN>=WORK_WINDOW_NUM*2)return;
 for(i=NORMAL_WINDOW_NUMBER;i<WINDOW_NUMBER;i++)
 {if(BUFFER_LINE_LEN>=WORK_WINDOW_NUM*2)break;
  if(WINDOW_SET[i].winState==1)
  {WINDOW_SET[i].winState=3;
   LANGUAGE?printf("编号为%d的动态窗口于T=%d预备关闭\n",i+1,PROGRAM_TIME):printf("dynamic window No. %d  plan to closed at T=%d\n",i+1,PROGRAM_TIME);
   LANGUAGE?fprintf(NORMAL_OUTPUT,"编号为%d的动态窗口于T=%d预备关闭\n",i+1,PROGRAM_TIME):fprintf(NORMAL_OUTPUT,"dynamic window No. %d  plan to closed at T=%d\n",i+1,PROGRAM_TIME);
   WORK_WINDOW_NUM--;
  }
 }
  return;
}
void DYNAMIC_MANAGEMENT()/*动态分配*/
{if(WORK_STATUS)return;
 while(1)
 {if(BUFFER_LINE_LEN>=WORK_WINDOW_NUM*3)
  {if(WORK_WINDOW_NUM-NORMAL_WORK_WINDOW_NUM==4)return;
   INCREASE_WINDOW();
   MAIN_SCAN();
  }
  else if(BUFFER_LINE_LEN<WORK_WINDOW_NUM*2)
  {if(WORK_WINDOW_NUM-NORMAL_WORK_WINDOW_NUM==0)return;
   DECREASE_WINDOW();
   MAIN_SCAN();
  }
   else break;
 }
  return;
}
