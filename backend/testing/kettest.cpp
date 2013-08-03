#include "../inc/Ket.hpp"
#include <iostream>

int main()
{
	using namespace std;
	Ket k;
	k.read("|test>(|hi>+|b>)|c>+|k>");
	k.echo();
	k.read("");
	k.echo();
	cout << "\n";
}