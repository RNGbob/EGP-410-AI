#pragma once

#include "Game.h"
#include "GameApp.h"
#include "Sprite.h"
#include "Steering.h"
#include <vector>
#include "Vector2D.h"
#include "BoxCollider.h"

enum EnemyType
{
	Purple,
	Green,
	Orange,
	Lime
};


class UnitManager : public Trackable
{
public:
	UnitManager();
	~UnitManager();

	void init(SpriteManager* &mpSprMan);
	void cleanup();
	
	void addUnit(SteeringType steeringType, Vector2D pos, IDType spr);
	void deleteUnit(KinematicUnit* unit);
	void deleteRandomUnit();

	void update(float time);
	void draw(GraphicsBuffer* gBuff);
	void changeVels1(float val);


	KinematicUnit* getPlayer(){ return mPlayerUnit; }
	KinematicUnit* getUnit(int i) { return mUnitList[i]; } // safe as long as i is set to be under list.size()
	KinematicUnit* checkAllCollisions(BoxCollider* mBox);
	int getSize() { return mUnitList.size(); }

private:

	std::vector<KinematicUnit*> mUnitList;
	KinematicUnit* mPlayerUnit; // I sometimes go back and forth from a seperate player unit or tracking the unit within Unit list
	SpriteManager* mpSpriteManager;
	
	
};

