#ifndef BULLET_H
#define BULLET_H

#include <QGraphicsPixmapItem>
#include <QMediaPlayer>
#include <QObject>

class Bullet: public QObject,public QGraphicsPixmapItem{
    Q_OBJECT
    public:
        Bullet();
    public slots:
        void move();
    private:
        QTimer* timer;
        QMediaPlayer * explosionsound;
};

class Bullete: public QObject,public QGraphicsPixmapItem{
    Q_OBJECT
    public:
        Bullete();
    public slots:
        void move();
    private:
        QTimer * timer;
        QMediaPlayer * explosionsound;
};

class Laser: public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
    public:
        Laser();
    public slots:
        //void move();
        void change();
        void hit();
    private:
        QTimer* timer1;
        QTimer* timer2;
};

#endif // BULLET_H
