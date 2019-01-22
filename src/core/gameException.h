#pragma once

#include <string>
#include <windows.h>

// Inherits from std::exception
class GameException : public std::exception
{
private:
	std::string message;
public:
	// default constructor
	GameException() throw() : message("Undefined error in game.") {}
	// copy constructor
	GameException(const GameException &e) throw() : std::exception(e), message(e.message) {}
	// constructor with args
	GameException(const std::string &s) throw() : message(s) {}
	// assignment operator
	GameException & operator= (const GameException &rhs) throw()
	{
		std::exception::operator=(rhs);
		this->message = rhs.message;
	}
	// destructor
	virtual ~GameException() throw() {};

	// override what from base class
	virtual const char* what() const throw() { return this->getMessage(); }

	const char* getMessage() const throw() { return message.c_str(); }
};
	
inline void ThrowIfFailed(HRESULT result, std::string msg = "Undefined error in game.") 
{
	if (FAILED(result)) 
	{
		throw GameException(msg);
	}
}
