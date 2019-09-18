#pragma once
#include <map>
#include <string>

template <class Type>
class ResourceContainer
{
private:
	std::map<std::string, Type*>	m_loaded; //look into string hashing
public:
	ResourceContainer<Type>() { ; };

	inline Type*	GetResource(std::string name)
	{
		return m_loaded[name];
	}

	inline void	AddResource(std::string name, Type* item)
	{
		m_loaded[name] = item;
	}

	inline void	ClearContainedResources()
	{
		for (const auto& item : m_loaded)
		{
			delete item.second;
		}
		m_loaded.clear();
	}

	~ResourceContainer<Type>() { ClearContainedResources(); };
};