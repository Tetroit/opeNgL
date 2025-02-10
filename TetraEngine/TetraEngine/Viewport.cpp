#include "tetrapc.h"
#include "Viewport.h"
#include "Framebuffer.h"
#include "Texture2D.h"
#include "Camera.h"

Viewport::Viewport(uint width, uint height, Camera& cam) : cam(&cam)
{
	framebuffer = new Framebuffer(width, height, true);
	
	cam.width = width;
	cam.height = height;
}

void Viewport::Unbind(uint width, uint height)
{
	Framebuffer::Unbind();
	glViewport(0, 0, width, height);
	glDisable(GL_DEPTH_TEST);
}

void Viewport::Bind()
{
	if (!framebuffer->IsComplete())
		std::cout << "FRAMEBUFFER NOT COMPLETE\n";
	framebuffer->Bind();
	glViewport(0, 0, GetWidth(), GetHeight());
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
}

uint Viewport::GetWidth()
{
	return cam->width;
}
uint Viewport::GetHeight()
{
	return cam->height;
}

void Viewport::SetSize(uint width, uint height)
{
	cam->width = width;
	cam->height = height;
}

Texture2D* Viewport::GetTexture()
{
	return framebuffer->GetTexture();
}
