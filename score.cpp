#include "score.h"
#include <QFont>

Score::Score(QGraphicsItem *parent):QGraphicsTextItem(parent){
    s = 0;
    setPlainText(QString("Score: ") + QString::number(s));
    setDefaultTextColor(Qt::black);
    setFont(QFont("times",16));
}

void Score::increase(){
    s+=10;
    setPlainText(QString("Score: ") + QString::number(s));
    setDefaultTextColor(Qt::black);
    setFont(QFont("times",16));
}

void Score::increase(int value){
    s+=value;
    setPlainText(QString("Score: ") + QString::number(s));
    setDefaultTextColor(Qt::black);
    setFont(QFont("times",16));
}

int Score::getScore(){
    return s;
}

