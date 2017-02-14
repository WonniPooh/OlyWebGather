#include <QNetworkCookie>
#include "parsecookies.h"
#include <QInputDialog>
#include <QDebug>

parseCookies::parseCookies()
{

}

void parseCookies::inputCookies()
{
    QInputDialog input_cookies;
    input_cookies.setModal(true);
    input_cookies.setLabelText(QString("<H3 align = \"center\">Enter cookies please!</H3>"));
    input_cookies.exec();

    cookies_string = input_cookies.textValue();
    parse(cookies_string);
}

QString parseCookies::getCookiesString()
{
    return cookies_string;
}

void parseCookies::parse(const QString& cookies)
{
    QStringList cookie_stringlist = cookies.split("; ", QString::SkipEmptyParts);
    for (const QString& cookie_string: cookie_stringlist)
    {
        QStringList cookie_kv = cookie_string.split("=", QString::KeepEmptyParts);

        QNetworkCookie cookie(cookie_kv[0].toLatin1(),
                              cookie_kv[1].toLatin1());
        cookie.normalize(QUrl("https://olymptrade.com"));
        cookie_list.push_back(cookie);
    }
}

QList<QNetworkCookie> parseCookies::getCookies()
{
    return cookie_list;
}
