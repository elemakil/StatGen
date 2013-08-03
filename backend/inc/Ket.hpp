#include <string>
#include <vector>

class CompoundParticle;

class Ket
{
public:
	Ket();
	Ket(std::string ketstring);
	int read(std::string ketstring);
	void echo();
	void distribute();
	
	std::vector<CompoundParticle *> *createCompounds(std::string ketstring = "");

	std::vector<std::vector<Ket> > parts;
	std::string content;
private:
	
};
