#include "musicplayer.h"

#include "albumview.h"
#include "album.h"
#include "player.h"

#include <QMediaPlaylist>
#include <QVBoxLayout>

class pMusicPlayer : public QObject
{
    Q_OBJECT
public:
    MusicPlayer *parent;
    QVBoxLayout *box = new QVBoxLayout;
    AlbumView *view = new AlbumView;
    Player *player = nullptr;

    pMusicPlayer(MusicPlayer *musicPlayer)
        : parent(musicPlayer)
    {
        connect(view, &AlbumView::playAlbum, this, &pMusicPlayer::playAlbum);

        parent->setLayout(box);

        box->addWidget(view);
        box->addStretch();
    }

    ~pMusicPlayer()
    {
        delete player;
        delete box;
        delete view;
    }

    void playAlbum(Album *a)
    {
        if(player)
        {
            qDebug() << "Adding: " << a->objectName();
            player->addPlaylist(a);
        }
        else
        {
            player = new Player(a);
            box->addWidget(player);

            qDebug() << "Playing: " << a->objectName();
            connect(player, &Player::stop, this, &pMusicPlayer::playlistDone);
        }

    }

    void playlistDone()
    {
        delete player;
        player = nullptr;
    }
};

MusicPlayer::MusicPlayer(QWidget *parent)
    : QWidget(parent)
    , p(new pMusicPlayer(this))
{

}

MusicPlayer::~MusicPlayer()
{
    delete p;
}

#include "musicplayer.moc"
