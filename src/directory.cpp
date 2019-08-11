#include "directory.h"

#ifdef __linux__

#include <sys/types.h>
#include <dirent.h>
#include <exception>

Directory::Directory(std::string dir_path){
	DIR * dir = opendir(dir_path.c_str());
	struct dirent * entry = nullptr;
	std::string file_path;

	if (!dir)
		throw std::exception(
			std::string("Directory ") + dir_path + " could not be opened!\n"
		);

	while (true){
		entry = readdir(dir);
		if (!entry) break;
		file_path = dir_path + "/" + entry->d_name;

		switch (entry->d_type){
		case DT_REG:
			this->files.push_back(std::string(file_path));
			break;
		case DT_DIR:
			this->subdirs.push_back(std::string(file_path));
			break;
		}
	}

	closedir(dir);
}

#else
#error Unsupported OS! (Or you are not compiling with gcc).
#endif

Directory::~Directory(){}

const std::vector<std::string> & Directory::getFiles() const{
	return this->files;
}

const std::vector<std::string> & Directory::getSubdirs() const{
	return this->subdirs;
}
