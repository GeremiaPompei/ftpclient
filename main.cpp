#include "utility.h"
#include "FTPClient.hpp"

int main(int argc, char **argv)
{
  FTPClient *client = new FTPClient("geremiapompei", "1234", "localhost", "21");
  cout << client->url() << endl;
  //client->receive("Desktop/prova.txt", "/home/geremiapompei/Desktop/new");
  client->send("/home/geremiapompei/Desktop/new/prova.txt", "Desktop");
}
