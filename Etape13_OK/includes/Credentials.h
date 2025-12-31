#ifndef CREDENTIALS_H
#define CREDENTIALS_H

struct Credentials {
    char login[20];
    char password[20];
    
    Credentials();
    Credentials(const char* l, const char* p);
    
    void crypt();
    void decrypt();
};

#endif