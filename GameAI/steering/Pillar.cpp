#include "Pillar.h"
#include <allegro5/allegro_primitives.h>

Pillar::Pillar()
{
}

Pillar::Pillar(Vector2D pos, float radius)
:mPos(pos)
,mRadius(radius)
{
	mCircle = CircleCollider(mPos, mRadius);
}

Pillar::~Pillar()
{
}

bool Pillar::checkCollision(BoxCollider * unit)
{
	return mCircle.checkCollison(unit);
}

bool Pillar::checkCollision(CircleCollider * unit)
{
	return mCircle.checkCollison(unit);
}

void Pillar::draw()
{
	al_draw_filled_circle(mPos.getX(), mPos.getY(), mRadius, al_map_rgb(127, 0, 160));
}
