#pragma once

#include "Resources/Resource.h"
#include "GUI.h"
#include <glm/glm.hpp>

namespace neu {
	class Program;

	class Material : public Resource, GUI {
	public:
		Material();
		~Material();

		bool Load(const std::string& filename);
		void Bind();

	public:		
		res_t<Texture> baseMap;
		glm::vec3 baseColor{ 1, 1, 1 };
		res_t<Texture> specularMap;

		float shininess = { 2 };
		glm::vec2 tiling{ 1, 1 };
		glm::vec2 offset{ 0, 0 };
		

		res_t<Texture> texture;
		res_t<Program> program;

		// Inherited via GUI
		void UpdateGUI() override;
	};
}