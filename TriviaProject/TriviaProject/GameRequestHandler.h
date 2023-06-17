#pragma once
#include "IRequestHandler.h"
#include "GameManager.h"
#include "RequestHandlerFactory.h"

enum GAME_CODES {LEAVE_GAME_CODE = 114, GET_QUESTION_CODE, SUBMIT_ANSWER_CODE, GET_GAME_RESULT_CODE};

class RequestHandlerFactory;

class GameRequestHandler : public IRequestHandler
{
public:
	GameRequestHandler(Game& game, const LoggedUser& loggedUser, GameManager& gameManager, RequestHandlerFactory& handlerFactory);

	bool isRequestRelevant(const RequestInfo& requestInfo) override;
	RequestResult handleRequest(const RequestInfo& requestInfo) override;

	Game getGame() const;

private:
	Game& m_game;
	LoggedUser m_user;
	GameManager& m_gameManager;
	RequestHandlerFactory& m_handlerFactory;

	RequestResult getQuestion(const RequestInfo& requestInfo);
	RequestResult submitAnswer(const RequestInfo& requestInfo);
	RequestResult getGameResults(const RequestInfo& requestInfo);
	RequestResult leaveGame(const RequestInfo& requestInfo);

};

