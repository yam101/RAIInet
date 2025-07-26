#ifndef DOWNLOAD_EDGE_H
#define DOWNLOAD_EDGE_H

#include "cellfeature.h"
#include "../../direction.h"

class DownloadEdge : public CellFeature
{
    Player &downloader;
    Direction downloadDirection; // direction to move off the board to download a link on it

public:
    DownloadEdge(Player &downloader, Direction dir);

    Player &getDownloader() const;
    Direction getDirection() const;

    char print() const override;
};

#endif
