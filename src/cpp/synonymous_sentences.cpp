/*

You are given a list of equivalent string pairs synonyms where synonyms[i] = [si, ti] indicates that si and ti are equivalent strings. You are also given a sentence text.

Return all possible synonymous sentences sorted lexicographically.

synonyms[i] = [si,ti] -> equivalent strings

synonyms = ['happy','joy'], ['sad','morose'], ['joy','cheerful']

Step 1:
synonymuys = graph - 
    Nodes -> set of words.
    edges -> set of edges. -> node -> list of edges (order them in opposite of lexigraphical order) ['joy', 'cheerful']

Step 2: 
iterate through each word ;
  Each word is a part of the nodes in the graph
    list_of_texts = [

  if q_word in graph and word not visited:
      dfsSearch(text, q_word, list_of_texts)

  replace the q_word.
  add to tlist_of_texts


dfsSearch(text, q_word):
  neighbhor 

output = [
  "you are a joy boy but Jack is a sad boy
  you are a happy boy ..... jack is a morose boy"
]

senteces are sorted lexicographically? 

Approach:
1. set of words = ()

1. word_1 -> replace, word_2 -> replace. => i am cheerful, i am j

1. order the nodes ->

2. got through the 

2. text - > vector of words
3. Get the list of query words in text.
4. find the connected comps of the graph

5. find the query word list, and their indices
6. different permutations and combinations
7. q_word1, b_word1 => (q_word1, b_word_2)


8. iterate through word in text
  get first query word, 
        -> getnerate lists of text for each n_word
9. get the word from text -> put it in seen, 



1. get the word in the text, 
  -> bfs -> 

  -> queue<word,text>  

*/

#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <map>
#include <list>
#include <sstream>
#include <queue>

using namespace std;

typedef pair<string, string> SynonymPair;
typedef map<string, list<string>> WordMapping; 

pair<set<string>, WordMapping> build_graph(const vector<SynonymPair>& synonyms) {
  std::set<string> words; // nodes
  WordMapping wordMapping;

  for(auto &pp : synonyms) {
    words.insert(pp.first);
    words.insert(pp.second);

    if (wordMapping.find(pp.first) == wordMapping.end()) wordMapping[pp.first] = list<string>();
    if (wordMapping.find(pp.second) == wordMapping.end()) wordMapping[pp.second] = list<string>();
    wordMapping[pp.first].push_back(pp.second);
    wordMapping[pp.second].push_back(pp.first);
  }
  return make_pair(words, wordMapping);
}

vector<string> splitText(string text) {
  stringstream ss(text);
  string word;
  vector<string> words;
  while (ss >> word) {
    words.push_back(word);
  }
  return words;
}

string joinText(vector<string> words) {
  string outStr ; 
  for(auto& word : words) {
    outStr += word;
    outStr += " ";
  }
  if (!outStr.empty()) outStr.pop_back();
  return outStr;
}

vector<string> bfs(const set<string>& synonymWords, WordMapping& wordMapping, string text) {
  // set the queue
  queue<string> qu; // each node is a sentence with children as the synonyms. Value if the text, nodes to iterate are the synonyms
  qu.push(text);
  set<string> textLists; // this puts the text and when iterating, puts it in sorted order based on ascending.
  textLists.insert(text);

  while (!qu.empty()) {
    string currText = qu.front();
    qu.pop();

    //iterate throught the split words
    // check if the word is a child node (if its a synonym word)
    // if it is, iterate throuhg the list of neighor nodes of that child
    // replace to replace

    vector<string> qWords = splitText(currText);
    vector<pair<string,int>> wordChildren;
    // find children and position
    for(auto it = qWords.begin(); it!= qWords.end(); it++) {
      // is it part of the synonmy words
      if (synonymWords.find(*it) != synonymWords.end()) {
        size_t pos = (int)(it - qWords.begin());
        wordChildren.push_back(make_pair(*it,pos));
      }
    }

    // bfs
    for(auto& pp : wordChildren) { //happy, strong
      // get the n words
      string currWord = pp.first; //happy, pos
      int pos = pp.second;
      for(auto& nWord : wordMapping[currWord]) {
        // replace the word
        qWords[pos] = nWord; // joy 
        string newText = joinText(qWords);
        if (textLists.find(newText) == textLists.end()) {
          // add to queue
          qu.push(newText);
          textLists.insert(newText);
        }
      }
      qWords[pos] = currWord;
    }
  }
  return vector<string>(textLists.begin(), textLists.end());
}

vector<string> generateSentences(const vector<SynonymPair>& synonyms, string text) {
  // create graph
  auto [words, wordMapping] = build_graph(synonyms);
  return bfs(words,wordMapping, text);
}


// To execute C++, please define "int main()"
int main() {
  vector<SynonymPair> synPairs{
    {"happy","cheerful"},
    {"sad", "sorrow"},
    {"cheerful", "joy"}
  };
  string text= "I am happy today but was sad yesterday";

  vector<string> result = generateSentences(synPairs, text);
  for(auto& tt : result) {
    std::cout << "Text : "<< tt << std::endl;
  }
  std::cout << "Num of texts generated : " << result.size() << std::endl;

}


// NOTE working for test casese
/*
synonyms =
[["a","b"],["b","c"],["d","e"],["c","d"]]

text = "a b"

*/