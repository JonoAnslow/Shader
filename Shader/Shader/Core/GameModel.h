#ifndef _GAME_MODEL_H_
#define _GAME_MODEL_H_

#pragma once
#include "..\..\Dependencies\glew\glew.h"
#include "..\..\Dependencies\freeglut\freeglut.h"
#include "VertexFormat.h"
#include <vector>
#include <map>

namespace Model
{
	struct Model
	{
		unsigned int vao;
		std::vector<unsigned int> vbos;

		Model() {}
	};
	class GameModel
	{
	public:
		GameModel();
		~GameModel();
		void createTriangleModel(const std::string& gameModelName);
		void deleteModel(const std::string& gameModelName);
		unsigned int getModel(const std::string& gameModelName);
	private:
		std::map<std::string, Model> GameModelList;
	};
}
#endif