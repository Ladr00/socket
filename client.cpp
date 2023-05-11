#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>
#include <unistd.h>

int main() {
    int clientSocket;
    struct sockaddr_in serverAddress;
    char buffer[1024];

    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        std::cerr << "Ошибка при создании сокета." << std::endl;
        return -1;
    }

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(9877);
    serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1) {
        std::cerr << "Ошибка при подключении к серверу." << std::endl;
        return -1;
    }

    std::cout << "Подключение к серверу установлено." << std::endl;

    std::cout << "Введите название сокета: ";
    std::string filename;
    std::cin >> filename;

    int bytesSent = send(clientSocket, filename.c_str(), filename.size(), 0);
    if (bytesSent == -1) {
        std::cerr << "Ошибка при отправке данных." << std::endl;
        return -1;
    }

    memset(buffer, 0, sizeof(buffer));
    int bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);
    if (bytesRead == -1) {
        std::cerr << "Ошибка при чтении данных." << std::endl;
        return -1;
    }

    std::cout << "Получен ответ от сервера: " << buffer << std::endl;

    close(clientSocket);

    return 0;
}
