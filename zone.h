#ifndef ZONE_H
#define ZONE_H
#include <QPushButton>
#include <QDebug>

class zone : public QPushButton
{
    Q_OBJECT
public:
    zone (QWidget *parent=nullptr);
    int envie;
    int envieGen;
private slots:
    void vie();
};

#endif // ZONE_H
