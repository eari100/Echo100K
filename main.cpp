#include <iostream>
#include <winsock2.h>
// IP 주소 다루는 함수
#include <ws2tcpip.h>

// Winsock2 link
#pragma comment(lib, "ws2_32.lib")

#define IO_READ         0
#define IO_WRITE        1
// 2^10
#define MAX_BUFFER_SIZE 1024

class IocpServer 
{
    private:
        // handle은 방을 관리하는 key역할
        HANDLE m_hIOCP;
		SOCKET m_hListenSock;
        int m_port;

    public:
		IocpServer(int port) : m_port(port), m_hIOCP(INVALID_HANDLE_VALUE), m_hListenSock(INVALID_SOCKET) {}

        ~IocpServer()
        {
            if (m_hListenSock != INVALID_SOCKET) 
            {
                closesocket(m_hListenSock);
			}
            if (m_hIOCP != INVALID_HANDLE_VALUE)
            {
				CloseHandle(m_hIOCP);
            }
        }

        // 서버 초기화 및 리슨 소켓 생성
        bool Start()
        {
            // 윈도우 커널에 고성능 IOCP포트 개설 요청
            m_hIOCP = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);
            if (m_hIOCP == NULL) 
            {
                std::cerr << "IOCP 포트 생성 실패" << "\n";
                return false;
			}

            // Async Overlapped IO TCP Socket 개방
            m_hListenSock = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);
            if (m_hListenSock == INVALID_SOCKET)
            {
                std::cerr << "Listen Socket 생성 실패" << "\n";
                return false;
            }

            std::cout << "IOCP 포트 및 중첩 IO 소켓 생성 완료.\n";

            return true;
        }
};

int main() 
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    std::cout << "HyperEcho Server Booting...\n";

    // WinSock 초기화
    WSADATA wsaData;
    // Winsock 2.2 version
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) 
    {
        std::cerr << "Winsock initialized fail";
        return 1;
    }

    IocpServer server(9000);
    if (!server.Start())
    {
        WSACleanup();
        return 1;
    }

	std::cout << "Winsock initialized successfully.\n";

    WSACleanup();
	return 0;
}