//
// Created by yaroslav_admin on 22.11.22.
//

#ifndef ARCANOID_CPP_LEVELSELECTMENU_HPP
#define ARCANOID_CPP_LEVELSELECTMENU_HPP

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
// #include <QMainWindow>
#include <QSizePolicy>

#ifndef MAINNDWLFU_H
#include "MainMenu.hpp"
#endif

#include "../level_files_handler.h++"

QT_BEGIN_NAMESPACE

class LevelSelectMenu : public QWidget
{
public:
    std::vector<QPushButton*> level_buttons;
    unsigned int selected_level = 0;

    void show(){
        QWidget::show();
        this->pushButton_play->setEnabled(false);
    }
private:
    GameWindow* gameWindow;
    QMainWindow* mainWindow;

    QVBoxLayout *verticalLayout;
    QWidget *Levels;
    QWidget *Buttons_bar;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_back;
    QPushButton *pushButton_play;
    QSpacerItem *horizontalSpacer_2;

    void onLevelButtonClicked(int button_number){
        std::cout << "Clicked level button ! "<< "It is " << button_number << std::endl;
        this->pushButton_play->setStyleSheet("color: rgba(0, 255, 128, 255);");
        this->pushButton_play->setEnabled(true);


        this->selected_level = button_number;
    }

    void onBackButtonPushed(){
        this->hide();
        this->mainWindow->show();
    }

    void setupUi(QWidget *Level_select)
    {
        QSizePolicy windowSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        this->setSizePolicy(windowSizePolicy);

        if (Level_select->objectName().isEmpty())
            Level_select->setObjectName(QString::fromUtf8("LevelSelectMenu"));
        Level_select->resize(640, 480);
        verticalLayout = new QVBoxLayout(Level_select);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        Levels = new QWidget(Level_select);
        Levels->setObjectName(QString::fromUtf8("Levels"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Levels->sizePolicy().hasHeightForWidth());
        Levels->setSizePolicy(sizePolicy);
        Levels->setMinimumSize(QSize(256, 256));

        verticalLayout->addWidget(Levels);

        Buttons_bar = new QWidget(Level_select);
        Buttons_bar->setObjectName(QString::fromUtf8("Buttons_bar"));
        Buttons_bar->setMinimumSize(QSize(228, 40));
        Buttons_bar->setMaximumSize(QSize(16777215, 48));
        horizontalLayout = new QHBoxLayout(Buttons_bar);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(407, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButton_back = new QPushButton(Buttons_bar);
        pushButton_back->setObjectName(QString::fromUtf8("pushButton_back"));
        QIcon icon(QIcon::fromTheme(QString::fromUtf8("application-exit")));
        pushButton_back->setIcon(icon);
        pushButton_back->setCheckable(true);
        QObject::connect(pushButton_back, &QPushButton::clicked, this, &LevelSelectMenu::onBackButtonPushed);

        horizontalLayout->addWidget(pushButton_back);

        pushButton_play = new QPushButton(Buttons_bar);
        pushButton_play->setObjectName(QString::fromUtf8("pushButton_play"));
        QIcon icon1(QIcon::fromTheme(QString::fromUtf8("media-playback-start")));
        pushButton_play->setIcon(icon1);
        pushButton_play->setEnabled(false);
        pushButton_play->setChecked(false);
        QObject::connect(pushButton_play, &QPushButton::clicked, this, &LevelSelectMenu::onPlayButtonPushed);

        horizontalLayout->addWidget(pushButton_play);

        horizontalSpacer_2 = new QSpacerItem(25, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout->addWidget(Buttons_bar);


        retranslateUi(Level_select);

        QMetaObject::connectSlotsByName(Level_select);
    } // setupUi

    void retranslateUi(QWidget *Level_select)
    {
        Level_select->setWindowTitle(QCoreApplication::translate("LevelSelectMenu", "Level select", nullptr));
        pushButton_back->setText(QCoreApplication::translate("LevelSelectMenu", "Back", nullptr));
        pushButton_play->setText(QCoreApplication::translate("LevelSelectMenu", "Play", nullptr));
    } // retranslateUi


public:
    void init(GameWindow* g_win, QMainWindow* main_window){
        this->gameWindow = g_win;
        this->mainWindow = main_window;
        this->setupUi(this);

        int w, h;
        w = this->width();
        h = this->height();

        //int h1 = (h - 64) / 64; // first 64 - bottom buttons bar
        //int w1 = (w - 16) / 64; // first 16 - left border, (48 - button + 16 - free space on right!) = 64

        unsigned int buttons_required = get_main_levels_count() + get_bonus_levels_count();

        unsigned int max_buttons_on_line = (w - 16) / 64;

        unsigned int lines_count = buttons_required / max_buttons_on_line;
        if (buttons_required % max_buttons_on_line > 0)
            lines_count += 1;

        unsigned int count = 1;
        for (int row_id = 0; count <= buttons_required; row_id++){
            for (int i = 0; i < max_buttons_on_line; i++){
                if (count > buttons_required)
                    continue;
                QPushButton* level_btn = new QPushButton(this->Levels);
                level_btn->setGeometry(8 + i * 64, 8 + row_id * 64 , 48, 48);

                auto callback = [this, count]() {
                    onLevelButtonClicked(count);
                    return;
                };

                QObject::connect(level_btn, &QPushButton::clicked, this, callback);
                level_btn->setText(std::to_string(count).c_str());
                if (count > get_main_levels_count()){
                    level_btn->setStyleSheet(" background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,     stop: 0 rgba(255, 191, 0, 255), stop: 1 rgba(255, 98, 0, 255));\n"
                                             "border-width: 2px;\n"
                                             " border-radius: 8px;");
                }
                else
                    level_btn->setStyleSheet(" background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,     stop: 0 rgba(0, 255, 255, 255), stop: 1 rgba(135, 140, 200, 255));\n"
                                             "border-width: 2px;\n"
                                             " border-radius: 8px;\n"
                                             "color: rgb(0, 0, 0);\n");


                //onLevelButtonDoubleClicked
                level_buttons.push_back(level_btn);

                count++;
            }
        }

    }

    void onPlayButtonPushed(){
        this->mainWindow->hide();
        this->hide();
        if (this->selected_level > get_main_levels_count())
            this->gameWindow->play_level((int)this->selected_level - (int)get_main_levels_count(), true);
        else
            this->gameWindow->play_level((int)this->selected_level, false);
        this->gameWindow->show();
    }
};


QT_END_NAMESPACE


#endif //ARCANOID_CPP_LEVELSELECTMENU_HPP
