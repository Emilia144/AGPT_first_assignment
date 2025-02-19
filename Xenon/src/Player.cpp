#include "Player.h"
#include "Missile.h"
#include "GameManager.h"
#include "Engine/Core/InputCodes.h"
#include "Engine/Core/Input.h"

using Frame = Engine::AnimatorComponent::AnimationFrame;

Player::Player()
{
    AddTag("Player");
    m_Transform = &AddComponent<Engine::TransformComponent>(glm::vec2(300.0f, 400.0f));
    m_SpriteRenderer = &AddComponent<Engine::SpriteRenderer2D>("Assets/Textures/Ship1.bmp", 64, 1);
    m_Animator = &AddComponent<Engine::AnimatorComponent>(m_SpriteRenderer->m_SpriteTexture);
    m_RigidBody2d = &AddComponent<Engine::Rigidbody2D>(Engine::Rigidbody2D::BodyType::Dynamic);
    m_Collider = &AddComponent<Engine::BoxCollider2DComponent>(
        glm::vec2(m_SpriteRenderer->m_SpriteTexture.t_PixelSize,
            m_SpriteRenderer->m_SpriteTexture.t_PixelSize),
        m_RigidBody2d);

    m_MissileTier = MissileTier::TIER1;
}

void Player::Start()
{
    __super::Start();

    m_Animator->SetStartFrame(Frame(4, 1));

    m_Animator->CreateAnimation(new Engine::AnimatorComponent::Animation("SpaceshipRight", { Frame(5, 1), Frame(6, 1), Frame(7, 1) }));
    m_Animator->CreateAnimation(new Engine::AnimatorComponent::Animation("IdleFromRight", { Frame(7, 1), Frame(6, 1), Frame(5, 1), Frame(4, 1) }));
    m_Animator->CreateAnimation(new Engine::AnimatorComponent::Animation("IdleFromLeft", { Frame(1, 1), Frame(2, 1), Frame(3, 1), Frame(4, 1) }));
    m_Animator->CreateAnimation(new Engine::AnimatorComponent::Animation("SpaceshipLeft", { Frame(3, 1), Frame(2, 1), Frame(1, 1) }));
}

void Player::Update(float deltaTime)
{
    __super::Update(deltaTime);
    m_CurrentTime += deltaTime;

    // Get the current state of all keys
    const Uint8* keyState = SDL_GetKeyboardState(NULL);

    // Movement variables
    float xMove = 0.0f;
    float yMove = 0.0f;
    const float speed = 150.0f;

    // Keyboard Input (using SDL_GetKeyboardState)
    if (keyState[SDL_SCANCODE_W]) yMove = -1.0f;
    if (keyState[SDL_SCANCODE_S]) yMove = 1.0f;
    if (keyState[SDL_SCANCODE_A]) xMove = -1.0f;
    if (keyState[SDL_SCANCODE_D]) xMove = 1.0f;

    // Apply movement
    m_Transform->AddPos(xMove * speed * deltaTime, yMove * speed * deltaTime);

    // ?? Animations based on movement direction
    if (xMove > 0) {
        m_Animator->PlayAnimation("SpaceshipRight", 0.06, deltaTime, true);
        lastX = xMove;
    }
    else if (xMove < 0) {
        m_Animator->PlayAnimation("SpaceshipLeft", 0.06, deltaTime, true);
        lastX = xMove;
    }
    else if (xMove == 0) {
        if (lastX > 0)
            m_Animator->PlayAnimation("IdleFromRight", 0.06, deltaTime, true);
        else
            m_Animator->PlayAnimation("IdleFromLeft", 0.06, deltaTime, true);
    }

    // ?? Shooting with Spacebar OR Gamepad Button (North)
    
    if (keyState[SDL_SCANCODE_SPACE]){
        if (m_NexShotTime < m_CurrentTime) {
            m_NexShotTime = m_CurrentTime + m_FireRate;
            GameManager::GetManager().InstantiateObject<Missile>(
                700.0f, glm::vec2(m_Transform->Position.x + 16, m_Transform->Position.y + 16), m_MissileTier
            );
        }
    }
}

void Player::UpgradeMissileTier()
{
    switch (m_MissileTier)
    {
    case MissileTier::TIER1: m_MissileTier = MissileTier::TIER2; break;
    case MissileTier::TIER2: m_MissileTier = MissileTier::TIER3; break;
    case MissileTier::TIER3: m_MissileTier = MissileTier::TIER1; break;
    }

    std::cout << "UPDATED MISSILE";
}

void Player::OnContactEvent(Object* other)
{
    __super::OnContactEvent(other);
}

void Player::OnEndContactEvent(Object* other)
{
    __super::OnEndContactEvent(other);
}
