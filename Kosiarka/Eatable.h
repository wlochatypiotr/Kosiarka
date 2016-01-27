#pragma once
#include "Entity.h"


class Eatable :public Entity
{
public:
	Eatable(const Eatable&) = delete;
	Eatable& operator=(const Eatable&) = delete;

	Eatable(Configuration::Textures tex_id, World& world);
	
	virtual int get_points() const = 0;
	virtual void OnDestroy();
	static int count_;
};
