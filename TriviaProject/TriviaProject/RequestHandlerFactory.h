#pragma once
#include "LoginManager.h"
#include "LoginRequestHandler.h"
#include "MenuRequestHandler.h"
#include "RoomManager.h"
#include "StatisticsManager.h"
#include "LoggedUser.h"
#include "RoomAdminRequestHandler.h"
#include "RoomMemberRequestHandler.h"
#include "GameManager.h"
#include "GameRequestHandler.h"

class LoginRequestHandler;
class MenuRequestHandler;
class RoomAdminRequestHandler;
class RoomMemberRequestHandler;
class GameRequestHandler;

class RequestHandlerFactory
{
public:
	//Methods
	RequestHandlerFactory(IDatabase* database); //c'tor

	LoginRequestHandler* createLoginRequestHandler();
	MenuRequestHandler* createMenuRequestHandler(const LoggedUser loggedUser);
	RoomAdminRequestHandler* createRoomAdminRequestHandler(const LoggedUser admin, const Room& room);
	RoomMemberRequestHandler* createRoomMemberRequestHandler(const LoggedUser member, const Room& room);
	GameRequestHandler* createGameRequestHandler(const LoggedUser& loggedUser, const Game game);

	//Getters
	LoginManager& getLoginManager();
	StatisticsManager& getStatisticsManager();
	RoomManager& getRoomManager();
	GameManager& getGameManager();
	IDatabase* getDatabase();

private:
	//Fields
	IDatabase* m_database;
	LoginManager m_loginManager;
	RoomManager m_roomManager;
	StatisticsManager m_statisticsManager;
	GameManager m_gameManager;
};

