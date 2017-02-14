#ifndef JSONHANDLER_H
#define JSONHANDLER_H

#include <QObject>
#include "assetstatus.h"
#include "assetstatusbar.h"
#include <QTextEdit>

class  TcpClient;

class jsonHandler : public QObject
{
    Q_OBJECT
public:
    explicit jsonHandler(assetStatusBar *status, TcpClient *client, QObject *parent = 0);
    void handle_json(QByteArray input);

public slots:
    void slotProcessJson();

signals:
    void doItAgain();

private:
    std::string inJson(QString name, assetStatus status);
    int init;
    TcpClient* m_client;
    assetStatusBar* status_widget;
    QMap<QString, assetStatus> asset_data;
};

#endif // JSONHANDLER_H
