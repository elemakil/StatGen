#include "QuantumNumbers.hpp"

const char * Flavour::Names [] = { "u", "d", "s", "c", "t", "b", "U", "D", "S", "C", "T", "B", 0 };
const char * Spin::Names [] = { "↑", "↓", "↕", 0 };
const char * Colour::Names [] = { "r", "g", "b", "w", "R", "G", "B", "W", "NoColour", 0 };
const char * Handedness::Names [] = { "⇜", "⇝", "↭", 0 };
const char * Type::Names [] = { "Fermion", "Boson", 0 };

const char * Colour::FileNames [] = { "red", "green", "blue", "white", "antired", "antigreen", "antiblue", "white", "white", 0 };

std::pair<QuantumNumber::aQuantumNumber,QuantumNumber::uQuantumNumber> QuantumNumber::GetFromChar( char cData ) {
    QuantumNumber::uQuantumNumber data;
    QuantumNumber::aQuantumNumber info;

    switch ( cData ){
    case '+': { info = QuantumNumber::Spin; data.Spin = Spin::Up; return std::make_pair( info, data ); }
    case '-': { info = QuantumNumber::Spin; data.Spin = Spin::Down; return std::make_pair( info, data ); }
	
    case 'l': { info = QuantumNumber::Handedness; data.Handedness = Handedness::Left; return std::make_pair( info, data ); }
    case 'r': { info = QuantumNumber::Handedness; data.Handedness = Handedness::Right; return std::make_pair( info, data ); }
	
    case '0': { info = QuantumNumber::Colour; data.Colour = Colour::White; return std::make_pair( info, data ); }
    case '1': { info = QuantumNumber::Colour; data.Colour = Colour::Red; return std::make_pair( info, data ); }
    case '2': { info = QuantumNumber::Colour; data.Colour = Colour::Green; return std::make_pair( info, data ); }
    case '3': { info = QuantumNumber::Colour; data.Colour = Colour::Blue; return std::make_pair( info, data ); }
    case '4': { info = QuantumNumber::Colour; data.Colour = Colour::AntiRed; return std::make_pair( info, data ); }
    case '5': { info = QuantumNumber::Colour; data.Colour = Colour::AntiGreen; return std::make_pair( info, data ); }
    case '6': { info = QuantumNumber::Colour; data.Colour = Colour::AntiBlue; return std::make_pair( info, data ); }
	
    case 'u': { info = QuantumNumber::Flavour; data.Flavour = Flavour::Up; return std::make_pair( info, data ); }
    case 'd': { info = QuantumNumber::Flavour; data.Flavour = Flavour::Down; return std::make_pair( info, data ); }
    case 's': { info = QuantumNumber::Flavour; data.Flavour = Flavour::Strange; return std::make_pair( info, data ); }
    case 'c': { info = QuantumNumber::Flavour; data.Flavour = Flavour::Charm; return std::make_pair( info, data ); }
    case 't': { info = QuantumNumber::Flavour; data.Flavour = Flavour::Top; return std::make_pair( info, data ); }
    case 'b': { info = QuantumNumber::Flavour; data.Flavour = Flavour::Bottom; return std::make_pair( info, data ); }
	
    case 'U': { info = QuantumNumber::Flavour; data.Flavour = Flavour::AntiUp; return std::make_pair( info, data ); }
    case 'D': { info = QuantumNumber::Flavour; data.Flavour = Flavour::AntiDown; return std::make_pair( info, data ); }
    case 'S': { info = QuantumNumber::Flavour; data.Flavour = Flavour::AntiStrange; return std::make_pair( info, data ); }
    case 'C': { info = QuantumNumber::Flavour; data.Flavour = Flavour::AntiCharm; return std::make_pair( info, data ); }
    case 'T': { info = QuantumNumber::Flavour; data.Flavour = Flavour::AntiTop; return std::make_pair( info, data ); }
    case 'B': { info = QuantumNumber::Flavour; data.Flavour = Flavour::AntiBottom; return std::make_pair( info, data ); }
	
    default: { info = QuantumNumber::Error; return std::make_pair( info, data ); }
    }
}

