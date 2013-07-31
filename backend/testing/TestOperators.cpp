#include <iostream>

#include "QuantumNumbers.hpp"
#include "Operators.hpp"
#include "Particle.hpp"

int main(){
    Flavour::aFlavour flv;
    
    flv = Flavour::Up;
    std::cout << "C |" << Flavour::Names[ flv ] << "> = ";
    SwitchFlavour( flv );
    std::cout << "|" << Flavour::Names[ flv ] << ">" << std::endl;
    
    flv = Flavour::Down;
    std::cout << "C |" << Flavour::Names[ flv ] << "> = ";
    SwitchFlavour( flv );
    std::cout << "|" << Flavour::Names[ flv ] << ">" << std::endl;
    
    flv = Flavour::Strange;
    std::cout << "C |" << Flavour::Names[ flv ] << "> = ";
    SwitchFlavour( flv );
    std::cout << "|" << Flavour::Names[ flv ] << ">" << std::endl;
    
    flv = Flavour::Charm;
    std::cout << "C |" << Flavour::Names[ flv ] << "> = ";
    SwitchFlavour( flv );
    std::cout << "|" << Flavour::Names[ flv ] << ">" << std::endl;
    
    flv = Flavour::Top;
    std::cout << "C |" << Flavour::Names[ flv ] << "> = ";
    SwitchFlavour( flv );
    std::cout << "|" << Flavour::Names[ flv ] << ">" << std::endl;
    
    flv = Flavour::Bottom;
    std::cout << "C |" << Flavour::Names[ flv ] << "> = ";
    SwitchFlavour( flv );
    std::cout << "|" << Flavour::Names[ flv ] << ">" << std::endl;
    
    flv = Flavour::AntiUp;
    std::cout << "C |" << Flavour::Names[ flv ] << "> = ";
    SwitchFlavour( flv );
    std::cout << "|" << Flavour::Names[ flv ] << ">" << std::endl;
    
    flv = Flavour::AntiDown;
    std::cout << "C |" << Flavour::Names[ flv ] << "> = ";
    SwitchFlavour( flv );
    std::cout << "|" << Flavour::Names[ flv ] << ">" << std::endl;
    
    flv = Flavour::AntiStrange;
    std::cout << "C |" << Flavour::Names[ flv ] << "> = ";
    SwitchFlavour( flv );
    std::cout << "|" << Flavour::Names[ flv ] << ">" << std::endl;
    
    flv = Flavour::AntiCharm;
    std::cout << "C |" << Flavour::Names[ flv ] << "> = ";
    SwitchFlavour( flv );
    std::cout << "|" << Flavour::Names[ flv ] << ">" << std::endl;
    
    flv = Flavour::AntiTop;
    std::cout << "C |" << Flavour::Names[ flv ] << "> = ";
    SwitchFlavour( flv );
    std::cout << "|" << Flavour::Names[ flv ] << ">" << std::endl;
    
    flv = Flavour::AntiBottom;
    std::cout << "C |" << Flavour::Names[ flv ] << "> = ";
    SwitchFlavour( flv );
    std::cout << "|" << Flavour::Names[ flv ] << ">" << std::endl;    

    std::cout << std::endl;
    
    Colour::aColour cl;
    
    cl = Colour::Red;
    std::cout << "C |" << Colour::Names[ cl ] << "> = ";
    SwitchColour( cl );
    std::cout << "|" << Colour::Names[ cl ] << ">" << std::endl;
    
    cl = Colour::Green;
    std::cout << "C |" << Colour::Names[ cl ] << "> = ";
    SwitchColour( cl );
    std::cout << "|" << Colour::Names[ cl ] << ">" << std::endl;
    
    cl = Colour::Blue;
    std::cout << "C |" << Colour::Names[ cl ] << "> = ";
    SwitchColour( cl );
    std::cout << "|" << Colour::Names[ cl ] << ">" << std::endl;
    
    cl = Colour::White;
    std::cout << "C |" << Colour::Names[ cl ] << "> = ";
    SwitchColour( cl );
    std::cout << "|" << Colour::Names[ cl ] << ">" << std::endl;
    
    cl = Colour::AntiRed;
    std::cout << "C |" << Colour::Names[ cl ] << "> = ";
    SwitchColour( cl );
    std::cout << "|" << Colour::Names[ cl ] << ">" << std::endl;
    
    cl = Colour::AntiGreen;
    std::cout << "C |" << Colour::Names[ cl ] << "> = ";
    SwitchColour( cl );
    std::cout << "|" << Colour::Names[ cl ] << ">" << std::endl;
    
    cl = Colour::AntiBlue;
    std::cout << "C |" << Colour::Names[ cl ] << "> = ";
    SwitchColour( cl );
    std::cout << "|" << Colour::Names[ cl ] << ">" << std::endl;
    
    cl = Colour::AntiWhite;
    std::cout << "C |" << Colour::Names[ cl ] << "> = ";
    SwitchColour( cl );
    std::cout << "|" << Colour::Names[ cl ] << ">" << std::endl;
    
    cl = Colour::NoColour;
    std::cout << "C |" << Colour::Names[ cl ] << "> = ";
    SwitchColour( cl );
    std::cout << "|" << Colour::Names[ cl ] << ">" << std::endl;
    
    std::cout << std::endl;
    
    Spin::aSpin sp;
    
    sp = Spin::Up;
    std::cout << "T |" << Spin::Names[ sp ] << "> = ";
    SwitchSpin( sp );
    std::cout << "|" << Spin::Names[ sp ] << ">" << std::endl;
    
    sp = Spin::Down;
    std::cout << "T |" << Spin::Names[ sp ] << "> = ";
    SwitchSpin( sp );
    std::cout << "|" << Spin::Names[ sp ] << ">" << std::endl;
    
    sp = Spin::NoSpin;
    std::cout << "T |" << Spin::Names[ sp ] << "> = ";
    SwitchSpin( sp );
    std::cout << "|" << Spin::Names[ sp ] << ">" << std::endl;
    
    std::cout << std::endl;
    
    Handedness::aHandedness hand;
    
    hand = Handedness::Left;
    std::cout << "P |" << Handedness::Names[ hand ] << "> = ";
    SwitchHandedness( hand );
    std::cout << "|" << Handedness::Names[ hand ] << ">" << std::endl;
    
    hand = Handedness::Right;
    std::cout << "P |" << Handedness::Names[ hand ] << "> = ";
    SwitchHandedness( hand );
    std::cout << "|" << Handedness::Names[ hand ] << ">" << std::endl;
    
    hand = Handedness::NoHandedness;
    std::cout << "P |" << Handedness::Names[ hand ] << "> = ";
    SwitchHandedness( hand );
    std::cout << "|" << Handedness::Names[ hand ] << ">" << std::endl;
    
    std::cout << std::endl;
    
    Particle part( Flavour::Up, Spin::Up, Colour::Red, Handedness::Left );
    
    part.Print();
    
    Operators::TransformC( & part );
    std::cout << "C: ";
    part.Print();
    
    Operators::TransformP( & part );
    std::cout << "P: ";
    part.Print();
    
    Operators::TransformT( & part );
    std::cout << "T: ";
    part.Print();
}
