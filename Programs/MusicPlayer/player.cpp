#include "player.h"
#include "album.h"

#include <QMediaPlaylist>
#include <QMediaPlayer>
#include <QGridLayout>
#include <QPushButton>
#include <QMouseEvent>
#include <QProcess>
#include <QSlider>
#include <QLabel>

#include <QDebug>

#include <cmath>
#include <ctime>

// I'm sure there are faster ways... but I don't care
template<class T>
QList<T> randomize(QList<T> in)
{
    QList<T> out;

    int s = in.size();
    int b = s;

    srand(time(0));

    while(s != 0)
    {
        out << in.takeAt(rand() % s);
        s--;
    }

    if(b != out.size())
    {
        qCritical() << "Error in random!";
        exit(1);
    }

    return out;
}

class PlayDurationSlider : public QSlider
{
    Q_OBJECT
public:
    PlayDurationSlider() : QSlider(Qt::Horizontal)
    {

    }

protected:
    void mouseReleaseEvent(QMouseEvent *ev)
    {
        QSlider::mouseReleaseEvent(ev);

        ev->accept();
        double percent = double(ev->x()) / double(width());
        int newPos = double(maximum() - minimum()) * percent + minimum();
        setValue(newPos);
    }
};

//
class pPlayer : public QObject
{
    Q_OBJECT
public:
    Player *parent;

    QGridLayout layout;
    QPushButton btnStop, btnPlayPause, btnNext, btnPrev;
    QMediaPlayer player;
    QLabel title;
    PlayDurationSlider slider;

    QStringList songs;
    QList<Album*> albums;

    bool disableSeek = false;

    pPlayer(Player *parent, Album *album)
        : parent(parent)
        , btnStop("S")
        , btnPlayPause("P")
        , btnNext("->")
        , btnPrev("<-")
    {
        connect(&slider, &QSlider::valueChanged,
                this,    &pPlayer::seek);

        connect(&player,       &QMediaPlayer::positionChanged, this, &pPlayer::positionChanged);
        connect(&player,       &QMediaPlayer::durationChanged, this, &pPlayer::durationChanged);
        connect(&btnPlayPause, &QPushButton::clicked,          this, &pPlayer::togglePlay);
        connect(&btnStop,      &QPushButton::clicked,        parent, &Player::stop);


        slider.setTracking(true);
        slider.setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Expanding );
//        .PlayDurationSlider {
//            background: #5F4141;
//        }

        slider.setStyleSheet(R"(

.PlayDurationSlider::handle:horizontal {
    background: #22B14C;
    border: 5px solid #B5E61D;
    width:  30px;
    height: 30px;
    margin: -15px -15px;
}
.PlayDurationSlider::groove:horizontal {
    border: 1px solid #262626;
    height: 7px;
    background: #393939;
    margin: 15px 15px;
}

)");

        {
            QSize s(100,100);

            btnPlayPause.setMinimumSize(s);
            btnNext.setMinimumSize(s);
            btnPrev.setMinimumSize(s);
            btnStop.setMinimumSize(s);

            btnPlayPause.setMaximumSize(s);
            btnNext.setMaximumSize(s);
            btnPrev.setMaximumSize(s);
            btnStop.setMaximumSize(s);
        }

        // Build the layout
        {
            parent->setLayout(&layout);
            layout.addWidget(&btnPrev,      0, 0);
            layout.addWidget(&btnPlayPause, 1, 0);
            layout.addWidget(&title,        0, 1);
            layout.addWidget(&slider,       1, 1);
            layout.addWidget(&btnNext,      0, 2);
            layout.addWidget(&btnStop,      1, 2);
        }

        addPlaylist(album);
        player.setVolume(100);

        // First play doesn't actully change the current song, so we have to grab it
        player.play();
        newSong(0);
    }

    void addPlaylist(Album *album)
    {
        QObject::disconnect(&btnNext, nullptr, nullptr, nullptr);
        QObject::disconnect(&btnPrev, nullptr, nullptr, nullptr);

        if(player.playlist())
            QObject::disconnect(player.playlist(), nullptr, nullptr, nullptr);

        player.stop();
        songs.clear();

        albums << album;
        struct D { QString p,s; };

        QList<D> sets;
        for(const auto *a : albums)
        {
            auto pa = a->songPath();
            auto ss = a->songs();
            for(const auto &s : ss)
                sets << D{pa, s};
        }

        auto pl = new QMediaPlaylist;

        sets = randomize(sets);
        for(const auto &s : sets)
        {
            pl->addMedia(QUrl::fromLocalFile(s.p + s.s));
            songs << s.s;
            // qDebug() << s.s;
        }

        QObject::connect(&btnNext, &QPushButton::clicked, pl, &QMediaPlaylist::next);
        QObject::connect(&btnPrev, &QPushButton::clicked, pl, &QMediaPlaylist::previous);
        QObject::connect(pl, &QMediaPlaylist::currentIndexChanged, this, &pPlayer::newSong);

        player.setPlaylist(pl);
        player.play();
    }

    void positionChanged(qint64 pos)
    {
        disableSeek = true;
        slider.setValue(int(pos));
        disableSeek = false;
    }

    void durationChanged(qint64 duration)
    {
        slider.setMaximum(int(duration));
    }

    void newSong(int index)
    {
        if(index < 0 || index >= songs.size())
            return;

        disableSeek = true;
        slider.setValue(0);
        disableSeek = false;

        title.setText(songs.at(index));
    }

    void togglePlay()
    {
        if(player.state() == QMediaPlayer::PlayingState)
            player.pause();
        else
            player.play();
    }

    void sliderSeek()
    {
        player.setPosition(slider.value());
    }

    void seek(int value)
    {
        if(!disableSeek)
            player.setPosition(int64_t(value));
    }
};


Player::Player(Album *album, QWidget *parent)
    : QWidget(parent)
    , p(new pPlayer(this, album))
{
}

Player::~Player()
{
    delete p;
}

void Player::addPlaylist(Album *album)
{
    p->addPlaylist(album);
}

#include "player.moc"
