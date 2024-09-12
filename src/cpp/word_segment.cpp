/*

Given a string s and a dictionary of strings wordDict, return true if s can be segmented into a space-separated sequence of one or more dictionary words.

Note that the same word in the dictionary may be reused multiple times in the segmentation.

*/

/*

s = "leetcode"

word_dict = ("leet", "code")


return true if this can be segmented.


# brute force method
start with first index,
keep incrementing, untill you find the word. if found, great. 
reset the pointer, and check if next word is present

s = "appleenapple", word_dict= ("apple","pen")

dp[i] = Substring(i-word_length-1:i) in wordset and ( i == word_length-1 or dp[i-word_length) => true

*/


#include <iostream>
#include <string>
#include <set>
#include <unordered_map>
#include <vector>

using namespace std;

// bottom up approach
bool IsStringSegmentable(std::string queryString, set<string> wordSet) {
  vector<bool> stringSegmentFound(queryString.size(), false);
  for(int i = 0; i < queryString.size(); i++) {
    // iterate across words
    for(auto& word : wordSet) {
      if (i >= word.size() - 1 && (i == word.size() -1 || stringSegmentFound[i-word.size()]) ) {
        string queryWord = queryString.substr(i-word.size()+1, word.size());
        if (wordSet.find(queryWord) != wordSet.end()){
          stringSegmentFound[i] = true;
          break;
        }
      }
    }
  } 

  return stringSegmentFound[queryString.size()-1];
}

bool IsWordPresent(int sIndex, unordered_map<int,bool>& cache, const set<string>& wordSet, const string& queryString) {
  if (sIndex < 0) return true;

  // if present
  if (cache.find(sIndex) != cache.end()) return cache[sIndex];

  for(const auto& word : wordSet) {
    if (sIndex >= word.size()-1 && ( sIndex == word.size()-1 || IsWordPresent(sIndex-word.size(), cache, wordSet, queryString) ) ) {
      string queryWord = queryString.substr(sIndex-word.size()+1, word.size());
      if (wordSet.find(queryWord) != wordSet.end()) {
        cache.insert(make_pair(sIndex, true));
        break;
      }
    }
  }

  return cache[sIndex];
}

// top-down approach
bool IsStringSegmentableTD(std::string queryString, const set<string>& wordSet) {
  unordered_map<int, bool> cache;
  return IsWordPresent(queryString.size()-1, cache, wordSet, queryString);
}

// To execute C++, please define "int main()"
int main() {
  set<string> wordSet {"leet","code","d"};
  string queryString = "leetcoder";

  std::cout << "Is String Segmentatable : " << IsStringSegmentableTD(queryString, wordSet) << std::endl;
}
