#include <iostream>
#include <cstdint>
#include <unistd.h>
#include <vector>
#include <sys/socket.h>
#include <netinet/in.h>

#define ERR_CONN -1
#define MAX_PORTS 65535

using std::cout; using std::endl;

void PrintHelp();

enum class ScanType {
  SynScan,
  TcpConn,
  UdpScan,
  OsDetect,
  ServVerDetect
};

struct ClientConfig {
  bool help = false;
  bool verbose = false;
  uint16_t noOfPorts = MAX_PORTS;
  ScanType scanType = ScanType::SynScan;
};

/**
 *
 * nmap [OPTIONS] target_address
 *
**/

int main(int argc, char *argv[]) {
  ClientConfig config;

  std::string targetIp = "127.0.0.1";
  
  if (argc < 2) {
    cout << "Target IP not specified, scanning on localhost..." << endl;
  } else {

    int index = 1;

    // Convert to string_view
    std::vector<std::string_view> args(argv + 1, argv + argc);

    for (auto arg : args) {
      // Parse short options
      if (arg.at(0) == '-' && arg.at(1) != '-') {
        for (auto opt : arg) {
          switch (opt) {
          case 'h':
            config.help = true;
            break;
          }
        }
      } else {
        // Parse long options
        if (arg == "--help") {
          config.help = true;
        }
      }
      

      
      cout << arg << endl;
    }

    // Verify IP format
    targetIp  = argv[index];
  }

  if (config.help) {
    PrintHelp();
    return 0;
  }

  cout << std::format("Scanning {}", targetIp) << endl;

    // Opening TCP socket
  int serverSock = socket(AF_INET, SOCK_STREAM, 0);

  sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = INADDR_ANY;
  
  // Open socket with IP as target
  for (int i = 1; i < MAX_PORTS; i++) {
    addr.sin_port = htons(i);

  
    if (connect(serverSock, (struct sockaddr *)&addr, sizeof(addr)) != ERR_CONN) {
      cout << std::format("PORT {} IS OPEN", i) << endl;
    } else {
      cout << std::format("PORT {} IS NOT OPEN", i) << endl;
      cout << std::format("ERR {}", errno) << endl;
    }

    close(serverSock);
  }

  
  return 0;
}

void PrintHelp() {
  cout << "Printing help menu" << endl;
}
