#include <string>
#include <vector>

class Directory{
public:
	Directory(std::string);
	~Directory();
	
	Directory(Directory & other) = delete;
	Directory(Directory && other) = delete;
	Directory & operator=(Directory & other) = delete;
	Directory & operator=(Directory && other) = delete;

	const std::vector<std::string> & getFiles() const;
	const std::vector<std::string> & getSubdirs() const;
	
private:
	std::vector<std::string> files;
	std::vector<std::string> subdirs;
};
