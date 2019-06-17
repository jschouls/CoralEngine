#include "resources/resourcemanager.h"


using namespace coral;
using namespace resources;

#ifdef CORAL_DEVELOP_MODE
/*
	Additional functionality for "Developer mode".
	Shall only cooperate with the resource manager
*/

#include <chrono>
#include <unordered_map>
#include <iostream>
#include <thread>
#include <assert.h>
#include <functional>

namespace coral
{
namespace resources
{
	// Hash, templated hash<fs::path> does not work?
	struct FileHash {
		std::size_t operator()(fs::path const& path) const noexcept
		{
			return fs::hash_value(path);
		}
	};

	static void FileEventCallback(fs::path path, FileEvent event, void* objPtr)
	{
		assert(objPtr);
		ResourceManager* rsm = static_cast<ResourceManager*>(objPtr);
		rsm->OnFileEvent(path, event);
	}

	class PathWatcher
	{
	public:
		
		PathWatcher()
		{	}
		~PathWatcher()
		{
			Stop();
		}

		void Start(const fs::path& path, ResourceManager* resourceManager)
		{
			rmPtr = resourceManager;
			CallFileEvent = &FileEventCallback;
			m_thread = std::thread(&PathWatcher::Scan, this, path);
			m_IsRunning = true;
		}

		void Stop()
		{
			m_IsRunning = false;
			m_thread.join();
		}

		bool IsRunning()
		{
			return m_IsRunning;
		}
	
	private:
		// Function that runs on seperate thread
		void Scan(const fs::path& path)
		{
			while (m_IsRunning)
			{
				std::this_thread::sleep_for(m_waitTime);

				FileEvent action = FileEvent::None;
				auto it = m_files.begin();
				while (it != m_files.end())
				{
					// Reset every file (needed?)
					action = FileEvent::None;
					if (!fs::exists(it->first))
					{
						action = FileEvent::Removed;
						//callback
						std::cout << "Erased: " << it->first.c_str() << std::endl;
						m_files.erase(it);
					}
					else
					{
						++it;
					}
				}

				for (auto& f : fs::recursive_directory_iterator(path))
				{
					auto search = m_files.find(f);
					auto fileWriteTime = fs::last_write_time(f);
					action = FileEvent::None;
					// If file is in list
					if (search != m_files.end())
					{
						// Modified
						if (search->second < fileWriteTime)
							action = FileEvent::Modified;
						else // If file is not Modified, go to next file
							continue;
					}
					else
					{
						// File Added
						action = FileEvent::Added;
					}
					// Call callback.
					CallFileEvent(f, action, rmPtr);
					m_files[f] = fileWriteTime; // Update or add file.
				}
			}
		}


		// The thread
		std::thread m_thread;
		// Time to wait
		std::chrono::microseconds m_waitTime = std::chrono::microseconds(500);
		// Store the files in asset folder.
		std::unordered_map<fs::path, fs::file_time_type, FileHash> m_files;
		// is thread running
		bool m_IsRunning = true;
		// Pointer to the resource manager
		ResourceManager* rmPtr = nullptr;

		std::function<void(fs::path, FileEvent, void*)> CallFileEvent;
	};
};
};

static std::unique_ptr<PathWatcher> g_FileWatcher(nullptr);

#endif


ResourceManager::ResourceManager()
{
	
}

ResourceManager::~ResourceManager()
{ 
#ifdef CORAL_DEVELOP_MODE
	g_FileWatcher.get()->Stop();
	g_FileWatcher.release();
#endif
}


ResourceManager& ResourceManager::GetInstance()
{
	static ResourceManager rm;
	return rm;
}

fs::path ResourceManager::SetPath(const fs::path& relativePath)
{
	m_assetFolder = fs::current_path() / fs::path(relativePath);
	
#ifdef CORAL_DEVELOP_MODE
	g_FileWatcher = std::unique_ptr<PathWatcher>(new PathWatcher());
	// Start thread
	g_FileWatcher.get()->Start(m_assetFolder, this);
#endif

	return m_assetFolder;
}

void ResourceManager::OnFileEvent(fs::path path, FileEvent event)
{
	std::cout << path.c_str() << ": " << (int)event << std::endl;
}

void ResourceManager::ScanFolder(fs::path path, bool recursive)
{
	
}

