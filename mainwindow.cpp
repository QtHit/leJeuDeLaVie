#include "mainwindow.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "zone.h"
#include <QThread>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    taille_i=40;
    taille_j=80;

    ui->setupUi(this);
    this->resize(2000,1000);

    it=new QPushButton("Itération",this);
    it->move(0,taille_i*20);
    it->resize(200,40);

    go=new QPushButton("Go",this);
    go->move(200,taille_i*20);
    go->resize(100,40);

    stop=new QPushButton("Stop",this);
    stop->move(300,taille_i*20);
    stop->resize(100,40);

    clean=new QPushButton("clean",this);
    clean->move(400,taille_i*20);
    clean->resize(200,40);

    creation();

    connect(this->it,SIGNAL(clicked()),this,SLOT(gen()));
    connect(this->go,SIGNAL(clicked()),this,SLOT(infini()));
    connect(this,SIGNAL(fin()),this,SLOT(infini()));
    connect(this,SIGNAL(fin()),this,SLOT(tempo()));
    connect(this->clean,SIGNAL(clicked()),this,SLOT(nettoyage()));
    connect(this->go,SIGNAL(clicked()),this,SLOT(tempo()));

    connect(this->stop,SIGNAL(clicked(bool)),this,SLOT(canon()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::creation()
{
    for(int i=0;i<taille_i;i++)
    {
        for (int j=0;j<taille_j;j++)
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
    for(int i=0;i<taille_i;i++)
    {
        for (int j=0;j<taille_j;j++)
        {
            somme = 0;

            for(int k=-1;k<2;k++)
            {
                for (int l=-1;l<2;l++)
                {
                    somme += tableau[(i+k+taille_i)%taille_i][(j+l+taille_j)%taille_j]->envie;
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

    for(int i=0;i<taille_i;i++)
    {
        for (int j=0;j<taille_j;j++)
        {
            tableau[i][j]->envie=tableau[i][j]->envieGen;
            tableau[i][j]->envieGen=0;
            if (tableau[i][j]->envie == 1)
            {
                tableau[i][j]->setText("X");
                tableau[i][j]->setPalette(QColor("red"));
            }
            if (tableau[i][j]->envie == 0)
            {
                tableau[i][j]->setText("");
                tableau[i][j]->setPalette(QColor("white"));
            }
        }
    }
}


void MainWindow::infini()
{
    generation();
}


void MainWindow::nettoyage()
{
    for(int i=0;i<taille_i;i++)
    {
        for (int j=0;j<taille_j;j++)
        {
            tableau[i][j]->envie=0;
            tableau[i][j]->envieGen=0;
            tableau[i][j]->setText("");
            tableau[i][j]->setPalette(QColor("white"));
        }
    }
}

void MainWindow::tempo()
{
    QThread::msleep(200);
    emit fin();
}

void MainWindow::canon()
{
    tableau[4][0]->naissance(); tableau[5][0]->naissance(); tableau[4][1]->naissance(); tableau[5][1]->naissance();

    tableau[4][10]->naissance(); tableau[5][10]->naissance(); tableau[6][10]->naissance();

    tableau[3][11]->naissance(); tableau[7][11]->naissance();

    tableau[2][12]->naissance(); tableau[2][13]->naissance(); tableau[8][12]->naissance(); tableau[8][13]->naissance();

    tableau[5][14]->naissance();tableau[3][15]->naissance();tableau[7][15]->naissance();

    tableau[4][16]->naissance();tableau[5][16]->naissance();tableau[6][16]->naissance();tableau[5][17]->naissance();

    tableau[2][20]->naissance();tableau[2][21]->naissance();
    tableau[3][20]->naissance();tableau[3][21]->naissance();
    tableau[4][20]->naissance();tableau[4][21]->naissance();

    tableau[1][22]->naissance();tableau[5][22]->naissance();

    tableau[0][24]->naissance();tableau[1][24]->naissance();tableau[5][24]->naissance();tableau[6][24]->naissance();

    tableau[2][34]->naissance();tableau[3][34]->naissance();tableau[2][35]->naissance();tableau[3][35]->naissance();
}

