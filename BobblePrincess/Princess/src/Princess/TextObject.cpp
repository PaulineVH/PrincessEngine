#include "EnginePCH.h"
#include <SDL.h>
#include <SDL_ttf.h>

#include "TextObject.h"
#include "Renderer.h"
#include "Font.h"
#include "Texture2D.h"

Princess::TextObject::TextObject(const std::string& text, Font* font) 
	: m_NeedsUpdate{ true }
	, m_Text{ text }
	, m_pFont{ font }
	, m_pTexture{ nullptr }
{ 
}

Princess::TextObject::~TextObject()
{
	delete m_pFont;
	m_pFont = nullptr;

	delete m_pTexture;
	m_pTexture = nullptr;
}

void Princess::TextObject::Update(const float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
	if (m_NeedsUpdate)
	{
		const SDL_Color color = { 255,255,255 }; // only white text is supported now
		const auto surf = TTF_RenderText_Blended(m_pFont->GetFont(), m_Text.c_str(), color);
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
		delete m_pTexture;
		m_pTexture = new Texture2D{ pTexture };
		m_NeedsUpdate = false;
	}
}

void Princess::TextObject::Render() const
{
	if (m_pTexture != nullptr)
	{
		const auto pos = m_Transform.GetPosition();
		Renderer::GetInstance().RenderTexture(*m_pTexture, pos.x, pos.y);
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


