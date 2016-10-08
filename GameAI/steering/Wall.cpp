#include "Wall.h"
#include <allegro5/allegro_primitives.h>
#include "Game.h"

Wall::Wall()
{
}

Wall::Wall(Vector2D start, Vector2D end, float width)
:mStart(start),
mEnd(end),
mWidth(width)
{
	//checks vertical or horizontal then makes new vectors for collision math.
	if (mStart.getX()==mEnd.getX())
	{
		mCorner = Vector2D(mStart.getX(), mStart.getY()-(mWidth/2));
		mDim = Vector2D(mWidth, abs(mStart.getY() - mEnd.getY()));
	}
	else if (mStart.getY() == mEnd.getY())
	{
		mCorner = Vector2D(mStart.getX() - (mWidth / 2), mStart.getY());
		mDim = Vector2D(abs(mStart.getX()-mEnd.getX()),mWidth);
	}
}

Wall::~Wall()
{
}

bool Wall::checkCollision(KinematicUnit* unit)
{
	if (unit->getPosition().getX() > (mCorner.getX() + mDim.getX()) ||
		unit->getPosition().getY() > (mCorner.getY() + mDim.getY()) ||
		mCorner.getX() > (unit->getPosition().getX() + unit->getDimension().getX()) ||
		mCorner.getY() > (unit->getPosition().getY() + unit->getDimension().getY())
		)
		{return false;}
	else { return true; }
		
		
		
		/*( unit->getPosition().getX() < (mCorner.getX() + mDim.getX())				&&
		(unit->getPosition().getX() + unit->getDimension().getX()) > mCorner.getX() &&
		unit->getPosition().getY() < (mCorner.getY() + mDim.getY())					&&
		(unit->getPosition().getY() + unit->getDimension().getY()) > mCorner.getY()
		)*/
	



	
}

void Wall::draw()
{
	al_draw_line(mStart.getX(), mStart.getY(), mEnd.getX(), mEnd.getY(), al_map_rgb(127, 0, 127), mWidth);
}
