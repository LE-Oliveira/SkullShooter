#include <QFont>
#include "health.h"
#include "game.h"

extern Game * game;

Health::Health(QGraphicsItem *parent):QGraphicsTextItem(parent){
    health = 10;
    setPlainText(QString("Health: ") + QString::number(health));
    setDefaultTextColor(Qt::green);
    setFont(QFont("times",16));
}

void Health::decrease(){
    health--;
    setPlainText(QString("Health: ") + QString::number(health));
    setDefaultTextColor(Qt::green);
    setFont(QFont("times",16));
    if(health < 1){
        qDebug() << game->scene->items().size();
        game->lose();
    }
}

int Health::getHealth(){
    return health;
}

