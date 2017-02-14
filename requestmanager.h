#ifndef REQUESTMANAGER_H
#define REQUESTMANAGER_H

#include <QObject>
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QNetworkReply>

class jsonHandler;

class requestManager : public QObject
{
    Q_OBJECT
public:
    requestManager(const jsonHandler* handler,
                   QList<QNetworkCookie> cookieList,
                   QObject *parent = 0);
    ~requestManager();
    void getState();
    void switchAccounts(bool account);

public slots:
    void slotAccountSwitched();
    void slotError(QNetworkReply::NetworkError code);

signals:
    void signalAccountChange(bool account);

private:
    const jsonHandler* json_handler;
    QNetworkCookieJar* cookie_jar;
    QNetworkAccessManager* connection;
    void configure_request(QNetworkRequest* request);
    int current_account;
    bool account_switchig_to;

};

#endif // REQUESTMANAGER_H
