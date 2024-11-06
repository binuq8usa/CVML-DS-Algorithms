/*

Given a string s, return all the palindromic permutations (without duplicates) of it.

You may return the answer in any order. If s has no palindromic permutation, return an empty list.

s = "aabb". => ab - 2,2 -> create a palindrome from this set -> 
"abba",  "baab"

s = "aabbc"

"abcba"
"bacab"

checkIf ()

s  = "abc"

s = ""


checkForPalidome
    -> create map<int, count> 
    -> if len is odd -> count %2 == 0 => 
    -> if len is odd -> only entity can have count %2 == 1 => pivot index
    
    pivot_char ="" if even or "c" odd
    <palindrome possible, pivot_char>         
    
    
left substring, rightsubstring 

left Substring, right substring - keys of the map -> counts reduced by 2. 


*/

#include <ios>
#include <iostream>
#include <iterator>
#include <map>
#include <utility>
#include <tuple>
#include <vector>
#include <set>

using namespace std;

typedef map<char,int> Counter;
typedef string::iterator CharIt;
typedef string::reverse_iterator RCharIt;

tuple<bool, Counter> checkPalindrome(const string& inputStr) {
    // build a map
    Counter counts;
    for(auto& ch : inputStr) {
        if (counts.find(ch) == counts.end()) {
            counts.insert(make_pair(ch,1));
        } else counts[ch]++;
    }
    
    char pivotChar = ' ';
    bool flag = true;
    for(auto& entry : counts) {
        if (entry.second % 2 != 0) {
            if (pivotChar == ' ' && inputStr.length() % 2 != 0) pivotChar = entry.first;
            else {
                flag = false;
                break;
            }
        }
    }
    return make_tuple(flag, counts);
}

void printMap(const Counter& counts) {
    for(auto& [key,val] : counts) {
        std::cout << key << ":" << val << std::endl;
    }
}

void dfsBacktrack(Counter& counts, set<string>& palindromes, CharIt leftIt, RCharIt rightIt, string& permStr) {
    
    if (leftIt > rightIt.base()-1) {
        palindromes.insert(permStr);
        return;
    }
    
    for(auto& entry : counts) {
        if (entry.second >= 2) {
            *leftIt = entry.first;
            *rightIt = entry.first;
            entry.second -= 2; // two counts have been removed
            dfsBacktrack(counts, palindromes, leftIt+1, rightIt+1, permStr);
            entry.second += 2;
        } else if ( leftIt == rightIt.base()-1 && entry.second == 1) { // if count == 1 and leftIt == rightIt
            *(leftIt) = entry.first;
            dfsBacktrack(counts, palindromes, leftIt+1, rightIt+1, permStr);
            return;
        }
    }
}

vector<string> getPalindromes(const string& inputStr) {
    auto [flag, counts] = checkPalindrome(inputStr);
    if (!flag) return vector<string>();
    
    set<string> palindromes;
    std::string tempInputStr = inputStr;
    dfsBacktrack(counts, palindromes, tempInputStr.begin(), tempInputStr.rbegin(), tempInputStr);
    
    return vector<string>(palindromes.begin(), palindromes.end());
}

/*
Once its palidrome, we do a graph
        set - a:2, b:2, c:1
            
            a b c b a -> 
            b a c a b            
    
*/


int main(int argc, char** argv) {
    string inputStr = "aabbc";
    std::cout << " Is Palindrone  : " << get<0>(checkPalindrome(inputStr)) << std::endl;   
    vector<string> palindromes = getPalindromes(inputStr);
    std::cout << "Set of palindromess : " << std::endl;
    for(auto& str : palindromes) {
        std::cout << str << std::endl;
    } 
}