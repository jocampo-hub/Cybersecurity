#include <iostream>
#include <vector>
using namespace std;

class Vigenere {
private:
    string key;
    static const string normalAlphabet;
    vector<vector<char>> cipherAlphabets;

public:
    Vigenere() {
        key = "";
        generateCipherAlphabets();
    }

    void setKey(const std::string& newKey) {
        // Convert the key to uppercase for case-agnostic functionality
        key = "";
        for (char ch : newKey) {
            key += toupper(ch);
        }
        generateCipherAlphabets();
    }

    std::string getKey() const {
        return key;
    }

    void displayCipherAlphabets() const {
        for (const auto& row : cipherAlphabets) {
            for (char characters : row) {
                std::cout << characters << " ";
            }
            std::cout << std::endl;
        }
    }

    string encrypt(const string& plaintext) const {
        string sanitizedText = sanitize(plaintext);
        string ciphertext = "";

        int keyIndex = 0;
        for (char characters : sanitizedText) {
            if (isalpha(characters)) {
                char encryptedChar = cipherAlphabets[keyIndex % key.length()][characters - 'A'];
                ciphertext += toupper(encryptedChar);
                keyIndex++;
            }
        }

        return ciphertext;
    }

    std::string decrypt(const string& ciphertext) const {
        std::string decryptedText = "";

        int keyIndex = 0;
        for (char ch : ciphertext) {
            if (isalpha(ch)) {
                char decryptedChar = getDecryptedChar(ch, keyIndex);
                decryptedText += decryptedChar;
                keyIndex++;
            }
        }

        return decryptedText;
    }

private:
    void generateCipherAlphabets() {
        cipherAlphabets.clear();
        for (char ch : key) {
            std::vector<char> row;
            for (int i = 0; i < normalAlphabet.length(); ++i) {
                row.push_back(normalAlphabet[(i + (ch - 'A')) % normalAlphabet.length()]);
            }
            cipherAlphabets.push_back(row);
        }
    }

    string sanitize(const string& text) const {
        string sanitizedText = "";
        for (char characters : text) {
            if (isalpha(characters)) {
                sanitizedText += toupper(characters);
            }
        }
        return sanitizedText;
    }

    char getDecryptedChar(char characters, int keyIndex) const {
        for (char rowCharacters : normalAlphabet) {
            if (toupper(characters) == cipherAlphabets[keyIndex % key.length()][rowCharacters - 'A']) {
                return tolower(rowCharacters);
            }
        }
        return characters; // If the character is not found in the cipher, return as is
    }
};

const string Vigenere::normalAlphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

int main() {
    Vigenere vigenereCipher;

    cout << "Enter a cipher key: ";
    string key;
    cin >> key;

    // Check if the key contains only uppercase alphabetic characters
    for (char characters : key) {
        if (!isalpha(characters) || !isupper(characters)) {
            cout << "Invalid key! Please enter only uppercase alphabetic characters." << endl;
            return 1;
        }
    }

    vigenereCipher.setKey(key);

    cout << "Cipher Alphabets:" << endl;
    vigenereCipher.displayCipherAlphabets();

    string plaintext;
    cin >> plaintext;

    string ciphertext = vigenereCipher.encrypt(plaintext);
    cout << "\nEncrypted Text: " << ciphertext << endl;

    string decryptedText = vigenereCipher.decrypt(ciphertext);
    cout << "Decrypted Text: " << decryptedText << endl;

    return 0;
}
