#ifndef SERVER_HPP
#define SERVER_HPP

# include <iostream>

# include "Connection.hpp"

class Server {
private:
	int				port;
	std::string		password;
	Connection		connection;

	Server();

public:
	Server(int port, const std::string& password);
	~Server();

	


};


#endif