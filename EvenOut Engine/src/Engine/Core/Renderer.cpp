#include "epch.h"
#include "Renderer.h"

namespace Engine {
	SDL_Renderer* Renderer::m_RenderTarget;

	void Renderer::Init(SDL_Window* window)
	{	
		if (window != nullptr) {
			m_RenderTarget = SDL_CreateRenderer(window, NULL, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (m_RenderTarget == nullptr) {
				std::cout << "Error Creating render target (Render is null)" << std::endl;
			}
			else {

				std::cout << "Render target created!" << std::endl;
			}

		}
		else {
			std::cout << "Error Creating render target (Window is null)" << std::endl;

		}

	}

	static SDL_Texture* LoadTexture(const std::string& path, SDL_Renderer* renderer) {
		SDL_RWops* rw = SDL_RWFromFile(path.c_str(), "rb");
		if (!rw) {
			SDL_Log("Failed to open file: %s", SDL_GetError());
			return nullptr;
		}

		// Use SDL_LoadBMP_RW instead of SDL_LoadBMP_IO
		SDL_Surface* surface = SDL_LoadBMP_RW(rw, SDL_TRUE);  // SDL_TRUE closes RWops automatically
		if (!surface) {
			SDL_Log("Failed to load BMP: %s", SDL_GetError());
			return nullptr;
		}

		// Use SDL_SetSurfaceColorMod instead of SDL_SetColorKey
		SDL_SetSurfaceColorMod(surface, 255, 0, 255);

		SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_DestroySurface(surface); // SDL_FreeSurface was renamed to SDL_DestroySurface

		if (!texture) {
			SDL_Log("Failed to create texture: %s", SDL_GetError());
		}

		return texture;
	}

	void Renderer::RenderTexture(Texture2D& texture) {
		SDL_RenderTexture(m_RenderTarget, texture, texture.t_ScreenRect, texture.t_ScreenPosition);
	}

}
