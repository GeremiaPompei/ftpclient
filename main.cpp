#include "utility.h"
#include "FTPClient.hpp"

int main(int argc, char **argv)
{
    FTPClient *client = new FTPClient(argv[0], argv[1], argv[2], argv[3]);
    cout << client->url() << endl;
    while(true) {
        try {
            string method, source, dest;
            cout << "Inserisci il SEND o RECEIVE." << endl;
            cin >> method;
            cout << "Inserisci il file sorgente." << endl;
            cin >> source;
            cout << "Inserisci il directory destinazione." << endl;
            cin >> dest;
            if(method == "SEND")
                client->send(source.c_str(), dest.c_str());
            else
                client->receive(source.c_str(), dest.c_str());
        } __catch(exception e) {
            cout << e.what() << endl;
        }
    }
    
}
