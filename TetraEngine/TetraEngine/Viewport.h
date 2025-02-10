#pragma once

class Camera;
class Framebuffer;
class Texture2D;

class Viewport
{
public:
	Camera* cam;
	Framebuffer* framebuffer;

	Viewport(uint width, uint height, Camera& cam);

	static void Unbind(uint width, uint height);
	void Bind();
	uint GetWidth();
	uint GetHeight();
	void SetSize(uint width, uint height);
	Texture2D* GetTexture();
};

