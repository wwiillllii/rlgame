#include <string>

class RLException{
public:
	RLException(std::string what, std::string why, std::string where);
	~RLException() = default;
	
	virtual std::string what() const noexcept;
	virtual std::string why() const noexcept;
	virtual std::string where() const noexcept;
	
	virtual std::string description() const noexcept;

protected:
	std::string _what;
	std::string _why;
	std::string _where;
};
