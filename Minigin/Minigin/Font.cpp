#include "MiniginPCH.h"

#include <SDL_ttf.h>

#include "Font.h"

Princess::Font::Font(const std::string& fullPath, unsigned int size) 
	: m_pFont(nullptr)
	, m_Size(size)
{
	m_pFont = TTF_OpenFont(fullPath.c_str(), size);
	if (m_pFont == nullptr) 
	{
		throw std::runtime_error(std::string("Failed to load font: ") + SDL_GetError());
	}
}

Princess::Font::~Font()
{
	TTF_CloseFont(m_pFont);
}

TTF_Font* Princess::Font::GetFont() const 
{
	return m_pFont;
}