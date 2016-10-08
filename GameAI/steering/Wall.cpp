#include "Wall.h"
#include <allegro5/allegro_primitives.h>
#include "Game.h"
#include "BoxCollider.h"

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
		mBox = BoxCollider(Vector2D(mStart.getX()- (mWidth / 4), mStart.getY() ), Vector2D(mWidth, abs(mStart.getY() - mEnd.getY())));
	}
	else if (mStart.getY() == mEnd.getY())
	{
		mBox = BoxCollider(Vector2D(mStart.getX() , mStart.getY()- (mWidth / 4)), Vector2D(abs(mStart.getX() - mEnd.getX()), mWidth));
	}
}

Wall::~Wall()
{
}

bool Wall::checkCollision(BoxCollider* unit)
{
	return mBox.checkBoxCollison(unit);
	
}

void Wall::draw()
{
	al_draw_line(mStart.getX(), mStart.getY(), mEnd.getX(), mEnd.getY(), al_map_rgb(127, 0, 127), mWidth);
}
