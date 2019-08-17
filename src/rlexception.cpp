#include <string>

#include "rlexception.h"

RLException::RLException(
		std::string what,
		std::string why,
		std::string where) : 
		_what(what),
		_why(why),
		_where(where)
		{}

std::string RLException::what() const noexcept{
	return _what.c_str();
}
std::string RLException::why() const noexcept{
	return _why.c_str();
}
std::string RLException::where() const noexcept{
	return _where.c_str();
}

std::string RLException::description() const noexcept{
	std::string _description = std::string();
	_description += "what: " + what();
	_description += "why: " + why();
	_description += "where: " + where();
	return _description.c_str();
}
