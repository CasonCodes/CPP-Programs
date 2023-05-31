//myEcho Project

#include <iostream>
#include <WinSock2.h>
using namespace std;

#pragma comment (lib, "ws2_32.lib")

SOCKET connectsock(const char[], const char[], const char[]);

const int maxBuffer = 128;
const int maxHostName = 80;

int main() 
{
	cout << "Echo Server: ";
	char host[maxHostName] = "";
	cin.getline(host, maxHostName - 1);

	if (strlen(host) > 0) 
	{
		WORD wVersion = 0x0202;
		WSADATA wsaData;
		int iResult = WSAStartup(wVersion, &wsaData);

		if (iResult != 0) 
		{
			cout << "Unable to initialize Windows Socket Library." << endl;
			return 0;
		}

		cout << "Attempting to connect to " << host << " using service = ECHO" << endl << endl;
		SOCKET s = connectsock(host, "echo", "TCP");
		
		if (s != INVALID_SOCKET)
		{
			cout << "TCP connection established!" << endl << endl;
			cout << "Message: ";

			char message[maxBuffer];
			cin.getline(message, maxBuffer - 1);

			while (strlen(message) > 0 && _stricmp(message, "quit") != 0)
			{
				cout << "Sending message: " << message << endl;
				int numBytesSent = send(s, message, strlen(message) + 1, 0);

				if (numBytesSent > 0)
				{
					cout << "Number of bytes sent: " << numBytesSent << endl << endl;

					char stringBuffer[maxBuffer];
					int numBytesRecvd = recv(s, stringBuffer, sizeof(stringBuffer), 0);

					if (numBytesRecvd > 0)
					{
						cout << "Received message: ";
						for (int i = 0; i < numBytesRecvd; i++)
						{
							cout << endl;
							cout << "Number of bytes received: " << numBytesRecvd << endl << endl;
						}
						cout << endl << endl;

						cout << "Message: ";
						cin.getline(message, maxBuffer - 1);
					}
					else
					{
						cout << "Unable to send message to remote machine." << endl;
						strcpy_s(message, maxBuffer, "quit");
					}
				}
				shutdown(s, 1);
				closesocket(s);
			}
			WSACleanup();
		}
	}
}