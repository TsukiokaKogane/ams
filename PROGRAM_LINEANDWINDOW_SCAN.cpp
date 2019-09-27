#include "PROGRAM_BASIC_ACTION.h"
#include "PROGRAM_CONFIGURATION.h"
#include<QLabel>
#include <QPropertyAnimation>
#include "PROGRAM_IO.h"
static int FIND_WINDOW()/*Ѱ�ҿ��д���*/
{int tempwindow/*��ʱ���ں�*/=-1,nowwindow/*��ǰ���ں�*/;
	for(nowwindow=0;nowwindow<WINDOW_NUMBER;nowwindow++)/*0-7*/
	 {if(!DYNAMIC_WINDOW_MANAGEMENT&&nowwindow==NORMAL_WINDOW_NUMBER)break;
	  if(WINDOW_SET[nowwindow].winState!=1)continue;/*�Ƿ���״̬ */
	  if(WINDOW_SET[nowwindow].lineLen==MAX_WAIT_LEN)continue;
	  if(tempwindow ==-1) {tempwindow = nowwindow;continue;}
	  if( SORT_MODE==0/*����ģʽ*/)
	   { if (WINDOW_SET[nowwindow].lineLen< WINDOW_SET[tempwindow].lineLen) tempwindow = nowwindow;/*�����*/ 
	   }/*length first*/
	else
	 {if(WINDOW_SET[nowwindow].lineTime+(int)( (double)BUFFER_LINE_HEADPTR->arrive_time/WINDOW_SET[nowwindow].effciency)< 
	     WINDOW_SET[tempwindow].lineTime+(int)( (double)BUFFER_LINE_HEADPTR->arrive_time/WINDOW_SET[tempwindow].effciency))
    	tempwindow =nowwindow;
	 }/*effcincy first*/
	 } 
	 return tempwindow;
}
static void ENTER_WINDOW(int WIN_NUM)/*�˿ͽ��봰��*/ 
{BUFFER_LINE_LEN--;/*���������ȼ�1 */
 BUFFER_LINE_HEADPTR->arrive_time = (int)( (double)BUFFER_LINE_HEADPTR->arrive_time/WINDOW_SET[WIN_NUM].effciency);/*Ϊ������ͷ�˿ͷ��䰲��ʱ�� */
 WINDOW_SET[WIN_NUM].lineTime+=BUFFER_LINE_HEADPTR->arrive_time ;/*����ȫ�ӳ���ʱ�� */
 if(WINDOW_SET[WIN_NUM].tailPtr!=NULL)
 {
   BUFFER_LINE_HEADPTR->previousPtr=WINDOW_SET[WIN_NUM].tailPtr;
  (WINDOW_SET[WIN_NUM].tailPtr)->nextPtr=BUFFER_LINE_HEADPTR;
 }
  else WINDOW_SET[WIN_NUM].headPtr=BUFFER_LINE_HEADPTR;
 WINDOW_SET[WIN_NUM].tailPtr=BUFFER_LINE_HEADPTR; /*�����������ͷ����ð���������β�����tail�Ǵ��ڵ�*/
 WINDOW_SET[WIN_NUM].listState=1;
 /*
 printf("���˿ͽ��봰�ڣ�enterTime=%d WIN_NUM=%d PASSENGER_NUM=%d ����������ʱ�䣩TIME=%d LineLen=%d CUSTIN\n",PROGRAM_TIME,WIN_NUM,BUFFER_LINE_HEADPTR->num,BUFFER_LINE_HEADPTR->arrive_time,BUFFER_LINE_LEN);
 */
 LANGUAGE?printf("���Ϊ%d�ĳ˿���%d���봰��%d\n",BUFFER_LINE_HEADPTR->num,PROGRAM_TIME,WIN_NUM+1):
 printf("PASSENGER No.%d enter window %d at %d\n",BUFFER_LINE_HEADPTR->num,WIN_NUM+1,PROGRAM_TIME);
 LANGUAGE?fprintf(NORMAL_OUTPUT,"���Ϊ%d�ĳ˿���%d���봰��%d\n",BUFFER_LINE_HEADPTR->num,PROGRAM_TIME,WIN_NUM+1):
 fprintf(NORMAL_OUTPUT,"PASSENGER No.%d enter window %d at %d\n",BUFFER_LINE_HEADPTR->num,WIN_NUM+1,PROGRAM_TIME);
 BUFFER_LINE_HEADPTR=BUFFER_LINE_HEADPTR->nextPtr;/*����������ڵ�ǰ�ã�*/
  (WINDOW_SET[WIN_NUM].tailPtr)->nextPtr=NULL;
 if(INPUT_MODE==3)
  {(WINDOW_SET[WIN_NUM].tailPtr)->po.setX(20+105*WIN_NUM);
  (WINDOW_SET[WIN_NUM].tailPtr)->po.setY(290+50*WINDOW_SET[WIN_NUM].lineLen);

 QPropertyAnimation* m_pAnimation;
 m_pAnimation = new QPropertyAnimation(&(WINDOW_SET[WIN_NUM].tailPtr)->pic, "geometry");
 m_pAnimation->setDuration(1000);//�����ƶ�ʱ��
 m_pAnimation->setStartValue(QRectF(900,690,70,70));//��ʼλ��
 m_pAnimation->setKeyValueAt(0.6,QRectF(20+105*WIN_NUM,690,70,70));//����λ��
// m_pAnimation->start();//��ʼ�ƶ�

//m_pAnimation->setDuration(2000);//�����ƶ�ʱ��
// m_pAnimation->setStartValue(QRectF(20+105*WIN_NUM,690,70,70));//��ʼλ��
 m_pAnimation->setEndValue(QRectF((WINDOW_SET[WIN_NUM].tailPtr)->po.x(),(WINDOW_SET[WIN_NUM].tailPtr)->po.y(),70,70));//����λ��
 //m_pAnimation->setEasingCurve(QEasingCurve::OutBounce);
 m_pAnimation->start();//��ʼ�ƶ�
 }
 WINDOW_SET[WIN_NUM].lineLen++;/*����ڳ��ȼ�1 */
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
             //�����ƶ�
             {
                 QPropertyAnimation* m_pAnimation;
                 m_pAnimation = new QPropertyAnimation(&tempPtr->pic, "geometry");
                 m_pAnimation->setDuration(350);//�����ƶ�ʱ��
                 m_pAnimation->setStartValue(QRectF(tempPtr->po.x(),tempPtr->po.y(),70,70));//��ʼλ��
                 m_pAnimation->setEndValue(QRectF(tempPtr->po.x(),tempPtr->po.y()+70,70,70));//����λ��
                 tempPtr->po.setY(tempPtr->po.y()+70);
                 m_pAnimation->start();//��ʼ�ƶ�
             }
         else{

                 //�����ƶ���ͼƬ
                              {QPropertyAnimation* m_pAnimation;
                              m_pAnimation = new QPropertyAnimation(&tempPtr->pic, "geometry");
                              m_pAnimation->setDuration(350);//�����ƶ�ʱ��
                              m_pAnimation->setStartValue(QRectF(tempPtr->po.x(),tempPtr->po.y(),70,70));//��ʼλ��
                              m_pAnimation->setEndValue(QRectF(tempPtr->po.x()-70,tempPtr->po.y(),70,70));//����λ��
                              tempPtr->po.setX(tempPtr->po.x()-70);
                              m_pAnimation->start();//��ʼ�ƶ�

                              }

         }
     }
     else
     {
         if(row==MAX_CUSTSINGLE_LINE&&line>1)
             //�����ƶ�
                 {
                     QPropertyAnimation* m_pAnimation;
                     m_pAnimation = new QPropertyAnimation(&tempPtr->pic, "geometry");
                     m_pAnimation->setDuration(350);//�����ƶ�ʱ��
                     m_pAnimation->setStartValue(QRectF(tempPtr->po.x(),tempPtr->po.y(),70,70));//��ʼλ��
                     m_pAnimation->setEndValue(QRectF(tempPtr->po.x(),tempPtr->po.y()+70,70,70));//����λ��
                     tempPtr->po.setY(tempPtr->po.y()+70);
                     m_pAnimation->start();//��ʼ�ƶ�
                   }
         else{
             //�����ƶ�
                       { QPropertyAnimation* m_pAnimation;
                        m_pAnimation = new QPropertyAnimation(&tempPtr->pic, "geometry");
                        m_pAnimation->setDuration(350);//�����ƶ�ʱ��
                        m_pAnimation->setStartValue(QRectF(tempPtr->po.x(),tempPtr->po.y(),70,70));//��ʼλ��
                        m_pAnimation->setEndValue(QRectF(tempPtr->po.x()+70,tempPtr->po.y(),70,70));//����λ��
                        tempPtr->po.setX(tempPtr->po.x()+70);
                        m_pAnimation->start();//��ʼ�ƶ�
                        }
         }
     }

  tempPtr=tempPtr->nextPtr;
 }


} 
extern void PROCESS_WINDOW_TIME()/*�������ʱ�� +1s*/
{ int i;
  for(i=0;i<WINDOW_NUMBER;i++)
  {if(!DYNAMIC_WINDOW_MANAGEMENT&&i==NORMAL_WINDOW_NUMBER)break;
   if(WINDOW_SET[i].winState==0)/*һ�㴰����Ϣ*/ 
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
	  printf("���������¿��ţ�TIME=%d WindowNUM=%d\n",PROGRAM_TIME,i+1);
	  */
       WINDOW_SET[i].picnum=rand()%3;
      LANGUAGE?printf("���Ϊ%d�Ĵ�����%d ����\n",i+1,PROGRAM_TIME):printf("WINDOW No.%d open at %d\n",i+1,PROGRAM_TIME);
      LANGUAGE?fprintf(NORMAL_OUTPUT,"���Ϊ%d�Ĵ�����%d ����\n",i+1,PROGRAM_TIME):fprintf(NORMAL_OUTPUT,"WINDOW No.%d open at %d\n",i+1,PROGRAM_TIME);
	 }
	}
	else if(WINDOW_SET[i].winState==4)/*��̬������Ϣ*/ 
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
	    printf("���˿��뿪���ڣ�leaveTime=%d WIN_NUM=%d PASSENGER_NUM=%d CUSTLEAVE\n",PROGRAM_TIME,i,tempPtr->num);
	    */
         tot_People_Num--;
	    LANGUAGE?printf("���Ϊ%d�ĳ˿���%d�뿪����%d\n",tempPtr->num,PROGRAM_TIME,i+1):
		printf("PASSENGER No.%d leave window %d at %d\n",tempPtr->num,i+1,PROGRAM_TIME);
		
	    LANGUAGE?fprintf(NORMAL_OUTPUT,"���Ϊ%d�ĳ˿���%d�뿪����%d\n",tempPtr->num,PROGRAM_TIME,i+1):
		fprintf(NORMAL_OUTPUT,"PASSENGER No.%d leave window %d at %d\n",tempPtr->num,i+1,PROGRAM_TIME);
       delete tempPtr;
        tempPtr=NULL;
        if(INPUT_MODE==3)

         { tempPtr=WINDOW_SET[i].headPtr;
            while(tempPtr!=NULL)
           {
                QPropertyAnimation* m_pAnimation;
                m_pAnimation = new QPropertyAnimation(&tempPtr->pic, "geometry");
                m_pAnimation->setDuration(350);//�����ƶ�ʱ��
                m_pAnimation->setStartValue(QRectF(tempPtr->po.x(),tempPtr->po.y(),70,70));//��ʼλ��
                m_pAnimation->setEndValue(QRectF(tempPtr->po.x(),tempPtr->po.y()-50,70,70));//����λ��
                tempPtr->po.setY(tempPtr->po.y()-50);
                m_pAnimation->start();//��ʼ�ƶ�
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
	  printf("�����ڹرգ�TIME=%d WindowNUM=%d rest_time=%d\n",PROGRAM_TIME,i,WINDOW_SET[i].left_time);
	  */
         WINDOW_SET[i].picnum=3;
	  LANGUAGE?printf("���Ϊ%d�Ĵ�����%d �ر�\n",i+1,PROGRAM_TIME):printf("WINDOW No.%d close at %d\n",i+1,PROGRAM_TIME);
	  LANGUAGE?fprintf(NORMAL_OUTPUT,"���Ϊ%d�Ĵ�����%d �ر�\n",i+1,PROGRAM_TIME):fprintf(NORMAL_OUTPUT,"WINDOW No.%d close at %d\n",i+1,PROGRAM_TIME);
	 }
	 if(WINDOW_SET[i].winState==2&&WINDOW_SET[i].lineTime==0)
	 {WINDOW_SET[i].winState=0;
	  WINDOW_SET[i].left_time=WINDOW_SET[i].totrestLen;
      WINDOW_SET[i].picnum=3;
	  /*
	  printf("�����ڹرգ�TIME=%d WindowNUM=%d rest_time=%d\n",PROGRAM_TIME,i,WINDOW_SET[i].left_time);
	  */
	   LANGUAGE?printf("���Ϊ%d�Ĵ�����%d �ر�\n",i+1,PROGRAM_TIME):printf("WINDOW No.%d close at %d\n",i+1,PROGRAM_TIME);
	  LANGUAGE?fprintf(NORMAL_OUTPUT,"���Ϊ%d�Ĵ�����%d �ر�\n",i+1,PROGRAM_TIME):fprintf(NORMAL_OUTPUT,"WINDOW No.%d close at %d\n",i+1,PROGRAM_TIME);
	 }/*������Ϣ */
	 if(WINDOW_SET[i].winState==3&&WINDOW_SET[i].lineTime==0)
     {WINDOW_SET[i].winState=4;printf("�����ڹرգ�TIME=%d WindowNUM=%d\n",PROGRAM_TIME,i);
         WINDOW_SET[i].picnum=3;
	   LANGUAGE?printf("���Ϊ%d�Ĵ�����%d �ر�\n",i+1,PROGRAM_TIME):printf("WINDOW No.%d close at %d\n",i+1,PROGRAM_TIME);
	  LANGUAGE?fprintf(NORMAL_OUTPUT,"���Ϊ%d�Ĵ�����%d �ر�\n",i+1,PROGRAM_TIME):fprintf(NORMAL_OUTPUT,"WINDOW No.%dclose at %d\n",i+1,PROGRAM_TIME);
	 }/*��̬���ڹر� */
	}
   }
void MAIN_SCAN()/*ɨ�� �ó˿ͽ��밲���*/
{ while(BUFFER_LINE_HEADPTR!=NULL)/*������ͷ���ǿ� */
 {BUFFER_LINE_HEADPTR->arrive_time=getTimeLen();
  int WIN_NUM/*�մ��ں�*/=FIND_WINDOW(); 
  /*ָ����ڵ�ʱ���*/
  if(WIN_NUM!=-1/*�մ��ں���Ч*/)ENTER_WINDOW(WIN_NUM);
    else break;
 }
   return;
}
/*extern void output_restline()������ ����������Ϣ����
{WINDOWLINE_DATA *tmpPtr=WINDOW_RESTLINE_PTR;
 if(tmpPtr==NULL)return;
 while(tmpPtr->nextPtr!=NULL)
 {printf("%d->",tmpPtr->num);
 tmpPtr=tmpPtr->nextPtr;
 }
 printf("%d",tmpPtr->num);
 puts("");
}*/
void PROCESS_WINDOW_RESTLINE()/*���������Ϣ����*/ 
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
   printf("�����ڹرգ�TIME=%d WindowNUM=%d rest_time=%d\n",PROGRAM_TIME,WINDOW_RESTLINE_PTR->num,WINDOW_SET[WINDOW_RESTLINE_PTR->num].left_time);
   */
   WINDOW_SET[WINDOW_RESTLINE_PTR->num].picnum=3;
   LANGUAGE?printf("���Ϊ%d�Ĵ�����%d ��Ϣ\n",WINDOW_RESTLINE_PTR->num,PROGRAM_TIME):printf("WINDOW No.%d CLOSE AT %d\n",WINDOW_RESTLINE_PTR->num+1,PROGRAM_TIME);
  LANGUAGE?fprintf(NORMAL_OUTPUT,"���Ϊ%d�Ĵ�����%d ��Ϣ\n",WINDOW_RESTLINE_PTR->num,PROGRAM_TIME):fprintf(NORMAL_OUTPUT,"WINDOW No.%d CLOSE AT %d\n",WINDOW_RESTLINE_PTR->num+1,PROGRAM_TIME);
  }
    else
	{LANGUAGE?printf("���Ϊ%d�Ĵ�����%d Ԥ����Ϣ\n",WINDOW_RESTLINE_PTR->num,PROGRAM_TIME):printf("WINDOW No.%d PREPARED TO CLOSE AT %d\n",WINDOW_RESTLINE_PTR->num+1,PROGRAM_TIME);
     LANGUAGE?fprintf(NORMAL_OUTPUT,"���Ϊ%d�Ĵ�����%d Ԥ����Ϣ\n",WINDOW_RESTLINE_PTR->num,PROGRAM_TIME):fprintf(NORMAL_OUTPUT,"WINDOW No.%d PREPARED TO CLOSE AT %d\n",WINDOW_RESTLINE_PTR->num+1,PROGRAM_TIME);
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

