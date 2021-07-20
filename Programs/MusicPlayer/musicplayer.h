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

    void changeBass(int newValue);
    void changeTreble(int newValue);


private:
    // default levels of bass and treble.
    int m_bass = 50;
    int m_treble = 50;

    // methods to change the default level of bass or treble.
    void setBass(int value);
    void setTreble(int value);
};

#endif // MUSICPLAYER_H
