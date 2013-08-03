#include "../inc/Ket.hpp"
#include <iostream>

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
}