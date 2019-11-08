#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "zone.h"
#include <QMainWindow>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    int taille_i;
    int taille_j;
    zone* tableau[160][160];
    QPushButton* it;
    QPushButton* go;
    QPushButton* stop;
    QPushButton* clean;
    QPushButton* quitter;
    QPushButton* canonB;
    QPushButton* moulinB;
    QTimer *updateTimer;
private:
    void creation();
    void generation();
    Ui::MainWindow *ui;
    void moulin(int deb_i,int deb_j);
private slots:
    void gen();
    void goinfini();
    void stopinfini();
    void nettoyage();
    void canon();
    void moulingen();
signals:
    void fin();
};

#endif // MAINWINDOW_H
