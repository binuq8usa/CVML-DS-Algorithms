/*
Messages can be made up of floats, ints, strings.
Assume strings are 256 bytes, ints 4 bytes, and floats 4 bytes.

Example Input:

// Begin Input
Message Vehicle
float x_position
float y_position
float velocity
float acceleration
int num_wheels
string name

Message Vector2d
float x_position
float y_position
Message SomethingNew
...
// End Input

Please write a parser that parses the input value into a data structure that supports the following queries:

Given a message type name, output its size in bytes.
Given a message type name and message field, output the type as a string

Expected Outputs:

parser.get_size("Vehicle") -> 276
parser.get_size("Vector2d") -> 8
parser.get_size("float") -> 4
parser.get_type("Vehicle", "x_position") -> "float"
parser.get_type("Vehicle", "name") -> "string"


*/

/*
Parser class

  - StructureMap Map<Message string, list<pair<string , enumvalue>> : (field_name, basic_data_type) 
  - Map<Message string, byte size> 

  read_multiline_text_file()

  Reads header - Message, field_type = Vehicle
  -> Create a Key - field type : values - pair of data type, field name

  -> Message 
        -> 

*/

#include <iostream>
#include <iterator>
#include <map>
#include <list>
#include <sstream>
#include <utility>
#include <fstream>
#include <cassert>
using namespace std;

enum class BasicDataType{
  FLOAT,
  INT,
  STRING,
  NONE
};

#define FLOAT_BYTES 4
#define INT_BYTES 4
#define STRING_BYTES 256

vector<string> splitStringToWords(std::string sentence) {
  std::stringstream stream(sentence);
  string word;
  vector<string> words;
  while (stream >> word) {
    words.push_back(word);
  }
  return words;
} 

const string basisDataTypeToString(BasicDataType datatype) {
  switch(datatype) {
    case BasicDataType::INT:
      return "int";
    case BasicDataType::STRING:
      return "string";
    case BasicDataType::FLOAT:
      return "float";
    default: 
      return "";
      break;
  }
}

const BasicDataType stringToBasicDataType(std::string datatype) {
  if (datatype == "string") return BasicDataType::STRING;
  if (datatype == "int") return BasicDataType::INT;
  if (datatype == "float") return BasicDataType::FLOAT;
  return BasicDataType::NONE;
}


typedef map<string, list<pair<string, BasicDataType>>> StructureMap; // Message string -> list (field_name, field_datatype)

class Parser{
  private: 
    StructureMap datatypes;
  public:
    /*
      Multi-line string
    */
    void readMultiLineString(const std::string& inputFileName);

    int getSize(string field_type);

    std::string getType(string message_name, string field_name);
};

void Parser::readMultiLineString(const std::string& inputFileName) {
  ifstream inFile(inputFileName, std::ifstream::in);
  if (inFile.is_open()) {
    std::string line;
    while(getline(inFile, line)) {
      // read the stringstream
      vector<string> entries = splitStringToWords(line);
      assert(entries.size() <= 2);

      if (entries[0] == "Message") {
        
      }


    }
    inFile.close();
  } else {
    std::cerr <<"Input file not found" << std::endl;
  }
}

int Parser::getSize(string field_type) {
  if (stringToBasicDataType(field_type) == BasicDataType::STRING) return STRING_BYTES;
  if (stringToBasicDataType(field_type) == BasicDataType::FLOAT) return FLOAT_BYTES;
  if (stringToBasicDataType(field_type) == BasicDataType::INT) return INT_BYTES;
  // search in the structure map
  auto it = datatypes.find(field_type);
  if (it == datatypes.end()) {
    return 0;
  }
  // iterate throuhg the list of itmes
  int datatypeSize = 0;
  for (auto& field : it->second) {
    datatypeSize += this->getSize(basisDataTypeToString(field.second)); // 
  }
  return datatypeSize;
}

std::string Parser::getType(string message_name, string field_name) {
  auto it = datatypes.find(message_name);
  if (it == datatypes.end()) return "";
  
  // search throuhg the list
  std::string value;
  auto pos = std::find_if(it->second.begin(), it->second.end(), [value](pair<string,string> const &p) {
    return p.first==value;
  });
  if (pos == it->second.end()) return "";
  else return basisDataTypeToString(pos->second);
}

// To execute C++, please define "int main()"
int main() {
  auto words = { "Hello, ", "World!", "\n" };
  for (const char* const& word : words) {
    cout << word;
  }
  return 0;
}
