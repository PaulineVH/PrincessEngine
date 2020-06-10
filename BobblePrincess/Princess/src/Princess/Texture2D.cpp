//2DAE07 - Vanden Heede, Pauline - 2019/2020

//Project includes
#include "EnginePCH.h"
#include "Texture2D.h"

//SDL includes
#include <SDL.h>

//---- Constructors ----
Princess::Texture2D::Texture2D(SDL_Texture* texture)
{
	m_pTexture = texture;
}

//----- Destructors ----
Princess::Texture2D::~Texture2D()
{
	SDL_DestroyTexture(m_pTexture);
}

//---- Functionality
SDL_Texture* Princess::Texture2D::GetSDLTexture() const
{
	return m_pTexture;
}