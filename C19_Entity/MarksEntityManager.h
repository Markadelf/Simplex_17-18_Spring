#pragma once
#include <unordered_map>
#include "MyEntity.h"
//Nicholas E. Zonenberg
//Mark DelFavero
namespace Simplex
{
	//Class that manages entities
	class MarksEntityManager
	{
		//Singleton Structure
		static MarksEntityManager * _active;
		MarksEntityManager();
		~MarksEntityManager(); 
		
		//Data and the list of keys
		std::unordered_map<String, MyEntity*> data;
		std::vector<String> keys;

	public:
		//Singleton accessor
		static MarksEntityManager * GetActive();
		//singleton release
		static void Release();
		
		//Adds an object to the manager via key and filename
		bool Add(String key, String fileName);
		//Removes an object from the manager via key name
		bool Remove(String);
		//Checks if an object is contained in the manager
		bool Contains(String);
		//Gets the entity for configuration purposes
		MyEntity * Get(String);
		//Adds all the models to the render list
		void AddToRenderList();
		//Collision detection
		bool CheckColliding();
		bool CheckCollidingWith(String);
	
	
	};
}
