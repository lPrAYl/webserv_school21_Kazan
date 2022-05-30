//
// Created by Jewcation Basmati on 5/29/22.
//

#ifndef TCPSERVER_CLIENT_H
#define TCPSERVER_CLIENT_H

#include "Server.h"

class Client {
public:
	Client();

	Client(Client *pClient);

	virtual ~Client();

	const std::string &getInputStr() const;

	const std::string &getPass() const;

	const std::string &getUser() const;

	const std::string &getNick() const;

	const std::string &getChannel() const;

	int getFd() const;

	int getListening() const;

	int getSockopt() const;

	int getClientSocket() const;

	void setInputStr(const std::string &inputStr);

	void setPass(const std::string &pass);

	void setUser(const std::string &user);

	void setNick(const std::string &nick);

	void setChannel(const std::string &channel);

	void setFd(int fd);

	void setListening(int listening);

	void setSockopt(int sockopt);

	void setClientSocket(int clientSocket);

private:
	std::string inputStr;
	std::string pass;
	std::string user;
	std::string nick;
	std::string channel;
	int fd;
	int listening;
	int sockopt;
	int clientSocket;
};


#endif //TCPSERVER_CLIENT_H
