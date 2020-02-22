#include "gamedata.h"
#include "status.h"
#include <QDebug>
#include <QDateTime>
#include <QFile>
#include <QDataStream>

GameData::GameData()
{
    QFile file("games.dat");
    if (file.exists()) {
        readFile();
    }
}

Status GameData::getGame(QString user) {    
    for(Game g: games) {
        if(g.getUser()==user) {
            qDebug() << QDateTime::currentDateTimeUtc().toString() +" - Wczytanie gry uzytkownika: "+user;
            return g.getStatus();
        }
    }
    return (Status("NOGAME", "", 0, 0, ""));
}

Status GameData::newGame(QString user) {
    Game newGame(user);
    int gameIndex = 0;
    for(Game g: games) {
        if(g.getUser()==user) {
            games.insert(gameIndex, newGame);
            saveFile();
            return (Status("NEWGAME", "", 0, newGame.getSteps(), QString(newGame.getBoard())));
        }
        gameIndex++;
    }
    games.append(newGame);
    qDebug() << QDateTime::currentDateTimeUtc().toString() +" - Nowa gra uzytkownika: "+user;
    saveFile();
    return (Status("NEWGAME", "", 0, newGame.getSteps(), QString(newGame.getBoard())));
}


Status GameData::shotGame(QString user, QString shot) {    
    for (int i=0; i<games.size(); i++) {
        if (games[i].getUser()==user) {
            qDebug() << QDateTime::currentDateTimeUtc().toString() +" - Strzal uzytkownika: "+user+", na pozycje: "+shot;
            Status status = games[i].shot(shot);
            saveFile();
            return status;
        }
    }
    return (Status("SHOT", "", 0, 0, ""));
}

void GameData::showGame(Game g){
    qDebug() << "User:"+ g.getUser()+" steps:"+QString::number(g.getSteps())+" board:"+QString(g.getBoard());
    for(int i=0;i<g.getShips().length();i++){
        qDebug() <<g.getShips()[i].getName();
        qDebug() <<g.getShips()[i].getPositions();
    }
}


void GameData::saveFile() {

    QFile file("games.dat");
    if (!file.open(QIODevice::WriteOnly)) {
      qDebug() << QDateTime::currentDateTimeUtc().toString() +" - Blad! zapisu pliku games.dat";
      return;
    }

    QDataStream out(&file);
    out.setVersion(QDataStream::Qt_4_7);

    out << QString::number(games.size());
    for (int i=0; i<games.size();i++){
        out << games[i];
    }
    //out << games;

    file.flush();
    file.close();
}

void GameData::readFile() {

    QFile file("games.dat");
    if (!file.open(QIODevice::ReadOnly)) {
      qDebug() << QDateTime::currentDateTimeUtc().toString() +" - Blad! wczytania pliku games.dat";
      return;
    }

    QDataStream in(&file);
    in.setVersion(QDataStream::Qt_4_7);

    QString tmp;
    int count;

    in >> tmp; count = tmp.toInt();
    for (int i=0; i<count;i++){
        Game* game = new Game();
        in >> game;
        games.append(*game);
    }

    //in >> games;

    file.close();
}

