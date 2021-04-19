#ifndef ALBUM_H
#define ALBUM_H

#include <QPushButton>

class Album : public QPushButton
{
    Q_OBJECT
    class pAlbum *p;

public:
    explicit Album(const QString &name, const QString &coverArt = "", QWidget *parent = nullptr);
    ~Album();

    QStringList songs() const;
    QString  songPath() const;
};

#endif // ALBUM_H
