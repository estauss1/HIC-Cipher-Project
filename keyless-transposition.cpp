#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using std::cout; using std::endl;
using std::string;

//input: a string to encrypt using keyless transposition cipher and an 
//integer for the row size of table used for encryption process
//output: string which is cyphertext from keyless transposition cipher
string encrypt(string name, const int rowSize);

//input: string which is cyphertext gotten from encrypt() and rowSize
//which matches row size from encrypt
//output: string which is the original string before encryption
string decrypt(string ciphertext, const int rowSize);

int main(){
  std::srand(std::time(nullptr)); //used for random numbers ignore this

  //can change fullName to string you want to encrypt/decrypt
  string fullName = "Eric Stauss";
  //get # of chars([2 - 5]) per row for encrypt/decrypt
  const int rowChars = rand() % 4 + 2;
  
  //encryption
  string ciphertext = encrypt(fullName, rowChars);
  cout << "String to encrypt: \"" << fullName << "\"" << endl
       << "Ciphertext of \"" << fullName << "\" using " << rowChars << " table row size: \""
       << ciphertext << "\"" << endl;
  
  //decryption
  cout << "Decrypting ciphertext now..." << endl;
  string originalFullName = decrypt(ciphertext, rowChars);
  cout << "The original string from ciphertext \"" << ciphertext << "\" is \"" 
       << originalFullName << "\"" << endl;
  
  return 0;
}

string encrypt(string name, const int rowSize){ 
  //determine # of rows
  int numOfRows = name.size() / rowSize;
  if(name.size() % rowSize != 0) ++numOfRows;
  //create matrix/table for chars
  char table[numOfRows][rowSize];
  //fill table row by row with chars from name
  auto nameItr = name.begin();
  for(int i = 0; i < numOfRows; ++i){
    for(int j = 0; j < rowSize; ++j){
      if(nameItr != name.end()){ 
        table[i][j] = *nameItr;
        ++nameItr;
      }
      else {
        table[i][j] = '\0';
      }
    }
  }
  //create the ciphertext
  string ciphertext = "";
  //take chars out column by column and add to ciphertext string
  for(int j = 0; j < rowSize; ++j){
    for(int i = 0; i < numOfRows; ++i){
      if(table[i][j] != '\0')
        ciphertext.append(1, table[i][j]);
    }
  }
  return ciphertext;
}

string decrypt(string ciphertext, const int rowSize){
  //determine # of rows and chars in last row 
  int numOfRows = ciphertext.size() / rowSize;
  int charsLastRow = ciphertext.size() % rowSize;
  if(charsLastRow != 0) 
    ++numOfRows;
  else
    charsLastRow = rowSize;
  //create table
  char table[numOfRows][rowSize];
  //put chars in column by column making sure last row is 
  //only row possibly not filled with chars
  auto cipherItr = ciphertext.begin();
  int charsAddedLastRow = 0;
  for(int j = 0; j < rowSize; ++j){
    for(int i = 0; i < numOfRows; ++i){
      if(i == numOfRows - 1){
        if(charsAddedLastRow < charsLastRow){
          table[i][j] = *cipherItr;
          ++cipherItr;
          ++charsAddedLastRow;
        }
        else{
          table[i][j] = '\0';
        }
      } 
      else {
        table[i][j] = *cipherItr;
        ++cipherItr;
      }
    }
  }
  //take chars out of table row by row
  string originalText = "";
  for(int i = 0; i < numOfRows; ++i){
    for(int j = 0; j < rowSize; ++j){
      if(table[i][j] != '\0')
        originalText.append(1, table[i][j]);
    }
  }
  return originalText;
}






