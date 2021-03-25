#include "FTPClient.hpp"

struct FtpFile 
{
    const char *filename;
    FILE *stream;
};

static size_t write_callback(void *buffer, size_t size, size_t nmemb, FILE *stream)
{
    struct FtpFile *out = (struct FtpFile *)stream;
    if(!out->stream) {
        out->stream = fopen(out->filename, "wb");
        if(!out->stream)
        return -1;
    }
    return fwrite(buffer, size, nmemb, out->stream);
}

static size_t read_callback(char *ptr, size_t size, size_t nmemb, FILE *stream)
{
  curl_off_t nread;
  size_t retcode = fread(ptr, size, nmemb, stream);
  nread = (curl_off_t)retcode;
  return retcode;
}

string getFileName(string source, string dest)
{
    string fileName = source;
    size_t p = fileName.find_last_of("/");
    fileName = fileName.substr(p, fileName.length());
    return dest+fileName;
}

bool FTPClient::init(string username, string password, string ip, string port)
{
    url_ = "ftp://"+username+":"+password+"@"+ip+":"+port+"/";
    /*CURL *curl;
    curl_easy_setopt(curl, CURLOPT_URL, url_.c_str());
    CURLcode res = curl_easy_perform(curl);
    if(res != CURLE_OK)
        return false;
    curl_easy_cleanup(curl);
    curl_global_cleanup();*/
    return true;
}


bool FTPClient::send(const char* fssource, const char* ftpdest)
{
    try {
        string dest = url_ + getFileName(fssource, ftpdest);
        CURL *curl;
        CURLcode res;
        FILE *hd_src;
        struct stat file_info;
        curl_off_t fsize;
        if(stat(fssource, &file_info))
            return false;
        fsize = (curl_off_t)file_info.st_size;
        hd_src = fopen(fssource, "rb");
        curl_global_init(CURL_GLOBAL_ALL);
        curl = curl_easy_init();
        if(curl) {
            curl_easy_setopt(curl, CURLOPT_READFUNCTION, read_callback);
            curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);
            curl_easy_setopt(curl, CURLOPT_URL, dest.c_str());
            curl_easy_setopt(curl, CURLOPT_READDATA, hd_src);
            curl_easy_setopt(curl, CURLOPT_INFILESIZE_LARGE, (curl_off_t)fsize);
            res = curl_easy_perform(curl);
            if(res != CURLE_OK)
                return false;
            curl_easy_cleanup(curl);
        }
        fclose(hd_src);
        curl_global_cleanup();
        return true;
    } __catch(exception e) {
        return false;
    }
}

bool FTPClient::receive(const char* ftpsource, const char* fsdest)
{
    try {
        string dest = getFileName(ftpsource, fsdest);
        CURL *curl;
        CURLcode res;
        struct FtpFile ftpfile = {
            dest.c_str(),
            NULL
        };
        curl_global_init(CURL_GLOBAL_DEFAULT);
        curl = curl_easy_init();
        if(curl) {
            string fullsource = url_+ ftpsource;
            curl_easy_setopt(curl, CURLOPT_URL, fullsource.c_str());
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &ftpfile);
            res = curl_easy_perform(curl);
            curl_easy_cleanup(curl);
            if(CURLE_OK != res) 
                return false;
        }
        if(ftpfile.stream)
            fclose(ftpfile.stream);
        curl_global_cleanup();
        return true;
    } __catch(exception e) {
        return false;
    }
}

const string FTPClient::url()
{
    return url_;
}
