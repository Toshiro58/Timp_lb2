#include "TableCipher.h"
#include <iostream>
#include <limits>
#include <locale>
#include <string>
using namespace std;

void check(const wstring& Text, const int& key, const bool destructCipherText = false) {
    try {
        wstring cipherText;
        wstring decryptedText;
        TableCipher cipher(key, Text); 
        cipherText = cipher.encrypt(Text); 
        if(destructCipherText) {
            cipherText.front() = towlower(cipherText.front());
        }
        decryptedText = cipher.decrypt(cipherText);
        wcout << L"Ключ = " << key << endl;
        wcout << L"Введенный текст: " << Text << endl;
        wcout << L"Зашифрованный текст: " << cipherText << endl;
        wcout << L"Расшифрованный текст: " << decryptedText << endl;

    } catch(const cipher_error& e) {
        cerr << "Error: " << e.what() << endl;
    }
}
int main()
{
    locale loc("ru_RU.UTF-8");
    locale::global(loc);

    wcout << L"Проверка на корректность ключа:" << endl;
    check(L"Башмачково", -7); 
    wcout << L"Проверка на преобразование:" << endl;
    check(L"Башмачково топ водку там не пьют", 8);
    wcout << L"Проверка на то, что после обработки ничего не осталось:" << endl;
    check(L"058058058058058058", 8);
    wcout << L"Проверка на коряво зашифрованный текст:" << endl;
    check(L"Башмачково топ водку там не пьют", 8, true);
    return 0;
}
