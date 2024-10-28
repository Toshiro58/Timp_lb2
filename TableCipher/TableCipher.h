#pragma once
#include <string>
#include <stdexcept>
#include <codecvt>
class TableCipher
{
private:
    int key;
public:
    TableCipher() = delete; 
    TableCipher(int key, const std::wstring& text);   
    std::wstring encrypt(const std::wstring& text);
    std::wstring decrypt(const std::wstring& encrypted_text);
    int getValidKey(const int& key, const std::wstring& text);
    std::wstring getValidOpenText(const std::wstring & s);
    std::wstring getValidCipherText(const std::wstring & s);
};

class cipher_error : public std::invalid_argument
{
public:
    explicit cipher_error(const std::string& what_arg)
        : std::invalid_argument(what_arg)
    {
    }

    explicit cipher_error(const char* what_arg)
        : std::invalid_argument(what_arg)
    {
    }
};
