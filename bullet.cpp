#include <QTimer>
#include <QGraphicsScene>
#include <QTimer>
#include <QDebug>
#include <QList>

#include "bullet.h"
#include "game.h"
#include "enemy.h"

// declaração da variavel do tipo extern
// indica que essa variavel já foi declarada em algum outro arquivo do projeto
extern Game * game;

Bullet::Bullet(){
    // desenhar o tiro
    setPixmap(QPixmap(":/images/pBullet.png").scaled(28,50,Qt::KeepAspectRatio));
    // conectar o timer com o movimento
    timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));
    // inicializar o timer
    timer->start(50);
}

void Bullet::move(){
    if(!game->play) return;
    QList<QGraphicsItem *> colliding_item = collidingItems();
    for(int i = 0; i < colliding_item.size(); i++){
        if(typeid(*(colliding_item[i])) == typeid(Enemy)){
            game->score->increase();
            if(game->score->getScore() >= 150 && !game->invoc){
                game->addBoss();
                game->invoc = !game->invoc;
            }
            scene()->removeItem(colliding_item[i]);
            scene()->removeItem(this);
            explosionsound = new QMediaPlayer();
            explosionsound->setMedia(QUrl("qrc:/sounds/sfx/Explosion2.mp3"));
            if(explosionsound->state() == QMediaPlayer::PlayingState) explosionsound->setPosition(0);
            else if(explosionsound->state() == QMediaPlayer::StoppedState)explosionsound->play();
            delete colliding_item[i];
            delete this;
            return;
        }
        if(typeid(*(colliding_item[i])) == typeid(Bullete)){
            game->score->increase(1);
            scene()->removeItem(colliding_item[i]);
            scene()->removeItem(this);
            delete colliding_item[i];
            delete this;
            return;
        }
        else if(typeid(*(colliding_item[i])) == typeid(Boss)){
            game->boss->hp--;
            if(game->boss->hp <= 0) game->win();
            scene()->removeItem(this);
            explosionsound = new QMediaPlayer();
            explosionsound->setMedia(QUrl("qrc:/sounds/sfx/Explosion2.mp3"));
            if(explosionsound->state() == QMediaPlayer::PlayingState) explosionsound->setPosition(0);
            else if(explosionsound->state() == QMediaPlayer::StoppedState) explosionsound->play();
            delete this;
            return;
        }
    }
    setPos(x(),y()-10);
    if(pos().y() < -10){
        scene()->removeItem(this);
        delete this;
    }
}

Laser::Laser(){
    if(!game->play) return;
    setPixmap(QPixmap(":/lb/images/lb0.png"));
    setPos(220, 120);
    timer1 = new QTimer();
    connect(timer1, SIGNAL(timeout()), this, SLOT(change()));
    timer1->start(166);
    timer2 = new QTimer();
    connect(timer2, SIGNAL(timeout()), this, SLOT(hit()));
    timer2->start(1000);
}

void Laser::change(){
    if(!game->play) return;
    if(game->boss->sprite == 6) game->boss->sprite = 0;
    else game->boss->sprite ++;
    QPixmap pix = game->boss->beam.at(game->boss->sprite);
    setPixmap(pix.scaled(x(),580-y()));
}

void Laser::hit(){
    if(!game->play) return;
    QList<QGraphicsItem *> colliding_item = collidingItems();
    for(int i = 0; i < colliding_item.size(); i++){
        if(typeid(*(colliding_item[i]))== typeid(Player)) game->health->decrease();
    }
}

Bullete::Bullete(){
    if(!game->play) return;
    setPixmap(QPixmap(":/images/eBullet.png").scaled(28,50, Qt::KeepAspectRatio));
    timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));
    timer->start(50);
}

void Bullete::move(){
    if(!game->play) return;
    QList<QGraphicsItem *> colliding_item = collidingItems();
    for(int i = 0; i < colliding_item.size(); i++){
        if(typeid(*(colliding_item[i]))== typeid(Player)){
            game->health->decrease();
            scene()->removeItem(this);
            explosionsound = new QMediaPlayer();
            explosionsound->setMedia(QUrl("qrc:/sounds/sfx/Explosion2.mp3"));
            if(explosionsound->state() == QMediaPlayer::PlayingState) explosionsound->setPosition(0);
            else if(explosionsound->state() == QMediaPlayer::StoppedState) explosionsound->play();
            delete this;
            return;
        }
    }
    setPos(x(),y()+10);
    if(pos().y() > 610){
        scene()->removeItem(this);
        delete this;
    }
}
