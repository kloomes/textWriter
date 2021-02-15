#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <string>
#include <stdlib.h>

std::ifstream in;
std::ofstream out;

std::map<std::string, std::vector<char>> probabilities;
std::string outputText;

std::string parseText(std::string file) {
  in.open(file);
  std::string line;
  std::string allText;
  while (std::getline(in, line)) {
    allText += line;
  }
  return allText;
}

void probGen(int key, std::string file) {
  std::string allText = parseText(file);
  for (int i = 0; i <= allText.size(); i++) {
    std::string word;
    for (int j = 0; j < key; j++) {
      word += allText[i + j];
    }
    if (probabilities.count(word) <= 0) {
      probabilities[word] = {allText[i + key]};
    } else {
      probabilities[word].push_back(allText[i + key]);
    }
  }
}

char nextCharacter(std::string key) {
  if (probabilities.count(key) <= 0) return '\0';
  int indexNum = rand() % probabilities[key].size();
  return probabilities[key][indexNum];
}

void genOutput(int size, std::string key) {
  if (size == 0) return;
  char next = nextCharacter(key);
  outputText += next;
  std::string temp = key + next;
  genOutput(size - 1, temp.substr(1));
}

void printToFile(std::string outFile, std::string key) {
  out.open(outFile);
  out << key;
  for (int i = 0; i < outputText.size(); i++) {
    out << outputText[i];
  }
}

int main() {
  std::string inputFile;
  std::string outputFile;

  int keySize;
  int outputSize;
  std::string initialKey;
  std::cout << "Initial key? ";
  std::getline(std::cin, initialKey);
  std::cout << "Input file? ";
  std::cin >> inputFile;
  std::cout << "Output file? ";
  std::cin >> outputFile;
  std::cout << "Key size? ";
  std::cin >> keySize;
  std::cout << "Output size? ";
  std::cin >> outputSize;
  probGen(keySize, inputFile);
  genOutput(outputSize, initialKey);
  printToFile(outputFile, initialKey);
}
