#include <vector>
#include <algorithm>
#include <string>
#include <iostream>
#include <cstring>

using namespace std;
class Function
{
public:
	static int Cuenta(string s, const char Separadorr, int TotalChars)
	{
		for (int i = 0; i < s.size(); i++)
		{
			if (s[i] == Separadorr)
				TotalChars++;
		}
		return TotalChars;
	}

	static vector<string> split(string str, string separator)
	{
		vector<string> v;
		size_t pos = 0;
		string k;
		while ((pos = str.find(separator)) != string::npos)
		{
			k = str.substr(0, pos);
			if (k == "")
			{
				return v;
			}
			v.push_back(k);
			str.erase(0, pos);
			size_t sizeString = str.size();
			str = str.substr(2, sizeString) + str.substr(0, separator.length());
		}
	}

	static int Contar(string Cadena, char Caracter)
	{
		int NumChars = 0;
		for (int IncNums = 0; IncNums <= Cadena.size(); IncNums++)
		{
			if (Cadena[IncNums] == Caracter)
			{
				NumChars++;
			}
		}
		return NumChars;
	}

	static void Multi(string Texto, int TotalRep)
	{
		string Texto2 = Texto;
		for (int SumaNums = 1; SumaNums < TotalRep; SumaNums++)
		{
			Texto += Texto2;
		}
	}

	static string UpperString(string str)
	{
		string result = "";
		for (int i = 0; i < str.size(); i++)
		{
			result += toupper(str[i]);
		}
		return result;
		//result.delete();
	}

	static string replaceAll(string str, const string from, const string to)
	{
		if (from.empty())
			return "";
		size_t start_pos = 0;
		while ((start_pos = str.find(from, start_pos)) != string::npos)
		{
			str.replace(start_pos, from.length(), to);
			start_pos += to.length();
		}
		return str;
	}

	static string replace(string str, const string from, const string to)
	{
		string rpl = "";
		size_t start_pos = str.find(from);
		if (start_pos == string::npos)
		{
			return str;
		}
		else
		{
			rpl += str.replace(start_pos, from.length(), to);
			return rpl;
		}
	}

	static bool Isreplace(string str, const string from, const string to)
	{
		string rpl = "";
		size_t start_pos = str.find(from);
		if (start_pos == string::npos)
		{
			return false;
		}
		else
		{
			rpl += str.replace(start_pos, from.length(), to);
			return true;
		}
	}

	string Trim(const string str)
	{
		size_t first = str.find_first_not_of(' ');
		if (string::npos == first)
		{
			return str;
		}
		size_t last = str.find_last_not_of(' ');
		return str.substr(first, (last - first + 1));
	}

	string TrimS(const string str, const string chmodf)
	{
		size_t first = str.find_first_not_of(chmodf);
		if (string::npos == first)
		{
			return str;
		}
		size_t last = str.find_last_not_of(chmodf);
		return str.substr(first, (last - first + 1));
	}

	string RTrim(const string str, const string chmodf)
	{
		size_t last = str.find_last_not_of(chmodf);
		if (string::npos == last)
		{
			return str;
		}
		return str.substr(0, (last + 1));
	}

	string LTrim(const string str, const string chmodf)
	{
		size_t first = str.find_first_not_of(chmodf);
		if (string::npos == first)
		{
			return str;
		}
		return str.substr(first, (str.size() - 1));
	}

	static string Encrypt(string pCh)
	{
		char encrsy[1024], auxChar[1024];
		string str = "";
		strncpy(encrsy, pCh.c_str(), sizeof(encrsy));
		int ch = pCh.size();
		for (int i = 0; i != ch; i++)
		{
			encrsy[i] = encrsy[i] - (6 + i) * 27;
			if (encrsy[i] == 26)
			{
				encrsy[i] = 72;
				ch = ch + 1;
				for (int j = i + 1; j != ch; j++)
				{
					auxChar[j] = encrsy[j];
				}
				encrsy[i + 1] = 27;
				for (int j = i + 2; j != ch; j++)
				{
					encrsy[j] = auxChar[j - 1];
				}
				str += encrsy[i];
				str += encrsy[i + 1];
				i = i + 1;
			}
			else
			{
				str += encrsy[i];
			}
		}
		return str;
	}

	static string Descrypt(string pCh)
	{
		char encrsy[1024];
		string str = "";
		int ch = pCh.size();
		strncpy(encrsy, pCh.c_str(), sizeof(encrsy));
		for (int i = 0; i != ch; i++)
		{
			if (encrsy[i] == 72)
			{
				if (encrsy[i + 1] == 27)
				{
					encrsy[i] = 26;
					encrsy[i] = encrsy[i] + (6 + i) * 27;
					str += encrsy[i];
					ch = ch - 1;
					i = i + 1;
				}
				else
				{
					encrsy[i] = encrsy[i] + (6 + i) * 27;
					str += encrsy[i];
				}
			}
			else
			{
				encrsy[i] = encrsy[i] + (6 + i) * 27;
				str += encrsy[i];
			}
		}
		return str;
	}

	bool isNumber(const char *cadena)
	{
		for (; *cadena; ++cadena)
		{			
			if (!std::isdigit(*cadena))
				return false;
		}

		return true;
	}
};