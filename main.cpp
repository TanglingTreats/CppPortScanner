#include <iostream>
#include <cstdint>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define ERR_CONN -1
#define MAX_PORTS 65535

#define HELP_OPTION 0x80
#define PORT_OPTION 0x01

using std::cout; using std::endl;

uint8_t optionmask = 0;

void PrintHelp();

int main(int argc, char* argv[]) {

  std::string targetIp = "127.0.0.1";
  
  if (argc < 2) {
    cout << "Target IP not specified, scanning on localhost..." << endl;
  } else {
    // TODO: Verify that first input is an IP
    int index = 1;

    // Parse optional arguments
    while (index < argc) {
      std::string arg = argv[index];
      if (arg[0] == '-') {
        // Parse options
        // Assumes option flags are all split up
        switch (arg[1]) {
        case 'h':
          optionmask |= HELP_OPTION;
          break;
        case 'p':
          optionmask |= PORT_OPTION;
          break;
        }
      } else {
        break;
      }

      ++index;
    }

    cout << std::format("Options: {}", optionmask) << endl;

    if (optionmask >= HELP_OPTION) {
      PrintHelp();
      return 0;
    }

    // Verify IP
    targetIp  = argv[index];
  }

  cout << std::format("Scanning {}", targetIp) << endl;

    // Opening TCP socket
  int serverSock = socket(AF_INET, SOCK_STREAM, 0);

  sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = INADDR_ANY;
  
  // Open socket with IP as target
  // for (int i = 1; i < MAX_PORTS; i++) {
  //   addr.sin_port = htons(i);

  
  //   if (connect(serverSock, (struct sockaddr *)&addr, sizeof(addr)) != ERR_CONN) {
  //     cout << std::format("PORT {} IS OPEN", i) << endl;
  //   } else {
  //     cout << std::format("PORT {} IS NOT OPEN", i) << endl;
  //     cout << std::format("ERR {}", errno) << endl;
  //   }

  //   close(serverSock);
  // }

  
  return 0;
}

void PrintHelp() {
  cout << "Printing help menu" << endl;
}
