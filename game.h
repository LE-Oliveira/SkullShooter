#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsScene>

#include "player.h"
#include "score.h"
#include "health.h"
#include "boss.h"

class Game: public QGraphicsView{
    public:
        Game(QWidget * parent=0);
        QGraphicsScene * scene;
        Player * player;
        Score * score;
        Health *health;
        Boss * boss;
        QMediaPlayer * music;
        bool invoc;
        bool play = true;
        void addBoss();
        void lose();
        void win();
};

#endif // GAME_H
