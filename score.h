#ifndef SCORE_H
#define SCORE_H

#include <QGraphicsTextItem>

class Score: public QGraphicsTextItem{
    public:
        Score(QGraphicsItem *parent = 0);
        void increase();
        void increase(int value);
        int getScore();
        int s;
};

#endif // SCORE_H
