#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QGridLayout>
#include "QPushButton"
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();


private slots:
    void on_exitButton_clicked();

    void on_newPButton_clicked();

    void on_offButton_clicked();

    void on_rest1Button_clicked();

    void on_rest2Button_clicked();

    void on_rest3Button_clicked();

    void on_rest4Button_clicked();

private:
    Ui::Widget *ui;
    QPushButton **emptyButton;
    void Change_Tooltip();
protected:
   void timerEvent(QTimerEvent *);
   void paintEvent(QPaintEvent *);
};

#endif // WIDGET_H
