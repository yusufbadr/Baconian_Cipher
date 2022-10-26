
/* Program Name : Baconian Cipher
 * Program Description: Encrypts and Decrypts text using the Baconian Cipher Method
 * Last Modification Date: 25/03/2022
 * Author: Yusuf Badr | Student at Faculty of Computers and Artificial Intelligence, Cairo University
 * Email: yusufbadr@yahoo.com
 * LinkedIn: linkedin.com/in/yusufbadr/
 */

#include <iostream>
#include <string>
#include <cctype>
#include <cmath>
#include <optional>
#include <regex>

using namespace std;

void displayWelcomeMessage();
void displayMenu();
int getValidatedMenuOption();
bool isInputSpacesValid (string inText);
string convertToBinary(string inText);
int binaryToDecimal(string inText);
optional<string> baconianDecrypt(string cipherText);
string baconianEncrypt(string plainText);
bool isAllAlpha(string inText);

// see function definitions for comments on the function's purpose


int main() {
    displayWelcomeMessage();
    int menuOption = getValidatedMenuOption();
    while (menuOption != 3){
        if (menuOption == 1){ // plain -> cipher
            string userInput;
            cout << "Enter plain text:\n";
            getline(cin, userInput) ;//
            if (isInputSpacesValid(userInput) and isAllAlpha(userInput)){
                cout << "Your ciphertext is:\n" << baconianEncrypt(userInput) << "\n\n";
            } else {
                cout << "Incorrect plain text format.. Please try again\n\n";
            }


        } else if (menuOption == 2) { // cipher -> plain
            string userInput;
            cout << "Enter ciphertext:\n";
            getline(cin, userInput);
            if (isInputSpacesValid(userInput) and baconianDecrypt(userInput).has_value()){
                cout << "Original plain text:\n" << baconianDecrypt(userInput).value() << "\n\n";

                } else {
                    cout << "Incorrect ciphertext format.. Please try again\n\n";
                }
            }
        menuOption = getValidatedMenuOption();
    }
    return 0;
}

void displayWelcomeMessage(){
    cout << "!Welcome to the Baconian Cipher!\n";
}


void displayMenu(){
    cout << "Please choose one of the following numbers\n"
            "1. Encrypt your message (plain text -> ciphertext) \n"
            "2. Decrypt your message (ciphertext -> plain text)\n"
            "3. Exit\n"
            "Number:\n";
}

int getValidatedMenuOption(){
    displayMenu();
    string inNumberString;
    getline(cin, inNumberString);
    regex validInt("[1-3]{1}");
    while (!regex_match(inNumberString, validInt)) {
        cout << "Enter 1, 2 or 3:\n";
        getline(cin, inNumberString);
        regex_match(inNumberString, validInt);
    }
    return stoi(inNumberString);
}


bool isInputSpacesValid (string inText) { // to make sure string has no more than one space between 2 letters and no leading and trailing spaces
    if (inText.length()>1){
        if (inText[0] == ' ' or inText[inText.length() - 1] == ' '){
            return false;
        }
    } else if (inText.length() == 1){
        if (inText[0] == ' '){
            return false;
        }
    } else {
        return false;
    }

    for (int i = 1; i <= inText.length() - 1; i++){

        if (inText[i] == ' '){
            if (inText[i-1] == ' ') {
                return false;
            }
        }
    }
    return true;
}


string convertToBinary(string inText) { // parameter is e.g. AAAAA which is converted to 00000
    string temp;
    string binary;
    for (auto i: inText) {
        temp = i == 'A' ? "0" : "1";
        binary += temp;
    }
    return binary;
}


int binaryToDecimal(string inText){
    int sum = 0;
    int length = inText.length() - 1;
    for (auto i: inText){
        if (i == '1'){
            sum += (int) pow(2, length);
        }
        length--;
    }
    return sum;
}

// assumes cipherText is all upper case AND cipherText has no extra unallowed spaces (i.e. no >= 2 consecutive spaces)
optional<string> baconianDecrypt(string cipherText){
    string plainText;
    for (int i = 0; i < cipherText.length(); i++){
        int upperI = i + 4; //6+5 == 11 (del) AAAAA 6-AAAAA-10 === 6 + 4 = 10
        if (upperI > cipherText.length() - 1){ // 11 (del)
            return {};
        }

        string cipherLetter;
        while (i <= upperI){
            if (cipherText[i] == ' '){
                return {};
            }
            cipherLetter += toupper(cipherText[i]);
            i++;
        }
        char plainLetter =  65 + binaryToDecimal(convertToBinary(cipherLetter)); // cipherLetter may be = AAAAA
        plainText += plainLetter;
        if (i == cipherText.length()){
            break;

        } else if (cipherText[i] == ' '){
            plainText += ' ';
        } else {
            i-=1;
        }

    }
    return plainText;

}



string baconianEncrypt(string plainText){ // also capitalise every letter

    string cipherText;

    for (auto i: plainText) {
        string cipherLetter;
        if (isalpha(i)){
            char letter = toupper( i);
            int letterOrder = letter - 'A';
            string temp;
            for (int j = 0; j < 5; j++){
                temp = letterOrder % 2 == 0? "A" : "B";
                letterOrder /= 2;
                cipherLetter = temp + cipherLetter;
            }
            cipherText += cipherLetter;
        } else {
            cipherText += " ";
            //continue; // consider removing
        }
    }
    return cipherText;
}

bool isAllAlpha(string inText){
    for (auto i: inText){
        if (!isalpha(i) and i != ' '){
            return false;
        }
    }
    return true;
}