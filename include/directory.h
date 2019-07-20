#include <string>

#ifdef __linux__

#else
#error Unsupported OS! (Or you are not compiling with gcc).
#endif

class Directory{
public:
	Directory(std::string);
	~Directory();
	
	Directory(Directory & other) = delete;
	Directory(Directory && other) = delete;
	Directory & operator=(Directory & other) = delete;
	Directory & operator=(Directory && other) = delete;

	
private:
	
};
