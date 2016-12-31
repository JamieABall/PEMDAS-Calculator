#ifndef __UTIL_H__
#define __UTIL_H__

#include <iostream>
#include <sstream>
#include <string>
#include <memory>
#include <cstddef>
#include <vector>
#include <cstddef>
using namespace std;

string& deep_trim(string& target);
vector<string>& find_paren_exper(string& target, vector<string>& expers);
#endif
