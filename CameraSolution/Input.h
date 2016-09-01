#pragma once



class Input
{
public:
	enum KEY_STATE { UP, DOWN, PRESS, RELEASE };

private:
	struct GLFWwindow *winHandle;
	KEY_STATE keys[350];

public:

	bool init(const class Window &);
	bool step();
	bool term();


	KEY_STATE getKeyState(int key) const
	{
		return keys[key];
	}


};