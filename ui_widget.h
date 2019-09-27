/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QPushButton *exitButton;
    QPushButton *newPButton;
    QPushButton *offButton;
    QPushButton *rest1Button;
    QPushButton *rest2Button;
    QPushButton *rest3Button;
    QPushButton *rest4Button;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QStringLiteral("Widget"));
        Widget->resize(1366, 768);
        exitButton = new QPushButton(Widget);
        exitButton->setObjectName(QStringLiteral("exitButton"));
        exitButton->setGeometry(QRect(280, 480, 99, 33));
        newPButton = new QPushButton(Widget);
        newPButton->setObjectName(QStringLiteral("newPButton"));
        newPButton->setGeometry(QRect(40, 480, 99, 33));
        newPButton->setStyleSheet(QStringLiteral(""));
        offButton = new QPushButton(Widget);
        offButton->setObjectName(QStringLiteral("offButton"));
        offButton->setGeometry(QRect(160, 480, 99, 33));
        rest1Button = new QPushButton(Widget);
        rest1Button->setObjectName(QStringLiteral("rest1Button"));
        rest1Button->setGeometry(QRect(930, 60, 99, 33));
        rest2Button = new QPushButton(Widget);
        rest2Button->setObjectName(QStringLiteral("rest2Button"));
        rest2Button->setGeometry(QRect(1060, 60, 99, 33));
        rest3Button = new QPushButton(Widget);
        rest3Button->setObjectName(QStringLiteral("rest3Button"));
        rest3Button->setGeometry(QRect(930, 110, 99, 33));
        rest4Button = new QPushButton(Widget);
        rest4Button->setObjectName(QStringLiteral("rest4Button"));
        rest4Button->setGeometry(QRect(1060, 110, 99, 33));

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Widget", Q_NULLPTR));
        exitButton->setText(QApplication::translate("Widget", "\351\200\200\345\207\272", Q_NULLPTR));
        newPButton->setText(QApplication::translate("Widget", "\346\226\260\344\271\230\345\256\242", Q_NULLPTR));
        offButton->setText(QApplication::translate("Widget", "\344\270\213\347\217\255", Q_NULLPTR));
        rest1Button->setText(QApplication::translate("Widget", "\347\252\227\345\217\2431\344\274\221\346\201\257\347\224\263\350\257\267", Q_NULLPTR));
        rest2Button->setText(QApplication::translate("Widget", "\347\252\227\345\217\2432\344\274\221\346\201\257\347\224\263\350\257\267", Q_NULLPTR));
        rest3Button->setText(QApplication::translate("Widget", "\347\252\227\345\217\2433\344\274\221\346\201\257\347\224\263\350\257\267", Q_NULLPTR));
        rest4Button->setText(QApplication::translate("Widget", "\347\252\227\345\217\2434\344\274\221\346\201\257\347\224\263\350\257\267", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
