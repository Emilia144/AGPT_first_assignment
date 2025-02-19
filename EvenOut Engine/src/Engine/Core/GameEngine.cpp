#include "epch.h"
#include "GameEngine.h"
#include "Engine/Core/GameWorld.h"
#include "Engine/Core/PhysicsWorld.h"


namespace Engine {

	GameEngine* GameEngine::m_Instance;

	GameEngine::GameEngine()
	{
		m_Instance = this;
	}

	GameEngine::~GameEngine()
	{
	}

	void GameEngine::Initialize(const char* title, int width, int height)
	{
		std::cout << "Initializing Window";

		if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMEPAD) != 0) {
			std::cout << "SDL Initialized";
		}

		m_Window = SDL_CreateWindow(title, width, height, 0);
		Renderer::Init(m_Window);

		m_World = new GameWorld();
		m_PhysicsWorld = new PhysicsWorld();
		m_PhysicsWorld->SetWorld(m_World);
	}

	void GameEngine::HandleEvents()
	{
		SDL_Event event;
		while (SDL_PollEvent(&event) != 0)
		{
			std::cout << "Event";
			switch (event.type)
			{
			case SDL_EVENT_KEY_DOWN:
				Engine::Input::SetKey(event.key.keysym.sym, true);
				std::cout << "Key Pressed";
				break;

			case SDL_EVENT_KEY_UP:
				Engine::Input::SetKey(event.key.keysym.sym, false);
				break;

			case SDL_EVENT_GAMEPAD_ADDED:
				m_ID = event.gdevice.which;
				m_Controller = SDL_OpenGamepad(event.gdevice.which);
				Input::SendGamepad(m_Controller);
				break;

			case SDL_EVENT_QUIT:
				isRunning = false;
				break;
			}
		}
	}


	void GameEngine::Run()
	{
		isRunning = true;
		while (isRunning) {
			m_Time = (float)SDL_GetTicks();
			float deltaTime = (m_Time - m_PreviousTime) / 1000.0f;
			m_PreviousTime = m_Time;

			m_FrameTime += deltaTime;

			HandleEvents();
			m_World->Refresh();
			m_PhysicsWorld->Update(deltaTime);
			m_World->Update(deltaTime);

			Render();
		}
		Clean();
	}

	void GameEngine::Render()
	{
		SDL_RenderClear(Renderer::GetRenderer());
		m_World->Draw();
		SDL_RenderPresent(Renderer::GetRenderer());
	}

	void GameEngine::Clean()
	{
		SDL_DestroyWindow(m_Window);
		SDL_DestroyRenderer(Renderer::GetRenderer());
		SDL_Quit();
		std::cout << "Engine cleaned!";
	}

	bool GameEngine::IsRunning()
	{
		return isRunning;
	}
}
