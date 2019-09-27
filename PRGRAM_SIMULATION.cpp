#include "PROGRAM_BASIC_ACTION.h"
#include "PROGRAM_IO.h"
static int SIMULATION_MODE;
static double MAX; 
/*
模拟模式
0 正态分布 
1 泊松分布 
*/
static void CHOOSE_SIMULATION_MODE()/*确定模拟模式*/ 
{char ch;
 while(1)
 {LANGUAGE?puts("请确定模拟模式:"):puts("Please confirm stimulation mode:");
  LANGUAGE?puts("1--正态分布"):puts("1--Normal distribution");
  LANGUAGE?puts("2--泊松分布 "):puts("2--Poisson distribution");
  ch=getchar();
  while(ch!='1'&&ch!='2')ch=getchar();
  if(ch=='1')SIMULATION_MODE=0;
    else SIMULATION_MODE=1;
  LANGUAGE?printf("您选择的是:"):printf("You choose:");
 if(SIMULATION_MODE==0)LANGUAGE?puts("正态分布"):puts("Normal distribution");
   else LANGUAGE?puts("泊松分布"):puts("Poisson distribution");
 LANGUAGE?puts("请确认操作"):puts("Please confrim your action:");
 puts("<Y/N>");
 while(ch!='Y'&&ch!='N')ch=getchar();
 if(ch=='Y'){ch=getchar();break;}
   else continue;
 }
}

static void SET_SIMULATION_PEAK()/*设置模拟峰值*/ 
{char ch=' ';
 while(1)
 {LANGUAGE?puts("请输入模拟峰值:"):puts("Please input stimulation Peak value:");
  scanf("%lf",&MAX); 
  LANGUAGE?printf("将峰值改为%.0lf?\n",MAX):printf("Change the peak value to %.0lf?\n",MAX);
  puts("<Y/N>");
  while(ch!='Y'&&ch!='N')ch=getchar();
  if(ch=='Y'){ch=getchar();break;}
    else continue;
 }
}
static double CALCULATE_PARAMETER(int T)
{double sum=MAX*7.0*exp(-8.0);
 int i;
 for(i=1;i<=T;i++)
 sum*=8.0/(double)i;
 return sum;
}
void  OUTPUT_SIMULATION_FILE()/*输出模拟文件*/ 
{FILE* fp = NULL;
 int T;
 int i;
 srand( (unsigned int)time(0));
	fp=fopen("input.txt","w");
	if(SIMULATION_MODE==0)/*正态分布*/
	{double GUEST;
     int R;
		for(T=0;;T+=R)
		{/*printf("T=%d\n",T);*/
		 GUEST=MAX*exp((double)(-((double)T-30.0)*((double)T-30.0)/200.0));
		 /*printf("test=%.10lf GUEST=%.10lf\n",(double)(-(T-30.0)*(T-30.0)/200.0),GUEST);*/
			if(T>30&&GUEST<1.0)break;
			else
			{if(GUEST<1.0){R=rand()%2+1;continue;}
			 fprintf(fp,"T=%d,EVENT=",T);
			 for(i=(int)GUEST;i>1;i--){fprintf(fp,"G|");}
			 fprintf(fp,"G\n");
			} 
			R=rand()%2+1;
		}
	}
	else/*泊松分布*/
	{
	   double GUEST;
		for(T=0;;T++)
		{/*printf("T=%d GUEST=%.5lf\n",T,GUEST);*/
			GUEST=CALCULATE_PARAMETER(T);
			/*printf("test=%d GUEST=%.10lf\n",T,GUEST);*/
			if(T>7&&GUEST<1.0)break;
			else
			{if(GUEST<1.0)continue;
			 fprintf(fp,"T=%d,EVENT=",T);
			 for(i=(int)GUEST;i>1;i--)
				{
					fprintf(fp,"G|");
				}
				fprintf(fp,"G\n");
			}
		}
	}
	fclose(fp);
}
void INUPUT_BY_SIMULATION()
{CHOOSE_SIMULATION_MODE();
 /*
  选择 模拟模式
 */
 SET_SIMULATION_PEAK();
 /*
 设置模拟峰值 
 */ 
 OUTPUT_SIMULATION_FILE();
 /*
 输出模拟文件 
 */ 
 INPUT_BY_FILE();
 LANGUAGE?puts("模拟结束"):puts("End of simulation");
 system("pause"); 
}

