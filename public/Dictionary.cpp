#include <iostream>
#include <fstream>
#include <string>
#include <map>
using namespace std;
void updateDictionary(const string &fileName, const map<string, string> &dictionary) {
    ofstream dictionaryFile(fileName);

    if (!dictionaryFile.is_open()) {
        cout << "Error: Unable to create or open the dictionary file." << endl;
        return;
    }

    for (const auto &entry : dictionary) {
        dictionaryFile << entry.first << " : " << entry.second << endl;
    }

    dictionaryFile.close();
    cout << "Dictionary has been updated successfully." << endl;
}
void addOrUpdateWord(map<string, string> &dictionary) {
    string word, meaning;
    cout << "Enter the word: ";
    cin >> word;
    cin.ignore();
    cout << "Enter the meaning: ";
    getline(cin, meaning);
    dictionary[word] = meaning;
    updateDictionary("dictionary.txt", dictionary);
}
void searchWord(const map<string, string> &dictionary) {
    string word;
    cout << "Enter the word to search: ";
    cin >> word;
    auto it = dictionary.find(word);
    if (it != dictionary.end()) {
        cout << "Meaning: " << it->second << endl;
    } else {
        cout << "Word not found in the dictionary." << endl;
    }
}
void removeWord(map<string, string> &dictionary) {
    string word;
    cout << "Enter the word to remove: ";
    cin >> word;
    auto it = dictionary.find(word);
    if (it != dictionary.end()) {
        dictionary.erase(it);
        updateDictionary("dictionary.txt", dictionary);
    } else {
        cout << "Word not found in the dictionary." << endl;
    }
}

int main() {
    map<string, string> dictionary;
    ifstream dictionaryFile("dictionary.txt");
    if (dictionaryFile.is_open()) {
        string line;
        while (getline(dictionaryFile, line)) {
            size_t pos = line.find(" : ");
            if (pos != string::npos) {
                string word = line.substr(0, pos);
                string meaning = line.substr(pos + 3);
                dictionary[word] = meaning;
            }
        }
        dictionaryFile.close();
    } else {
        cout << "Dictionary file not found. Creating a new dictionary." << endl;
    }

    int choice;
    while (true) {
        cout << "Dictionary Console Tool" << endl;
        cout << "1. Add/Update Word" << endl;
        cout << "2. Search Word" << endl;
        cout << "3. Remove Word" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addOrUpdateWord(dictionary);
                break;
            case 2:
                searchWord(dictionary);
                break;
            case 3:
                removeWord(dictionary);
                break;
            case 4:
                cout << "Exiting the dictionary tool." << endl;
                return 0;
            default:
                cout << "Invalid choice. Please select 1, 2, 3, or 4." << endl;
        }
    }

    return 0;
}
