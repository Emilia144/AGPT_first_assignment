#pragma once
#include "Engine/Core/Object.h"
#include "Engine/Core/Components.h"

class Background : public Engine::Object
{

public:
	Background() {};

	void Start() override;
	void Update(float deltaTime) override;


	void OnContactEvent(Object* other) override;


	void OnEndContactEvent(Object* other) override;

private:
	Engine::Texture2D bacgroundTexture;
	Engine::SpriteRenderer2D m_SpriteRenderer;

};

