//2DAE07 - Vanden Heede, Pauline - 2019/2020
#pragma once

//Class Forward Declarations
struct SDL_Texture;

namespace Princess
{
	/**
	 * Simple RAII wrapper for an SDL_Texture
	 */
	class Texture2D
	{
	public:
		//---- Constructors ----
		explicit Texture2D(SDL_Texture* texture);
		Texture2D(const Texture2D &) = delete;
		Texture2D(Texture2D &&) = delete;

		//---- Destructor ----
		~Texture2D();

		//---- Operators -----
		//-- Assignment Operators --
		Texture2D & operator= (const Texture2D &) = delete;
		Texture2D & operator= (const Texture2D &&) = delete;
		
		//----Functionality ----
		SDL_Texture* GetSDLTexture() const;

	private:
		SDL_Texture* m_pTexture;
	};
}
