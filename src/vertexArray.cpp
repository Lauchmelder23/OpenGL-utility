#include "vertexArray.hpp"

#include <fstream>
#include <string>
#include <sstream>
#include <vector>

namespace oglu
{
	AbstractVertexArray::AbstractVertexArray(const AbstractVertexArray& other) :
		VAO(other.VAO), VBO(other.VBO), EBO(other.EBO), count(other.count)
	{
	}

	AbstractVertexArray::~AbstractVertexArray()
	{
		glBindVertexArray(0);
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		glDeleteBuffers(1, &EBO);
	}

	VertexArray MakeVertexArray(const GLfloat* vertices, size_t verticesSize, const GLuint* indices, size_t indicesSize, const VertexAttribute* topology, size_t topologySize)
	{
		AbstractVertexArray* obj = new AbstractVertexArray(vertices, verticesSize, indices, indicesSize, topology, topologySize);
		return VertexArray(obj);
	}

	std::shared_ptr<AbstractVertexArray> MakeVertexArray(const char* filepath)
	{
		std::ifstream file(filepath);
		if (!file.good())
		{
			file.close();
			throw std::runtime_error("Missing file: " + std::string(filepath));
		}

		std::vector<GLfloat> vertices;
		std::vector<GLuint> indices;
		
		std::string line;
		while(!file.eof())
		{
			std::getline(file, line);
			switch (line[0])
			{
			case 'v':
			{
				GLfloat x, y, z;
				int shut_up_vs = sscanf(line.c_str(), "v %f %f %f", &x, &y, &z);
				vertices.push_back(x);
				vertices.push_back(y);
				vertices.push_back(z);
			} break;

			case 'f':
			{
				GLuint a, b, c;
				int shut_up_vs = sscanf(line.c_str(), "f %u %u %u", &a, &b, &c);
				indices.push_back(a - 1);
				indices.push_back(b - 1);
				indices.push_back(c - 1);
			} break;

			default: break;
			}
		}

		VertexAttribute topology[] = {
			{0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0 },
		};

		return MakeVertexArray(vertices.data(), sizeof(GLfloat) * vertices.size(),
			indices.data(), sizeof(GLuint) * indices.size(),
			topology, sizeof(topology)
		);
	}

	AbstractVertexArray::AbstractVertexArray(const GLfloat* vertices, size_t verticesSize, 
					const GLuint* indices, size_t indicesSize, 
					const VertexAttribute* topology, size_t topologySize) :
		VAO(0), VBO(0), EBO(0), count(0)
	{
		topologySize /= sizeof(VertexAttribute);

		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, verticesSize, vertices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize, indices, GL_STATIC_DRAW);

		for (int i = 0; i < topologySize; i++)
		{
			RegisterVertexAttribPointer(i, topology[i]);
		}

		glBindVertexArray(0);

		count = indicesSize / sizeof(GLuint);
	}

	void AbstractVertexArray::Bind()
	{
		glBindVertexArray(VAO);
	}

	void AbstractVertexArray::Unbind()
	{
		glBindVertexArray(0);
	}

	void AbstractVertexArray::Draw()
	{
		glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, (GLvoid*)0);
	}

	void AbstractVertexArray::BindAndDraw()
	{
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, (GLvoid*)0);
		glBindVertexArray(0);
	}

	void AbstractVertexArray::RegisterVertexAttribPointer(GLuint index, const VertexAttribute& topology)
	{
		glVertexAttribPointer(topology.index, topology.size, topology.type, topology.normalized, topology.stride, topology.pointer);
		glEnableVertexAttribArray(index);
	}
}