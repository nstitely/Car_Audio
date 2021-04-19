#include "album.h"

#include <QMediaPlaylist>
#include <QPixmap>
#include <QDebug>
#include <QIcon>
#include <QDir>

class pAlbum
{
public:
    const QString name;
    const QString coverArt;
    QDir d;

    pAlbum(const QString &name, const QString &coverArt) :
        name(name), coverArt(coverArt),
        d(MUSIC_LIBRARY + name)
    {

    }

    QStringList songs() const
    {
        return d.entryList(QStringList() << "*.opus" << "*.mp3" << "*.mp4" << "*.ogg", QDir::Files);
    }
};

Album::Album(const QString &name, const QString &coverArt, QWidget *parent)
    : QPushButton(parent)
    , p(new pAlbum(name, coverArt))
{
    setObjectName(name);

    if(coverArt.isEmpty())
    {
        setText(name);
    }
    else
    {
        setIcon(QIcon(songPath() + coverArt));
        setIconSize(QSize(150,150));
    }

    setMinimumSize(160,160);

    // qDebug() << name << songs();
}

Album::~Album()
{
    delete p;
}

QStringList Album::songs() const
{
    return p->songs();
}

QString Album::songPath() const
{
    return p->d.path() + QDir::separator();
}
