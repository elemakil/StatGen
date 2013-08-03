#include <string>
#include <vector>


class Ket
{
public:
	Ket();
	Ket(std::string ketstring);
	int read(std::string ketstring);
	void restruct();
	void echo();
	
	
private:
	std::vector<std::vector<Ket> > parts;
	std::string content;
};
