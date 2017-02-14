#include "mainclass.h"
#include <QScrollArea>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>
#include <QLabel>
#include <QPushButton>

MainClass::MainClass()
{
    parse = new parseCookies();
    parse->inputCookies();

    handler = new jsonHandler(&bar, &client);
    manager = new requestManager(handler, parse->getCookies());

    QWidget* widget = new QWidget;
    QScrollArea* area = new QScrollArea;
    QVBoxLayout* layout = new QVBoxLayout(this);
    QHBoxLayout* button_layout = new QHBoxLayout;
    QLabel* button_header = new QLabel;
    QLabel* asset_header = new QLabel;
    real_account = new QPushButton("Real");
    demo_account = new QPushButton("Demo");

    button_layout->addWidget(demo_account);
    button_layout->addWidget(real_account);

    button_header->setText(QString("<H1 align = \"center\"> Change Account </H1>"));
    asset_header->setText(QString("<H1 align = \"center\"> Assets Status </H1>"));

    widget->setLayout(bar.getGrid());
    area->setWidget(widget);
    area->setMinimumSize(750, 500);

    button_header->setMaximumHeight(50);
    asset_header->setMaximumHeight(50);

    layout->addWidget(button_header, Qt::AlignCenter);
    layout->addLayout(button_layout);
    layout->addWidget(asset_header, Qt::AlignCenter);
    layout->addWidget(area);

    client.setUpConnection(std::string("localhost"), 2323, 10001);
    QObject::connect(handler, &jsonHandler::doItAgain, this, &MainClass::slotWork);
    QObject::connect(this, &MainClass::doItAgain, this, &MainClass::slotWork);
    QObject::connect(real_account, &QPushButton::clicked, this, &MainClass::slotRealPressed);
    QObject::connect(demo_account, &QPushButton::clicked, this, &MainClass::slotDemoPressed);
    QObject::connect(manager, &requestManager::signalAccountChange, this, &MainClass::slotChangeButtonsColor);

    this->show();
}

void MainClass::slotWork()
{
    QObject().thread()->msleep(1);

    if(!time.isValid())
    {
        time.start();
        manager->switchAccounts(0);
    }

    if(time.elapsed() >= 1000)
    {
        manager->getState();
        time.restart();
        this->show();
        return;
    }

    emit doItAgain();
}

void MainClass::slotRealPressed()
{
    manager->switchAccounts(1);
}

void MainClass::slotDemoPressed()
{
    manager->switchAccounts(0);
}

void MainClass::slotChangeButtonsColor(bool account)
{
    if(account == 0)
    {
        real_account->setStyleSheet("background-color: gray");
        demo_account->setStyleSheet("background-color: green");
    }
    else
    {
        real_account->setStyleSheet("background-color: green");
        demo_account->setStyleSheet("background-color: gray");
    }
}


MainClass::~MainClass()
{
    delete handler;
    delete parse;
    delete manager;
    client.closeConnection();
}
