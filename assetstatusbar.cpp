#include "assetstatusbar.h"
#include <QDateTime>

assetStatusBar::assetStatusBar(QWidget* parent) : QWidget(parent)
{
    main_layout.setSizeConstraint(QLayout::SetMinAndMaxSize);
    grid_free_pos = 0;
}

assetStatusBar::~assetStatusBar()
{
    for(QMap<QString, assetBar>::iterator it = assetsBars.begin(); it != assetsBars.end(); it++)
    {
        delete it.value().name;
        delete it.value().status;
        delete it.value().time_close;
        delete it.value().time_open;
        delete it.value().winperc;
    }
}


QGridLayout* assetStatusBar::getGrid()
{
    return &main_layout;
}

void assetStatusBar::changeStatus(QString name, assetStatus status)
{
    assetBar newBar;

    if(assetsBars.contains(name))
        newBar = assetsBars.value(name);
    else
    {
        newBar.grid_pos = grid_free_pos++;
        newBar.name = new QLabel;
        newBar.status = new QLabel;
        newBar.time_close = new QLabel;
        newBar.time_open = new QLabel;
        newBar.winperc = new QLabel;
        assetsBars.insert(name, newBar);
    }

    newBar.name->setText(QString("<H3>") + name + QString("</H3>"));

    if(!status.getAssetStatus())
        newBar.status->setText("<H3>Status:</H3> <font color=\"green\">\"active\"</font>");
    else
        newBar.status->setText("<H3>Status:</H3> <font color=\"red\">\"locked\"</font>");

    if(status.getWinperc() < 80)
        newBar.winperc->setText(QString("<H3>Winperc:</H3> ") + QString("<font color=\"red\">") + QString::number(status.getWinperc()) + QString("</font>"));
    else
        newBar.winperc->setText(QString("<H3>Winperc:</H3> ") + QString("<font color=\"green\">") + QString::number(status.getWinperc()) + QString("</font>"));

    QDateTime datetime = QDateTime::fromTime_t((uint)status.getTimeClose());
    QString textdate = datetime.toString( Qt::TextDate );

    newBar.time_open->setText(QString("<H3>Open:</H3> ") + textdate);

    datetime = QDateTime::fromTime_t((uint)status.getTimeOpen());
    textdate = datetime.toString( Qt::TextDate );

    newBar.time_close->setText(QString("<H3>Close:</H3> ") + textdate);

    main_layout.addWidget(newBar.name, newBar.grid_pos, 0);
    main_layout.addWidget(newBar.status, newBar.grid_pos, 1);
    main_layout.addWidget(newBar.winperc, newBar.grid_pos, 2);
    main_layout.addWidget(newBar.time_open, newBar.grid_pos, 3);
    main_layout.addWidget(newBar.time_close, newBar.grid_pos, 4);
}

void assetStatusBar::deleteAsset(QString name)
{
    assetBar to_delete = assetsBars.value(name);
    assetsBars.remove(name);

    //main_layout.removeWidget();

    delete to_delete.name;
    delete to_delete.status;
    delete to_delete.time_close;
    delete to_delete.time_open;
    delete to_delete.winperc;

}
