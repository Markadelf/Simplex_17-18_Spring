#include "MarksEntityManager.h"

//Nicholas E. Zonenberg
//Mark DelFavero
namespace Simplex
{
	MarksEntityManager * MarksEntityManager::_active = nullptr;

	MarksEntityManager::MarksEntityManager()
	{
	}

	//Deallocate all the memory
	MarksEntityManager::~MarksEntityManager()
	{
		for (int i = 0; i < keys.size(); i++)
		{
			SafeDelete(data[keys[i]]);
		}
	}
	//Singleton pattern
	MarksEntityManager * MarksEntityManager::GetActive()
	{
		if (_active == nullptr)
			_active = new MarksEntityManager();
		return _active;
	}

	//Singleton release
	void MarksEntityManager::Release()
	{
		if(_active != nullptr)
			delete _active;
		_active = nullptr;
	}

	//Add model to manager
	bool MarksEntityManager::Add(String key, String fileName)
	{
		//Do not allow duplicate keys
		if (Contains(key))
			return false;
		data[key] = new MyEntity(fileName, key);
		keys.push_back(key);
		return true;
	}
	//Remove an item by key
	bool MarksEntityManager::Remove(String key)
	{
		if (data.erase(key))
		{
			keys.erase(std::find(keys.begin(), keys.end(), key));
			return true;
		}
		else
			return false;
	}
	//Check if a key is used
	bool MarksEntityManager::Contains(String name)
	{
		return data.find(name) != data.end();
	}
	//Gets a pointer to a model
	MyEntity * MarksEntityManager::Get(String name)
	{
		return data[name];
	}
	//Adds all models to the render list
	void MarksEntityManager::AddToRenderList()
	{
		for (int i = 0; i < keys.size(); i++)
		{
			data[keys[i]]->AddToRenderList(true);
		}
	}
	//Checks if any model is colliding with any other
	bool MarksEntityManager::CheckColliding()
	{
		bool ret = false;
		for (int i = 0; i < keys.size(); i++)
		{
			for (int j = i + 1; j < keys.size(); j++)
			{
				if (data[keys[i]]->IsColliding(data[keys[j]])) {
					ret = true;
				}
			}
		}
		return ret;
	}
	//Checks if any models are colliding with a specific model
	bool MarksEntityManager::CheckCollidingWith(String key)
	{
		bool ret = false;
		for (int i = 0; i < keys.size(); i++)
		{
			if (key != keys[i] && data[key]->IsColliding(data[keys[i]]))
				ret = true;
		}
		return ret;
	}
}