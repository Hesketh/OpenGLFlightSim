#pragma once
#include "Vector2.h"
#include <string>
#include <map>

class Input
{
private:
	static Input*	m_instance;
	Input();

	std::map<std::string, int> m_keybinds;
	std::map<int, bool> m_keys;

	Vector2 m_mousePos;
public:
	static Input* Instance()
	{
		if (m_instance == nullptr)
		{
			m_instance = new Input();
		}
		return m_instance;
	}

	void RegisterKeybinding(std::string keybind, int key);
	void ToggleKeyState(int key, bool pressed);

	void UpdateMousePosition(int x, int y);
	Vector2 GetMousePosition();

	bool KeybindingPressed(std::string keybind);
	bool KeyPressed(int key);
};