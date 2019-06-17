#pragma once
#include <filesystem>
#include <map>


namespace coral
{
namespace resources
{
	namespace fs = std::filesystem;
	struct Resource
	{
		// meta data 
	};

	enum class FileEvent
	{
		None,
		Added,
		Modified,
		Removed
	};

	class ResourceManager
	{
	public:

		ResourceManager();
		~ResourceManager();

		static ResourceManager& GetInstance();
		
		// Returns the absolute path
		fs::path SetPath(const fs::path& relativePath);

		// Scans all assets within that folder.
		void ScanFolder(fs::path path, bool recursive);

		void OnFileEvent(fs::path path, FileEvent event);

	private:
		// Disable
		ResourceManager(ResourceManager&& other) = delete;
		ResourceManager(const ResourceManager& other) = delete;
		
		// Members
		fs::path		m_assetFolder;
		std::map<size_t, Resource>	m_metaData;
	};


};
};