#include "PROGRAM_BASIC_ACTION.h"
static void CHECK_FOR_SORT_MODE()/*改变排序模式*/
{char ch;
 while(1)
 {LANGUAGE?puts("请输入排序模式:"):puts("Please confirm sort mode:");
  LANGUAGE?puts("1--队伍长短"):puts("1--Line length");
  LANGUAGE?puts("2--效率"):puts("2--effciency");
  ch=getchar();
  while(ch!='1'&&ch!='2')ch=getchar();
  if(ch=='1')SORT_MODE=0;
    else SORT_MODE=1;
   LANGUAGE?puts("请确认操作"):puts("Please confrim your action:");
 if(SORT_MODE==0)LANGUAGE?puts("队伍长短优先"):puts("Line length first");
   else LANGUAGE?puts("效率优先"):puts("effciency first");
 puts("<Y/N>");
 while(ch!='Y'&&ch!='N')ch=getchar();
 if(ch=='Y'){ch=getchar();break;}
   else continue;
 }
}
static void CHECK_FOR_DYNAMIC_MANAGEMENT()/*修改动态窗口*/ 
{char ch; 
 while(1)
 {LANGUAGE?puts("您需要动态窗口开放吗?"):puts("Do you want to open the dynamic window?");
  puts("<Y/N>");
  ch=getchar();
   while(ch!='Y'&&ch!='N')ch=getchar();
   if(ch=='Y')DYNAMIC_WINDOW_MANAGEMENT=1;
     else DYNAMIC_WINDOW_MANAGEMENT=0;
  ch=getchar();
  LANGUAGE?printf("请确认操作:"):printf("Please confrim your action:");
  if(DYNAMIC_WINDOW_MANAGEMENT)LANGUAGE?puts("开放动态窗口"):puts("dynamic windows are opened");
    else LANGUAGE?puts("关闭动态窗口"):puts("dynamic windows are closed");
  puts("<Y/N>");
  while(ch!='Y'&&ch!='N')ch=getchar();
  if(ch=='Y'){ch=getchar();break;}
   else continue;
 }
}
static void INPUT_WINDOW_EFFCIENCY()/*输入窗口效率*/ 
{char ch;
 int i; 
 for(i=0;i<NORMAL_WINDOW_NUMBER;i++)
 {LANGUAGE?printf("您当前输入的是第%d号窗口的效率指数\n",i+1):printf("You are currently set the effciency index of window number %d\n",i+1);
  scanf("%lf",&WINDOW_SET[i].effciency);  
  ch=getchar();
  LANGUAGE?printf("请确认操作:"):printf("Please confrim your action:");
  LANGUAGE?printf("第%d号窗口的效率指数是: %.2lf\n",i+1,WINDOW_SET[i].effciency):printf("the effciency index of window number %d is: %.2lf\n",i+1,WINDOW_SET[i].effciency);
  puts("<Y/N>");
  while(ch!='Y'&&ch!='N')ch=getchar();
  if(ch=='N')i--;
 }
 if(DYNAMIC_WINDOW_MANAGEMENT==0)return;
 for(i=NORMAL_WINDOW_NUMBER;i<WINDOW_NUMBER;i++)
 {LANGUAGE?printf("您当前输入的是第%d号窗口的效率指数\n",i+1):printf("You are currently set the effciency index of window number %d\n",i+1);
  scanf("%lf",&WINDOW_SET[i].effciency);  
  ch=getchar();
  LANGUAGE?printf("请确认操作:"):printf("Please confrim your action:");
  LANGUAGE?printf("第%d号窗口的效率指数是: %.2lf\n",i+1,WINDOW_SET[i].effciency):printf("the effciency index of window number %d is: %.2lf\n",i+1,WINDOW_SET[i].effciency);
  puts("<Y/N>");
  while(ch!='Y'&&ch!='N')ch=getchar();
  if(ch=='N')i--;
 }
}
extern void OUTPUT_ADVANCED_SETTING()/*输出高级设定*/
{LANGUAGE?puts("当前高级设定状态:"):puts("current advanced settings:"); 
 LANGUAGE?printf("当前动态窗口状态:"):printf("current dynamic window state:");
 if(DYNAMIC_WINDOW_MANAGEMENT){LANGUAGE?puts("开放"):puts("opened");}
    else LANGUAGE?puts("关闭"):puts("closed");
  LANGUAGE?printf("当前排序模式:"):printf("current sort mode:");
  if(SORT_MODE==0)LANGUAGE?puts("队伍长短优先"):puts("Line length first");
   else 
   {LANGUAGE?puts("效率优先"):puts("effciency first");
   int i;
    for(i=0;i<NORMAL_WINDOW_NUMBER;i++)LANGUAGE?printf("第%d号窗口的效率指数是: %.2lf\n",i+1,WINDOW_SET[i].effciency):printf("the effciency index of window number %d is: %.2lf\n",i+1,WINDOW_SET[i].effciency);
    if(DYNAMIC_WINDOW_MANAGEMENT)
   {for(i=NORMAL_WINDOW_NUMBER;i<WINDOW_NUMBER;i++)LANGUAGE?printf("第%d号窗口的效率指数是: %.2lf\n",i+1,WINDOW_SET[i].effciency):printf("the effciency index of window number %d is: %.2lf\n",i+1,WINDOW_SET[i].effciency);
    }
  }
  LANGUAGE?printf("当前刷新率:%d\n",CYCLE):printf("current refreshing rate:%d\n",CYCLE);
}
extern void MODIFY_ADVANCED_SETTING()/*修改高级设定*/
{char ch;
 LANGUAGE?puts("您要修改高级设置吗?"):puts("Do you want to change the advanced settings?");
  puts("<Y/N>");
  ch=getchar();
  while(ch!='Y'&&ch!='N')ch=getchar();
  if(ch=='N')return;
  CHECK_FOR_DYNAMIC_MANAGEMENT();
  LANGUAGE?puts("您要修改排序模式吗?"):puts("Do you want to change the sort mode?");
  puts("<Y/N>");
  ch=getchar();
  while(ch!='Y'&&ch!='N')ch=getchar();
  if(ch=='Y')CHECK_FOR_SORT_MODE();
  if(SORT_MODE)INPUT_WINDOW_EFFCIENCY();
    else 
    {int i;
      for(i=0;i<NORMAL_WINDOW_NUMBER;i++)WINDOW_SET[i].effciency=1.0;
      if(DYNAMIC_WINDOW_MANAGEMENT)
      {for(i=NORMAL_WINDOW_NUMBER;i<WINDOW_NUMBER;i++)WINDOW_SET[i].effciency=1.0;
	  }
	}
 LANGUAGE?puts("您要修改刷新率吗?(范围1-9)"):puts("Do you want to change the refreshing rate? (range from 1-9)");
 puts("<Y/N>");
 ch=getchar();
 while(ch!='Y'&&ch!='N')ch=getchar();
 if(ch=='Y')
 {LANGUAGE?puts("注意范围：1-9"):puts("attention: the range is from 1-9");
  while(ch<'1'||ch>'9')ch=getchar();
  CYCLE=ch-'0';
 }
 OUTPUT_ADVANCED_SETTING();
}
extern void output_configuration_data()/*输出配置信息*/
{FILE *fPtr=CONFIG_FILE;
 CONFIGURATION_DATA current;
 LANGUAGE?puts("当前配置数据:"):puts("current configuration data:");
 int i;
 for(i=0;i<CONFIGURATION_LENGTH;i++)
 {fseek(fPtr,i*sizeof(CONFIGURATION_DATA),SEEK_SET);
  fread(&current,sizeof(CONFIGURATION_DATA),1,fPtr);
  printf("%s %d",current.name,current.data);
  if(i>2)printf(" minute(s)\n");
    else puts("");
 }
}
extern void output_window_data()/*输出窗口信息*/
{int i;
 for(i=0;i<WINDOW_NUMBER;i++)
 {LANGUAGE?printf("窗口号"):printf("window's serial number:");
  printf("%d\n",i+1);
  printf("winState=%d\n",WINDOW_SET[i].winState);
  printf("left_time=%d\n",WINDOW_SET[i].left_time);
  printf("restLen=%d\n",WINDOW_SET[i].restLen);
  printf("servLen=%d\n",WINDOW_SET[i].servLen);
  printf("lineLen=%d\n",WINDOW_SET[i].lineLen);
  printf("lineTime=%d\n",WINDOW_SET[i].lineLen);
  printf("effciency=%.2lf\n",WINDOW_SET[i].effciency);
 }
}
void WINDOW_INITIALIZATION()/*窗口初始化*/
{int i;
 WINDOW_SET=(WINDOW_DATA*)malloc(sizeof(WINDOW_DATA)*WINDOW_NUMBER);
 WORK_WINDOW_NUM=4;
 for(i=0;i<WINDOW_NUMBER;i++)
 {WINDOW_SET[i].winState=0;
  WINDOW_SET[i].left_time=0;
  WINDOW_SET[i].totrestLen=0;
  WINDOW_SET[i].restLen=0;
  WINDOW_SET[i].servLen=0;
  WINDOW_SET[i].lineLen=0;
  WINDOW_SET[i].lineTime=0;
  WINDOW_SET[i].effciency=1.0;
  WINDOW_SET[i].headPtr=NULL;
  WINDOW_SET[i].tailPtr=NULL;

 }
  for(i=0;i<NORMAL_WINDOW_NUMBER;i++)
  {WINDOW_SET[i].winState=1;
   WINDOW_SET[i].picnum=rand()%3;
  }
  for(i=NORMAL_WINDOW_NUMBER;i<WINDOW_NUMBER;i++)
  {WINDOW_SET[i].winState=4;
  WINDOW_SET[i].picnum=3;
  }
  /*output_window_data();*/
} 
extern void CONFIGURATION_INITIALIZATION()/*配置文件初始化*/
{FILE *fPtr=CONFIG_FILE;
 if(CONFIG_FILE==NULL){LANGUAGE?puts("无法生成配置文件 请退出并重新运行程序:("):puts("can not create confiuration file Please exit and restart the program :(");return;} 
 CONFIGURATION_DATA emptydata;
 strcpy(emptydata.name,"MaxCustSingleLine");
 emptydata.data=10;
 fseek(fPtr,0,SEEK_SET);
 fwrite(&emptydata,sizeof(CONFIGURATION_DATA),1,fPtr);

 strcpy(emptydata.name,"MaxLines");
 emptydata.data=5;
 fseek(fPtr,1*sizeof(CONFIGURATION_DATA),SEEK_SET);
 fwrite(&emptydata,sizeof(CONFIGURATION_DATA),1,fPtr);
 
 strcpy(emptydata.name,"MaxSeqLen");
 emptydata.data=10;
 fseek(fPtr,2*sizeof(CONFIGURATION_DATA),SEEK_SET);
 fwrite(&emptydata,sizeof(CONFIGURATION_DATA),1,fPtr);
 
 strcpy(emptydata.name,"MinTimeLen");
 emptydata.data=5;
 fseek(fPtr,3*sizeof(CONFIGURATION_DATA),SEEK_SET);
 fwrite(&emptydata,sizeof(CONFIGURATION_DATA),1,fPtr);
 
 strcpy(emptydata.name,"MaxTimeLen");
 emptydata.data=5;
 fseek(fPtr,4*sizeof(CONFIGURATION_DATA),SEEK_SET);
 fwrite(&emptydata,sizeof(CONFIGURATION_DATA),1,fPtr);

 strcpy(emptydata.name,"MinRestTimeLen");
 emptydata.data=20;
 fseek(fPtr,5*sizeof(CONFIGURATION_DATA),SEEK_SET);
 fwrite(&emptydata,sizeof(CONFIGURATION_DATA),1,fPtr);
 strcpy(emptydata.name,"MaxRestTimeLen");
 emptydata.data=20;
 fseek(fPtr,6*sizeof(CONFIGURATION_DATA),SEEK_SET);
 fwrite(&emptydata,sizeof(CONFIGURATION_DATA),1,fPtr);
}
static void getMaxCustSingleLine()
{FILE *fPtr=CONFIG_FILE;
 CONFIGURATION_DATA current;
 fseek(fPtr,0*sizeof(CONFIGURATION_DATA),SEEK_SET);
 fread(&current,sizeof(CONFIGURATION_DATA),1,fPtr);
 MAX_CUSTSINGLE_LINE=current.data;
}
static void getMaxLines()
{FILE *fPtr=CONFIG_FILE;
 CONFIGURATION_DATA current;
 fseek(fPtr,1*sizeof(CONFIGURATION_DATA),SEEK_SET);
 fread(&current,sizeof(CONFIGURATION_DATA),1,fPtr);
 MAX_LINES=current.data;
}
static void getMaxLinelen(){MAX_BUFFERLINE_LENGTH=MAX_LINES*MAX_CUSTSINGLE_LINE;return;}
static void getMaxSeqLen()
{FILE *fPtr=CONFIG_FILE;
 CONFIGURATION_DATA current;
 fseek(fPtr,2*sizeof(CONFIGURATION_DATA),SEEK_SET);
 fread(&current,sizeof(CONFIGURATION_DATA),1,fPtr);
 MAX_SEQUENCE_LENGTH=current.data;
}
extern void getBasicData()
{getMaxCustSingleLine();
 getMaxLines();
 getMaxLinelen();
 getMaxSeqLen();
}
static int getMinTimeLen()
{FILE *fPtr=CONFIG_FILE;
 CONFIGURATION_DATA current;
 fseek(fPtr,3*sizeof(CONFIGURATION_DATA),SEEK_SET);
 fread(&current,sizeof(CONFIGURATION_DATA),1,fPtr);
 return current.data;
}
static int getMaxTimeLen()
{FILE *fPtr=CONFIG_FILE;
 CONFIGURATION_DATA current;
 fseek(fPtr,4*sizeof(CONFIGURATION_DATA),SEEK_SET);
 fread(&current,sizeof(CONFIGURATION_DATA),1,fPtr);
 return current.data;
}
static int getMinRestTimeLen()
{FILE *fPtr=CONFIG_FILE;
 CONFIGURATION_DATA current;
 fseek(fPtr,5*sizeof(CONFIGURATION_DATA),SEEK_SET);
 fread(&current,sizeof(CONFIGURATION_DATA),1,fPtr);
 return current.data;
}
static int getMaxRestTimeLen()
{FILE *fPtr=CONFIG_FILE;
 CONFIGURATION_DATA current;
 fseek(fPtr,6*sizeof(CONFIGURATION_DATA),SEEK_SET);
 fread(&current,sizeof(CONFIGURATION_DATA),1,fPtr);
 return current.data;
}
extern int getTimeLen()/*得到乘客时间*/
{int minTimeLen=getMinTimeLen();
 /*if(INPUT_MODE)minTimeLen*=60;*/
 int maxTimeLen=getMaxTimeLen();
 /* if(INPUT_MODE)maxTimeLen*=60;*/
 if(minTimeLen==maxTimeLen)return maxTimeLen;
 return minTimeLen+rand()%(maxTimeLen-minTimeLen);
}
extern int getRestTimeLen()/*得到窗口休息时间*/
{int minTimeLen=getMinRestTimeLen();
 /*if(INPUT_MODE)minTimeLen*=60;*/
 int maxTimeLen=getMaxRestTimeLen();
  /*if(INPUT_MODE)maxTimeLen*=60;*/
 /*printf("2=%d %d\n",minTimeLen,maxTimeLen);*/
 if(minTimeLen==maxTimeLen)return maxTimeLen;
 return minTimeLen+rand()%(maxTimeLen-minTimeLen);
}
static int CHECK_MODOFIED_CONFIGURATION()/*检查逻辑*/ 
{if(getMinRestTimeLen()>getMaxRestTimeLen())return 0;
 if(getMinTimeLen()>getMaxTimeLen())return 0;
 return 1;
}
extern void MODIFY_CONFIGURATION()/*修改配置文件*/
{FILE *fPtr=CONFIG_FILE;
 CONFIGURATION_DATA current;
 int i;
 for(i=0;i<CONFIGURATION_LENGTH;i++)
 {char ch='0';
  fseek(fPtr,i*sizeof(CONFIGURATION_DATA),SEEK_SET);
  fread(&current,sizeof(CONFIGURATION_DATA),1,fPtr);
  if(LANGUAGE)
  {printf("你要改变");
   printf(" %s ",current.name);
   puts("吗?(换行跳过，输入数字修改)");
  }
   else 
   {printf("Do you want to change");
    printf(" %s ",current.name);
    puts("?(press enter to skip,input number to change)");
   }
   ch=getchar();
   while((ch<'0'||ch>'9')&&ch!='\n')ch=getchar();
   if(ch=='\n')continue;
   current.data=0;
   while('0'<=ch&&ch<='9'){current.data=current.data*10+ch-'0';ch=getchar();}
   fseek(fPtr,i*sizeof(CONFIGURATION_DATA),SEEK_SET);
   fwrite(&current,sizeof(CONFIGURATION_DATA),1,fPtr);
   printf(" %s ",current.name);
   LANGUAGE?printf("修改为 "):printf("is modified to ");
   printf("%d",current.data);
   if(i>2)printf(" minute(s)\n");
     else puts("");
 }
 if(CHECK_MODOFIED_CONFIGURATION()==0)
 {LANGUAGE?puts("您输入的配置文件有逻辑错误 请重新输入:("):puts("The configuration data you input has logic error plese input again:(");
  MODIFY_CONFIGURATION();
 }
 else
 {output_configuration_data();
  system("pause");
  return;
 } 
 
}
