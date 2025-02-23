#pragma once
#include "Engine/Core/Actor.h"
#include "Engine/Core/Components.h"

class SmallAsteroid : public Engine::Actor
{
public:
	SmallAsteroid(const char* asteroidPath, float PositionX, float PositionY);
	~SmallAsteroid() {}

	void Start() override;


	void Update(float deltaTime) override;

	void OnDie();

	void OnContactEvent(Object* other) override;


	void OnEndContactEvent(Object* other) override;

private:
	Engine::TransformComponent* m_Transform;
	Engine::SpriteRenderer2D* m_SpriteRender;
	Engine::AnimatorComponent* m_Animator;
	Engine::BoxCollider2DComponent* m_Collider;
	Engine::Rigidbody2D* m_Rigidbody;
	Engine::HealthComponent* m_Health;

	float m_PositionX;
	float m_PositionY;

	std::string m_FilePath;
	float m_VelocityY = 0.0f;
	float m_VelocityX = 0.0f;
};

