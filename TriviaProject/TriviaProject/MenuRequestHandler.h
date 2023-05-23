#pragma once
#include "IRequestHandler.h"
#include "LoggedUser.h"
#include "StatisticsManager.h"
#include "RequestHandlerFactory.h"

enum CODES {SIGNOUT_CODE = 103, GET_ROOM_CODE, GET_PLAYERS_CODE, GET_STATS_CODE, 
			GET_HIGH_SCORE_CODE, JOIN_ROOM_CODE, CREATE_ROOM_CODE};

class RequestHandlerFactory;

class MenuRequestHandler : public IRequestHandler
{
public:
	MenuRequestHandler(const LoggedUser user, RoomManager& roomManager, StatisticsManager& statisticsManager, RequestHandlerFactory& handlerFactory);

	virtual bool isRequestRelevant(const RequestInfo& requestInfo) override;
	virtual RequestResult handleRequest(const RequestInfo& requestInfo) override;

private:
	LoggedUser m_user;
	RoomManager& m_roomManager;
	StatisticsManager& m_statisticsManager;
	RequestHandlerFactory& m_handlerFactory;

	RequestResult signout(const RequestInfo request);
	RequestResult getRooms(const RequestInfo request);
	RequestResult getPlayersInRoom(const RequestInfo request);
	RequestResult getPersonalStats(const RequestInfo request);
	RequestResult getHighScore(const RequestInfo request);
	RequestResult joinRoom(const RequestInfo request);
	RequestResult createRoom(const RequestInfo request);

};
