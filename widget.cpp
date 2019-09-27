#include "widget.h"
#include "ui_widget.h"
#include "qwidget.h"
#include "QTimer"
#include "QPainter"
#include "PROGRAM_BASIC_ACTION.h"
#include "PROGRAM_MAIN_PROCESS.h"
#include "PROGRAM_LINEANDWINDOW_SCAN.h"
#include "PROGRAM_IO.h"
#include "QPushButton"
#include "QString"
#include "QMovie"
QString fileroute[]={"../airport/material/NEXT1.jpg","../airport/material/NEXT2.jpg","../airport/material/NEXT3.jpg","../airport/material/NEXT4.png"};
 Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{ ui->setupUi(this);
 ui->exitButton->setGeometry(250,720,99,33);
 ui->newPButton->setGeometry(10,720,99,33);
 ui->offButton->setGeometry(130,720,99,33);
 ui->rest1Button->setGeometry(10,210,92,30);
 ui->rest2Button->setGeometry(115,210,92,30);
 ui->rest3Button->setGeometry(220,210,92,30);
 ui->rest4Button->setGeometry(322,210,92,30);
 emptyButton=new QPushButton*[8];
 for(int i=0;i<8;i++)
 {emptyButton[i]=new QPushButton;
  emptyButton[i]->setParent(this);
  emptyButton[i]->setFlat(1);
  emptyButton[i]->setStyleSheet("QPushButton{border:none;}");
  emptyButton[i]->show();
 }
 emptyButton[0]->setGeometry(5,56,102,133);
 emptyButton[1]->setGeometry(110,56,102,133);
 emptyButton[2]->setGeometry(215,56,102,133);
 emptyButton[3]->setGeometry(317,56,102,133);
 emptyButton[4]->setGeometry(422,56,102,133);
 emptyButton[5]->setGeometry(527,56,102,133);
 emptyButton[6]->setGeometry(634,56,102,133);
 emptyButton[7]->setGeometry(740,56,102,133);
  startTimer(1000);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_exitButton_clicked()
{if(tot_People_Num)
    {LANGUAGE?puts("安检区未完全清空 无法关闭！"):puts("secrity check area is not cleared can't be stopped!");
     return;
    }
    this->close();
    puts("图形化模拟结束");
     return;
}

void Widget::on_newPButton_clicked()
{ if(!ENTER_BUFFER_AREA())return;
    int Row, Line;

       Line=BUFFER_LINE_LEN/MAX_CUSTSINGLE_LINE;
       Row=BUFFER_LINE_LEN%MAX_CUSTSINGLE_LINE;
       if(Line%2==0)
       {if(Row!=0)
           BUFFER_LINE_TAILPTR->po.setX(900+(Row-1)*70);
         else
            BUFFER_LINE_TAILPTR->po.setX(900+Row*70);
       }

       else
       {if(Row!=0)
           BUFFER_LINE_TAILPTR->po.setX(900+(MAX_CUSTSINGLE_LINE-1)*70-(Row-1)*70);
        else
            BUFFER_LINE_TAILPTR->po.setX(900+(MAX_CUSTSINGLE_LINE-1)*70-Row*70);
       }

   if(Row!=0)
    BUFFER_LINE_TAILPTR->po.setY(690-Line*70);
    else
     BUFFER_LINE_TAILPTR->po.setY(690-(Line-1)*70);
     BUFFER_LINE_TAILPTR->pic.setParent(this);
     QMovie *movie = new QMovie("../airport/material/pica.gif");
     //BUFFER_LINE_TAILPTR->pic.resize(70,70);
    BUFFER_LINE_TAILPTR->pic.setMovie(movie);
    movie->start();
     BUFFER_LINE_TAILPTR->pic.move(BUFFER_LINE_TAILPTR->po);
      BUFFER_LINE_TAILPTR->pic.setGeometry(BUFFER_LINE_TAILPTR->po.x(),BUFFER_LINE_TAILPTR->po.y(),70,70);
     BUFFER_LINE_TAILPTR->pic.show();
}

void Widget::on_offButton_clicked()
{ ASK_FOR_QUIT();
}
void Widget::Change_Tooltip()
{QString str,str1;
  for(int i=0,x;i<8;i++)
 {str="";
  str+=QStringLiteral("工作状态:");
  if(WINDOW_SET[i].winState==0)str1=QStringLiteral("休息\n");
   else if(WINDOW_SET[i].winState==4)str1=QStringLiteral("关闭\n");
     else if(WINDOW_SET[i].lineLen)str1=QStringLiteral("工作\n");
     else str1=QStringLiteral("开启\n");
  str+=str1;
  str1="";
  str+=QStringLiteral("动态:");
  if(WINDOW_SET[i].listState==1)str1=QStringLiteral("CUSTIN\n");
   else if(WINDOW_SET[i].listState==2)str1=QStringLiteral("CUSTOUT\n");
    else str1=QStringLiteral("NOCHANGED\n");
  str+=str1;
  str1="";
  str+=QStringLiteral("已工作时间:");
  x=WINDOW_SET[i].servLen;
  if(x==0)str1="0";
  while(x)
  {str1=(char)(x%10+'0')+str1;
   x/=10;
  }
  str+=str1;
  str+="\n";
  str1="";
  str+=QStringLiteral("当前服务乘客:");
 if(WINDOW_SET[i].headPtr==NULL)str1=QStringLiteral("无");
  else
 {x=WINDOW_SET[i].headPtr->num;
  if(x==0)str1="0";
  while(x)
  {str1=(char)(x%10+'0')+str1;
   x/=10;
   }
 }
 str+=str1;
 str+="\n";
 str1="";
 if(WINDOW_SET[i].headPtr!=NULL)
 {str+=QStringLiteral("当前乘客剩余时间:");
  x=WINDOW_SET[i].headPtr->arrive_time;
  if(x==0)str1="0";
  while(x)
  {str1=(char)(x%10+'0')+str1;
   x/=10;
  }
  str+=str1;
  str+="\n";
  str1="";
 }
  str+=QStringLiteral("当前队伍长度:");
  x=WINDOW_SET[i].lineLen;
  if(x==0)str1="0";
  while(x)
  {str1=(char)(x%10+'0')+str1;
   x/=10;
  }
  str+=str1;
  str+="\n";
  str1="";
  str+=QStringLiteral("当前队伍总时间:");
  x=WINDOW_SET[i].lineTime;
  if(x==0)str1="0";
   while(x)
  {str1=(char)(x%10+'0')+str1;
  x/=10;
  }
   str+=str1;
   str+="\n";
   str1="";
  emptyButton[i]->setToolTip(str);
  str="";
  PASSENGER_DATA *tempPtr=WINDOW_SET[i].headPtr;
  int sum=0;
  while(tempPtr!=NULL)
  {str=QStringLiteral("乘客编号:");
   x=tempPtr->num;
   if(x==0)str1="0";
   while(x)
   {str1=(char)(x%10+'0')+str1;
    x/=10;
   }
   str+=str1;
   str+="\n";
   str1="";
   str+=QStringLiteral("预计离开时间:");
   sum+=tempPtr->arrive_time;
   x=sum;
   if(x==0)str1="0";
   while(x)
   {str1=(char)(x%10+'0')+str1;
    x/=10;
   }
   str+=str1;
   tempPtr->pic.setToolTip(str);
   tempPtr=tempPtr->nextPtr;
   str="";
   str1="";
  }
 }
  return;
}
void  Widget::timerEvent(QTimerEvent *)
{if(PROGRAM_TIME%CYCLE==0)
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
  Change_Tooltip();
  update();
}
void Widget::paintEvent(QPaintEvent *)
{ QPainter painter(this);
  QPixmap pix;
  pix.load("../airport/material/background.png");
  painter.drawPixmap(0, 0, 1980,1020, pix);
  pix.load("../airport/material/background2.png");
  painter.drawPixmap(840,22 , 800,350, pix);
  pix.load("../airport/material/background3.jpg");
  painter.drawPixmap(840,372 , 800,390, pix);
    QPen pen;
    pen.setStyle(Qt::SolidLine);
    int line=MAX_LINES,row=MAX_CUSTSINGLE_LINE,x0=900,y0=760,i;
    if(line%2==1)
        painter.drawLine(QPointF(x0, y0-70), QPointF(x0, y0-line*70));
    else
         painter.drawLine(QPointF(x0, y0-70), QPointF(x0, y0-((line-1)*70)));
    if(line%2==1)
        painter.drawLine(QPointF(x0+row*70, y0), QPointF(x0+row*70, y0-(line-1)*70));
    else
        painter.drawLine(QPointF(x0+row*70, y0), QPointF(x0+row*70, y0-line*70));
    painter.drawLine(QPointF(x0, y0), QPointF(x0+row*70, y0));
    for(i=1;i<line;i++)
    {
        if(i%2==1)
        {
            painter.drawLine(QPointF(x0, y0-i*70), QPointF(x0+(row-1)*70, y0-i*70));
        }
        else
        {
            painter.drawLine(QPointF(x0+row*70, y0-i*70), QPointF(x0+70, y0-i*70));
        }
    }
    painter.drawLine(QPointF(x0, y0-line*70), QPointF(x0+row*70, y0-line*70));

   for(i=0;i<NORMAL_WINDOW_NUMBER;i++)
  {if(i==0)
       {pix.load(fileroute[WINDOW_SET[i].picnum]);
        painter.drawPixmap(5,56,102,133, pix);
       }
   if(i==1)
     {pix.load(fileroute[WINDOW_SET[i].picnum]);
       painter.drawPixmap(110,56,102,133, pix);

     }
   if(i==2)
        {pix.load(fileroute[WINDOW_SET[i].picnum]);
          painter.drawPixmap(215,56,102,133, pix);

        }
   if(i==3)
        {pix.load(fileroute[WINDOW_SET[i].picnum]);
          painter.drawPixmap(317,56,102,133, pix);

        }

  }
  if(DYNAMIC_WINDOW_MANAGEMENT)for(i=NORMAL_WINDOW_NUMBER;i<WINDOW_NUMBER;i++)
  {//system("pause");
       //printf("%d %d\n",i,WINDOW_SET[i].picnum);
      if(i==4)
      {pix.load(fileroute[WINDOW_SET[i].picnum]);
       painter.drawPixmap(422,56,102,133, pix);
       }
      if(i==5)
      {pix.load(fileroute[WINDOW_SET[i].picnum]);
       painter.drawPixmap(527,56,102,133, pix);
      }
      if(i==6)
      {pix.load(fileroute[WINDOW_SET[i].picnum]);
       painter.drawPixmap(634,56,102,133, pix);
      }
      if(i==7)
      {pix.load(fileroute[WINDOW_SET[i].picnum]);
       painter.drawPixmap(740,56,102,133, pix);
      }
  }
  return;
}

void Widget::on_rest1Button_clicked()
{
REST_REQUIREMENT(0);
}

void Widget::on_rest2Button_clicked()
{REST_REQUIREMENT(1);
}

void Widget::on_rest3Button_clicked()
{
REST_REQUIREMENT(2);
}

void Widget::on_rest4Button_clicked()
{
REST_REQUIREMENT(3);
}
