#include "PROGRAM_BASIC_ACTION.h"
#include "PROGRAM_LINEANDWINDOW_SCAN.h"
#include "PROGRAM_MAIN_PROCESS.h"
#include "PROGRAM_CONFIGURATION.h"
#include "QApplication"
/*void output_all()输出整个缓冲区（非蛇形版本）测试用 
{PASSENGER_DATA *tempPtr=BUFFER_LINE_HEADPTR;
 if(tempPtr==NULL)return;
 puts("");
 while(tempPtr->nextPtr){printf("%d->",tempPtr->num);tempPtr=tempPtr->nextPtr;}
 printf("%d",tempPtr->num);
  puts("");
}*/
static void foward_output(PASSENGER_DATA *nowPtr,int totnum)
{int tt=1;
 while(tt<totnum){tt++;fprintf(OUTPUT_DETAIL,"%d\t<-\t",nowPtr->num);nowPtr=nowPtr->nextPtr;}
 fprintf(OUTPUT_DETAIL,"%d\t",nowPtr->num);
 fputc('\n',OUTPUT_DETAIL);
}
static void backward_output(PASSENGER_DATA *nowPtr,int totnum)
{int tt=1;
 while(tt<totnum){tt++;fprintf(OUTPUT_DETAIL,"%d\t->\t",nowPtr->num);nowPtr=nowPtr->previousPtr;}
 fprintf(OUTPUT_DETAIL,"%d\t",nowPtr->num);
 fputc('\n',OUTPUT_DETAIL);
}
static void interval_output(int now_row)
{if(now_row==1)return;
 fputc('\n',OUTPUT_DETAIL);
 int i;
 if(now_row%2==0)
 {for(i=1;i<=MAX_CUSTSINGLE_LINE*2-2;i++)fprintf(OUTPUT_DETAIL," \t");
  fprintf(OUTPUT_DETAIL,"↑\t");
  fputc('\n',OUTPUT_DETAIL);
 }
 else 
 {fprintf(OUTPUT_DETAIL,"↑\t");
  fputc('\n',OUTPUT_DETAIL);
 }
  fputc('\n',OUTPUT_DETAIL);
}
static void BUFFERLINE_OUTPUT()/*文件输出完整缓冲区*/ 
{LANGUAGE?fprintf(OUTPUT_DETAIL,"缓冲区队列:\n"):fprintf(OUTPUT_DETAIL,"BUFFER LINE STATUS:\n");
 PASSENGER_DATA *tempPtr=BUFFER_LINE_HEADPTR,*endPtr=NULL;
 int row_num=BUFFER_LINE_LEN/MAX_CUSTSINGLE_LINE;
 int left_num=BUFFER_LINE_LEN%MAX_CUSTSINGLE_LINE;
 int now_row;
 tempPtr=BUFFER_LINE_HEADPTR;
 for(now_row=1;now_row<=row_num;now_row++)
 {endPtr=tempPtr;
   int tt=1;
   while(tt<MAX_CUSTSINGLE_LINE){tt++;endPtr=endPtr->nextPtr;}
   interval_output(now_row);
   if(now_row%2)
   {foward_output(tempPtr,MAX_CUSTSINGLE_LINE);
   }
   else
   {backward_output(endPtr,MAX_CUSTSINGLE_LINE);}
   tempPtr=endPtr->nextPtr;
 }
 if(left_num==0)return;
 row_num++;
 interval_output(row_num);
 if(row_num%2)
 {foward_output(tempPtr,left_num);
 }
   else 
   {int tt;
    for(tt=1;tt<(MAX_CUSTSINGLE_LINE-left_num)*2+1;tt++)fprintf(OUTPUT_DETAIL," \t");
    endPtr=tempPtr;
    while(endPtr->nextPtr!=NULL)endPtr=endPtr->nextPtr;
    backward_output(endPtr,left_num);
   }
 fputc('\n',OUTPUT_DETAIL);
}

static void foward_output_lite(PASSENGER_DATA *nowPtr,int totnum)
{int tt=1;
 while(tt<totnum){tt++;printf("%3d->",nowPtr->num%1000);nowPtr=nowPtr->nextPtr;}
 printf("%3d",nowPtr->num%1000);
 puts("");
}
static void backward_output_lite(PASSENGER_DATA *nowPtr,int totnum)
{int tt=1;
 while(tt<totnum){tt++;printf("%3d<-",nowPtr->num%1000);nowPtr=nowPtr->previousPtr;}
 printf("%3d",nowPtr->num%1000);
 puts("");
}
static void interval_output_lite(int now_row)
{if(now_row==1)return;
 int i;
 if(now_row%2==0)
 {for(i=1;i<MAX_CUSTSINGLE_LINE;i++)printf("     ");
  printf(" ↓");
  puts("");
 }
 else 
 {printf(" ↓");
  puts("");
 }
}
static void BUFFERLINE_OUTPUT_LITE()/*命令行输出简短版缓冲区*/ 
{LANGUAGE?puts("乘客缓冲区："):puts("passenger buffer area:");
 PASSENGER_DATA *tempPtr=BUFFER_LINE_HEADPTR,*endPtr=NULL;
 int row_num=BUFFER_LINE_LEN/MAX_CUSTSINGLE_LINE;
 int left_num=BUFFER_LINE_LEN%MAX_CUSTSINGLE_LINE;
 int now_row;
 tempPtr=BUFFER_LINE_HEADPTR;
 for(now_row=1;now_row<=row_num;now_row++)
 {endPtr=tempPtr;
   int tt=1;
   while(tt<MAX_CUSTSINGLE_LINE){tt++;endPtr=endPtr->nextPtr;}
   interval_output_lite(now_row);
   if(now_row%2)
   {foward_output_lite(tempPtr,MAX_CUSTSINGLE_LINE);
   }
   else
   {backward_output_lite(endPtr,MAX_CUSTSINGLE_LINE);}
   tempPtr=endPtr->nextPtr;
 }
 if(left_num==0)return;
 row_num++;
 interval_output_lite(row_num);
 if(row_num%2)
 {foward_output_lite(tempPtr,left_num);
 }
   else 
   {int tt;
    for(tt=1;tt<(MAX_CUSTSINGLE_LINE-left_num)+1;tt++)printf("     ");
    endPtr=tempPtr;
    while(endPtr->nextPtr!=NULL)endPtr=endPtr->nextPtr;
    backward_output_lite(endPtr,left_num);
   }
 puts("");
}
static void FILE_OUTPUT()/*文件输出*/
{fprintf(OUTPUT_DETAIL,"T=<%d>\n",PROGRAM_TIME);
 int nowwindow;
 for(nowwindow=0;nowwindow<WINDOW_NUMBER;++nowwindow)
 {if(!DYNAMIC_WINDOW_MANAGEMENT&&nowwindow==NORMAL_WINDOW_NUMBER)break;
  fprintf(OUTPUT_DETAIL,"WIN%d:State=",nowwindow+1);
  if(WINDOW_SET[nowwindow].winState==0)fprintf(OUTPUT_DETAIL,"rest");
   else if(WINDOW_SET[nowwindow].winState==4)fprintf(OUTPUT_DETAIL,"closed");
     else if(WINDOW_SET[nowwindow].lineLen)fprintf(OUTPUT_DETAIL,"working");
     else fprintf(OUTPUT_DETAIL,"open");
  fprintf(OUTPUT_DETAIL,",ServeLen=%d,",WINDOW_SET[nowwindow].servLen);
  fprintf(OUTPUT_DETAIL,"RestLen=%d/%d,",WINDOW_SET[nowwindow].left_time,WINDOW_SET[nowwindow].restLen);
  if(WINDOW_SET[nowwindow].listState==1)fprintf(OUTPUT_DETAIL,"WinListState=CUSTIN,");
   else if(WINDOW_SET[nowwindow].listState==2)fprintf(OUTPUT_DETAIL,"WinListState=CUSTOUT,");
    else if(WINDOW_SET[nowwindow].listState==0)fprintf(OUTPUT_DETAIL,"WinListState=NOCHANGED,");
      else fprintf(OUTPUT_DETAIL,"WinListState=%d,",WINDOW_SET[nowwindow].listState);
    
  /*fprintf(OUTPUT_DETAIL,"WinListState=%d,",WINDOW_SET[nowwindow].restLen);*/
  fprintf(OUTPUT_DETAIL,"WinListCustCount=%d\n",WINDOW_SET[nowwindow].lineLen);
  fprintf(OUTPUT_DETAIL,"WinListCust=");
  PASSENGER_DATA *tempPtr=WINDOW_SET[nowwindow].headPtr;
  if(tempPtr!=NULL)
  {while(tempPtr->nextPtr!=NULL)
   {fprintf(OUTPUT_DETAIL,"%d",tempPtr->num);
    fprintf(OUTPUT_DETAIL,"->");
    tempPtr=tempPtr->nextPtr;
   }
   fprintf(OUTPUT_DETAIL,"%d",tempPtr->num);
  }
  fputc('\n',OUTPUT_DETAIL);
  }
 fprintf(OUTPUT_DETAIL,"ListLines=%d\n",BUFFER_LINE_LEN/MAX_CUSTSINGLE_LINE+(BUFFER_LINE_LEN%MAX_CUSTSINGLE_LINE>0));
 fprintf(OUTPUT_DETAIL,"ListCustCount=%d\n",BUFFER_LINE_LEN);
 fprintf(OUTPUT_DETAIL,"BufferlineCust=\n");
 BUFFERLINE_OUTPUT();
}
/*void TEST_OUTPUT()测试用输出
{int nowwindow;
 printf("NORMAL_WORK_WINDOW_NUM=%d\nWORK_WINDOW_NUM=%d\n",NORMAL_WORK_WINDOW_NUM,WORK_WINDOW_NUM);
 LANGUAGE?puts("窗口情况:"):puts("window status:");
 for(nowwindow=0;nowwindow<WINDOW_NUMBER;++nowwindow)
 {if(!DYNAMIC_WINDOW_MANAGEMENT&&nowwindow==NORMAL_WINDOW_NUMBER)break;
  printf("WIN%d:State=",nowwindow);
  if(WINDOW_SET[nowwindow].winState==0)printf("Rest");
   else if(WINDOW_SET[nowwindow].winState==4)printf("Closed");
     else if(WINDOW_SET[nowwindow].lineLen)printf("Working");
      else printf("Open");
  puts("");
  printf("ServeLen=%d,",WINDOW_SET[nowwindow].servLen);
  printf("RestLen=%d/%d,",WINDOW_SET[nowwindow].left_time,WINDOW_SET[nowwindow].restLen);
  printf("WinListCustCount=%d\n",WINDOW_SET[nowwindow].lineLen);
  printf("WinListCust=");
  PASSENGER_DATA *tempPtr=WINDOW_SET[nowwindow].headPtr;
  if(tempPtr!=NULL)
  {while(tempPtr->nextPtr!=NULL)
   {printf("%d",tempPtr->num);
    printf("->");
    tempPtr=tempPtr->nextPtr;
   }
   printf("%d",tempPtr->num);
  }
  puts("");
 }
 puts("bufferline status:");
 output_all();
 puts("restline status:");
 output_restline();
}*/ 
static void output_chart()
{int i;
 printf("------------|");
  printf("-----------|");
 for(i=1;i<(DYNAMIC_WINDOW_MANAGEMENT?WINDOW_NUMBER:NORMAL_WINDOW_NUMBER);i++)
  printf("---------------|");
 puts("");
}
static void CMD_OUTPUT()
{LANGUAGE?printf("当前时间=%d",PROGRAM_TIME):printf("PROGRAM_TIME=%d",PROGRAM_TIME);
 if(!INPUT_MODE)printf(" min ");
   else printf(" sec "); 
 LANGUAGE?printf(" 刷新率=%d",CYCLE):printf("REFRESHING REATE=%d",CYCLE);
 if(!INPUT_MODE)printf("/min\n");
   else printf("/sec\n"); 
 int i; 
 printf("---------");
 for(i=0;i<(DYNAMIC_WINDOW_MANAGEMENT?WINDOW_NUMBER:NORMAL_WINDOW_NUMBER);i++)
 printf("----------------");
 puts("");
 LANGUAGE?printf("窗口号      |"):printf("Window No.  |");
 for(i=0;i<(DYNAMIC_WINDOW_MANAGEMENT?WINDOW_NUMBER:NORMAL_WINDOW_NUMBER);i++)printf("\t%d\t|",i+1);
 puts("");
 output_chart();
 LANGUAGE?printf("当前状态    |"):printf("Event       |");
 for(i=0;i<(DYNAMIC_WINDOW_MANAGEMENT?WINDOW_NUMBER:NORMAL_WINDOW_NUMBER);i++)
 {if(WINDOW_SET[i].listState==0)printf("\tNOCHANGE|");
   else if(WINDOW_SET[i].listState==1)printf("\tCUSTIN\t|");
      else printf("\tCUSTOUT\t|");
        WINDOW_SET[i].listState=0;
 }
 puts("");
 output_chart();
 LANGUAGE?printf("当前事件    |"):printf("Status      |");
 for(i=0;i<(DYNAMIC_WINDOW_MANAGEMENT?WINDOW_NUMBER:NORMAL_WINDOW_NUMBER);i++)
 {if(WINDOW_SET[i].winState==0)printf("\trest\t|");
   else if(WINDOW_SET[i].winState==4)printf("\tclosed\t|");
     else if(WINDOW_SET[i].lineLen)printf("\twork\t|");
      else printf("\topen\t|");
 }
 puts("");
 output_chart();
 LANGUAGE?printf("已工作时间  |"):printf("WORK TIME   |");
 for(i=0;i<(DYNAMIC_WINDOW_MANAGEMENT?WINDOW_NUMBER:NORMAL_WINDOW_NUMBER);i++)
 {if(WINDOW_SET[i].winState==0)printf("\t%d\t|",WINDOW_SET[i].servLen);
   else if(WINDOW_SET[i].winState==4)printf("\t%d\t|",WINDOW_SET[i].servLen);
     else if(WINDOW_SET[i].lineLen)printf("\t%d\t|",WINDOW_SET[i].servLen);
      else printf("\t%d\t|",WINDOW_SET[i].servLen);
 }
 puts("");
 output_chart();
 LANGUAGE?printf("已休息时间  |"):printf("REST TIME   |");
 for(i=0;i<(DYNAMIC_WINDOW_MANAGEMENT?WINDOW_NUMBER:NORMAL_WINDOW_NUMBER);i++)
 {if(WINDOW_SET[i].winState==0)printf("\t%d\t|",WINDOW_SET[i].restLen);
   else if(WINDOW_SET[i].winState==4)printf("\t%d\t|",WINDOW_SET[i].restLen);
     else if(WINDOW_SET[i].lineLen)printf("\t%d\t|",WINDOW_SET[i].restLen);
      else printf("\t%d\t|",WINDOW_SET[i].restLen);
 }
 puts("");
 output_chart();
 PASSENGER_DATA *tmpPtr[8]; 
 LANGUAGE?printf("当前办理乘客|"):printf("CURRENT CUST|");
 for(i=0;i<(DYNAMIC_WINDOW_MANAGEMENT?WINDOW_NUMBER:NORMAL_WINDOW_NUMBER);i++)
 {tmpPtr[i]=WINDOW_SET[i].headPtr;
  if(WINDOW_SET[i].headPtr==NULL)printf("\t \t|" );
      else{printf("\t%d\t|",(WINDOW_SET[i].headPtr)->num);
           tmpPtr[i]=(tmpPtr[i])->nextPtr;
	     } 
 }
 puts("");
 /**/
 printf("            |");
 printf("           |");
 for(i=1;i<(DYNAMIC_WINDOW_MANAGEMENT?WINDOW_NUMBER:NORMAL_WINDOW_NUMBER);i++)
  printf("               |");
 puts("");
 LANGUAGE?printf("窗口乘客队列|"):printf("WATING LINE |");
 printf("-----------|");
 for(i=1;i<(DYNAMIC_WINDOW_MANAGEMENT?WINDOW_NUMBER:NORMAL_WINDOW_NUMBER);i++)
  printf("---------------|");
 puts("");
 /**/
 for(i=0;i<MAX_WAIT_LEN;i++)
 {printf("\t    |");
  if(tmpPtr[0]==NULL)printf("    \t|");
    else 
	{printf("   %d\t| ",(tmpPtr[0])->num);
	 tmpPtr[0]=(tmpPtr[0])->nextPtr;
	}
  int j;
  for(j=1;j<(DYNAMIC_WINDOW_MANAGEMENT?WINDOW_NUMBER:NORMAL_WINDOW_NUMBER);j++)
  {if(tmpPtr[j]==NULL)printf("\t \t|" );
    else 
	{printf("\t%d\t|",(tmpPtr[j])->num);
	 tmpPtr[j]=(tmpPtr[j])->nextPtr;
	}
  }
  puts("");
 }
 puts("");
 printf("=========");
 for(i=0;i<(DYNAMIC_WINDOW_MANAGEMENT?WINDOW_NUMBER:NORMAL_WINDOW_NUMBER);i++)
 printf("================");
 puts("");
 LANGUAGE?puts("隔离区"):puts("restricted area:");
 printf("=========");
 for(i=0;i<(DYNAMIC_WINDOW_MANAGEMENT?WINDOW_NUMBER:NORMAL_WINDOW_NUMBER);i++)
 printf("================");
 puts("");
 BUFFERLINE_OUTPUT_LITE();
 puts("");
 printf("=========");
 for(i=0;i<(DYNAMIC_WINDOW_MANAGEMENT?WINDOW_NUMBER:NORMAL_WINDOW_NUMBER);i++)
 printf("================");
 puts("");
}
extern void OUTPUT()
{FILE_OUTPUT();
 CMD_OUTPUT();
} 
extern void ASK_FOR_QUIT()
{if(WORK_STATUS)
 {LANGUAGE?puts("正在执行下班指令 请不要急躁 ヽ（゜ロ゜；）ノ"):puts("already working on off duty order Please don't get rashヽ（゜ロ゜；）ノ");
  return;
 }
 WORK_STATUS=1;
 if(INPUT_MODE==3)WORK_STATUS=2;
 LANGUAGE?fputs("接收到下班指令\n",NORMAL_OUTPUT):fputs("receive off duty order",NORMAL_OUTPUT);
 if(INPUT_MODE!=3)MAIN_SCAN();
}
static int CHECK_FOR_EXIT()
{if(!WORK_STATUS)return 0; 
 if(WINDOW_SET[0].lineLen==0&&
    WINDOW_SET[1].lineLen==0&&
	WINDOW_SET[2].lineLen==0&&
	WINDOW_SET[3].lineLen==0&&
	WINDOW_SET[4].lineLen==0&&
	WINDOW_SET[5].lineLen==0&&
	WINDOW_SET[6].lineLen==0&&
	WINDOW_SET[7].lineLen==0
  )return 1;
  return 0;
}
extern void BASIC_INITIALIZATION()
{srand( (unsigned int)time(NULL));
 PROGRAM_TIME=0;
 PASSENGER_NUMBER=0;
 tot_People_Num=0;
 BUFFER_LINE_LEN=0;
 WORK_WINDOW_NUM=4;
 NORMAL_WORK_WINDOW_NUM=4;
 SORT_MODE=0;
 DYNAMIC_WINDOW_MANAGEMENT=0;
 WORK_STATUS=0;
 WINDOW_INITIALIZATION();
 WINDOW_RESTLINE_PTR=NULL;
 BUFFER_LINE_HEADPTR=NULL;
 BUFFER_LINE_TAILPTR=NULL;
 OUTPUT_DETAIL=fopen("outputDetail.txt","w+");
 if(OUTPUT_DETAIL==NULL)LANGUAGE?puts("无法输出详细信息\n"):puts("can't give out detailed imformation");
 NORMAL_OUTPUT=fopen("output.txt","w+");
 if(NORMAL_OUTPUT==NULL)LANGUAGE?puts("无法输出普通信息\n"):puts("can't give out normal imformation");
}
extern void FREE_SPACE()
{free(WINDOW_SET);
 WINDOWLINE_DATA *tempPtr1=NULL;
 while(WINDOW_RESTLINE_PTR!=NULL)
 {tempPtr1=WINDOW_RESTLINE_PTR;
  WINDOW_RESTLINE_PTR=WINDOW_RESTLINE_PTR->nextPtr;
  free(tempPtr1);
  tempPtr1=NULL;
 }
 PASSENGER_DATA *tempPtr2=NULL;
 while(BUFFER_LINE_HEADPTR!=NULL)
 {tempPtr2=BUFFER_LINE_HEADPTR;
  BUFFER_LINE_HEADPTR=BUFFER_LINE_HEADPTR->nextPtr;
  free(tempPtr2);
  tempPtr2=NULL;
 }
 BUFFER_LINE_TAILPTR=NULL;
}
static void time_count()
{clock_t start, finish;
 double duration=0.0;
 start=clock();
 while(duration<1.0)
 {finish=clock();
  duration=(finish-start)/CLOCKS_PER_SEC;
 }
 return;
}
HANDLE hMutex;
static void getInput()
{int flag=0;
 while(1)
 {if(CHECK_FOR_EXIT())break;
  char ch;
  ch=getchar();
  WaitForSingleObject(hMutex,INFINITE);/*请求互斥对象*/
  if(flag)
  {flag=0;
   if(ch-'0'>NORMAL_WINDOW_NUMBER||ch-'0'<1){puts("invaild window number");}
     else REST_REQUIREMENT(ch-'0'-1);
   ch=' ';
  }
  if(ch=='G')
  {MAIN_SCAN();
   ENTER_BUFFER_AREA();
  } 
  if(ch=='R')
  {flag=1;
  }
  if(ch=='Q')ASK_FOR_QUIT();
  ReleaseMutex(hMutex);/*释放互斥对象*/
 }
}
void INUPUT_BY_KEYBORAD()
{system("cls");
 INPUT_MODE=1;
 BASIC_INITIALIZATION();
 OUTPUT_ADVANCED_SETTING();
 MODIFY_ADVANCED_SETTING();
 DWORD ThreadID1;
 HANDLE thRead1;
 hMutex=CreateMutex(NULL,FALSE,NULL);/*创建互斥对象*/
 thRead1=CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)getInput,NULL,0,&ThreadID1);   
 while(1)
 {if(CHECK_FOR_EXIT())break;
  WaitForSingleObject(hMutex,INFINITE);
  if(PROGRAM_TIME%CYCLE==0)
  {system("cls");
   OUTPUT();
   LANGUAGE?puts("事件日志:"):puts("EVENT LOG:");
  }
  PROGRAM_TIME++;
  PROCESS_WINDOW_TIME();
  MAIN_SCAN();
  if(WORK_STATUS==1){WORK_STATUS=2;}
  PROCESS_WINDOW_RESTLINE();
  if(DYNAMIC_WINDOW_MANAGEMENT)DYNAMIC_MANAGEMENT();
  ReleaseMutex(hMutex);
  time_count();
 }
 LANGUAGE?puts("程序结束"):puts("END OF PROGRAM");
 system("pause");
 CloseHandle(thRead1);
 fclose(OUTPUT_DETAIL);
 OUTPUT_DETAIL=NULL;
 fclose(NORMAL_OUTPUT);
 NORMAL_OUTPUT=NULL;
 FREE_SPACE();
}
int CHECK_FOR_END()
{if(BUFFER_LINE_LEN)return 0;
 int i;
 for(i=0;i<(DYNAMIC_WINDOW_MANAGEMENT?WINDOW_NUMBER:NORMAL_WINDOW_NUMBER);i++)
 {if(WINDOW_SET[i].lineLen)return 0;
 }
 return 1;
}
void INPUT_BY_FILE()
{INPUT_MODE=0; 
 system("cls");
 FILE *fPtr=fopen("input.txt","r");
 if(fPtr==NULL){LANGUAGE?puts("无法打开输入文件！"):puts("can't open the input file!'");system("pause");return;}
 BASIC_INITIALIZATION();
 OUTPUT_ADVANCED_SETTING();
 MODIFY_ADVANCED_SETTING();
  system("cls");
 LANGUAGE?puts("事件日志:"):puts("EVENT LOG:");
 char ch=fgetc(fPtr);
 while(ch!='T')ch=fgetc(fPtr);
 int STATE=1;
 while(!feof(fPtr))
 {switch(STATE)
  {case 1:
   ch=fgetc(fPtr);
   int currentTime; 
   fscanf(fPtr,"%d",&currentTime);
   while(PROGRAM_TIME<currentTime)
   {PROGRAM_TIME++;
    MAIN_SCAN();
    PROCESS_WINDOW_TIME();
    MAIN_SCAN();
	PROCESS_WINDOW_RESTLINE();
	if(PROGRAM_TIME%CYCLE==0&&PROGRAM_TIME!=currentTime)
	 {OUTPUT();
      system("pause");
      system("cls");
      LANGUAGE?puts("事件日志:"):puts("EVENT LOG:");
	 }
   }
   ch=fgetc(fPtr);
   while(ch!='=')ch=fgetc(fPtr);
   STATE=2;
   break;
   case 2:
   ch=fgetc(fPtr);
   while(ch!='R'&&ch!='T'&&ch!='G'&&ch!='Q')
   {if(ch=='\n')
    {MAIN_SCAN();
	 if(WORK_STATUS==1)WORK_STATUS=2;
	  PROCESS_WINDOW_RESTLINE();
     if(DYNAMIC_WINDOW_MANAGEMENT)DYNAMIC_MANAGEMENT();
     if(PROGRAM_TIME%CYCLE==0)
	 {OUTPUT();
      system("pause"); 
      system("cls");
      LANGUAGE?puts("事件日志:"):puts("EVENT LOG:");
	 }
	}
    ch=fgetc(fPtr);
    if(feof(fPtr))break;
   }
   if(feof(fPtr))break;
   switch(ch)
   {case 'T':
   	 STATE=1;
   	 break;
   	 case 'G':
   	 STATE=3;
   	 break;
   	 case 'R':
   	 STATE=4;
   	 break;
   	 case 'Q':
   	 STATE=5;
   	 break;
   	 default:
   	 puts("INPUT ERROR");
   	 break;
   }
   break;
   case 3:
   ENTER_BUFFER_AREA();
   MAIN_SCAN();
   STATE=2;
   break;
   case 4:
   ch=fgetc(fPtr);
   if(ch-'0'<1||ch-'0'>NORMAL_WINDOW_NUMBER)puts("invaild window number");
   else  REST_REQUIREMENT(ch-'0'-1);
   STATE=2;
   break;
   case 5:
   ASK_FOR_QUIT();
   STATE=2;
   break;
   default:
   puts("INVAILD STATE");
   break; 
  }
 }
 while(1)
 {PROGRAM_TIME++;
  PROCESS_WINDOW_TIME();
  MAIN_SCAN();
  PROCESS_WINDOW_RESTLINE();
  if(PROGRAM_TIME%CYCLE==0)
	 {OUTPUT();
      system("pause");
      system("cls");
      LANGUAGE?puts("事件日志:"):puts("EVENT LOG:");
	 }
  if(CHECK_FOR_END())break;
 }
 LANGUAGE?puts("程序结束"):puts("END OF PROGRAM");
 system("pause");
 fclose(fPtr);
 fPtr=NULL;
 fclose(OUTPUT_DETAIL);
 OUTPUT_DETAIL=NULL;
 fclose(NORMAL_OUTPUT);
 NORMAL_OUTPUT=NULL;
 FREE_SPACE();
}
