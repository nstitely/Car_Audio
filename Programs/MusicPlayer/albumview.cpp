#include "albumview.h"
#include "album.h"
#include "player.h"

#include <QGridLayout>
#include <QThread>
#include <QDebug>
#include <QList>
#include <QDir>

class pAlbumView : public QObject
{
public:
    AlbumView *parent;
    QList<Album*> albumWidgets;

    explicit pAlbumView(AlbumView *p) : parent(p) { }

    void updateGUI()
    {
        delete parent->layout();
        auto *l = new QGridLayout;
        parent->setLayout(l);

        auto it = albumWidgets.begin();
        for(int i = 0; true; i++)
        {
            for(int j = 0; j < 6; j++)
            {
                l->addWidget(*it, i, j);

                ++it;
                if(it == albumWidgets.end())
                    return;
            }
        }
    }
};


AlbumView::AlbumView(QWidget *parent)
    : QWidget(parent)
    , p(new pAlbumView(this))
{
    reloadAlbums();
}

AlbumView::~AlbumView()
{
    delete p;
}

void AlbumView::reloadAlbums()
{
    qDeleteAll(p->albumWidgets);

    const QDir d(MUSIC_LIBRARY);
    const auto albums = d.entryList(QDir::Dirs | QDir::NoDotAndDotDot);

    for(const auto &album : albums)
    {
        QString albumCover = "";
        if(QFile::exists(MUSIC_LIBRARY + album + "/album.jpg"))
        {
            albumCover = "album.jpg";
        }
        else if(QFile::exists(MUSIC_LIBRARY + album + "/album.png"))
        {
            albumCover = "album.png";
        }

        auto a = new Album(album, albumCover);
        p->albumWidgets << a;
        connect(a, &QPushButton::clicked, this, [=](){ playAlbum(a); });
    }

    p->updateGUI();
}
