#include <string>

#include "rlexception.h"

RLException::RLException(
		std::string what,
		std::string why,
		std::string where) : 
		__what(what),
		_why(why),
		_where(where),
		full_messasge("\nwhat: " + what + "why: " + why + "where: " + where)
		{}


const char* RLException::what() const noexcept{
	return this->full_messasge.c_str();
}

std::string RLException::_what() const noexcept{
	return __what;
}
std::string RLException::why() const noexcept{
	return _why;
}
std::string RLException::where() const noexcept{
	return _where;
}

std::string RLException::description() const noexcept{
	std::string _description = std::string();
	_description += "what: " + _what();
	_description += "why: " + why();
	_description += "where: " + where();
	return _description.c_str();
}
