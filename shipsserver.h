#ifndef SHIPSSERVER_H
#define SHIPSSERVER_H

#include <QObject>
#include "restrequestlistener.h"
#include "restrequest.h"
#include "gamedata.h"

class ShipsServer : public RESTRequestListener
{
    Q_OBJECT

private:
    GameData gameData;

public:
    explicit ShipsServer(QObject *parent = 0);

signals:

public slots:
    void http_get_api_newgame( RESTRequest * request );
    void http_get_api_shotgame( RESTRequest * request );
    void http_get_api_getgame( RESTRequest * request );

};


#endif // SHIPSSERVER_H
