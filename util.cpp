#include "util.h"

/*removes all white space from a string*/
string& deep_trim(string& target) {
	if(target.empty()) {
		return target;
	} else {
		size_t space_check = target.find_first_of(' ');
		
		if(space_check == string::npos) {
			return target;
		} else {
			for(string::const_iterator it = target.cbegin(); it != target.cend(); ++it) {
				if(*it == ' ') {
					string::const_iterator tmp_it = it;
					target.erase(tmp_it);
					it = target.begin();
				}
			}
		}
		return target;
	}
}
/* replaces  the characters in @param target in positions given by
   @param start and @param end for use with find_paren_exper*/
void flag(string& target, size_t start, size_t end) {
	target[start] = '!';
	target[end] = '~';
}
/*a function to unflag expressions in @param target so that they may be referenced during evaluation*/
string& restore_exper(string& target) {
	for(int i = 0; i < target.length(); ++i) {
		if(target[i] == '!') {
			target[i] = '(';
		} else if(target[i] == '~') {
			target[i] = ')';
		}
	}
	return target;
}
/* a function that finds parenthetical expressions in @param target and stores them in
   @param expers so that they can be evaluated*/
vector<string> find_paren_exper(string& target, vector<string>& expers) {
	if(target.empty()) {
		return expers;
	} else {
		size_t open_index = target.find_last_of("(");
		size_t close_index = target.find_first_of(")", open_index);
		
		if(open_index != string::npos && close_index != string::npos) {
			string temp = target.substr(open_index + 1, close_index - (open_index + 1));
			expers.insert(expers.cbegin(), restore_exper(temp)); //restore_exper is called in case additional passes were required. 
			flag(target, open_index, close_index); 
			find_paren_exper(target, expers);
		}
		return expers;
	}
}
/*function for removing operators after numbers are parsed from experssions*/
vector<string>& remove_operators(vector<string>& target) {
	for(auto it = target.begin(); it != target.end(); ++it) {
		if(*it == "(" ||
		   *it == ")" ||
		   *it == "^" ||
		   *it == "*" ||
		   *it == "/" ||
		   *it == "+" ||
		   *it == "-" ||
		   *it == " " ){
			   auto tmp = it;
			   target.erase(tmp);
			   it = target.begin();
		   }
	}
	return target;
}

vector<string> split (const string& line, const string& delimiters) {
   vector<string> words;
   int end = 0;
   for (;;) {
      size_t start = line.find_first_not_of (delimiters, end);
      if (start == string::npos) break;
      end = line.find_first_of (delimiters, start);
      words.push_back (line.substr (start, end - start));
   }
   return words;
}
/*function for breaking the expression string into strings of operands*/
vector<string>& parse_for_operands(string& target, vector<string>& result) {
	const string EXPER = target;
	const string DELIMS = "()^*/ ";
	
    result = split(EXPER, DELIMS);
	result = remove_operators(result);
	return result;
	
}
