#include "modAlphaCipher.h"
#include <iostream>
#include <cctype>
#include <string>
using namespace std;

void check(const wstring& Text, const wstring& key, const bool destructCipherText = false)
{
    try {
        wstring cipherText;
        wstring decryptedText;
        modAlphaCipher cipher(key);
        cipherText = cipher.encrypt(Text); // зашифровывание
        if(destructCipherText) {
            cipherText.front() = towlower(cipherText.front());
        }
        decryptedText = cipher.decrypt(cipherText);
        wcout << L"Ключ = " << key << endl;
        wcout << L"Введенный текст: "<< Text << endl;
        wcout << L"Зашифрованный текст: "<< cipherText << endl;
        wcout << L"Расшифрованный текст: "<<decryptedText << endl;

    } catch(const cipher_error& e) {
        cerr << "Error: " << e.what() << endl;
    }
}

int main()
{
    locale loc("ru_RU.UTF-8");
    locale::global(loc);

    wcout << L"Проверка на  коррекность ключа:" << endl;
    check(L"Башмачково", L"К1Ю4"); 
    wcout << L"Проверка на преобразование регистра:" << endl;
    check(L"Башмачково", L"КЛЮЧ");
    wcout << L"Проверка на то,что после обработки ничего не остаолось:" << endl;
    check(L"058", L"КЛЮЧ");
    wcout << L"Проверка на коряво зашифрованный текс:" << endl;
    check(L"Башмачково", L"КЛЮЧ", true);
    
    return 0;
}
