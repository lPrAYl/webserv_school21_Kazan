//
// Created by Jewcation Basmati on 5/29/22.
//

#include "Client.h"

Client::Client() {}

Client::~Client() {

}

const std::string &Client::getInputStr() const {
	return inputStr;
}

const std::string &Client::getPass() const {
	return pass;
}

const std::string &Client::getUser() const {
	return user;
}

const std::string &Client::getNick() const {
	return nick;
}

const std::string &Client::getChannel() const {
	return channel;
}

int Client::getFd() const {
	return fd;
}

int Client::getListening() const {
	return listening;
}

int Client::getSockopt() const {
	return sockopt;
}

int Client::getClientSocket() const {
	return clientSocket;
}

void Client::setInputStr(const std::string &inputStr) {
	Client::inputStr = inputStr;
}

void Client::setPass(const std::string &pass) {
	Client::pass = pass;
}

void Client::setUser(const std::string &user) {
	Client::user = user;
}

void Client::setNick(const std::string &nick) {
	Client::nick = nick;
}

void Client::setChannel(const std::string &channel) {
	Client::channel = channel;
}

void Client::setFd(int fd) {
	Client::fd = fd;
}

void Client::setListening(int listening) {
	Client::listening = listening;
}

void Client::setSockopt(int sockopt) {
	Client::sockopt = sockopt;
}

void Client::setClientSocket(int clientSocket) {
	Client::clientSocket = clientSocket;
}

Client::Client(Client *pClient) {

}
