#include "equalizerdialog.h"

#include <QtWidgets>

EqualizerDialog::EqualizerDialog(QWidget *parent)
    : QDialog(parent)
    , balance(new QLabel)
    , bass(new QLabel)
    , treble(new QLabel)
{



    QVBoxLayout *verticalLayout;


    int frameStyle = QFrame::Sunken | QFrame::Panel;

    balanceLabel = new QLabel;
    balanceLabel->setFrameStyle(frameStyle);
    QPushButton *balanceBtn =
            new QPushButton(tr("Update Balance"));
    balanceLabel->setText(tr("%1%").arg(x));

    bassLabel = new QLabel;
    bassLabel->setFrameStyle(frameStyle);
    QPushButton *bassBtn =
            new QPushButton(tr("Update Bass"));
    bassLabel->setText(tr("%1%").arg(y));

    trebleLabel = new QLabel;
    trebleLabel->setFrameStyle(frameStyle);
    QPushButton *trebleBtn =
            new QPushButton(tr("Update Treble"));
    trebleLabel->setText(tr("%1%").arg(z));



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

// setters for the new balance, bass, and treble levels.
// also prevents users from inputting anything that isn't between 0-100%
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

// passes the balance, bass, and treble levels by reference from the main window to the dialog window so that when the user changes the values they get updated in the main window.
void EqualizerDialog::getLevels(int &balance, int &bass, int &treble)
{
    balance = x;
    bass = y;
    treble = z;
    return;
}

