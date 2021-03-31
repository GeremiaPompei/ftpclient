#ifndef FTPCLIENT_H
#define FTPCLIENT_H

#include "utility.h"

/**
 * Classe utile per costruire oggetti capaci di inviare e ricevere file tramite protocollo FTP.
 */
class FTPClient {
private:
    /**
     * Stringa di connessione ftp avente formato: ftp://domainname/
     */
    string url_;
    /**
     * Numero di porta del server ftp.
     */
    string port_;
    /**
     * Username utile ad identificare il profilo dell'utente connesso.
     */
    string username_;
    /**
     * Password relativa all'username.
     */
    string password_;
    
    /**
     * Metodo utile a fornire alla curl i vari parametri per la connessione.
     */
    void connection(CURL *curl, string extensionUrl);
    
public:
    /**
     * Metodo utile per inizializzare la stringa di connessione.
     */
    bool init(string url, string port, string username, string password);
    
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
