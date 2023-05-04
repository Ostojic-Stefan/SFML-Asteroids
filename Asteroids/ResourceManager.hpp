#pragma once
#include <string>
#include <string_view>
#include <fstream>
#include <unordered_map>
#include <map>
#include <iostream>
#include <sstream>

template<typename Resource>
class ResourceManager
{
public:
	ResourceManager(std::string_view pathFile)
	{
		LoadPaths(pathFile);
	}
	~ResourceManager()
	{
		PurgeResources();
	}
	Resource* GetResource(const std::string& resId) const
	{
		auto foundItr = m_Resources.find(resId);
		return foundItr != m_Resources.end() ? foundItr->second.resource : nullptr;
	}
	bool RequireResource(const std::string& resId)
	{
		ResourceInfo* resource = FindResource(resId);
		if (resource != nullptr)
		{
			resource->usageCount += 1;
			return true;
		}
		auto path = m_Paths.find(resId);
		if (path == m_Paths.end())
			return false;

		Resource* loadedResource = Load(path->second);
		if (loadedResource == nullptr)
		{
			std::cerr << "Failed to load the resource " << path->second << std::endl;
			return false;
		}
		m_Resources.emplace(resId, ResourceInfo{ loadedResource, 1 });
		return true;
	}
	bool ReleaseResource(const std::string& resId)
	{
		auto foundItr = m_Resources.find(resId);
		if (foundItr == m_Resources.end()) return false;
		foundItr->second.usageCount -= 1;
		if (foundItr->second.usageCount <= 0)
			Unload(resId);
		return true;
	}
	Resource* Load(const std::string& path)
	{
		Resource* res = new Resource;
		if (!res->loadFromFile(path))
		{
			delete res;
			res = nullptr;
			std::cerr << "! Failed to load texture: " << path << std::endl;
		}
		return res;
	}
	bool Unload(const std::string& resId)
	{
		auto foundItr = m_Resources.find(resId);
		if (foundItr == m_Resources.end()) return false;
		delete foundItr->second.resource;
		m_Resources.erase(foundItr);
		return true;
	}
	void PurgeResources()
	{
		for (; m_Resources.begin() != m_Resources.end();)
		{
			delete m_Resources.begin()->second.resource;
			m_Resources.erase(m_Resources.begin());
		}
	}
public:
	struct ResourceInfo
	{
		Resource* resource;
		uint32_t usageCount;
	};
private:
	ResourceInfo* FindResource(const std::string& resId)
	{
		auto foundItr = m_Resources.find(resId);
		return foundItr != m_Resources.end() ? &foundItr->second : nullptr;
	}
	void LoadPaths(std::string_view pathFile)
	{
		std::ifstream stream;
		stream.open(pathFile.data());
		if (stream.is_open())
		{
			std::string line;
			while (std::getline(stream, line))
			{
				std::stringstream keyStream(line);
				std::string resId, path;
				keyStream >> resId >> path; 
				m_Paths.emplace(resId, path);
			}
			stream.close();
			return;
		}
		std::cerr << "Error opening the pathFile " << pathFile.data() << "\n";
	}
private:
	std::unordered_map<std::string, ResourceInfo> m_Resources;
	std::unordered_map<std::string, std::string> m_Paths;
};