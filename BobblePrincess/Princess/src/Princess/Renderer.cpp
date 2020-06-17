//2DAE07 - Vanden Heede, Pauline - 2019/2020
//Project Includes
#include "EnginePCH.h"
#include "Renderer.h"
#include "SceneManager.h"
#include "Texture2D.h"
#include "Components.h"

//3rdParty Includes
#include <SDL.h>

void Princess::Renderer::Init(SDL_Window * window)
{
	m_pRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (m_pRenderer == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());
	}
}

void Princess::Renderer::Render() const
{
	SDL_RenderClear(m_pRenderer);

	SceneManager::GetInstance().Render();
	
	SDL_RenderPresent(m_pRenderer);
}

void Princess::Renderer::Destroy()
{
	if (m_pRenderer != nullptr)
	{
		SDL_DestroyRenderer(m_pRenderer);
		m_pRenderer = nullptr;
	}
}

void Princess::Renderer::RenderTexture(const TextureComponent* pComponent, const Float2& pos) const
{
	RenderTexture(*pComponent->pTexture, pos.x, pos.y);
}

void Princess::Renderer::RenderTexture(const Texture2D* pTexture, const Princess::Float2& pos) const
{
	SDL_Rect dest{};
	dest.x = static_cast<int>(pos.x);
	dest.y = static_cast<int>(pos.y);

	SDL_QueryTexture(pTexture->GetSDLTexture(), nullptr, nullptr, &dest.w, &dest.h);
	SDL_RenderCopy(GetSDLRenderer(), pTexture->GetSDLTexture(), nullptr, &dest);
}




void Princess::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y) const
{
	SDL_Rect dst;
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	SDL_QueryTexture(texture.GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

void Princess::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y, const float width, const float height) const
{
	SDL_Rect dst;
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	dst.w = static_cast<int>(width);
	dst.h = static_cast<int>(height);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

void Princess::Renderer::RenderScaledTexture(const TextureComponent& pComponent, const TransformComponent& transform) const
{
	SDL_Rect destRect;
	destRect.x = static_cast<int>(transform.position.x);
	destRect.y = static_cast<int>(transform.position.y);
	SDL_QueryTexture(pComponent.pTexture->GetSDLTexture(), nullptr, nullptr, &destRect.w, &destRect.h);

	destRect.w = static_cast<int>(destRect.w * transform.scale.x);
	destRect.h = static_cast<int>(destRect.h * transform.scale.y);

	SDL_RenderCopy(GetSDLRenderer(), pComponent.pTexture->GetSDLTexture(), nullptr, &destRect);
}
