#include "FTPClient.hpp"

/**
 * Funzione utile a scrivere il contenuto del buffer nel file out.
 */
static size_t write_callback(void *buffer, size_t size, size_t nmemb, FILE *out)
{
    return fwrite(buffer, size, nmemb, out);
}

/**
 * Funzione utile a leggere il contenuto del file in nel buffer.
 */
static size_t read_callback(char *buffer, size_t size, size_t nmemb, FILE *in)
{
  curl_off_t nread;
  size_t retcode = fread(buffer, size, nmemb, in);
  nread = (curl_off_t)retcode;
  return retcode;
}

/**
 * Metodo utile a costruire il filename completo della destinazione data il path della directory dest e il nome estrapolato dal path source.
 */
string getFileName(string source, string dest)
{
    string fileName = source;
    size_t p = fileName.find_last_of("/");
    fileName = fileName.substr(p, fileName.length());
    return dest + fileName;
}

/**
 * Metodo utile a fornire alla curl i vari parametri per la connessione.
 */
void FTPClient::connection(CURL *curl, string extensionUrl)
{
    curl_easy_setopt(curl, CURLOPT_URL, (url_ + extensionUrl).c_str());
    curl_easy_setopt(curl, CURLOPT_PORT, port_.c_str());
    curl_easy_setopt(curl, CURLOPT_USERNAME, username_.c_str());
    curl_easy_setopt(curl, CURLOPT_PASSWORD, password_.c_str());
}

/**
 * Implementazione del metodo init utile per inizializzare la stringa della connessione.
 */
bool FTPClient::init(string url, string port, string username, string password)
{
    bool success = false;
    url_ = url;
    port_ = port;
    username_ = username;
    password_ = password;
    CURL *curl;
    CURLcode res;
    curl = curl_easy_init();
    if(curl) {
        connection(curl, "");
        curl_easy_setopt(curl, CURLOPT_NOBODY, 1L);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        if(res == CURLE_OK)
            success = true;
    }
    return success;
}

/**
 * Implementazione del metodo send utile per inviare il file fssource nella directory ftpdest.
 */
bool FTPClient::send(const char* fssource, const char* ftpdest)
{
    bool success = false;
    string dest = getFileName(fssource, ftpdest);
    struct stat file_info;
    if(stat(fssource, &file_info))
        return false;
    CURL *curl;
    CURLcode res;
    FILE *hd_src;
    curl_off_t fsize;
    fsize = (curl_off_t)file_info.st_size;
    hd_src = fopen(fssource, "rb");
    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();
    if(curl) {
        connection(curl, dest);
        curl_easy_setopt(curl, CURLOPT_READFUNCTION, read_callback);
        curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);
        curl_easy_setopt(curl, CURLOPT_READDATA, hd_src);
        curl_easy_setopt(curl, CURLOPT_INFILESIZE_LARGE, (curl_off_t)fsize);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        if(res == CURLE_OK)
            success = true;
    }
    fclose(hd_src);
    curl_global_cleanup();
    return success;
}

/**
 * Implementazione del metodo receive utile per salvare il file ftpsource nella directory fsdest.
 */
bool FTPClient::receive(const char* ftpsource, const char* fsdest)
{
    bool success = false;
    string dest = getFileName(ftpsource, fsdest);
    FILE *out = fopen(dest.c_str(), "wb");
    if(!out)
        return false;
    CURL *curl;
    CURLcode res;
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if(curl) {
        connection(curl, ftpsource);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, out);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        if(CURLE_OK == res)
            success = true;
    } 
    fclose(out);
    curl_global_cleanup();
    if (!success)
        remove(dest.c_str());
    return success;
}
