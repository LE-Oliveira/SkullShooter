#include "player.h"
#include "bullet.h"
#include "enemy.h"
#include "game.h"

#include <QGraphicsScene>
#include <QObject>
#include <QGraphicsItem>
#include <QDebug>
#include <QKeyEvent>

extern Game * game;

Player::Player(QGraphicsItem *parent): QGraphicsPixmapItem(parent){
    setPixmap(QPixmap(":/images/player.png").scaled(80, 80));

    bulletsound = new QMediaPlayer();
    bulletsound->setMedia(QUrl("qrc:/sounds/sfx/Laser.mp3"));
}

void Player::keyPressEvent(QKeyEvent *event){
    if(!game->play) return;
    if(event->key() == Qt::Key_Left){
        // limite para não sair da tela
        if(pos().x() > 0) setPos(x()-10,y());
    }
    else if(event->key() == Qt::Key_Right){
        // limite para não sair da tela
        if(pos().x() < 730 ) setPos(x()+10,y());
    }
    else if(event->key() == Qt::Key_Up){
        if(pos().y() > 0) setPos(x(),y()-10);
    }
    else if(event->key() == Qt::Key_Down) {
        if(pos().y() < 550) setPos(x(),y()+10);
    }
    // criar tiro (bullet)
    else if(event->key() == Qt::Key_Space){
        // teste via Debug
        // qDebug()<<"Bullet created";
        Bullet * bullet = new Bullet();
        bullet->setPos(x()+35,y()-30);
        scene()->addItem(bullet);

        // adicionar barulho de tiro
        // analizando o estado de reprodução de Player
        if(bulletsound->state() == QMediaPlayer::PlayingState){
            // caso o som ainda esta tocando resetar o Player para posição inicial
            bulletsound->setPosition(0);
        }
        else if(bulletsound->state() == QMediaPlayer::StoppedState){
            bulletsound->play();
        }
    }
}

void Player::spawn(){
    // cria inimigo
    if(!game->play) return;
    Enemy * enemy = new Enemy();
    scene()->addItem(enemy);
}
