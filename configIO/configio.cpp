#include "stdafx.h"
#include "configio.h"
#include <cstdio>
#include <cstdlib>
#include <string>


ConfigIO::ConfigIO():
m_cAnnotateSymbol(def_annotate_symbol),
m_cSplitSybol(def_split_symbol),
m_nItemCount(0)
{

}

ConfigIO::~ConfigIO()
{
	Release();
}

bool ConfigIO::Init(const string &strFileName, char anChar, char spChar)
{
	bool bRet = false;
	char temp[1024];
	size_t found;
	string key;
	string val;
	FILE *pFile = NULL;

	m_strFileName = strFileName;
	m_cAnnotateSymbol = anChar;
	m_cSplitSybol = spChar;

	if(NULL == fopen_s(&pFile, m_strFileName.c_str(), "r"))
	{
		while(NULL != fgets(temp, 1024, pFile))
		{
			string strTemp(temp);
			if(strTemp.size() == 0)
				continue;
			found = strTemp.find(m_cAnnotateSymbol);
			if(found != string::npos)
			{
				strTemp.resize(found);
			}
			if(strTemp.empty())
				continue;
			found = strTemp.find(m_cSplitSybol);
			if (found != string::npos)
			{
				key = strTemp.substr(0, found); TrimSpace(key);
				val = strTemp.substr(found+sizeof(m_cSplitSybol)); TrimSpace(val);
				m_Map.insert(pair<string,string>(key,val));
			}
		}
		fclose(pFile);
		bRet = true;
	}
	return bRet;
}
void ConfigIO::Release()
{
	m_Map.clear();
}
bool ConfigIO::IsNameExist(string str)
{
	bool bRet = false;
	return bRet;
}
int ConfigIO::GetItemNum()
{
	int nCount = -1;
	if(!m_Map.empty())
	{
		nCount = m_Map.size();
	}
	return nCount;
}
string ConfigIO::GetItemValue(string str)
{
	string item("");
	StrMapIter ite = m_Map.find(str);
	if(ite != m_Map.end())
	{
		item = ite->second;
	}
	return item;
}

void ConfigIO::EraseItem(string str)
{
}
void ConfigIO::SetItemValue(string str, string info)
{
	StrMapIter ite = m_Map.find(str);
	if(ite != m_Map.end())
	{
		ite->second = info;
	}
}
bool ConfigIO::Save()
{
	bool bRet = false;
	FILE *pFile = NULL;
	if(NULL == fopen_s(&pFile, m_strFileName.c_str(), "w"))
	{
		StrMapIter ite;
		for(ite=m_Map.begin(); ite!=m_Map.end(); ite++)
		{
			fprintf(pFile, "%s", ite->first.c_str());
			fprintf(pFile, "%c", m_cSplitSybol);
			fprintf(pFile, "%s", ite->second.c_str());
			fprintf(pFile, "\r\n");
		}
		fclose(pFile);
	}
	return bRet;
}

void ConfigIO::TrimSpace(string &str)
{
	if(str.empty())
		return;
	size_t count = str.size();
	size_t found = str.find_first_not_of(" \r\n");
	size_t start = (found==string::npos)?0:found;
	found = str.find_last_not_of(" \r\n");
	size_t end = (found==string::npos)?count-1:found;
	
	str.assign(str, start, end-start+1);
}