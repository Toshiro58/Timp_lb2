#include "TableCipher.h"

#include <iostream>
#include <locale>
#include <string>
using namespace std;

TableCipher::TableCipher(int key, const std::wstring& text)
    : key(getValidKey(key, text))
{
}

std::wstring TableCipher::encrypt(const std::wstring& text)
{
    // Вычисляем количество строк
    wstring tmp = getValidOpenText(text);
    int rows = static_cast<int>((tmp.length() + key - 1) / key); // округляем вверх
    wchar_t table[rows][key];

    // Заполнение массива символами из строки tmp
    int index = 0; // индекс для перебора символов в строке tmp
    for (int i = 0; i < rows; i++) { // проход по строкам таблицы
        for (int j = 0; j < key; j++) { // проход по столбцам
            if (index < static_cast<int>(tmp.length())) {
                table[i][j] = tmp[index];
                index++;
            } else {
                table[i][j] = L' '; 
            }
        }
    }

    std::wstring encrypted_text; // строка для хранения шифрованного текста

    // Порядок чтения на "сверху вниз, справа налево"
    for (int i = key - 1; i >= 0; i--) {
        for (int j = 0; j < rows; j++) {
            if (table[j][i] == L' ') {
                encrypted_text += L'*'; // заменяем пробел на звёздочку в зашифрованном тексте
            } else {
                encrypted_text += table[j][i];
            }
        }
    }

    return encrypted_text;
}

std::wstring TableCipher::decrypt(const std::wstring& encrypted_text)
{
    wstring tmp = getValidCipherText(encrypted_text);
    int rows = static_cast<int>((tmp.length() + key - 1) / key);
    wchar_t table[rows][key];

    int index = 0;
    for (int i = key - 1; i >= 0; i--) {
        for (int j = 0; j < rows; ++j) {
            if (index < static_cast<int>(tmp.length())) {
                table[j][i] = tmp[index];
                index++;
            } else {
                table[j][i] = L' ';
            }
        }
    }

    std::wstring decrypted_text;
    index = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < key; j++) {
            if (table[i][j] == L'*') {
                decrypted_text += L' '; // заменяем звёздочки на пробелы
            } else {
                decrypted_text += table[i][j];
            }
        }
    }
    
    return decrypted_text;
}

inline std::wstring TableCipher::getValidOpenText(const std::wstring& s)
{
    std::wstring tmp;
    for (auto c : s) {
        if (iswalpha(c)) {
            if (iswlower(c))
                tmp.push_back(towupper(c));
            else
                tmp.push_back(c);
        } else if (iswspace(c)) {
            tmp.push_back(c); 
        }
    }
    if (tmp.empty())
        throw cipher_error("Пустой открытый текст");
    return tmp;
}

inline std::wstring TableCipher::getValidCipherText(const std::wstring& s)
{
    if(s.empty())
        throw cipher_error("Пустой зашифрованный текст");

    std::wstring tmp(s);
    std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> converter;
    std::string m = converter.to_bytes(tmp);

    for (auto c : s) {
        if (c == L'*') {
            continue; 
        }
        if (!iswupper(c)) {
            throw cipher_error(std::string("Неправильный зашифрованный текст : ") + m);
        }
    }
    return tmp;
}

inline int TableCipher::getValidKey(const int& key, const std::wstring& text)
{
    if (key <= 1) {
        throw cipher_error("Некорректный ключ");
    }
    if (key > static_cast<int>(text.length()) / 2) {
        throw cipher_error("Длина ключа не должна превышать половину длины текста");
    }

    return key;
}
