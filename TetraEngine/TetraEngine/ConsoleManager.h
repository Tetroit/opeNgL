#pragma once

#include <Windows.h>
#include <string.h>
#include <queue>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>

#include "Utils.h"
#include "Scene.h"

static class ConsoleManager {
	

private:

	static void WriteObject(GameObject* obj, std::string prefix) {

		std::cout << prefix << " " << obj->name << '\n';
		for (int i = 0; i < obj->children.size(); i++) {
			WriteObject(obj->children[i], '\t' + prefix);
		}
	}


	static enum Command
	{
		G_Quit,
		G_FPS,
		G_Tree,
		G_GameObject,
		GO_Transform,
		GO_Parent,
	};
	static enum Type
	{
		T_Null,
		T_GameObject
	};

	static ConsoleManager::Command IdentifyCommand(std::string str) {
		if (str == "quit") return G_Quit;
		if (str == "fps") return G_FPS;
		if (str == "tree") return G_Tree;
		if (str == "gameobject" || str == "go") return G_GameObject;
		if (str == "transform" || str == "t") return GO_Transform;
		if (str == "parent" || str == "p") return GO_Parent;
	}

	static void* context;
	static Type contextType;

public:

	static HANDLE console;
	static GLFWwindow* window;

	static void Initialize(GLFWwindow* window) {
		ConsoleManager::window = window;
	}
	
	template <typename mat>
	static void PrintMatrix(mat matrix) {
		int cols = matrix.length();
		int rows = matrix[0].length();
		std::cout << "+-------";
		for (int j = 0; j < cols; j++) {

			std::cout << "--------";
		}
		for (int i = 0; i < rows; i++) {
			std::cout << "\n|\t";
			for (int j = 0; j < cols; j++) {
				std::string value = std::to_string(matrix[j][i]);
				int difference = value.size() - 7;
				if (difference < 0) 
				{
					for (int i = difference; i < 0; i++)
						value += ' ';
				}
				if (difference > 0)
				{
					value = value.substr(0, 7);
				}
				std::cout << value << '\t';
			}
		}
	}

	static void ParseCommand(std::string command) {

		//general commands

		std::shared_ptr<std::vector<std::string>> args = Utils::Words(command, ' ');
		int size = args->size();
		if (size == 0) return;

		Command prefix = IdentifyCommand((*args)[0]);

		switch (prefix)
		{
		default:
		{
			break;
		}
		case G_Quit:

		{
			SetConsoleTextAttribute(console, 10);
			std::cout << "closing app\n";
			glfwSetWindowShouldClose(window, true);

			break;
		}

		case G_FPS:

		{
			std::cout << Time::fps;

			break;
		}

		case G_Tree:

		{
			SetConsoleTextAttribute(console, 10);
			std::cout << "scene\n";
			std::string prefix = "";
			Scene* scene = Scene::currentScene;
			for (int i = 0; i < scene->objects.size(); i++)
			{
				if (scene->objects[i]->parent == NULL)
					WriteObject(scene->objects[i], "`-->");

			}

			break;
		}

		case G_GameObject:

		{
			if (size < 2) {
				SetConsoleTextAttribute(console, 12);
				std::cout << "SyntaxError: gameobject <name>";
				break;
			}
			Scene* scene = Scene::currentScene;
			GameObject* gameobject;
			bool found = false;

			std::queue<GameObject*> queue;

			for (int i = 0; i < scene->objects.size(); i++)
			{
				gameobject = scene->objects[i];
				queue.push(gameobject);
			}
			while (queue.size() > 0) {

				gameobject = queue.front();
				queue.pop();

				if ((*args)[1] == gameobject->name) {
					SetConsoleTextAttribute(console, 10);
					std::cout << "Selected object '" << gameobject->name << "'";
					found = true;

					context = gameobject;
					contextType = T_GameObject;
					break;
				}
				if (gameobject->children.size() > 0)
				{
					for (GameObject* child : gameobject->children)
						queue.push(child);
				}
			}
			if (!found) {
				SetConsoleTextAttribute(console, 12);
				std::cout << "Object not found";
			}

			break;
		}

		case GO_Transform:
		{
			if (contextType != T_GameObject) {

				SetConsoleTextAttribute(console, 12);
				std::cout << "No GameObject selected";
				break;
			}
			GameObject* gameObject = static_cast<GameObject*>(context);
			PrintMatrix(gameObject->transform);
			
			break;
		}
		case GO_Parent:
		{
			if (contextType != T_GameObject) {

				SetConsoleTextAttribute(console, 12);
				std::cout << "No GameObject selected";
				break;
			}
			GameObject* gameObject = static_cast<GameObject*>(context);
			if (gameObject->parent == nullptr)
			{
				SetConsoleTextAttribute(console, 12);
				std::cout << "This gameobject is orphan";
				break;
			}
			SetConsoleTextAttribute(console, 10);
			std::cout << gameObject->parent->name << ' ';
			if (size > 1 && ((*args)[1] == "s" || (*args)[1] == "select")) {
				context = gameObject->parent;
			}

			break;
		}
		}

		SetConsoleTextAttribute(console, 15);
		std::cout << '\n';
	}
};

GLFWwindow* ConsoleManager::window = nullptr;
HANDLE ConsoleManager::console = GetStdHandle(STD_OUTPUT_HANDLE);
void* ConsoleManager::context = nullptr;
ConsoleManager::Type ConsoleManager::contextType = T_Null;