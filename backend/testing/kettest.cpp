#include <iostream>

#include "Ket.hpp"
#include "Particle.hpp"

int main()
{
	using namespace std;
	Ket k;
	k.read("|a>+|b>(|c>+|d>)+(|e>+|f>)(|g>+|h>)+|i>(|j>+(|k>+(|l>+|m>)))");
	k.echo();
	k.distribute();
	k.echo();
	
	k.read("(|a>+|b>)(((|c>+|d>)(|e>+|f>))(|g>+|h>))");
	k.echo();
	k.distribute();
	k.echo();
	cout << "\n";
	
	
	vector<CompoundParticle *> *cpvec  = k.createCompounds("|uud>(|++->+|+-+>+|-++>)(|123>+|231>+|312>-|321>-|132>-|213>)");
	if (!cpvec)
		return -1;
	
	for (auto elem : *cpvec)
	{
		cout << "\n";
		elem->Print();
	}
	
	
	k.read("|uud>(|++->+|+-+>+|-++>");
	k.echo();
	k.distribute();
	k.echo();
	cout << "\n";
}