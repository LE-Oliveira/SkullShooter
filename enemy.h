#ifndef ENEMY_H
#define ENEMY_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QMediaPlayer>

class Enemy: public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
    public:
        Enemy();
        QTimer * timer1;
        QTimer * timer2;
    public slots:
        void move();
        void shoot();
    private:
        QMediaPlayer * bulletsound;
};

#endif // ENEMY_H

