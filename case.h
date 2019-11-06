#ifndef CASE_H
#define CASE_H
#include <QPushButton>


class zone : public QPushButton
{
    Q_OBJECT
public:
    zone (QWidget *parent=nullptr);
};

#endif // CASE_H

#include "case.h"

zone::zone(QWidget *parent):QPushButton(parent)
{

}
