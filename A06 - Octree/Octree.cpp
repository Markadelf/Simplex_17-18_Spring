#include "Octree.h"



Octree::Octree()
{
}


Octree::~Octree()
{
}

void Octree::Initialize(vector3 min, vector3 max)
{
	//The center is between the minimum and the maximum
	_center = vector3((min.x + max.x) / 2, (min.y + max.y) / 2, (min.y + max.y) / 2);
	//The half distance is the largest half distance
	_halfDistance = max - _center;
}

//Get an address from the Octree
OctreeAddress Octree::GetAddress(vector3 min, vector3 max)
{
	OctreeAddress ret = OctreeAddress();

	vector3 cen = _center;
	vector3 bounds = _halfDistance;

	for (size_t i = 0; i < OctreeAddress::depth; i++)
	{
		unsigned _int8 a = Quad(cen, min);
		unsigned _int8 b = Quad(cen, max);
		if (a == b && a != 0) {
			ret.Set(i, a);
			bounds.x /= 2;
			bounds.y /= 2;
			bounds.z /= 2;
			if (min.x > cen.x)
				cen.x += bounds.x;
			else
				cen.x -= bounds.x;
			if (min.y > cen.y)
				cen.y += bounds.y;
			else
				cen.y -= bounds.y;
			if (min.z > cen.z)
				cen.z += bounds.z;
			else
				cen.z -= bounds.z;
		}
		else
			return ret;
	}
	return ret;
}

unsigned _int8 Octree::Quad(vector3 center, vector3 location)
{
	if(location.x == center.x || location.y == center.y || location.z == center.z)
		return 0;
	_int8 ret = 1;
	if (location.x > center.x)
		ret = ret | (1 << 1);
	if (location.y > center.y)
		ret = ret | (1 << 2);
	if (location.z > center.z)
		ret = ret | (1 << 3);
	return ret;
}
