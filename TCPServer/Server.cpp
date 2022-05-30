//
// Created by Jewcation Basmati on 5/26/22.
//

#include "Server.h"

//void Server::setListening(int listening) {
//    Server::listening = listening;
//}

Server::Server() {}

Server::Server(Server *pServer) {

}

//int Server::getListening() const {
//    return listening;
//}

void Server::setPass(const std::string &pass) {
    Server::pass = pass;
}

const unsigned short Server::getPort() const {
    return port;
}

const std::string &Server::getPass() const {
    return pass;
}

//void Server::setSockopt(int sockopt) {
//	Server::sockopt = sockopt;
//}
//
//int Server::getSockopt() const {
//	return sockopt;
//}
//
//void Server::setClientSocket(int clientSocket) {
//	Server::clientSocket = clientSocket;
//}
//
//int Server::getClientSocket() const {
//	return clientSocket;
//}
//
//const std::string &Server::getInputStr() const {
//	return inputStr;
//}
//
//void Server::setInputStr(const std::string &inputStr) {
//	Server::inputStr = inputStr;
//}

void Server::setPort(unsigned short port) {
	Server::port = port;
}

//const std::string &Server::getInputPass() const {
//    return inputPass;
//}
//
//void Server::setInputPass(const std::string &inputPass) {
//    Server::inputPass = inputPass;
//}
