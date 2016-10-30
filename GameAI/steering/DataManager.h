#pragma once
#include "Game.h"
#include <fstream>
#include <string>

const std::string SAVE_FILE = "saveData.txt";


class DataManager : public Trackable
{
public:
	DataManager();
	~DataManager();

	void save();
	void load();


private:
};