#include "GameManager.h"
#include "Background.h"
#include "ParallaxBG.h"
#include "EnemyManager.h"
#include "EnemyDrone.h"
#include "DestructionParticle.h"
#include "PowerUp.h"


GameManager* GameManager::m_Instance;

GameManager::GameManager()
{
	m_Instance = this;
}
void GameManager::Start()
{
	std::cout << "Start";
	m_World.CreateActor<Background>();
	m_World.CreateActor<ParallaxBG>();

	m_World.CreateActor<EnemyManager>();
	m_World.CreateActor<PowerUp>(PowerUpType::MISSILE_PU, glm::vec2(400.0f, -200.f));


	player = m_World.CreateActor<Player>();

}

void GameManager::Update(float deltaTime)
{
	
}

void GameManager::OnContactEvent(Object* other)
{
	
}

void GameManager::OnEndContactEvent(Object* other)
{
	
}
