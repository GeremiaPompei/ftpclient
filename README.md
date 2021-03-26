# ftpclient

**ftpclient** è un programma scritto in C++ per inviare e ricevere dati tramite il protocollo FTP. 
Come si deduce dal nome esso funge da client che contatta un server FTP per le varie opzioni.
Il progetto si basa sull'uso delle librerie [**libcurl**](https://curl.se/libcurl/).

## Istallazione e build
### Istallazione libcurl
```
sudo apt install libcurl4-gnutls-dev
```
### Istallazione cmake
```
sudo apt install cmake
```
### Build
Installate le librerie libcurl e il tool cmake bisogna dare i seguenti comandi per creare l'eseguibile. Spostati con il terminale nella folder del progetto 
basta digitare 
```
mkdir build
cd build
cmake ..
make
```
Costruito il file eseguibile basta lanciarlo tramite il comando 
```
./ftpclient
```
Se viene mostrato un messaggio che informa del fatto che mancano i permessi basta lanciare il comando 
```
chmod +x ftpclient
```
## Utilizzo
Avviato il programma esso è composto da 3 semplici comandi, ovvero l'*inizializzatore* della stringa di connessione e i comandi relativi all'*invio* e alla 
*ricezione* di un file. L'inizializzatore deve essere ovviamente eseguito prima degli altri due comandi. Inoltre vi è il comando *exit* per terminare l'esecuzione.
Ogni comando tranne exit genera una risposta con **0** in caso di **errore** o **1** in caso di **successo**.
#### INITIALIZER
Permette di inizializzare una stringa di connessione FTP fornando l'*url* del server remoto. Il comando è 
```
I ftp://<URL>
```
#### SEND
Permette di inviare un *file* *locale* in una *directory* *remota*. Il comando è 
```
S /<LOCALDIR>/<LOCALFILE> /<REMOTEDIR>
```
#### RECEIVE
Permette di ricevere un *file* *remoto* in una *directory* *locale*. Il comando é 
```
R /<REMOTEDIR>/<REMOTEFILE> /<LOCALDIR>
```
