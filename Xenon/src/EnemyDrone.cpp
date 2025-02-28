#include "EnemyDrone.h"
using Frame = Engine::AnimatorComponent::AnimationFrame;
using Animation = Engine::AnimatorComponent::Animation;

EnemyDrone::EnemyDrone(float PositionX, float PositionY)
{
	m_PositionX = PositionX;
	m_PositionY = PositionY;

	AddTag("Enemy");
	m_Transform = &AddComponent<Engine::TransformComponent>(glm::vec2(m_PositionX, m_PositionY));
	m_SpriteRenderer = &AddComponent<Engine::SpriteRenderer2D>("Assets/Textures/drone.bmp", 32, 0);
	m_Animator = &AddComponent<Engine::AnimatorComponent>(m_SpriteRenderer->m_SpriteTexture);
	m_RigidBody = &AddComponent<Engine::Rigidbody2D>(Engine::Rigidbody2D::BodyType::Dynamic);
	m_Collider = &AddComponent<Engine::BoxCollider2DComponent>(glm::vec2(m_SpriteRenderer->m_SpriteTexture.t_PixelSize,
																m_SpriteRenderer->m_SpriteTexture.t_PixelSize), m_RigidBody);
}

void EnemyDrone::Start()
{
	__super::Start();

	m_Animator->CreateAnimation(new Animation("IdleEnemy", std::vector <Frame>{
			Frame(1, 1),
			Frame(9, 2)
	}));

	m_Animator->SetStartFrame(Frame(1, 1));
}

void EnemyDrone::Update(float deltaTime)
{
	__super::Update(deltaTime);

	m_Animator->PlayAnimationContiniousToFrame("IdleEnemy", 0.06, deltaTime, true);

	m_Transform->SetPosition(m_PositionX + (std::sin(m_Transform->Position.y / 6) * m_XThreshold) * deltaTime, m_Transform->Position.y + (m_VelocityY * deltaTime));

}

void EnemyDrone::OnContactEvent(Object* other)
{
	__super::OnContactEvent(other);
	if (other->HasTag("Missile")) {
		std::cout << "Destroyed!";
		Destroy();
	}
}

void EnemyDrone::OnEndContactEvent(Object* other)
{
	__super::OnEndContactEvent(other);
}
