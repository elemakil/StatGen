#ifndef STRINGTREE_H
#define STRINGTREE_H

#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iterator>

enum StringTreeLevel {
    Parentheses,
    KetNotation,
    Particles
};

struct StringTreeNode {
    StringTreeNode * Parent;
    
    size_t PartStart;
    size_t PartEnd;
    
    std::vector<StringTreeNode*> Children;
    std::vector<std::string> Operators;
};

    
class StringTree {
public:
    StringTree( std::string sInput );
    virtual ~StringTree();
    
    virtual void Atomise( StringTreeNode * parent, StringTreeNode * target, StringTreeLevel stage = Parentheses );
private:        
    virtual void DeleteChildren( StringTreeNode * target );

    StringTreeNode * m_RootNode;
    std::string m_sInput;
};

#endif // STRINGTREE_H
