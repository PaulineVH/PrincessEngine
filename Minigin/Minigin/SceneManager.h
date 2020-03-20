#pragma once
#include "Singleton.h"

namespace Princess
{
	class Scene;
	class TextObject;

	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		~SceneManager();

		Scene& CreateScene(const std::string& name);

		void Update(const float deltaTime);
		void Render();
	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		std::vector<Scene*> m_pScenes;
		TextObject* m_pFPS;
		uint32_t m_FPSCounter;
	};
}
