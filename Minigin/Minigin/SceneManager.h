#pragma once
#include "Singleton.h"

namespace Princess
{
	class Scene;

	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		~SceneManager();

		Scene& CreateScene(const std::string& name);

		void Update();
		void Render();
	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		std::vector<Scene*> m_pScenes;
	};
}
