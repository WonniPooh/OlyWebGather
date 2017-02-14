#ifndef parseCookies_H
#define parseCookies_H

#include <QWidget>
#include <QNetworkCookie>
#include <QNetworkCookieJar>
#include <QNetworkRequest>
#include <QString>

class QTextEdit;

class parseCookies
{
public:
    explicit parseCookies();
    QList<QNetworkCookie> getCookies();
    QString getCookiesString();
    void inputCookies();

private:
    QString cookies_string;
    QList<QNetworkCookie> cookie_list;
    void parse(const QString& cookies);
};

#endif // parseCookies_H
