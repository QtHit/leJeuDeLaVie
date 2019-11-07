#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "zone.h"
#include <QMainWindow>

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
    zone* tableau[100][100];
    QPushButton* it;
    QPushButton* go;
    QPushButton* stop;
    QPushButton* clean;
private:
    void creation();
    void generation();
    Ui::MainWindow *ui;
private slots:
    void gen();
    void infini();
    void nettoyage();
    void tempo();
    void canon();
signals:
    void fin();
};

#endif // MAINWINDOW_H
