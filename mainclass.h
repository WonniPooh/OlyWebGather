#ifndef MAINCLASS_H
#define MAINCLASS_H

#include "assetstatusbar.h"
#include "parsecookies.h"
#include "requestmanager.h"
#include "jsonhandler.h"
#include "tcpclient.h"
#include <QPushButton>

class MainClass : public QWidget
{
   Q_OBJECT

public:
    MainClass();
    ~MainClass();

public slots:
    void slotWork();
    void slotRealPressed();
    void slotDemoPressed();
    void slotChangeButtonsColor(bool account);

signals:
    void doItAgain();

private:
    QTime time;
    jsonHandler* handler;
    parseCookies* parse;
    requestManager* manager;
    assetStatusBar bar;
    TcpClient client;
    QPushButton* real_account;
    QPushButton* demo_account;
};

#endif // MAINCLASS_H
