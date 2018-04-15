#pragma once
//An adress that corresponds to one quadrant of the octree
class OctreeAddress
{
public:
	static const unsigned int depth = 10;
private:
	const unsigned _int8 masks[2] = {15, 15 << 4};
	//bitset
	unsigned _int8 _address[(depth + 1) / 2];

public:
	OctreeAddress();
	~OctreeAddress();

	OctreeAddress& OctreeAddress::operator= (OctreeAddress);
	
	bool Set(int index, unsigned _int8 state);

	bool Compare(OctreeAddress &other);

};

