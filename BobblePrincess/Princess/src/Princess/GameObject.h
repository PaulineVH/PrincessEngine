#pragma once
#include "Transform.h"
#include "SceneObject.h"
#include "Utils.h"

namespace Princess
{
	class Texture2D;

	class GameObject : public SceneObject
	{
	public:
		GameObject() = default;
		virtual ~GameObject();

		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;
		
		void Update(const float deltaTime) override;
		void Render() const override;

		void SetTexture(const std::string& filename);
		void SetPosition(float x, float y);

	private:

		//std::vector<Princess::ID> m_ComponentIDs;

		Transform m_Transform;
		Texture2D* m_pTexture;
	};
}
