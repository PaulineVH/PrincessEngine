#pragma once
#include "SceneObject.h"
#include "Transform.h"

namespace Princess
{
	class Font;
	class Texture2D;

	class TextObject final : public SceneObject
	{
	public:
		explicit TextObject(const std::string& text, Font* font);
		virtual ~TextObject();
		
		TextObject(const TextObject& other) = delete;
		TextObject(TextObject&& other) = delete;
		TextObject& operator=(const TextObject& other) = delete;
		TextObject& operator=(TextObject&& other) = delete;
		
		void Update(const float deltaTime) override;
		void Render() const override;

		void SetText(const std::string& text);
		void SetPosition(float x, float y);

	private:
		bool m_NeedsUpdate;
		std::string m_Text;
		Transform m_Transform;

		//Resource manager doesn't manage the pointers.
		Font* m_pFont; 
		Texture2D* m_pTexture;
	};
}
