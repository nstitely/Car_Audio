#include "volumecontroller.h"

#include <QFile>
#include <QDebug>
#include <QMouseEvent>
#include <QTextStream>
#include <QGridLayout>

VolumeSlider::VolumeSlider()
    : QSlider(Qt::Vertical)
{
    setRange(0,100);

    setPageStep(1);
    setSingleStep(1);

    setTracking(false);

    setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Expanding );

    setStyleSheet(R"(

    .VolumeSlider {
    }

    .VolumeSlider::groove:vertical {
        border: 1px solid #262626;
        width: 5px;
        background: #393939;
        margin: 24px 12px;
    }

    .VolumeSlider::handle:vertical {
        background: #22B14C;
        border: 5px solid #B5E61D;
        height: 23px;
        margin: -24px -12px;
    }

    )");
}

void VolumeSlider::mouseReleaseEvent(QMouseEvent *ev)
{
    QSlider::mouseReleaseEvent(ev);

    ev->accept();
    double percent = double(height() - ev->y()) / double(height());
    int newPos = double(maximum() - minimum()) * percent + minimum();
    setValue(newPos);
}

VolumeController::VolumeController(QWidget *parent)
    : QWidget(parent)
{
    setObjectName("Volume Controller");

    btnUp.setText(tr("Louder"));
    btnDn.setText(tr("Quieter"));

    btnDn.setMinimumHeight(50);
    btnUp.setMinimumHeight(50);
    mute.setMinimumHeight(50);

    mute.setText(tr("Mute"));
    mute.setCheckable(true);

    auto l = new QGridLayout;
    setLayout(l);
    l->addWidget(             &btnUp, 1,0, 1,2);
    l->addItem(new QSpacerItem(0,25), 2,0, 1,2);
    l->addWidget(             &front, 3,0);
    l->addWidget(              &rear, 3,1);
    l->addItem(new QSpacerItem(0,25), 4,0, 1,2);
    l->addWidget(             &btnDn, 5,0, 1,2);
    l->addItem(new QSpacerItem(0,25), 6,0, 1,2);
    l->addWidget(              &mute, 7,0, 1,2);

    connect(&front, &QSlider::valueChanged,
            this, [=](int vol) { volume.setVolume(0,vol); save(); });

    connect(&rear, &QSlider::valueChanged,
            this, [=](int vol) { volume.setVolume(1,vol); save(); });

    connect(&mute, &QPushButton::clicked, this, [=](){
        volume.toggleMute();
        bool muted = volume.muted();
        mute.setChecked(muted);
        mute.setText(muted ? tr("Muted") : tr("Mute"));
    });

    connect(&btnUp, &QPushButton::clicked, this, [=](){
        front.setValue(front.value() + 5);
        rear.setValue(  rear.value() + 5);
    });

    connect(&btnDn, &QPushButton::clicked, this, [=](){
        front.setValue(front.value() - 5);
        rear.setValue(  rear.value() - 5);
    });

    load();
}

void VolumeController::load()
{
    QFile f(saveFile);
    if(!f.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Save File Missing - Starting at 25%";
        front.setValue(25);
        rear.setValue(25);
        return;
    }

    QTextStream in(&f);
    QStringList lines = in.readAll().split("\n");
    if(lines.size() < 2)
    {
        qDebug() << "Save File Corrupt - Starting at 25%";
        front.setValue(25);
        rear.setValue(25);
        return;
    }

    front.setValue(lines.at(0).toInt());
    rear.setValue(lines.at(1).toInt());
}

void VolumeController::save() const
{
    QFile f(saveFile);
    if(!f.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug() << "Save File Missing - Starting at 25%";
        return;
    }

    QTextStream in(&f);
    in << front.value();
    in << "\n";
    in << rear.value();
    in << "\n";
}
