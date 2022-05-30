
#include "Server.h"
#include "Client.h"

using namespace std;

int socketCreate(Server *Server, Client *client) {
	//  Create a socket
	client->setListening(socket(AF_INET, SOCK_STREAM, 0));

	int yes = 1;
	client->setSockopt(setsockopt(client->getListening(), SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)));
	if (client->getSockopt() == -1){ // for Address already in use
		perror("setsockopt");
		exit(EXIT_FAILURE);
	}
	// Server.getListening() - дискрептор сокета.
	// AF_INET - домен (для IPV4 - AF_INET),
	// SOCK_STREM - протокол связи  TCP->
	// 0 - значение протокола, для IP - 0

	if (client->getListening() == -1) {
		cerr << "Can't create a socket!";
		return -1;
	}
	return 0;
}

int ft_bind(Server *server, Client *client) {
	sockaddr_in hint;   // описывает сокет для работы с протоколами IP
	hint.sin_family = AF_INET;  // Всегда равно AF_INET
	hint.sin_port = htons(server->getPort());   // номер порта для сокета
	inet_pton(AF_INET, "0.0.0.0", &hint.sin_addr);  // переводит адрес в целое число
//  sin_addr содержит IP адрес, к которому будет привязан сокет

//  связывает сокет listening с номером порта hint.
	if (bind(client->getListening(), (sockaddr *) &hint, sizeof(hint)) == -1) {
		cerr << "Can't bind to IP/port";
		return -2;
	}
	//	Mark the socket for listening in
//  Переводит сокет сервера в пассивный режим (режим ожидания клиента).
//  SOMAXCONN - максимальная длинна очереди, ожидающих соединение для сокета listening
	if (listen(client->getListening(), SOMAXCONN) == -1) {
		cerr << "Can;t listen!";
		return -3;
	}
	return 0;
}

int ft_accept(Server *Server, Client *client) {
	sockaddr_in _client;
	socklen_t clientSize = sizeof(_client);
	char host[NI_MAXHOST];
	char svc[NI_MAXSERV];

//  создает новый FD, помещая в него первый запрос на соединение из очереди в сокет listening.
//  устанавливается соединение между сервером и клиентом.
	client->setClientSocket(accept(client->getListening(),
							  (sockaddr *) &_client,
							  &clientSize));
	if (client->getClientSocket() == -1) {
		cerr << "Problem with client connecting!";
		return -4;
	}
	//  Close the listener socket
	close(client->getListening());

	memset(host, 0, NI_MAXHOST);
	memset(svc, 0, NI_MAXSERV);

	int result = getnameinfo((sockaddr *) &_client,
							 sizeof(_client),
							 host,
							 NI_MAXHOST,
							 svc,
							 NI_MAXSERV,
							 0);
	if (result) {
		cout << host << " connected on " << svc << endl;
	} else {
		inet_ntop(AF_INET, &_client.sin_addr, host, NI_MAXHOST);
		cout << host << " connected on " << ntohs(_client.sin_port) << endl;
	}
	return 0;
}

int parser(int argc, char **argv, Server *Server) {
	if (argc != 3) {
		cerr << "Wrong argument's number!" << endl;
		return -1;
	}
	Server->setPort((unsigned short)strtol(argv[1],NULL,10));
	Server->setPass(argv[2]);
    return 0;
}

int finishFind(int start, string str) {
	for(int i = start; ; i++) {
		if ((char)(str[i]) == '\n') {
			return i - 1;
		}
	}
}

char *ft_slice(int start, int finish, string str) {
	char *res = new char[finish - start];
	int j = 0;
	for(int i = start; i < finish; i++) {
		res[j] = (char)str[i];
		j++;
	}
	return res;
}

int passCheck(Server *Server, Client *client) {
    int start = client->getInputStr().find("PASS :") + 6;
    int finish = finishFind(start, client->getInputStr());
    char *tmpPass = ft_slice(start, finish, client->getInputStr());
    client->setPass(tmpPass);
    if (Server->getPass() == client->getPass()) {
        cout << "Correct password!" << endl;
        return 0;
    } else {
        cerr << "Wrong password!" << endl;
        return -1;
    }
}

	void userParsing(Server *Server, Client *client) {
		int startSubstr = client->getInputStr().find("USER");
		string tmpString = client->getInputStr().substr(startSubstr);
		int start =tmpString.find(":") + 1;
		int finish = finishFind(start, tmpString);
		char *tmpUser = ft_slice(start, finish, tmpString);
		client->setUser(tmpUser);
}

	void nickParsing(Server *Server, Client *client) {
		int startSubstr = client->getInputStr().find("NICK");
		string tmpString = client->getInputStr().substr(startSubstr);
		int start =tmpString.find(" ") + 1;
		int finish = finishFind(start, tmpString);
		char *tmpNick = ft_slice(start, finish, tmpString);
		client->setNick(tmpNick);
}

	void clientParser(Server *Server, Client *client) {
		userParsing(Server, client);
		nickParsing(Server, client);
}


void displayMsg(Server *Server, Client *client) {
	char buf[4096];
	while (true) {
		// Clear the buffer
		memset(buf, 0, 4096);
		// Wait for a message
		int bytesRecv = recv(client->getClientSocket(), buf, 4096, 0);
		if (bytesRecv == -1) {
			cerr << "There was a connection issue" << endl;
			break;
		}
		if (bytesRecv == 0) {
			cout << "The client disconnected" << endl;
			break;
		}
		client->setInputStr(string(buf, 0, bytesRecv));
//        cout << Server->getInputStr().find("PASS :") << endl;

//		Парсинг клиента
		clientParser(Server, client);
//      проверка пароля
        if (passCheck(Server, client) != 0) {
            return ;
        }


        // Display message
		cout << "Recieved: " << string(buf, 0, bytesRecv) << endl;

		cout << ">>>>>>>>>>     Client parsing results     <<<<<<<<<<" << endl;
		cout << "InputStr: " << client->getInputStr() << endl;
		cout << "Listening: " << client->getListening() << endl;
		cout << "ClientSocket: " << client->getClientSocket() << endl;
		cout << "Sockopt: " << client->getSockopt() << endl;
		cout << "Nick: " << client->getNick() << endl;
		cout << "Pass: " << client->getPass() << endl;
		cout << "User: " << client->getUser() << endl;



		// Resend message
		send(client->getClientSocket(), buf, bytesRecv + 1, 0);
	}
}


int main(int argc, char **argv) {
    Server server = new Server();
//	массив клиентов для обеспечения возможности подключения нескольких клиентов
	Client client[10];
	client[0] = new Client();
	if (parser(argc, argv, &server) < 0) {
		return -1;
	}
	cout << "PORT: " << server.getPort() << endl;
	cout << "PASS :" << server.getPass() << endl;
//  Create a socket
	socketCreate(&server, &client[0]);

//  Bind the socket to a IP port
	ft_bind(&server, &client[0]);

//  Accept a call
	ft_accept(&server, &client[0]);

//  Write receiving display message, echo message
    displayMsg(&server, &client[0]);

//  Close socket
    close(client[0].getClientSocket());
    return 0;
}
