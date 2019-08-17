#include "directory.h"
#include "rlexception.h"

#ifdef __linux__

#include <sys/types.h>
#include <dirent.h>
#include <errno.h>

// TODO Move this functioin to some global file, it will be useful elsewhere.
static std::string getErrnoDescription(int saved_errno){
	switch(errno){
	case EACCES:
		return "Permission denied!\n";
	case EBADF:
		return "The given fd can't be used in this case.\n";
	case EMFILE:
		return "This program has opened too many files.\n"
			"There is probably a resource leak in this program.\n";
	case ENFILE:
		return "There are too many files opened in the system.\n"
			"There is probably a resource leak somewhere, possibly here.\n";
	case ENOENT:
		return "File/directory could not be found.\n";
	case ENOMEM:
		return "Out of memory!\n"
			"There is probably a resource leak in this program.\n";
	case ENOTDIR:
		return "Directory expected, got something else.\n";
	default:
		return "unknown errno: " + std::to_string(saved_errno) + "\n";
	}
}

Directory::Directory(std::string dir_path){
	DIR * dir = opendir(dir_path.c_str());
	struct dirent * entry = nullptr;
	std::string file_path;

	if (!dir){
		int saved_errno = errno;
		throw RLException(
			std::string("Directory ")
				+ dir_path
				+ std::string(" could not be opened!\n"),
			getErrnoDescription(saved_errno),
			std::string("Directory::Directory(std::string dir_path)\n")
			);
	}

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
