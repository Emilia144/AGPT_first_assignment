#include "Background.h"

void Background::Start()
{
	std::cout << "Loading background texture";
	m_SpriteRenderer = AddComponent<Engine::SpriteRenderer2D>("Assets/Textures/galaxy2.bmp", 0);
}

void Background::Update(float deltaTime)
{
}

void Background::OnContactEvent(Object* other)
{
}

void Background::OnEndContactEvent(Object* other)
{
	
}

