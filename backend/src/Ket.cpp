#include "Ket.hpp"

#include <iostream>

Ket::Ket() {}

Ket::Ket(std::string ketstring) : content(ketstring) {}

void Ket::echo()
{
	if (parts.size())
		std::cout << " { ";
	for (int i = 0; i < parts.size(); i++)
	{
		for (int j = 0; j < parts[i].size(); j++)
		{
			parts[i][j].echo();
		}
		std::cout << " + ";
	}
		
	if (parts.size())
		std::cout << " } ";
	if (!parts.size())
		std::cout << content << " ";
	
}

void restruct()
{
	
}

int Ket::read(std::string ketstring)
{
	std::cout << "ghm?\n";
	//return 0;
	
	using namespace std;
	int originallen = ketstring.length();
	parts.push_back(vector<Ket>());

	while (ketstring != "")
	{
		cerr << ketstring << "\n";
		if (ketstring[0] == '(')
		{
			ketstring.erase(0, 1);
			Ket neuket;
			int n = neuket.read(ketstring);
			ketstring.erase(0, n);
			parts[parts.size()-1].push_back(neuket);
		}
		else if (ketstring[0] == ')')
		{
			ketstring.erase(0, 1);
			return originallen - ketstring.length();
		}	
		else if (ketstring[0] == '|')
		{
			ketstring.erase(0, 1);
			int ketlen = ketstring.find('>');
			string newstr = ketstring.substr(0, ketlen);
			ketstring.erase(0, ketlen+1);
			Ket neuket(newstr);
			parts[parts.size()-1].push_back(neuket);
		}
		else if (ketstring[0] == '+')
		{
			parts.push_back(vector<Ket>());
			/*ketstring.erase(0, 1);
			Ket neuket(true);
			parts.push_back(neuket);*/
		}
		else if (ketstring[0] == ' ' || ketstring[0] == '\t' || ketstring[0] == '\n' || ketstring[0] == '\r')
		{
			ketstring.erase(0, 1);
		}
		else
		{
			cerr << "halp: " << ketstring;
			return 0;
		}
	}
	return 0;
}