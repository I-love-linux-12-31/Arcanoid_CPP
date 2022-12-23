//
// Created by yaroslav_admin on 06.12.22.
//

#ifndef ABOUT_FORMYGRSGU_H
#define ABOUT_FORMYGRSGU_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AboutForm : public QWidget
{
public:
    QVBoxLayout *verticalLayout;
    QTextBrowser *textBrowser_2;
    QLabel *label;
    QTextBrowser *textBrowser;

    void setupUi(QWidget *AboutForm)
    {
        if (AboutForm->objectName().isEmpty())
            AboutForm->setObjectName(QString::fromUtf8("AboutForm"));
        AboutForm->resize(362, 514);
        AboutForm->setMaximumSize(QSize(362, 16777215));
        verticalLayout = new QVBoxLayout(AboutForm);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        textBrowser_2 = new QTextBrowser(AboutForm);
        textBrowser_2->setObjectName(QString::fromUtf8("textBrowser_2"));

        verticalLayout->addWidget(textBrowser_2);

        label = new QLabel(AboutForm);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMinimumSize(QSize(350, 350));
        label->setMaximumSize(QSize(350, 350));
        label->setStyleSheet(QString::fromUtf8("background-image: url(../icons/SourcesQR.png);border: none"));

        verticalLayout->addWidget(label);

        textBrowser = new QTextBrowser(AboutForm);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));

        verticalLayout->addWidget(textBrowser);


        retranslateUi(AboutForm);

        QMetaObject::connectSlotsByName(AboutForm);
    } // setupUi

    void retranslateUi(QWidget *AboutForm)
    {
        AboutForm->setWindowTitle(QCoreApplication::translate("AboutForm", "About", nullptr));
        textBrowser_2->setHtml(QCoreApplication::translate("AboutForm", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
                                                                        "<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
                                                                        "p, li { white-space: pre-wrap; }\n"
                                                                        "hr { height: 1px; border-width: 0; }\n"
                                                                        "</style></head><body style=\" font-family:'Cantarell'; font-size:11pt; font-weight:700; font-style:normal;\">\n"
                                                                        "<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:600;\">Source code are available on </span></p>\n"
                                                                        "<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:600;\">https://github.com/I-love-linux-12-31/Arcanoid_CPP/:</span></p></body></html>", nullptr));
        label->setText(QString());
        textBrowser->setHtml(QCoreApplication::translate("AboutForm", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
                                                                      "<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
                                                                      "p, li { white-space: pre-wrap; }\n"
                                                                      "hr { height: 1px; border-width: 0; }\n"
                                                                      "</style></head><body style=\" font-family:'Cantarell'; font-size:11pt; font-weight:700; font-style:normal;\">\n"
                                                                      "<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:600;\">Copyright (c) 2022, Yaroslav Kuznetsov</span></p>\n"
                                                                      "<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:600;\">GPL v3 License</span></p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AboutForm: public Ui_AboutForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // ABOUT_FORMYGRSGU_H
