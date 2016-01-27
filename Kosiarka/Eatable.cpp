#include "stdafx.h"
#include "Fruit.h"

int Eatable::count_ = 0;
Eatable::Eatable(Configuration::Textures tex_id, World & world) : Entity(tex_id, world)
{
	++count_;
}

void Eatable::OnDestroy()
{
	Entity::OnDestroy();
	Configuration::IncreaseScore(get_points());
	--count_;
}


