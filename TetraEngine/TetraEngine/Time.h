#pragma once
class Time
{
public:
	static float time;
	static float prevTime;
	static float deltaTime;
	static float GetFPS();
	static void Update();
};

