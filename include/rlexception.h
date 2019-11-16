#include <string>

class RLException : public std::exception{
public:
	RLException(std::string what, std::string why, std::string where);
	~RLException() = default;

	virtual const char* what() const noexcept override;

	virtual std::string _what() const noexcept;
	virtual std::string why() const noexcept;
	virtual std::string where() const noexcept;

	virtual std::string description() const noexcept;

protected:
	std::string __what;
	std::string _why;
	std::string _where;

	std::string full_messasge;
};
