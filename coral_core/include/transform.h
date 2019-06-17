#pragma once
#include "config.h"
#include <glm/vec3.hpp>
#include <glm/matrix.hpp>


namespace coral
{
namespace core
{
	
	class CORAL_DLL Transform
	{
	public:
		
		Transform() = default;
		Transform(glm::vec3& position, glm::quat& rotation, glm::vec3& scale) : m_position(position), m_rotation(rotation), m_scale(scale) { }
		~Transform() {}

		/*
			Translate
			Rotate
			Scale
			etc.
		*/

		void Reset();

		// Local values
		glm::mat4 m_local;
		glm::mat4 m_world;
		glm::vec3 m_position;
		glm::quat m_rotation;
		glm::vec3 m_scale;
	private:

	};

};
};
