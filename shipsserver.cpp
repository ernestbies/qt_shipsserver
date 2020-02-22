#include "shipsserver.h"
#include "status.h"
#include "gamedata.h"
#include <QDebug>



/*
http://localhost:8080/api/shotgame?user=ernest&shot=02
http://localhost:8080/api/newgame?user=ernest
http://localhost:8080/api/getgame?user=ernest
 */


ShipsServer::ShipsServer(QObject *parent) : RESTRequestListener("/", parent)
{

}

void ShipsServer::http_get_api_newgame(RESTRequest *request)
{    
    QMap<QString, QString> params = request->params();
    QString user = request->params()["user"];
    Status status = gameData.newGame(user);    
    request->result()->setData(status.toString());
    request->result()->setStatusCode( 200 );
}

void ShipsServer::http_get_api_getgame(RESTRequest *request) {

    QMap<QString, QString> params = request->params();
    QString user = request->params()["user"];
    Status status = gameData.getGame(user);
    request->result()->setData(status.toString());
    request->result()->setStatusCode( 200 );
}

void ShipsServer::http_get_api_shotgame(RESTRequest *request) {
    QMap<QString, QString> params = request->params();
    QString user = request->params()["user"];
    QString shot = request->params()["shot"];
    Status status = gameData.shotGame(user, shot);
    request->result()->setData(status.toString());
    request->result()->setStatusCode( 200 );

}

