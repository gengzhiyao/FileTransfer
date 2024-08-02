/********************************************************************************
** Form generated from reading UI file 'transfileclient.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TRANSFILECLIENT_H
#define UI_TRANSFILECLIENT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TransFileClient
{
public:
    QTextEdit *FileDisplay;
    QLabel *StatusLabel;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QLabel *AddressLabel;
    QLineEdit *Address;
    QLabel *PortLabel;
    QLineEdit *Port;
    QPushButton *ConnectButton;
    QWidget *widget1;
    QHBoxLayout *horizontalLayout_2;
    QProgressBar *ProgressBar;
    QPushButton *OpenButton;
    QPushButton *SendButton;

    void setupUi(QWidget *TransFileClient)
    {
        if (TransFileClient->objectName().isEmpty())
            TransFileClient->setObjectName("TransFileClient");
        TransFileClient->resize(553, 344);
        FileDisplay = new QTextEdit(TransFileClient);
        FileDisplay->setObjectName("FileDisplay");
        FileDisplay->setGeometry(QRect(10, 0, 531, 241));
        StatusLabel = new QLabel(TransFileClient);
        StatusLabel->setObjectName("StatusLabel");
        StatusLabel->setGeometry(QRect(10, 290, 531, 16));
        QFont font;
        font.setPointSize(10);
        StatusLabel->setFont(font);
        widget = new QWidget(TransFileClient);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(11, 250, 531, 31));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        AddressLabel = new QLabel(widget);
        AddressLabel->setObjectName("AddressLabel");
        QFont font1;
        font1.setPointSize(12);
        AddressLabel->setFont(font1);

        horizontalLayout->addWidget(AddressLabel);

        Address = new QLineEdit(widget);
        Address->setObjectName("Address");

        horizontalLayout->addWidget(Address);

        PortLabel = new QLabel(widget);
        PortLabel->setObjectName("PortLabel");
        PortLabel->setFont(font1);

        horizontalLayout->addWidget(PortLabel);

        Port = new QLineEdit(widget);
        Port->setObjectName("Port");

        horizontalLayout->addWidget(Port);

        ConnectButton = new QPushButton(widget);
        ConnectButton->setObjectName("ConnectButton");
        ConnectButton->setFont(font1);

        horizontalLayout->addWidget(ConnectButton);

        widget1 = new QWidget(TransFileClient);
        widget1->setObjectName("widget1");
        widget1->setGeometry(QRect(10, 310, 531, 31));
        horizontalLayout_2 = new QHBoxLayout(widget1);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        ProgressBar = new QProgressBar(widget1);
        ProgressBar->setObjectName("ProgressBar");
        ProgressBar->setFont(font);
        ProgressBar->setValue(24);

        horizontalLayout_2->addWidget(ProgressBar);

        OpenButton = new QPushButton(widget1);
        OpenButton->setObjectName("OpenButton");
        OpenButton->setFont(font1);

        horizontalLayout_2->addWidget(OpenButton);

        SendButton = new QPushButton(widget1);
        SendButton->setObjectName("SendButton");
        SendButton->setFont(font1);

        horizontalLayout_2->addWidget(SendButton);


        retranslateUi(TransFileClient);

        QMetaObject::connectSlotsByName(TransFileClient);
    } // setupUi

    void retranslateUi(QWidget *TransFileClient)
    {
        TransFileClient->setWindowTitle(QCoreApplication::translate("TransFileClient", "TransFileClient", nullptr));
        StatusLabel->setText(QCoreApplication::translate("TransFileClient", "\347\212\266\346\200\201\357\274\232\347\255\211\345\276\205\346\211\223\345\274\200\346\226\207\344\273\266", nullptr));
        AddressLabel->setText(QCoreApplication::translate("TransFileClient", "Address", nullptr));
        PortLabel->setText(QCoreApplication::translate("TransFileClient", "Port", nullptr));
        ConnectButton->setText(QCoreApplication::translate("TransFileClient", "Connect", nullptr));
        OpenButton->setText(QCoreApplication::translate("TransFileClient", "Open File", nullptr));
        SendButton->setText(QCoreApplication::translate("TransFileClient", "Send", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TransFileClient: public Ui_TransFileClient {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TRANSFILECLIENT_H
