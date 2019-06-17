#pragma once
#include <stdint.h>
#include <functional>
#include <config.h>


namespace coral
{
namespace core
{
	//
	class CORAL_DLL Entity
	{
	private:
		uint16_t m_id = 0;
		uint16_t m_version = 0;
	public:
		Entity() = default;
		explicit Entity(uint32_t n)
		{
			m_version = (n & 0x0000FFFF);
			m_id = (n & 0xFFFF0000);
		}
		explicit Entity(uint16_t id, uint16_t version) : m_id(id), m_version(version) {}
		//Entity(const Entity& e) { m_id = e.ID(); m_version = e.Version(); }
		//Entity& operator=(const Entity& e) { m_id = e.ID(); m_version = e.Version(); }


		uint16_t ID() const { return m_id; }
		uint16_t Version() const { return m_version; }

		operator uint32_t() const { return (m_id << 16 | m_version); }
		uint32_t Value() const { return (m_id << 16 | m_version); }
		bool operator== (const Entity& other)
		{
			return (this->Value() == other.Value());
		}
		bool operator!= (const Entity& other)
		{
			return (this->Value() != other.Value());
		}
		bool operator< (const Entity& other)
		{
			return (this->Value() < other.Value());
		}
		bool operator> (const Entity& other)
		{
			return (this->Value() > other.Value());
		}


		// Utilities to handle entities.
		constexpr static uint32_t NOTVALID = 0;
		static Entity	Create();
		static void		Remove(Entity& id);
		
	};

};
};

namespace std {

	template <>
	struct hash<coral::core::Entity>
	{
		std::size_t operator()(const coral::core::Entity& e) const
		{
			return e.Value();
		}
	};

}