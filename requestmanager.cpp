#include "requestmanager.h"
#include "jsonhandler.h"
#include <QUrl>
#include <QDateTime>
#include <QNetworkCookie>
#include <QNetworkCookieJar>
#include <QDebug>

enum
{
    demo,
    real
};

requestManager::requestManager(const jsonHandler* handler,
                               QList<QNetworkCookie> cookieList,
                               QObject *parent) : QObject(parent)
{
    json_handler = handler;
    connection = new QNetworkAccessManager;

    cookie_jar = new QNetworkCookieJar;
    cookie_jar->setCookiesFromUrl(cookieList, QUrl("https://olymptrade.com/"));
    connection->setCookieJar(cookie_jar);

    current_account = -1;
}

requestManager::~requestManager()
{
    delete connection;
}

void requestManager::configure_request(QNetworkRequest* request)
{
    request->setRawHeader(QByteArray("Accept"), QByteArray("text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8"));
    request->setRawHeader(QByteArray("Accept-Language"), QByteArray("en-US,en;q=0.8"));
    request->setRawHeader(QByteArray("Cache-Control"), QByteArray("max-age=0"));
    request->setRawHeader(QByteArray("Connection"), QByteArray("keep-alive"));
    request->setRawHeader(QByteArray("Host"), QByteArray("olymptrade.com"));
    request->setRawHeader(QByteArray("Upgrade-Insecure-Requests"), QByteArray("1"));
    request->setHeader(QNetworkRequest::UserAgentHeader, QVariant("Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/56.0.2924.87 Safari/537.36"));
}
void requestManager::getState()
{
    QNetworkReply* reply = NULL;
    QUrl get_state(QString("https://olymptrade.com/platform/state?_=") + QString::number(QDateTime::currentMSecsSinceEpoch()));
    QNetworkRequest request(get_state);
    configure_request(&request);
    reply = connection->get(request);
    QObject::connect(reply, &QNetworkReply::finished, json_handler, &jsonHandler::slotProcessJson);
}

void requestManager::switchAccounts(bool account)
{
    if(current_account == account)
        return;

    account_switchig_to = account;
    QNetworkRequest request;
    QNetworkReply* reply = NULL;
    QUrl play_demo(QString("https://olymptrade.com/user/playdemo?_=") + QString::number(QDateTime::currentMSecsSinceEpoch()));
    QUrl play_real(QString("https://olymptrade.com/user/playreal?_=") + QString::number(QDateTime::currentMSecsSinceEpoch()));

    if(account == real)
        request.setUrl(play_real);
    else
        request.setUrl(play_demo);

    configure_request(&request);

    reply = connection->get(request);
    QObject::connect(reply, &QNetworkReply::finished, this, &requestManager::slotAccountSwitched);
}

void requestManager::slotAccountSwitched()
{
    QNetworkReply* reply = (QNetworkReply*)sender();

    QString income_json(reply->readAll());
    reply->deleteLater();

    if(income_json.contains(QString("{\"result\":true}")))
    {
        current_account = account_switchig_to;
    }
    emit signalAccountChange((bool)current_account);
}

void requestManager::slotError(QNetworkReply::NetworkError code)
{
    //TODO error handler
}
