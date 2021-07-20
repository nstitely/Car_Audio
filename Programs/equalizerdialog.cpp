#include "equalizerdialog.h"

#include <QtWidgets>

EqualizerDialog::EqualizerDialog(QWidget *parent)
    : QDialog(parent)
    , balance(new QLabel)
    , bass(new QLabel)
    , treble(new QLabel)
{



    QVBoxLayout *verticalLayout;
    if (QGuiApplication::styleHints()->showIsFullScreen() || QGuiApplication::styleHints()->showIsMaximized()) {
        QHBoxLayout *horizontalLayout = new QHBoxLayout(this);
        QGroupBox *groupBox = new QGroupBox(QGuiApplication::applicationDisplayName(), this);
        horizontalLayout->addWidget(groupBox);
    }

    int frameStyle = QFrame::Sunken | QFrame::Panel;

    balanceLabel = new QLabel;
    balanceLabel->setFrameStyle(frameStyle);
    QPushButton *balanceBtn =
            new QPushButton(tr("Balance"));
    balanceLabel->setText(tr("%1%").arg(50));

    bassLabel = new QLabel;
    bassLabel->setFrameStyle(frameStyle);
    QPushButton *bassBtn =
            new QPushButton(tr("Bass"));
    bassLabel->setText(tr("%1%").arg(50));

    trebleLabel = new QLabel;
    trebleLabel->setFrameStyle(frameStyle);
    QPushButton *trebleBtn =
            new QPushButton(tr("Treble"));
    trebleLabel->setText(tr("%1%").arg(50));



    connect(balanceBtn, &QAbstractButton::clicked, this, &EqualizerDialog::setBalance);
    connect(bassBtn, &QAbstractButton::clicked, this, &EqualizerDialog::setBass);
    connect(trebleBtn, &QAbstractButton::clicked, this, &EqualizerDialog::setTreble);

    QWidget *page = new QWidget;
    QGridLayout *layout = new QGridLayout(page);
    layout->setColumnStretch(1, 1);
    layout->setColumnMinimumWidth(1, 250);
    layout->addWidget(balanceBtn, 0, 0);
    layout->addWidget(balanceLabel, 0, 1);
    layout->addWidget(bassBtn, 1, 0);
    layout->addWidget(bassLabel, 1, 1);
    layout->addWidget(trebleBtn, 2, 0);
    layout->addWidget(trebleLabel, 2, 1);
    layout->addItem(new QSpacerItem(0, 0, QSizePolicy::Ignored, QSizePolicy::MinimumExpanding), 5, 0);

    setLayout(layout);

}

void EqualizerDialog::setBalance()
{
    bool ok;
    x = QInputDialog::getInt(this, tr("Balance Level"),
                                 tr("Percentage:"), 50, 0, 100, 1, &ok);
    if (ok)
        balanceLabel->setText(tr("%1%").arg(x));
}

void EqualizerDialog::setBass()
{
    bool ok;
    y = QInputDialog::getInt(this, tr("Bass Level"),
                                 tr("Percentage:"), 50, 0, 100, 1, &ok);
    if (ok)
        bassLabel->setText(tr("%1%").arg(y));
}

void EqualizerDialog::setTreble()
{
    bool ok;
    z = QInputDialog::getInt(this, tr("Treble Level"),
                                 tr("Percentage:"), 50, 0, 100, 1, &ok);
    if (ok)
        trebleLabel->setText(tr("%1%").arg(z));
}

int EqualizerDialog::getBalance()
{
    return x;
}

int EqualizerDialog::getBass()
{
    return y;
}

int EqualizerDialog::getTreble()
{
    return z;
}

void EqualizerDialog::getLevels(int &balance, int &bass, int &treble)
{
    balance = x;
    bass = y;
    treble = z;
    return;
}



/*

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , time(new QLabel)
    , volume(new VolumeController)
    , player(new MusicPlayer)
    , bright(new Brightness)
{
    grid.addWidget(             bright, 0, 0, 2, 1);
    grid.addItem(new QSpacerItem(25,0), 0, 1, 2, 1);
    grid.addWidget(             player, 0, 2, 2, 1);
    grid.addItem(new QSpacerItem(25,0), 0, 3, 2, 1);
    grid.addWidget(               time, 0, 4, 1, 1);
    grid.addWidget(             volume, 1, 4, 1, 1);

    grid.setMargin(50);

    startTimer(100, Qt::PreciseTimer);

    setCentralWidget(new QWidget);
    centralWidget()->setLayout(&grid);

    QFont f = QApplication::font();
    f.setPointSize(48);
    time->setFont(f);

    bright->setValue(100);

    connect(volume, &VolumeController::setEqualizer, this, &MainWindow::getEqualizer);
}

*/
