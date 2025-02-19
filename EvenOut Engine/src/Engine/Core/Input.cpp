#include "epch.h"
#include "Input.h"


namespace Engine{ 
std::unordered_map<SDL_Keycode, bool> Engine::Input::m_KeyStates;
//SDL_Gamepad* Input::m_Pad = nullptr; 


bool Input::IsKeyPressed(SDL_Keycode key)
{
    return m_KeyStates[key];
}

void Input::SetKey(SDL_Keycode key, bool isPressed)
{
    m_KeyStates[key] = isPressed;
}

/*float Input::GetGamepadAxis(SDL_GamepadAxis axis)
{
	Sint16 value = SDL_GetGamepadAxis(m_Pad, axis);

	return value = std::clamp((float)value, -1.0f, 1.0f);
}

bool Input::IsGamepadButtonPressed(SDL_GamepadButton button, bool singleClick)
{
	if (singleClick) {
		static bool flag = false;
		//std::this_thread::sleep_for(0.1s);
		if (SDL_GetGamepadButton(m_Pad, button) != 0 && !flag) {
			flag = true;
			return true;
		}
		if (SDL_GetGamepadButton(m_Pad, button) == 0) {
			flag = false;
			return false;
		}
	}
	else {
		if (SDL_GetGamepadButton(m_Pad, button) != 0) {
			return true;
		}
	}
	return false;
}

void Input::SendGamepad(SDL_Gamepad* controller)
{
    m_Pad = controller;
}
*/

}