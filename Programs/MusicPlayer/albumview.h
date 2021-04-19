#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

class AlbumView : public QWidget
{
    Q_OBJECT

    class pAlbumView *p;

public:
    AlbumView(QWidget *parent = nullptr);
    ~AlbumView();

    void reloadAlbums();

signals:
    void playAlbum(class Album *album);
};
#endif // WIDGET_H
