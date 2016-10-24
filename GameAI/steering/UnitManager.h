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
	void changeVels1(float val);


	KinematicUnit* getPlayer(){ return mPlayerUnit; }
	KinematicUnit* getUnit(int i) { return mUnitList[i]; } // safe as long as i is set to be under list.size()
	int getSize() { return mUnitList.size(); }

private:

	std::vector<KinematicUnit*> mUnitList;
	KinematicUnit* mPlayerUnit; // I sometimes go back and forth from a seperate player unit or tracking the unit within Unit list
	SpriteManager* mpSpriteManager;
	
	
};

