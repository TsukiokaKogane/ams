#include "PROGRAM_BASIC_ACTION.h"
#include "PROGRAM_CONFIGURATION.h"
#include<QLabel>
#include <QPropertyAnimation>
#include "PROGRAM_IO.h"
static int FIND_WINDOW()/*寻找空闲窗口*/
{int tempwindow/*暂时窗口号*/=-1,nowwindow/*当前窗口号*/;
	for(nowwindow=0;nowwindow<WINDOW_NUMBER;nowwindow++)/*0-7*/
	 {if(!DYNAMIC_WINDOW_MANAGEMENT&&nowwindow==NORMAL_WINDOW_NUMBER)break;
	  if(WINDOW_SET[nowwindow].winState!=1)continue;/*非服务状态 */
	  if(WINDOW_SET[nowwindow].lineLen==MAX_WAIT_LEN)continue;
	  if(tempwindow ==-1) {tempwindow = nowwindow;continue;}
	  if( SORT_MODE==0/*查找模式*/)
	   { if (WINDOW_SET[nowwindow].lineLen< WINDOW_SET[tempwindow].lineLen) tempwindow = nowwindow;/*找最短*/ 
	   }/*length first*/
	else
	 {if(WINDOW_SET[nowwindow].lineTime+(int)( (double)BUFFER_LINE_HEADPTR->arrive_time/WINDOW_SET[nowwindow].effciency)< 
	     WINDOW_SET[tempwindow].lineTime+(int)( (double)BUFFER_LINE_HEADPTR->arrive_time/WINDOW_SET[tempwindow].effciency))
    	tempwindow =nowwindow;
	 }/*effcincy first*/
	 } 
	 return tempwindow;
}
static void ENTER_WINDOW(int WIN_NUM)/*乘客进入窗口*/ 
{BUFFER_LINE_LEN--;/*缓冲区长度减1 */
 BUFFER_LINE_HEADPTR->arrive_time = (int)( (double)BUFFER_LINE_HEADPTR->arrive_time/WINDOW_SET[WIN_NUM].effciency);/*为缓冲区头乘客分配安检时间 */
 WINDOW_SET[WIN_NUM].lineTime+=BUFFER_LINE_HEADPTR->arrive_time ;/*更新全队出检时间 */
 if(WINDOW_SET[WIN_NUM].tailPtr!=NULL)
 {
   BUFFER_LINE_HEADPTR->previousPtr=WINDOW_SET[WIN_NUM].tailPtr;
  (WINDOW_SET[WIN_NUM].tailPtr)->nextPtr=BUFFER_LINE_HEADPTR;
 }
  else WINDOW_SET[WIN_NUM].headPtr=BUFFER_LINE_HEADPTR;
 WINDOW_SET[WIN_NUM].tailPtr=BUFFER_LINE_HEADPTR; /*缓冲区链表表头进入该安检口链表表尾；这个tail是窗口的*/
 WINDOW_SET[WIN_NUM].listState=1;
 /*
 printf("（乘客进入窗口）enterTime=%d WIN_NUM=%d PASSENGER_NUM=%d （安检理论时间）TIME=%d LineLen=%d CUSTIN\n",PROGRAM_TIME,WIN_NUM,BUFFER_LINE_HEADPTR->num,BUFFER_LINE_HEADPTR->arrive_time,BUFFER_LINE_LEN);
 */
 LANGUAGE?printf("编号为%d的乘客于%d进入窗口%d\n",BUFFER_LINE_HEADPTR->num,PROGRAM_TIME,WIN_NUM+1):
 printf("PASSENGER No.%d enter window %d at %d\n",BUFFER_LINE_HEADPTR->num,WIN_NUM+1,PROGRAM_TIME);
 LANGUAGE?fprintf(NORMAL_OUTPUT,"编号为%d的乘客于%d进入窗口%d\n",BUFFER_LINE_HEADPTR->num,PROGRAM_TIME,WIN_NUM+1):
 fprintf(NORMAL_OUTPUT,"PASSENGER No.%d enter window %d at %d\n",BUFFER_LINE_HEADPTR->num,WIN_NUM+1,PROGRAM_TIME);
 BUFFER_LINE_HEADPTR=BUFFER_LINE_HEADPTR->nextPtr;/*缓冲区链表节点前置；*/
  (WINDOW_SET[WIN_NUM].tailPtr)->nextPtr=NULL;
 if(INPUT_MODE==3)
  {(WINDOW_SET[WIN_NUM].tailPtr)->po.setX(20+105*WIN_NUM);
  (WINDOW_SET[WIN_NUM].tailPtr)->po.setY(290+50*WINDOW_SET[WIN_NUM].lineLen);

 QPropertyAnimation* m_pAnimation;
 m_pAnimation = new QPropertyAnimation(&(WINDOW_SET[WIN_NUM].tailPtr)->pic, "geometry");
 m_pAnimation->setDuration(1000);//设置移动时间
 m_pAnimation->setStartValue(QRectF(900,690,70,70));//开始位置
 m_pAnimation->setKeyValueAt(0.6,QRectF(20+105*WIN_NUM,690,70,70));//结束位置
// m_pAnimation->start();//开始移动

//m_pAnimation->setDuration(2000);//设置移动时间
// m_pAnimation->setStartValue(QRectF(20+105*WIN_NUM,690,70,70));//开始位置
 m_pAnimation->setEndValue(QRectF((WINDOW_SET[WIN_NUM].tailPtr)->po.x(),(WINDOW_SET[WIN_NUM].tailPtr)->po.y(),70,70));//结束位置
 //m_pAnimation->setEasingCurve(QEasingCurve::OutBounce);
 m_pAnimation->start();//开始移动
 }
 WINDOW_SET[WIN_NUM].lineLen++;/*安检口长度加1 */
 if(BUFFER_LINE_HEADPTR!=NULL)BUFFER_LINE_HEADPTR->previousPtr=NULL;
 if(INPUT_MODE!=3) return ;
 PASSENGER_DATA *tempPtr=BUFFER_LINE_HEADPTR;
 if(tempPtr==NULL)return;
 int i;
 for(i=1;i<=(BUFFER_LINE_LEN);++i)
 {
   //
     if(tempPtr==NULL)return;
     int line,row;
     row=((tempPtr->po.x()-900)/70)+1;
     line=((690-tempPtr->po.y())/70)+1;
     if(line%2==1)
     {
         if(row==1&&line>1)
             //往下移动
             {
                 QPropertyAnimation* m_pAnimation;
                 m_pAnimation = new QPropertyAnimation(&tempPtr->pic, "geometry");
                 m_pAnimation->setDuration(350);//设置移动时间
                 m_pAnimation->setStartValue(QRectF(tempPtr->po.x(),tempPtr->po.y(),70,70));//开始位置
                 m_pAnimation->setEndValue(QRectF(tempPtr->po.x(),tempPtr->po.y()+70,70,70));//结束位置
                 tempPtr->po.setY(tempPtr->po.y()+70);
                 m_pAnimation->start();//开始移动
             }
         else{

                 //往左移动此图片
                              {QPropertyAnimation* m_pAnimation;
                              m_pAnimation = new QPropertyAnimation(&tempPtr->pic, "geometry");
                              m_pAnimation->setDuration(350);//设置移动时间
                              m_pAnimation->setStartValue(QRectF(tempPtr->po.x(),tempPtr->po.y(),70,70));//开始位置
                              m_pAnimation->setEndValue(QRectF(tempPtr->po.x()-70,tempPtr->po.y(),70,70));//结束位置
                              tempPtr->po.setX(tempPtr->po.x()-70);
                              m_pAnimation->start();//开始移动

                              }

         }
     }
     else
     {
         if(row==MAX_CUSTSINGLE_LINE&&line>1)
             //往下移动
                 {
                     QPropertyAnimation* m_pAnimation;
                     m_pAnimation = new QPropertyAnimation(&tempPtr->pic, "geometry");
                     m_pAnimation->setDuration(350);//设置移动时间
                     m_pAnimation->setStartValue(QRectF(tempPtr->po.x(),tempPtr->po.y(),70,70));//开始位置
                     m_pAnimation->setEndValue(QRectF(tempPtr->po.x(),tempPtr->po.y()+70,70,70));//结束位置
                     tempPtr->po.setY(tempPtr->po.y()+70);
                     m_pAnimation->start();//开始移动
                   }
         else{
             //往右移动
                       { QPropertyAnimation* m_pAnimation;
                        m_pAnimation = new QPropertyAnimation(&tempPtr->pic, "geometry");
                        m_pAnimation->setDuration(350);//设置移动时间
                        m_pAnimation->setStartValue(QRectF(tempPtr->po.x(),tempPtr->po.y(),70,70));//开始位置
                        m_pAnimation->setEndValue(QRectF(tempPtr->po.x()+70,tempPtr->po.y(),70,70));//结束位置
                        tempPtr->po.setX(tempPtr->po.x()+70);
                        m_pAnimation->start();//开始移动
                        }
         }
     }

  tempPtr=tempPtr->nextPtr;
 }


} 
extern void PROCESS_WINDOW_TIME()/*处理安检口时间 +1s*/
{ int i;
  for(i=0;i<WINDOW_NUMBER;i++)
  {if(!DYNAMIC_WINDOW_MANAGEMENT&&i==NORMAL_WINDOW_NUMBER)break;
   if(WINDOW_SET[i].winState==0)/*一般窗口休息*/ 
	{WINDOW_SET[i].restLen++; 
	 WINDOW_SET[i].left_time--;
	 if(WORK_STATUS)
	 {WINDOW_SET[i].winState=4;
	  WINDOW_SET[i].left_time=WINDOW_SET[i].totrestLen=0;
	  continue;
	 }
	 if(WINDOW_SET[i].left_time==0)
	 {WINDOW_SET[i].winState=1;
	  WINDOW_SET[i].totrestLen=0;
	  WORK_WINDOW_NUM++;
	  if(i<NORMAL_WINDOW_NUMBER)NORMAL_WORK_WINDOW_NUM++;
	  /*
	  printf("（窗口重新开放）TIME=%d WindowNUM=%d\n",PROGRAM_TIME,i+1);
	  */
       WINDOW_SET[i].picnum=rand()%3;
      LANGUAGE?printf("编号为%d的窗口于%d 开放\n",i+1,PROGRAM_TIME):printf("WINDOW No.%d open at %d\n",i+1,PROGRAM_TIME);
      LANGUAGE?fprintf(NORMAL_OUTPUT,"编号为%d的窗口于%d 开放\n",i+1,PROGRAM_TIME):fprintf(NORMAL_OUTPUT,"WINDOW No.%d open at %d\n",i+1,PROGRAM_TIME);
	 }
	}
	else if(WINDOW_SET[i].winState==4)/*动态窗口休息*/ 
	{WINDOW_SET[i].restLen++;continue;}
	else
	{PASSENGER_DATA *tempPtr=WINDOW_SET[i].headPtr;
	 WINDOW_SET[i].servLen++;
 	 if(tempPtr!=NULL)
	  {WINDOW_SET[i].lineTime--;
	   tempPtr->arrive_time--;
	   if(tempPtr->arrive_time==0)
	   {WINDOW_SET[i].headPtr=(WINDOW_SET[i].headPtr)->nextPtr;
	    WINDOW_SET[i].lineLen--;
	     WINDOW_SET[i].listState=2;
	     /*
	    printf("（乘客离开窗口）leaveTime=%d WIN_NUM=%d PASSENGER_NUM=%d CUSTLEAVE\n",PROGRAM_TIME,i,tempPtr->num);
	    */
         tot_People_Num--;
	    LANGUAGE?printf("编号为%d的乘客于%d离开窗口%d\n",tempPtr->num,PROGRAM_TIME,i+1):
		printf("PASSENGER No.%d leave window %d at %d\n",tempPtr->num,i+1,PROGRAM_TIME);
		
	    LANGUAGE?fprintf(NORMAL_OUTPUT,"编号为%d的乘客于%d离开窗口%d\n",tempPtr->num,PROGRAM_TIME,i+1):
		fprintf(NORMAL_OUTPUT,"PASSENGER No.%d leave window %d at %d\n",tempPtr->num,i+1,PROGRAM_TIME);
       delete tempPtr;
        tempPtr=NULL;
        if(INPUT_MODE==3)

         { tempPtr=WINDOW_SET[i].headPtr;
            while(tempPtr!=NULL)
           {
                QPropertyAnimation* m_pAnimation;
                m_pAnimation = new QPropertyAnimation(&tempPtr->pic, "geometry");
                m_pAnimation->setDuration(350);//设置移动时间
                m_pAnimation->setStartValue(QRectF(tempPtr->po.x(),tempPtr->po.y(),70,70));//开始位置
                m_pAnimation->setEndValue(QRectF(tempPtr->po.x(),tempPtr->po.y()-50,70,70));//结束位置
                tempPtr->po.setY(tempPtr->po.y()-50);
                m_pAnimation->start();//开始移动
                tempPtr=tempPtr->nextPtr;

            }

         }
        }

       }
	  if(WINDOW_SET[i].headPtr==NULL)WINDOW_SET[i].tailPtr=NULL;
	 }
	 if(WORK_STATUS==2&&BUFFER_LINE_LEN==0&&WINDOW_SET[i].winState<=2&&WINDOW_SET[i].lineLen==0)
	 {WINDOW_SET[i].winState=4;
	  /*
	  printf("（窗口关闭）TIME=%d WindowNUM=%d rest_time=%d\n",PROGRAM_TIME,i,WINDOW_SET[i].left_time);
	  */
         WINDOW_SET[i].picnum=3;
	  LANGUAGE?printf("编号为%d的窗口于%d 关闭\n",i+1,PROGRAM_TIME):printf("WINDOW No.%d close at %d\n",i+1,PROGRAM_TIME);
	  LANGUAGE?fprintf(NORMAL_OUTPUT,"编号为%d的窗口于%d 关闭\n",i+1,PROGRAM_TIME):fprintf(NORMAL_OUTPUT,"WINDOW No.%d close at %d\n",i+1,PROGRAM_TIME);
	 }
	 if(WINDOW_SET[i].winState==2&&WINDOW_SET[i].lineTime==0)
	 {WINDOW_SET[i].winState=0;
	  WINDOW_SET[i].left_time=WINDOW_SET[i].totrestLen;
      WINDOW_SET[i].picnum=3;
	  /*
	  printf("（窗口关闭）TIME=%d WindowNUM=%d rest_time=%d\n",PROGRAM_TIME,i,WINDOW_SET[i].left_time);
	  */
	   LANGUAGE?printf("编号为%d的窗口于%d 关闭\n",i+1,PROGRAM_TIME):printf("WINDOW No.%d close at %d\n",i+1,PROGRAM_TIME);
	  LANGUAGE?fprintf(NORMAL_OUTPUT,"编号为%d的窗口于%d 关闭\n",i+1,PROGRAM_TIME):fprintf(NORMAL_OUTPUT,"WINDOW No.%d close at %d\n",i+1,PROGRAM_TIME);
	 }/*窗口休息 */
	 if(WINDOW_SET[i].winState==3&&WINDOW_SET[i].lineTime==0)
     {WINDOW_SET[i].winState=4;printf("（窗口关闭）TIME=%d WindowNUM=%d\n",PROGRAM_TIME,i);
         WINDOW_SET[i].picnum=3;
	   LANGUAGE?printf("编号为%d的窗口于%d 关闭\n",i+1,PROGRAM_TIME):printf("WINDOW No.%d close at %d\n",i+1,PROGRAM_TIME);
	  LANGUAGE?fprintf(NORMAL_OUTPUT,"编号为%d的窗口于%d 关闭\n",i+1,PROGRAM_TIME):fprintf(NORMAL_OUTPUT,"WINDOW No.%dclose at %d\n",i+1,PROGRAM_TIME);
	 }/*动态窗口关闭 */
	}
   }
void MAIN_SCAN()/*扫描 让乘客进入安检口*/
{ while(BUFFER_LINE_HEADPTR!=NULL)/*缓冲区头结点非空 */
 {BUFFER_LINE_HEADPTR->arrive_time=getTimeLen();
  int WIN_NUM/*空窗口号*/=FIND_WINDOW(); 
  /*指安检口的时间点*/
  if(WIN_NUM!=-1/*空窗口号有效*/)ENTER_WINDOW(WIN_NUM);
    else break;
 }
   return;
}
/*extern void output_restline()测试用 输出安检口休息队列
{WINDOWLINE_DATA *tmpPtr=WINDOW_RESTLINE_PTR;
 if(tmpPtr==NULL)return;
 while(tmpPtr->nextPtr!=NULL)
 {printf("%d->",tmpPtr->num);
 tmpPtr=tmpPtr->nextPtr;
 }
 printf("%d",tmpPtr->num);
 puts("");
}*/
void PROCESS_WINDOW_RESTLINE()/*处理安检口休息队列*/ 
{if(WINDOW_RESTLINE_PTR==NULL)return;
 if(WORK_STATUS==1||WORK_STATUS==2)return;
 while(WINDOW_RESTLINE_PTR!=NULL&&MAX_SEQUENCE_LENGTH*WORK_WINDOW_NUM>BUFFER_LINE_LEN)
 {WINDOWLINE_DATA *tmpPtr=WINDOW_RESTLINE_PTR;
  if(NORMAL_WORK_WINDOW_NUM==1)break;
  WINDOW_SET[WINDOW_RESTLINE_PTR->num].totrestLen=getRestTimeLen();
  if(WINDOW_SET[WINDOW_RESTLINE_PTR->num].lineLen==0)
  {WINDOW_SET[WINDOW_RESTLINE_PTR->num].winState=0;
   WINDOW_SET[WINDOW_RESTLINE_PTR->num].left_time=WINDOW_SET[WINDOW_RESTLINE_PTR->num].totrestLen;
   WINDOW_SET[WINDOW_RESTLINE_PTR->num].totrestLen=0;
   /*
   printf("（窗口关闭）TIME=%d WindowNUM=%d rest_time=%d\n",PROGRAM_TIME,WINDOW_RESTLINE_PTR->num,WINDOW_SET[WINDOW_RESTLINE_PTR->num].left_time);
   */
   WINDOW_SET[WINDOW_RESTLINE_PTR->num].picnum=3;
   LANGUAGE?printf("编号为%d的窗口于%d 休息\n",WINDOW_RESTLINE_PTR->num,PROGRAM_TIME):printf("WINDOW No.%d CLOSE AT %d\n",WINDOW_RESTLINE_PTR->num+1,PROGRAM_TIME);
  LANGUAGE?fprintf(NORMAL_OUTPUT,"编号为%d的窗口于%d 休息\n",WINDOW_RESTLINE_PTR->num,PROGRAM_TIME):fprintf(NORMAL_OUTPUT,"WINDOW No.%d CLOSE AT %d\n",WINDOW_RESTLINE_PTR->num+1,PROGRAM_TIME);
  }
    else
	{LANGUAGE?printf("编号为%d的窗口于%d 预备休息\n",WINDOW_RESTLINE_PTR->num,PROGRAM_TIME):printf("WINDOW No.%d PREPARED TO CLOSE AT %d\n",WINDOW_RESTLINE_PTR->num+1,PROGRAM_TIME);
     LANGUAGE?fprintf(NORMAL_OUTPUT,"编号为%d的窗口于%d 预备休息\n",WINDOW_RESTLINE_PTR->num,PROGRAM_TIME):fprintf(NORMAL_OUTPUT,"WINDOW No.%d PREPARED TO CLOSE AT %d\n",WINDOW_RESTLINE_PTR->num+1,PROGRAM_TIME);
	 WINDOW_SET[WINDOW_RESTLINE_PTR->num].winState=2;
	} 
  /*WINDOW_SET[WINDOW_RESTLINE_PTR->num].left_time=WINDOW_SET[WINDOW_RESTLINE_PTR->num].totrestLen;*/
  WORK_WINDOW_NUM--;
  if(tmpPtr->num<NORMAL_WINDOW_NUMBER)NORMAL_WORK_WINDOW_NUM--;
  WINDOW_RESTLINE_PTR=WINDOW_RESTLINE_PTR->nextPtr;
 delete tmpPtr;
 }
 return;
}

