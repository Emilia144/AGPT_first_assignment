#include "BigAsteroid.h"
#include "Global.h"
#include "GameManager.h"
#include "EnemyManager.h"

using Frame = Engine::AnimatorComponent::AnimationFrame;
using Animation = Engine::AnimatorComponent::Animation;

BigAsteroid::BigAsteroid(const char* asteroidPath, float PositionX, float PositionY)
{
	AddTag("Asteroid");
	m_FilePath = asteroidPath;

	m_PositionX = PositionX;
	m_PositionY = PositionY;

	m_Transform = &AddComponent<Engine::TransformComponent>(glm::vec2(m_PositionX, m_PositionY));
	m_SpriteRender = &AddComponent<Engine::SpriteRenderer2D>(asteroidPath, 96, 0);
	m_Animator = &AddComponent<Engine::AnimatorComponent>(m_SpriteRender->m_SpriteTexture);
	m_Rigidbody = &AddComponent<Engine::Rigidbody2D>(Engine::Rigidbody2D::BodyType::Dynamic);
	m_Collider = &AddComponent<Engine::BoxCollider2DComponent>(glm::vec2(m_SpriteRender->m_SpriteTexture.t_PixelSize,
		m_SpriteRender->m_SpriteTexture.t_PixelSize), m_Rigidbody);

	m_Health = &AddComponent<Engine::HealthComponent>(100.0f);
	m_Health->setOnDieCallback(this, &BigAsteroid::OnDie);
}

void BigAsteroid::Start()
{
	__super::Start();

	m_VelocityY = GameManager::GetManager().RandomNumber<float>(30.0f, 70.0f);

	m_Animator->CreateAnimation(new Animation("AsteroidIdle", std::vector<Frame>{
		Frame(1, 1),
		Frame(5, 5)
	}));
}

void BigAsteroid::Update(float deltaTime)
{
	__super::Update(deltaTime);
	m_Animator->PlayAnimationContiniousToFrame("AsteroidIdle", 0.06f, deltaTime, true);
	m_Transform->AddPos(0.0f, m_VelocityY * deltaTime);
}

void BigAsteroid::OnDie()
{
	std::cout << "im dead";
	Destroy();

	std::string newPath = m_FilePath;

	std::string toReplace = "96";

	std::size_t pos = newPath.find(toReplace);

	if (pos == std::string::npos) return;

	newPath.replace(pos, toReplace.length(), "64");

	EnemyManager::GetEnemyManager().SpawnAsteroids(newPath.c_str(), GameManager::GetManager().RandomNumber<int>(1, 5)
		, m_Transform->Position.x - 32.0f , m_Transform->Position.x + 32.0f, m_Transform->Position.y - 24.0f, m_Transform->Position.y + 24.0f, AsteroidsSize::MEDIUM);
	
	Destroy();
}

void BigAsteroid::OnContactEvent(Object* other)
{
	__super::OnContactEvent(other);

	if (other->HasTag("Missile")) {
		m_Health->TakeDamage(50.0f);
	}
}

void BigAsteroid::OnEndContactEvent(Object* other)
{
	__super::OnEndContactEvent(other);
}
