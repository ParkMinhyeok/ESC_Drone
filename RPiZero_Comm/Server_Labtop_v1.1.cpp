#include <opencv2/opencv.hpp>
#include <iostream>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

using namespace cv;

int main() {
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		std::cerr << "Error: WSAStartup failed." << std::endl;
		return -1;
	}

	//Socket Reset
	SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (serverSocket == INVALID_SOCKET) {
		std::cerr << "Error: Could not create socket." << std::endl;
		WSACleanup();
		return -1;
	}

	sockaddr_in serverAddr;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(12345);  // Server Port Num
	serverAddr.sin_addr.s_addr = INADDR_ANY;

	// Bind
	if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
		std::cerr << "Error: Could not bind." << std::endl;
		closesocket(serverSocket);
		WSACleanup();
		return -1;
	}

	// Listen
	if (listen(serverSocket, 1) == SOCKET_ERROR) {
		std::cerr << "Error: Could not listen." << std::endl;
		closesocket(serverSocket);
		WSACleanup();
		return -1;
	}

	// Accept
	sockaddr_in clientAddr;
	int clientAddrSize = sizeof(clientAddr);
	SOCKET clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &clientAddrSize);
	if (clientSocket == INVALID_SOCKET) {
		std::cerr << "Error: Could not accept client connection." << std::endl;
		closesocket(serverSocket);
		WSACleanup();
		return -1;
	}

	int cntFrame = 0;
	Mat frame(Size(320, 240), CV_8UC1);
	int imgSize = frame.total() * frame.elemSize();
	while (true) {
		// Comm
		int bytes = recv(clientSocket, reinterpret_cast<char*>(frame.data), imgSize, 0);
		if (bytes == imgSize || cntFrame > 50) {
			if (bytes == SOCKET_ERROR) {
				std::cerr << "Error: Could not receive data." << std::endl;
				break;
			}
			else if (bytes == 0) {
				std::cerr << "Client disconnected." << std::endl;
				break;
			}

			imshow("Received Frame", frame);
		}
		cntFrame++;
		if (waitKey(100) >= 0)
			break;

	}

	closesocket(clientSocket);
	closesocket(serverSocket);
	WSACleanup();
	return 0;
}
