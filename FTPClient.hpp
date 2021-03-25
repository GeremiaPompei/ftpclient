#ifndef FTPCLIENT_H
#define FTPCLIENT_H

#include "utility.h"

/**
 * Classe utile per costruire oggetti capaci di inviare e ricevere file tramite protocollo FTP.
 */
class FTPClient {
private:
    /**
     * Stringa di connessione ftp avente formato: ftp://username:password@ip:port
     */
    string url_;
    
public:
    /**
     * Metodo utile per inizializzare i parametri della stringa di connessione.
     */
    bool init(string username, string password, string ip, string port);
    
    /**
     * Metodo utile ad inviare il file locale fssource alla directory remota ftpdest.
     */
    bool send(const char* fssource, const char* ftpdest);
    
    /**
     * Metodo utile a ricevere il file remoto ftpsource nella directory locale fsdest.
     */
    bool receive(const char* ftpsource, const char* fsdest);
};

#endif
