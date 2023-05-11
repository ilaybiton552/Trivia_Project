#pragma once
#include <string>
#include <iostream>
#include <io.h>
#include "IDatabase.h"
#include "sqlite3.h"

using std::cout;
using std::endl;
using std::string;

class SqliteDatabase : public IDatabase
{
public:
	//Methods
	virtual bool open() override;
	virtual bool close() override;
	virtual int doesUserExist(const string username) override;
	virtual int doesPasswordMatch(const string username, const string password) override;
	virtual int addNewUser(const string username, const string password, const string email) override;

private:
	//Field
	sqlite3* m_database;

	//Method
	bool sqlQuery(sqlite3* db, const char* sqlStatement);
};

