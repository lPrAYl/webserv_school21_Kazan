//
// Created by Jewcation Basmati on 5/26/22.
//

#ifndef TCPSERVER_SERVER_H
#define TCPSERVER_SERVER_H


#include <string>
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#include "Server.h"

class Server {
public:
    Server();

    Server(Server *pData);

//    void setListening(int listening);

//    int getListening() const;

    void setPass(const std::string &pass);

    const unsigned short getPort() const;

    const std::string &getPass() const;

//	void setSockopt(int sockopt);

//	int getSockopt() const;

//	const sockaddr_in &getHint() const;

//	void setClientSocket(int clientSocket);

//	int getClientSocket() const;

//	const std::string &getInputStr() const;

//	void setInputStr(const std::string &inputStr);

	void setPort(unsigned short port);

//    const std::string &getInputPass() const;

//    void setInputPass(const std::string &inputPass);

private:
    unsigned short port;
    std::string pass;

//    int listening;
//	int sockopt;
//	int clientSocket;
//	std::string inputStr;
//    std::string inputPass;

};


#endif //TCPSERVER_SERVER_H
