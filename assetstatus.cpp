#include "assetstatus.h"

assetStatus::assetStatus()
{
    time_open = 0;
    time_close = 0;
    asset_status = 0;
    asset_winperc = 0;
}

assetStatus::assetStatus(bool status, int new_winperc, double open, double close)
{
    asset_status = status;
    asset_winperc = new_winperc;
    time_open = open;
    time_close = close;
}

void assetStatus::setStatus(bool status)
{
    asset_status = status;
}

void assetStatus::setWinperc(int winperc)
{
    asset_winperc = winperc;
}

void assetStatus::setOpen(double open)
{
    time_open = open;
}

void assetStatus::setClose(double close)
{
    time_close = close;
}

int assetStatus::getWinperc()
{
    return asset_winperc;
}

bool assetStatus::getAssetStatus()
{
    return asset_status;
}

double assetStatus::getTimeOpen()
{
    return time_open;
}

double assetStatus::getTimeClose()
{
    return time_close;
}

bool operator!=(assetStatus left, assetStatus right)
{
    return left.getAssetStatus() != right.getAssetStatus() || left.getWinperc() != right.getWinperc() || left.getTimeClose() != right.getTimeClose() || left.getTimeOpen() != right.getTimeOpen();
}


