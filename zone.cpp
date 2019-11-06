#include "zone.h"
#include <QPalette>
#include <QColor>

zone::zone(QWidget *parent):QPushButton(parent)
{
    connect(this,SIGNAL(clicked()),this,SLOT(vie()));
}

void zone::vie()
{
    this->setText("X");
    this->envie=1;
}
