#include "utility.h"
#include "FTPClient.hpp"

void split(string str, vector<string> *v, char delimiter) {
        string token = "";
        for(auto c : str) {
            if(c == delimiter) {
                token += "\0";
                v->push_back(token);
                token = "";
            } else {
                token += c;
            }
        }
        token += "\0";
        v->push_back(token);
    }

int main(int argc, char **argv)
{
    FTPClient *client = new FTPClient();
    while(true) {
        try {
            cout << "Inserisci I, S o R(INITIALIZER, SEND o RECEIVE), username, password, ip e porta (per I) o sorgente e destinazione separati da uno spazio (per S o R). Scrivi exit per uscire!" << endl << "I user pass ip port" << endl << "S/D path_source/file path_dest" << endl;
            vector<string> v;
            char in[200];
            cout << " > ";
            cin.getline(in, sizeof(in));
            if(string(in) == "exit") break;
            split(in, &v, ' ');
            if(v[0] == "I") {
                cout << "Response: " << client->init(v[1].c_str(), v[2].c_str(), v[3].c_str(), v[4].c_str()) << endl;
                cout << client->url() << endl;
            } else if(v[0] == "S")
                cout << "Response: " << client->send(v[1].c_str(), v[2].c_str()) << endl;
            else if(v[0] == "R")
                cout << "Response: " << client->receive(v[1].c_str(), v[2].c_str()) << endl;
            else
                cout << "Metodo non valido!" << endl;
        } __catch(exception e) {
            cout << e.what() << endl;
        }
    }
    
}
