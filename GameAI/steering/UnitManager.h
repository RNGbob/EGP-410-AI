#pragma once

#include "Game.h"
#include "Sprite.h"
#include <vector>
#include "Vector2D.h"

class UnitManager : public Trackable
{
public:
	UnitManager();
	~UnitManager();

	void init(SpriteManager* &mpSprMan);
	void cleanup();
	
	void addUnit(Method steeringType);
	void deleteUnit();
	void deleteRandomUnit();

	void update(float time);
	void draw(GraphicsBuffer* gBuff);

	KinematicUnit* getPlayer(){ return mPlayerUnit; }


private:

	std::vector<KinematicUnit*> mUnitList;
	KinematicUnit* mPlayerUnit; // I sometimes go back and forth from a seperate player unit or tracking the unit within Unit list
	SpriteManager* mpSpriteManager;
	
};

