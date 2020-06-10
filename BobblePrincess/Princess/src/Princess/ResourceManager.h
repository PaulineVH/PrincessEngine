//2DAE07 - Vanden Heede, Pauline - 2019/2020
#pragma once
//Project Includes
#include "Singleton.h"
#include "Texture2D.h"

//Project Includes
#include <unordered_map>

namespace Princess
{
	class Texture2D;
	class Font;

	//Flyweight pattern
	class ResourceManager final : public Singleton<ResourceManager>
	{
	public:
		//---- Destructor ----
		~ResourceManager();


		void Initialise(const std::string& data);
		Texture2D* LoadTexture(const std::string& file);
		void UnloadTexture(const std::string& file);
		Texture2D* GetTexture(const std::string& file) const;
		Font* LoadFont(const std::string& file, unsigned int size) const;
	private:
		// ---- Private Friends ----
		friend class Singleton<ResourceManager>;
		//---- Private Constructor ----
		ResourceManager() = default;

		//---- Datamembers ----
		std::string m_DataPath;
		std::unordered_map<std::string, Texture2D*> m_pTextures;
	};
}
