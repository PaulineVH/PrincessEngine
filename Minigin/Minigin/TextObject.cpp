#include "MiniginPCH.h"
#include <SDL.h>
#include <SDL_ttf.h>

#include "TextObject.h"
#include "Renderer.h"
#include "Font.h"
#include "Texture2D.h"

Princess::TextObject::TextObject(const std::string& text, const std::shared_ptr<Font>& font) 
	: m_NeedsUpdate{ true }
	, m_Text{ text }
	, m_spFont{ font }
	, m_spTexture{ nullptr }
{ 
}

void Princess::TextObject::Update()
{
	if (m_NeedsUpdate)
	{
		const SDL_Color color = { 255,255,255 }; // only white text is supported now
		const auto surf = TTF_RenderText_Blended(m_spFont->GetFont(), m_Text.c_str(), color);
		if (surf == nullptr) 
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto pTexture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
		if (pTexture == nullptr) 
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surf);
		m_spTexture = std::make_shared<Texture2D>(pTexture);
		m_NeedsUpdate = false;
	}
}

void Princess::TextObject::Render() const
{
	if (m_spTexture != nullptr)
	{
		const auto pos = m_Transform.GetPosition();
		Renderer::GetInstance().RenderTexture(*m_spTexture, pos.x, pos.y);
	}
}

// This implementation uses the "dirty flag" pattern
void Princess::TextObject::SetText(const std::string& text)
{
	m_Text = text;
	m_NeedsUpdate = true;
}

void Princess::TextObject::SetPosition(const float x, const float y)
{
	m_Transform.SetPosition(x, y, 0.0f);
}


