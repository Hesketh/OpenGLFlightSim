#include "Input.h"

Input* Input::m_instance = 0;

Input::Input()
{
	m_keybinds = std::map<std::string, int>();
	m_keys = std::map<int, bool>();
}

void Input::RegisterKeybinding(std::string keybind, int key)
{ 
	m_keybinds[keybind] = key;
}

void Input::ToggleKeyState(int key, bool pressed)
{
	m_keys[key] = pressed;
}

void Input::UpdateMousePosition(int x, int y)
{
	m_mousePos.x = x;
	m_mousePos.y = y;
}

Vector2 Input::GetMousePosition()
{
	return m_mousePos;
}

bool Input::KeybindingPressed(std::string keybind)
{
	if (m_keybinds.find(keybind) == m_keybinds.end())
	{
		//This keybind did not exist
		return false;
	}
	else
	{
		//Check if the key of this keybind is pressed
		return KeyPressed(m_keybinds[keybind]);
	}
}

bool Input::KeyPressed(int key)
{
	if (m_keys.find(key) == m_keys.end())
	{
		return false;
	}
	else
	{
		return m_keys[key];
	}
}