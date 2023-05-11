#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>
#include <unistd.h>

int main() {
    int serverSocket, clientSocket;
    struct sockaddr_in serverAddress, clientAddress;
    char buffer[1024];

    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        std::cerr << "Ошибка при создании сокета." << std::endl;
        return -1;
    }

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(9877);

    if (bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1) {
        std::cerr << "Ошибка при привязке сокета." << std::endl;
        return -1;
    }

    if (listen(serverSocket, 5) == -1) {
        std::cerr << "Ошибка при прослушивании сокета." << std::endl;
        return -1;
    }

    std::cout << "Сервер запущен и ожидает соединений..." << std::endl;

    socklen_t clientAddressLength = sizeof(clientAddress);

    clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddress, &clientAddressLength);
    if (clientSocket == -1) {
        std::cerr << "Ошибка при принятии соединения." << std::endl;
        return -1;
    }

    std::cout << "Соединение установлено." << std::endl;

    memset(buffer, 0, sizeof(buffer));
    int bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);
    if (bytesRead == -1) {
        std::cerr << "Ошибка при чтении данных." << std::endl;
        return -1;
    }

    std::cout << "Получено название от клиента: " << buffer << std::endl;

    const char* response = "Получен сервером.";
    int bytesSent = send(clientSocket, response, strlen(response), 0);
    if (bytesSent == -1) {
        std::cerr << "Ошибка при отправке данных." << std::endl;
        return -1;
    }


    return 0;
}
