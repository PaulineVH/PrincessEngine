//2DAE07 - Vanden Heede, Pauline - 2019/2020
#pragma once
#include "Singleton.h"
#include "Utils.h"

struct SDL_Window;
struct SDL_Renderer;

namespace Princess
{
	class Texture2D;
	struct TextureComponent;
	/**
	 * Simple RAII wrapper for the SDL renderer
	 */
	class Renderer final : public Singleton<Renderer>
	{
	public:
		void Init(SDL_Window* window);
		void Render() const;
		void Destroy();

		void RenderTexture(const TextureComponent* pComponent, const Float2& pos) const;
		void RenderTexture(const Texture2D* pTexture, const Float2& pos) const;
		void RenderTexture(const Texture2D& texture, float x, float y) const;
		void RenderTexture(const Texture2D& texture, float x, float y, float width, float height) const;

		SDL_Renderer* GetSDLRenderer() const { return m_Renderer; }
	private:
		SDL_Renderer* m_Renderer{};
	};
}

