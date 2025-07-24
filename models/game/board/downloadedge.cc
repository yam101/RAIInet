#include "downloadedge.h"

DownloadEdge::DownloadEdge(Player &downloader, Direction dir) : downloader{downloader}, downloadDirection{dir} {}

Player &DownloadEdge::getDownloader() const
{
    return downloader;
}

Direction DownloadEdge::getDirection() const
{
    return downloadDirection;
}

char DownloadEdge::print() const
{
    return '.';
}
