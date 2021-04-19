#ifndef MUSICPLAYER_H
#define MUSICPLAYER_H

#include <QWidget>

class MusicPlayer : public QWidget
{
    Q_OBJECT

    class pMusicPlayer *p;

public:
    explicit MusicPlayer(QWidget *parent = nullptr);
    ~MusicPlayer();
};

#endif // MUSICPLAYER_H
