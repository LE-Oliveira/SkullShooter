#include <QTimer>
#include <QGraphicsScene>
#include <stdlib.h>
#include <QDebug>

#include "bullet.h"
#include "enemy.h"
#include "game.h"

extern Game * game;

Enemy::Enemy(){
    int a = rand() % 700;
    int b = rand() % 300;
    setPos(a, b);
    setPixmap(QPixmap(":/images/enemy.png").scaled(79, 133));
    timer1 = new QTimer();
    connect(timer1, SIGNAL(timeout()), this, SLOT(move()));
    timer1->start(50);
    timer2 = new QTimer();
    connect(timer2, SIGNAL(timeout()), this, SLOT(shoot()));
    timer2->start(1500);
    bulletsound = new QMediaPlayer();
    bulletsound->setMedia(QUrl("qrc:/sounds/sfx/Laser.mp3"));
}

void Enemy::move(){
    if(!game->play)return;
    srand(time(NULL));
    int aux = (rand() % 5 + 1) * (rand() %3 - 1);
    if(x() + aux > 730||x()+ aux <0) aux = -aux;
    setPos(x()+aux,y());
}

void Enemy::shoot(){
    if(!game->play)return;
    Bullete * bullete = new Bullete();
    bullete->setPos(x()+28,y()+85);
    scene()->addItem(bullete);
    if(bulletsound->state() == QMediaPlayer::PlayingState) bulletsound->setPosition(0);
    else if(bulletsound->state() == QMediaPlayer::StoppedState) bulletsound->play();
}
