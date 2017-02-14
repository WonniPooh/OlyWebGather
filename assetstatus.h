#ifndef ASSETSTATUS_H
#define ASSETSTATUS_H

#include <QString>

class assetStatus
{
public:
    explicit assetStatus();
    assetStatus(bool asset_status, int new_winperc, double open, double close);

    int getWinperc();
    bool getAssetStatus();
    double getTimeOpen();
    double getTimeClose();

    void setStatus(bool status);
    void setWinperc(int winperc);
    void setOpen(double open);
    void setClose(double close);

private:
    bool asset_status;
    int asset_winperc;
    double time_open;
    double time_close;

};

bool operator!=(assetStatus left, assetStatus right);

#endif // ASSETSTATUS_H
