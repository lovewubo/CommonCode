#pragma once

#include <iostream>
#include <map>
#include <algorithm>
using namespace std;

#define def_annotate_symbol '#'
#define def_split_symbol ':'

typedef map<string,string> StrMap;
typedef map<string,string>::iterator StrMapIter;
class ConfigIO
{
public:
	ConfigIO();
	~ConfigIO();
	
	bool Init(const string &strFileName, char anChar = def_annotate_symbol, char spChar = def_split_symbol);
	void Release();
	bool IsNameExist(string str);
	int GetItemNum();
	string GetItemValue(string str);
	void EraseItem(string str);
	void SetItemValue(string str, string info);
	bool Save();
private:
	string m_strFileName;
	char m_cAnnotateSymbol;
	char m_cSplitSybol;
	int m_nItemCount;
	StrMap m_Map;
	
	void TrimSpace(string &str);
};