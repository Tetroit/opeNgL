#pragma once

#include <string.h>
#include <GLFW/glfw3.h>
#include <Windows.h>

#include "Utils.h"
#include "Scene.h"

static class ConsoleManager {
	
private:

	void static WriteObject(GameObject* obj, std::string prefix) {

		std::cout << prefix << " " << obj->name << '\n';
		for (int i = 0; i < obj->children.size(); i++) {
			WriteObject(obj->children[i], '\t' + prefix);
		}
	}

public:

	static HANDLE console;
	static GLFWwindow* window;

	static void Initialize(GLFWwindow* window) {
		ConsoleManager::window = window;
	}
	static void ParseCommand(std::string command) {

		std::shared_ptr<std::vector<std::string>> args = Utils::Words(command, ' ');
		int size = args->size();
		if (size == 0) return;

		if ((*args)[0] == "quit") {
			SetConsoleTextAttribute(console, 10);
			std::cout << "closing app\n";
			glfwSetWindowShouldClose(window, true);
		}
		if ((*args)[0] == "fps") {
			std::cout << Time::fps;
		}
		if ((*args)[0] == "tree") {

			SetConsoleTextAttribute(console, 10);
			std::cout << "scene\n";
			std::string prefix = "";
			Scene* scene = Scene::currentScene;
			for (int i = 0; i < scene->objects.size(); i++)
			{
				if (scene->objects[i]->parent == NULL)
					WriteObject(scene->objects[i], "`-->");

			}
		}
		if ((*args)[0] == "gameobject") {

			if (size < 2) {
				SetConsoleTextAttribute(console, 12);
				std::cout << "SyntaxError: gameobject <name>";
			}
			else
			{
				Scene* scene = Scene::currentScene;
				GameObject* gameobject;
				bool found = false;
				for (int i = 0; i < scene->objects.size(); i++)
				{
					if ((*args)[1] == scene->objects[i]->name) {
						gameobject = scene->objects[i];
						SetConsoleTextAttribute(console, 10);
						std::cout << "Selected object '" << gameobject->name << "'";
						found = true;
					}
				}
				if (!found) {
					SetConsoleTextAttribute(console, 12);
					std::cout << "Object not found";
				}
			}
		}

		SetConsoleTextAttribute(console, 15);
		std::cout << '\n';
	}
};

GLFWwindow* ConsoleManager::window = nullptr;
HANDLE ConsoleManager::console = GetStdHandle(STD_OUTPUT_HANDLE);