#include "jsonhandler.h"
#include <QByteArray>
#include <QJsonValue>
#include <QJsonObject>
#include <QJsonDocument>
#include <QNetworkReply>
#include "tcpclient.h"
#include <QDebug>

jsonHandler::jsonHandler(assetStatusBar* status, TcpClient* client, QObject *parent) : QObject(parent)
{
    init = 0;
    m_client = client;
    status_widget = status;
}

std::string jsonHandler::inJson(QString name, assetStatus status)
{
    QJsonObject json_obj;
    json_obj.insert(QString("name"), QJsonValue(name));

    if(status.getAssetStatus())
        json_obj.insert(QString("status"), QJsonValue("active"));
    else
        json_obj.insert(QString("status"), QJsonValue("locked"));

    json_obj.insert(QString("winperc"), QJsonValue(status.getWinperc()));
    json_obj.insert(QString("time_open"), QJsonValue(status.getTimeOpen()));
    json_obj.insert(QString("time_close"), QJsonValue(status.getTimeClose()));

    QJsonDocument doc(json_obj);
    QString str_json(doc.toJson(QJsonDocument::Compact));
    return str_json.toStdString();
}

void jsonHandler::handle_json(QByteArray input)
{
    // Parse document
    QJsonDocument doc(QJsonDocument::fromJson(input));

    // Get JSON object
    QJsonObject json = doc.object();

    QJsonObject pairs = json["pairs"].toObject();

    QJsonObject current = pairs["pairs"].toObject();

    QJsonObject::iterator current_asset = current.begin();

    if(init++ == 0)
    {
        while(current_asset != current.end())
        {
            QJsonObject asset = current_asset.value().toObject();

            assetStatus status_struct;

            status_struct.setClose(asset["time_close"].toDouble());
            status_struct.setOpen(asset["time_open"].toDouble());
            status_struct.setStatus(asset["locked"].toBool());
            status_struct.setWinperc(asset["winperc"].toInt());
            asset_data.insert(asset["name"].toString(), status_struct);

            current_asset++;
            status_widget->changeStatus(asset["name"].toString(), status_struct);
            //convert to json + forward data
            m_client->sendMsg(inJson(asset["name"].toString(), status_struct));
        }
    }
    else
    {
        while(current_asset != current.end())
        {
            QJsonObject asset = current_asset.value().toObject();

            assetStatus status_struct;
            QString asset_name;

            status_struct.setClose(asset["time_close"].toDouble());
            status_struct.setOpen(asset["time_open"].toDouble());
            status_struct.setStatus(asset["locked"].toBool());
            status_struct.setWinperc(asset["winperc"].toInt());
            asset_name = asset["name"].toString();

            if(status_struct != (assetStatus)asset_data.value(asset_name))
            {
                asset_data.insert(asset_name, status_struct);
                status_widget->changeStatus(asset_name, status_struct);
                //convert to json + forward data
                m_client->sendMsg(inJson(asset_name, status_struct));
            }

            current_asset++;
        }
    }

    emit doItAgain();
}

void jsonHandler::slotProcessJson()
{
    QNetworkReply* reply = (QNetworkReply*)sender();
    QByteArray recieved_data = reply->readAll();
    reply->deleteLater();
    handle_json(recieved_data);
}
