#include "zone.h"
#include <QPalette>
#include <QColor>

zone::zone(QWidget *parent):QPushButton(parent)
{
    connect(this,SIGNAL(clicked()),this,SLOT(vie()));
}

void zone::naissance()
{
    envie=1;
    this->setPalette(QColor("red"));
    this->setText("X");
}

void zone::mort()
{
    this->setText("");
    this->setPalette(QColor("white"));
    this->envie=0;
}

void zone::vie()
{
    this->setText("X");
    this->setPalette(QColor("red"));
    this->envie=1;
}
