#include "mainwindow.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "zone.h"
#include <QThread>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    taille_i=40;
    taille_j=80;

    ui->setupUi(this);
    this->resize(taille_j*20+2,taille_i*20);

    it=new QPushButton("Itération",this);
    it->move(0,taille_i*20);
    it->resize(200,40);

    go=new QPushButton("Go",this);
    go->move(200,taille_i*20);
    go->resize(100,40);

    stop=new QPushButton("Stop",this);
    stop->move(300,taille_i*20);
    stop->resize(100,40);

    clean=new QPushButton("Clean",this);
    clean->move(400,taille_i*20);
    clean->resize(200,40);

    canonB=new QPushButton("Canon",this);
    canonB->move(600,taille_i*20);
    canonB->resize(200,40);

    moulinB=new QPushButton("Moulin",this);
    moulinB->move(800,taille_i*20);
    moulinB->resize(200,40);

    quitter=new QPushButton("Quitter",this);
    quitter->move(1000,taille_i*20);
    quitter->resize(280,40);

    creation();

    updateTimer = new QTimer(this);
    connect(updateTimer, SIGNAL(timeout()), this, SLOT(gen()));
    connect(go,SIGNAL(clicked(bool)),this,SLOT(goinfini()));
    connect(stop,SIGNAL(clicked(bool)),this,SLOT(stopinfini()));
    connect(it,SIGNAL(clicked()),this,SLOT(gen()));
    connect(clean,SIGNAL(clicked()),this,SLOT(nettoyage()));
    connect(quitter,SIGNAL(clicked(bool)),this,SLOT(close()));
    connect(canonB,SIGNAL(clicked(bool)),this,SLOT(canon()));
    connect(moulinB,SIGNAL(clicked(bool)),this,SLOT(moulingen()));
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
            tableau[i][j]->setPalette(QColor("green"));
        }
    }
}

void MainWindow::gen()
{
    generation();
}

void MainWindow::goinfini()
{
    updateTimer->start(500);
}

void MainWindow::stopinfini()
{
    updateTimer->stop();
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
                tableau[i][j]->setPalette(QColor("green"));
            }
        }
    }
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
            tableau[i][j]->setPalette(QColor("green"));
        }
    }
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

void MainWindow::moulingen()
{
    moulin(5,5);
    moulin(5,20);
    moulin(5,35);
    moulin(5,50);

    moulin(20,5);
    moulin(20,20);
    moulin(20,35);
    moulin(20,50);

    moulin(35,5);
    moulin(35,20);
    moulin(35,35);
    moulin(35,50);
}

void MainWindow::moulin(int deb_i,int deb_j)
{

    for (int i=deb_i;i<deb_i+9;i++)
    {
        for (int j=deb_j;j<deb_j+9;j++)
        {
            tableau[i][j]->naissance();
        }
    }

    for (int i=deb_i+2;i<deb_i+7;i++)
    {
        for (int j=deb_j+2;j<deb_j+7;j++)
        {
            tableau[i][j]->mort();
        }
    }

    tableau[deb_i][deb_j+6]->mort();
    tableau[deb_i+1][deb_j+6]->mort();
    tableau[deb_i+2][deb_j]->mort();
    tableau[deb_i+2][deb_j+1]->mort();

    tableau[deb_i+7][deb_j+2]->mort();
    tableau[deb_i+8][deb_j+2]->mort();
    tableau[deb_i+6][deb_j+7]->mort();
    tableau[deb_i+6][deb_j+8]->mort();
}
