#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "zone.h"
#include <QThread>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->resize(600,700);

    it=new QPushButton("Itération",this);
    it->move(0,600);
    it->resize(200,100);

    go=new QPushButton("Go",this);
    go->move(200,600);
    go->resize(100,100);

    stop=new QPushButton("Stop",this);
    stop->move(300,600);
    stop->resize(100,100);

    clean=new QPushButton("clean",this);
    clean->move(400,600);
    clean->resize(200,100);

    creation();

    connect(this->it,SIGNAL(clicked()),this,SLOT(gen()));
    connect(this->go,SIGNAL(clicked()),this,SLOT(infini()));
    connect(this,SIGNAL(fin()),this,SLOT(infini()));
    connect(this->clean,SIGNAL(clicked()),this,SLOT(nettoyage()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::creation()
{
    for(int i=0;i<30;i++)
    {
        for (int j=0;j<30;j++)
        {
            tableau[i][j]=new zone(this);
            tableau[i][j]->resize(20,20);
            tableau[i][j]->move(j*20,i*20);
            tableau[i][j]->envie=0;
            tableau[i][j]->envieGen=0;
        }
    }
}

void MainWindow::gen()
{
    generation();
}

void MainWindow::generation()
{
    int somme=0;
    for(int i=0;i<30;i++)
    {
        for (int j=0;j<30;j++)
        {
            somme = 0;

            for(int k=-1;k<2;k++)
            {
                for (int l=-1;l<2;l++)
                {
                    somme += tableau[(i+k+30)%30][(j+l+30)%30]->envie;
                }
            }
            somme -= tableau[i][j]->envie;

            if (tableau[i][j]->envie==0 and somme==3)
                tableau[i][j]->envieGen=1;
            if (tableau[i][j]->envie)
                tableau[i][j]->envieGen=1;
            if (tableau[i][j]->envie==1 and somme != 3 and somme !=2)
                tableau[i][j]->envieGen=0;
        }
    }

    for(int i=0;i<30;i++)
    {
        for (int j=0;j<30;j++)
        {
            tableau[i][j]->envie=tableau[i][j]->envieGen;
            tableau[i][j]->envieGen=0;
            if (tableau[i][j]->envie == 1)
                tableau[i][j]->setText("X");
            if (tableau[i][j]->envie == 0)
                tableau[i][j]->setText("");
        }
    }

}

void MainWindow::infini()
{
    generation();
    QThread::msleep(100);
    emit fin();
}

void MainWindow::nettoyage()
{
    for(int i=0;i<30;i++)
    {
        for (int j=0;j<30;j++)
        {
            tableau[i][j]->envie=0;
            tableau[i][j]->envieGen=0;
            tableau[i][j]->setText("");
        }
    }
}

