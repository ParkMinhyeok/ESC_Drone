#include <unistd.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

using namespace cv;
using namespace std;

int main() {
    // 카메라 초기화
    VideoCapture cap(0);
    if (!cap.isOpened()) {
        cerr << "Error: Could not open camera." << endl;
        return -1;
    }

    int width = 640;
    int height = 480;
    cout << width << "X"<< height << endl;
    cap.set(CAP_PROP_FRAME_WIDTH, width);
    cap.set(CAP_PROP_FRAME_HEIGHT, height);

    // 소켓 초기화
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        cerr << "Error: Could not create socket." << endl;
        return -1;
    }

    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(12345);  // 서버 포트 번호
    serverAddr.sin_addr.s_addr = inet_addr("192.168.1.5");  // PC의 IP 주소 입력

    // 서버에 연결
    if (connect(clientSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == -1) {
        cerr << "Error: Could not connect to server." << endl;
        return -1;
    }

    Mat frame;
    int imgSize = 76800;
    while (true) {
        cap >> frame;
        if (frame.empty()) {
            cerr << "Error: Could not read frame." << endl;
            break;
        }

        cvtColor(frame, frame, COLOR_BGR2GRAY);
        resize(frame, frame, Size(320, 240));

//      cout << frame.cols * frame.rows << endl;
        if (send(clientSocket, frame.data, imgSize, 0) == -1) {
            cerr << "Error: Could not send data." << endl;
            break;
        }

        imshow("frame", frame);

        if (waitKey(40) >= 0)
            break;
    }

    close(clientSocket);
    return 0;
}
