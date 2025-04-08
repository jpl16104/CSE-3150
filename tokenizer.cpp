#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <unordered_map>
#include <vector>

class Tokenizer {
private:
    // Mapping from word to token (unique integer)
    std::unordered_map<std::string, int> wordToToken;
    // Mapping from token to word
    std::vector<std::string> tokenToWord;
    // Regex to match words: one or more alphanumeric characters bound by word boundaries
    std::regex wordRegex;

public:
    // Constructor initializes the regular expression
    Tokenizer() : wordRegex("\\b\\w+\\b") {}

    // Reads text from a file and tokenizes the words
    void tokenizeFile(const std::string &filename) {
        std::ifstream infile(filename);
        if (!infile) {
            std::cerr << "Error opening file: " << filename << std::endl;
            return;
        }

        // Read the whole file content into a string
        std::string text((std::istreambuf_iterator<char>(infile)), std::istreambuf_iterator<char>());

        // Use regex iterator to find all words
        std::sregex_iterator begin(text.begin(), text.end(), wordRegex);
        std::sregex_iterator end;
        for (auto it = begin; it != end; ++it) {
            std::string word = it->str();
            // Optionally, to handle case-insensitivity, convert the word to lowercase here.
            addWord(word);
        }
    }

    // Adds a word to the dictionary if not present. Returns its token.
    int addWord(const std::string &word) {
        // Check if the word exists; if not, assign the next token
        if (wordToToken.find(word) == wordToToken.end()) {
            int token = tokenToWord.size();
            tokenToWord.push_back(word);
            wordToToken[word] = token;
            return token;
        }
        return wordToToken[word];
    }

    // Returns the token for a given word, or -1 if not found.
    int getToken(const std::string &word) const {
        auto it = wordToToken.find(word);
        if (it != wordToToken.end()) {
            return it->second;
        }
        return -1; // Not found
    }

    // Returns the word associated with a given token, or an empty string if invalid.
    std::string getWord(int token) const {
        if (token < 0 || token >= static_cast<int>(tokenToWord.size())) {
            return "";
        }
        return tokenToWord[token];
    }

    // Outputs the mapping of tokens to words
    void outputTokens() const {
        std::cout << "Token mapping:" << std::endl;
        for (int i = 0; i < static_cast<int>(tokenToWord.size()); i++) {
            std::cout << i << " => " << tokenToWord[i] << std::endl;
        }
    }
};

int main() {
    Tokenizer tokenizer;
    std::string filename = "input.txt";  // Replace with your actual file path

    // Tokenize the file content
    tokenizer.tokenizeFile(filename);
    // Output the mapping between tokens and words
    tokenizer.outputTokens();

    // Example: get token for a specific word
    std::string queryWord = "example";
    int token = tokenizer.getToken(queryWord);
    if (token != -1)
        std::cout << "Token for word '" << queryWord << "': " << token << std::endl;
    else
        std::cout << "Word '" << queryWord << "' not found." << std::endl;

    // Example: get word from a token
    int queryToken = 2;
    std::string word = tokenizer.getWord(queryToken);
    if (!word.empty())
        std::cout << "Word for token " << queryToken << ": " << word << std::endl;
    else
        std::cout << "Invalid token: " << queryToken << std::endl;

    return 0;
}
