#include "Ket.hpp"

#include <iostream>
#include <algorithm>

#include "Particle.hpp"

typedef unsigned int uint;

Ket::Ket() {}

Ket::Ket(std::string ketstring) : content(ketstring) {}



std::vector<CompoundParticle *> *Ket::createCompounds(std::string ketstring)
{
	if (ketstring != "")
	{
		if (read(ketstring) == -1)
			return 0;
		distribute();
	}
	
	std::vector<CompoundParticle *> *vec = new std::vector<CompoundParticle *>();
	for (uint i = 0; i < parts.size(); i++)
	{
		std::vector<Flavour::aFlavour> flavs;
		std::vector<Spin::aSpin> spins;
		std::vector<Colour::aColour> cols;
		for (uint j = 0; j < parts[i].size(); j++)
		{
			for (uint s = 0; s < parts[i][j].content.size(); s++)
			{
				//std::cout << parts[i][j].content[s];
				
				//std::pair<QuantumNumber::aQuantumNumber,QuantumNumber::uQuantumNumber>
				auto blub = QuantumNumber::GetFromChar(parts[i][j].content[s]);
				switch(blub.first)
				{
					case QuantumNumber::Flavour:
						flavs.push_back(blub.second.Flavour);				break;
					case QuantumNumber::Spin:
						spins.push_back(blub.second.Spin);					break;
					case QuantumNumber::Colour:
						cols.push_back(blub.second.Colour);					break;
					case QuantumNumber::Error:
					default:
						std::cerr << "MÖÖÖÖÖP MÖÖÖÖÖP MÖÖÖÖP";
				}
			}
		}
		uint n = std::max(flavs.size(),std::max(spins.size(),cols.size()));
		while (flavs.size() < n)
			flavs.push_back(Flavour::Up);
		while (spins.size() < n)
			spins.push_back(Spin::NoSpin);
		while (cols.size() < n)
			cols.push_back(Colour::NoColour);
		
		CompoundParticle *cp = new CompoundParticle(n);
		for (uint k = 0; k < n; k++)
		{
			Particle *p = new Particle(flavs[k], spins[k], cols[k], Handedness::NoHandedness);
			cp->SetConstituent(k, *p);
		}
		vec->push_back(cp);
		
		//std::cout << "\n";
	}
	return vec;
}

void Ket::echo()
{
	if (parts.size())
		std::cout << " { ";
	for (uint i = 0; i < parts.size(); i++)
	{
		if (i > 0)
			std::cout << " + ";
		for (uint j = 0; j < parts[i].size(); j++)
		{
			parts[i][j].echo();
		}
	}
		
	if (parts.size())
		std::cout << " } ";
	if (!parts.size())
		std::cout << content << " ";
	
}

void Ket::distribute()
{
	using namespace std;
	
	//cerr << "k";
	
	for (uint i = 0; i < parts.size(); i++)
		for (uint j = 0; j < parts[i].size(); j++)
		{
			//cerr << "1: " <<  i << " " << j << "\n";
			parts[i][j].distribute();
			
			
			
			if (parts[i][j].parts.size() && parts[i][j].parts[0].size()) // ggf noch mal spezifiziern
			{
				for (uint n = 0; n < parts[i][j].parts.size(); n++)
				{
					parts.push_back(vector<Ket>());
					
					for (uint k = 0; k < j; k++)
						parts[parts.size()-1].push_back(parts[i][k]);
					
					for (uint m = 0; m < parts[i][j].parts[n].size(); m++)
						parts[parts.size()-1].push_back(parts[i][j].parts[n][m]);
					
					for (uint k = j+1; k < parts[i].size(); k++)
						parts[parts.size()-1].push_back(parts[i][k]);
				}
				parts.erase(parts.begin()+i);
				i--;
				break;
			}
		}
	

}

int Ket::read(std::string ketstring)
{
	//std::cout << "ghm?\n";
	//return 0;
	
 	using namespace std;
	int originallen = ketstring.length();
	parts.clear();
	parts.push_back(vector<Ket>());

	while (ketstring != "")
	{
		//cerr << ketstring << "\n";
		if (ketstring[0] == '(')
		{
			ketstring.erase(0, 1);
			Ket neuket;
			int n = neuket.read(ketstring);
			if (!n)
			{
				parts.clear();
				cout  << "Unmatched parantheses..." << "\n";
				return -1;
			}
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
			ketstring.erase(0, 1);
			/*Ket neuket(true);
			parts.push_back(neuket);*/
		}
		else if (ketstring[0] == '-')
		{
			parts.push_back(vector<Ket>());
			ketstring.erase(0, 1);
		}
		else if (ketstring[0] == ' ' || ketstring[0] == '\t' || ketstring[0] == '\n' || ketstring[0] == '\r')
		{
			ketstring.erase(0, 1);
		}
		else
		{
			cout << "Error parsing parameters.";// << ketstring;
			return 0;
		}
	}
	return 0;
}