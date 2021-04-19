#ifndef PLAYER_H
#define PLAYER_H

#include <QWidget>

class Player : public QWidget
{
    Q_OBJECT

    class pPlayer *p;
public:
    Player(class Album *album, QWidget *parent = nullptr);
    ~Player();

    void addPlaylist(class Album *album);

signals:
    void stop();
};

#endif // PLAYER_H
