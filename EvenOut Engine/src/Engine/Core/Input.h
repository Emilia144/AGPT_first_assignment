#pragma once
#include <unordered_map>

namespace Engine {
    class Input
    {
    public:
        static bool IsKeyPressed(SDL_Keycode key);
        static void SetKey(SDL_Keycode key, bool isPressed);
        static float GetGamepadAxis(SDL_GamepadAxis axis);
        static bool IsGamepadButtonPressed(SDL_GamepadButton button, bool repeat);
        static void SendGamepad(SDL_Gamepad* controller);
        
    private:
        static std::unordered_map<SDL_Keycode, bool> m_KeyStates;
        static SDL_Gamepad* m_Pad;
    };
}
