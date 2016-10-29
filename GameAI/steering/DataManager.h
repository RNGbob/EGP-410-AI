#pragma once
#include "Game.h"
#include <fstream>
#include <string>

const std::string SAVE_FILE = "saveData.txt";

/*
enum Method
{
	Arrive,
	Seek,
	Wander,
	WanderSeek,
	WanderFlee,
	Boids
};

enum ChangeableVal
{
	EnemyVel,
	ReactionRadius,
	AngularVel,
	AvoidRadius,
	AlignWeight,
	CohesionWeight,
	SeperateWeight
};*/


class DataManager : public Trackable
{
public:
	DataManager();
	~DataManager();

	void save();
	void load();


private:
};