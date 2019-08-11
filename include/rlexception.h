#include <exception>
#include <string>

class RLException : public std::exception{

	RLException();
	RLException(std::string what, std::string why, std::string where);
	~RLException() override;
	
	const char* what() const noexcept override;
	virtual const char* why() const noexcept;
	virtual const char* where() const noexcept;
	
	virtual const char* description() const noexcept;
};
