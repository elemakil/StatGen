#include "../inc/Ket.hpp"
#include <iostream>

int main()
{
	using namespace std;
	Ket k;
	k.read("|test>(|hi>+|b>)|c>+|k>");
	k.echo();
	cout << "\n";
}