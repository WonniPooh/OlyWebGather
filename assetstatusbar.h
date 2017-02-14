#ifndef ASSETSTATUSBAR_H
#define ASSETSTATUSBAR_H

#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QMap>
#include "assetstatus.h"

struct assetBar
{
    int grid_pos;
    QLabel* name;
    QLabel* status;
    QLabel* winperc;
    QLabel* time_open;
    QLabel* time_close;
};

class assetStatusBar : public QWidget
{
    Q_OBJECT
public:
    QGridLayout* getGrid();
    int grid_free_pos;
    assetStatusBar(QWidget* parent = 0);
    ~assetStatusBar();
    void changeStatus(QString name, assetStatus status);
    void deleteAsset(QString name);

private:
    QMap<QString, assetBar> assetsBars;
    QGridLayout main_layout;
};

#endif // ASSETSTATUSBAR_H
