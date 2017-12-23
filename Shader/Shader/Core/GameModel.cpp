#include "GameModel.h"
using namespace Model;

GameModel::GameModel() {}

GameModel::~GameModel()
{
	std::map<std::string, Model>::iterator iter;
	for (iter = GameModelList.begin(); iter != GameModelList.end(); ++iter)
	{
		unsigned int* p = &iter->second.vao;
		glDeleteVertexArrays(1, p);
		glDeleteBuffers(iter->second.vbos.size(), &iter->second.vbos[0]);
		iter->second.vbos.clear();
	}
	GameModelList.clear();
}

void GameModel::createTriangleModel(const std::string& gameModelName)
{
	unsigned int vao;
	unsigned int vbo;

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	std::vector<VertexFormat> vertices;
	vertices.push_back(VertexFormat(glm::vec3(0.25, -0.25, 0.0)));
	vertices.push_back(VertexFormat(glm::vec3(-0.25, -0.25, 0.0)));
	vertices.push_back(VertexFormat(glm::vec3(0.25, 0.25, 0.0)));

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexFormat) * 3, &vertices[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)0);

	Model model;
	model.vao = vao;
	model.vbos.push_back(vbo);
	GameModelList[gameModelName] = model;
}

void GameModel::deleteModel(const std::string& gameModelName)
{
	Model model = GameModelList[gameModelName];
	unsigned int p = model.vao;
	glDeleteVertexArrays(1, &p);
	glDeleteBuffers(model.vbos.size(), &model.vbos[0]);
	model.vbos.clear();
	GameModelList.erase(gameModelName);
}

unsigned int GameModel::getModel(const std::string& gameModelName)
{
	return GameModelList[gameModelName].vao;
}