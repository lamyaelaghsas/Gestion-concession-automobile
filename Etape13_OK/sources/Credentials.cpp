#include "../includes/Credentials.h"
#include <cstring>

Credentials::Credentials() {
    login[0] = '\0';
    password[0] = '\0';
}

Credentials::Credentials(const char* l, const char* p) {
    strncpy(login, l, 19);
    login[19] = '\0';
    strncpy(password, p, 19);
    password[19] = '\0';
}

void Credentials::crypt() {
    for (int i = 0; i < 20 && login[i] != '\0'; i++) {
        unsigned char c = (unsigned char)login[i];
        c += 9;
        if (c > 255) c -= 255;
        login[i] = (char)c;
    }
    
    for (int i = 0; i < 20 && password[i] != '\0'; i++) {
        unsigned char c = (unsigned char)password[i];
        c += 5;
        if (c > 255) c -= 255;
        password[i] = (char)c;
    }
}

void Credentials::decrypt() {
    for (int i = 0; i < 20 && login[i] != '\0'; i++) {
        unsigned char c = (unsigned char)login[i];
        if (c < 9) c += 255;
        c -= 9;
        login[i] = (char)c;
    }
    
    for (int i = 0; i < 20 && password[i] != '\0'; i++) {
        unsigned char c = (unsigned char)password[i];
        if (c < 5) c += 255;
        c -= 5;
        password[i] = (char)c;
    }
}