#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"

using namespace std;
std::string convToLower(std::string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment **/
std::set<std::string> parseStringToWords(string rawWords)
{
    // IF STRING IS NUMBERS THIS DOESN"T WORK!
    set<string> myset; 
    stringstream ss(rawWords);
    string temp; 
    string a = "";
    while (ss >> temp){
        for (int i = 0; i < temp.length(); i++){
            if ((temp[i] >= 'A' && temp[i] <= 'Z')||(temp[i] >= 'a' && temp[i] <= 'z')){
                a += temp[i];
                if (i == temp.length()-1){
                    if (a.length() != 1){
                        myset.insert(a); 
                    }
                    a = ""; 
                }
            }else{
                if (a.length() != 1){
                    myset.insert(a); 
                }
                a = ""; 
            }
        }
    }
    return myset; 
}

/**************************************************
 * COMPLETED - You may use the following functions
 **************************************************/

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s) {
    s.erase(s.begin(), 
	    std::find_if(s.begin(), 
			 s.end(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &rtrim(std::string &s) {
    s.erase(
	    std::find_if(s.rbegin(), 
			 s.rend(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))).base(), 
	    s.end());
    return s;
}

// trim from both ends
std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}
