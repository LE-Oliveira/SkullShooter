#include <QGraphicsPixmapItem>
#include <QObject>
#include <QTimer>
#include <string>

#include "boss.h"
#include "game.h"

extern Game * game;

Boss::Boss(){
    hp = 25;
    open = false;
    QPixmap pix(":/images/boss.png");
    setPixmap(pix.scaled(90, 90, Qt::KeepAspectRatio));
    QString s;
    for(int i = 0; i<7; i++){
        s = QString(":/lb/images/lb") + QString::number(i) + QString(".png");
        beam.push_back(s);
    }
    timer1 = new QTimer();
    connect(timer1, SIGNAL(timeout()), this, SLOT(move()));
    timer1->start(50);
    timer2 = new QTimer();
    connect(timer2, SIGNAL(timeout()), this, SLOT(shoot()));
    timer2->start(2000);
    setPos(300,50);
    game->scene->addItem(this);
    l = new Laser();
}

void Boss::move(){
    int a, b;
    srand(time(NULL));
    if(open){
        a = rand() % 5 + 1;
        b = rand() % 5 + 1;
    }
    else{
        a = rand() % 20 + 1;
        b = rand() % 20 + 1;
    }
    a = a * (rand() % 3 - 1);
    b = b * (rand() % 3 - 1);
    if(x()+a<0||x()+a>730) a = -a;
    if(y()+b<0||y()+b>400) b = -b;
    setPos(x() + a, y() + b);
}

void Boss::shoot(){
    QPixmap pix;
    if(!open){
        pix = QPixmap(":/images/bosslaser.png");
        l = new Laser;
        l->setPos(x(), y());
        game->scene->addItem(l);
    }
    else
    {
        pix = QPixmap(":/images/boss.png");
        game->scene->removeItem(l);
        delete l;
    }
    setPixmap(pix.scaled(90, 90, Qt::KeepAspectRatio));
    open = !open;

}

void Boss::stop(){

}
