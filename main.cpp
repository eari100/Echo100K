#include <iostream>
#include <winsock2.h>
// IP 주소 다루는 함수
#include <ws2tcpip.h>

// Winsock2 link
#pragma comment(lib, "ws2_32.lib")

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    std::cout << "HyperEcho Server Booting...\n";

    // WinSock 초기화
    WSADATA wsaData;
    // Winsock 2.2 version
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "Winsock initialized fail";
        return 1;
    }

	std::cout << "Winsock initialized successfully.\n";

    WSACleanup();
	return 0;
}