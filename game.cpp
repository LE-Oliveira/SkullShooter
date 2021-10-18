#include <QGraphicsTextItem>
#include <QGraphicsScene>
#include <QTimer>
#include <QImage>
#include <QBrush>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QIcon>
#include <QString>

#include "game.h"
#include "enemy.h"


Game::Game(QWidget *parent){
    invoc = false;
    setWindowTitle("Skull Shooter");
    setWindowIcon(QIcon(":/images/skullShooter.ico"));
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,800,600);
    scene->setBackgroundBrush(QBrush(QImage(":/images/spaceground.png").scaled(800,600)));
    setScene(scene);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(800,600);
    player = new Player();
    player->setPos(400,500);
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();
    scene->addItem(player);
    QTimer * timer = new QTimer();
    QObject::connect(timer,SIGNAL(timeout()),player,SLOT(spawn()));
    timer->start(2000);
    score = new Score();
    scene->addItem(score);
    health = new Health();
    health->setPos(health->x(), health->y()+25);
    scene->addItem(health);
    music = new QMediaPlayer(this);
    music->setMedia(QUrl("qrc:/sounds/sfx/Soundtrack.mp3"));
    music->play();

    show();
}

void Game::addBoss(){
    boss = new Boss();
    music->stop();
    music->setMedia(QUrl("qrc:/sounds/sfx/bossMusic.mp3"));
    music->play();
}

void Game::lose(){
    play = false;
    for(int i = scene->items().size() - 1; i > -1; i--){
        scene->items().at(i)->hide();
        music->stop();
        qDebug() << scene->items().size();
        if(typeid(*(scene->items().at(i)))== typeid(Health)) scene->items().at(i)->show();
    }
    scene->setBackgroundBrush(QBrush(QPixmap(":/images/go.png").scaled(800,600)));
    health->setPlainText(QString("YOU LOST"));
    health->setDefaultTextColor(Qt::red);
    health->setFont(QFont("gabriola",30));
    health->setPos(330,260);
    music->setMedia(QUrl("qrc:/sounds/sfx/deadUR.mp3"));
    music->play();
}

void Game::win(){
    play = false;
    for(int i = scene->items().size() - 1; i > -1; i--){
        scene->items().at(i)->hide();
        music->stop();
        if(typeid(*(scene->items().at(i)))== typeid(Score)) scene->items().at(i)->show();
        if(typeid(*(scene->items().at(i)))== typeid(Health)) scene->items().at(i)->show();
    }
    scene->setBackgroundBrush(QBrush(QPixmap(":/images/win.png").scaled(800,600)));
    health->setPlainText(QString("YOU WIN"));
    health->setDefaultTextColor(Qt::green);
    health->setFont(QFont("gabriola",30));
    health->setPos(330,260);
    score->s+=100;
    QString str;
    score->setPlainText(QString("Score: ") + str.setNum(score->s));
    score->setDefaultTextColor(Qt::white);
    setFont(QFont("times",16));
    score->setPos(340,220);
    music->setMedia(QUrl("qrc:/sounds/sfx/win.mp3"));
    music->play();
}
