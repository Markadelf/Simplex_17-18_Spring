#pragma once
#include "OctreeAddress.h"
#include "Definitions.h"

using namespace Simplex;
class Octree
{
	vector3 _center;
	vector3 _halfDistance;

public:
	Octree();
	~Octree();

	void Initialize(vector3 min, vector3 max);

	OctreeAddress GetAddress(vector3 min, vector3 max);
private:
	unsigned _int8 Quad(vector3 center, vector3 location);
};

