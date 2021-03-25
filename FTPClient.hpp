#ifndef FTPCLIENT_H
#define FTPCLIENT_H

#include "utility.h"

class FTPClient {
private:
    string url_;
    
public:
    bool init(string username, string password, string ip, string port);
    bool send(const char* fssource, const char* ftpdest);
    bool receive(const char* ftpsource, const char* fsdest);
    const string url();
};

#endif
