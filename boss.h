#ifndef BOSS_H
#define BOSS_H

#include <QGraphicsItem>
#include <QObject>
#include <QGraphicsPixmapItem>
#include <string>

#include "bullet.h"

class Boss : public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
    public:
        Boss();
        QVector<QString> beam;
        int sprite = 0;
        int hp;
        Laser * l;
        bool open;
        QTimer * timer1;
        QTimer * timer2;
        void stop();
    public slots:
        void move();
        void shoot();
};
#endif // BOSS_H
