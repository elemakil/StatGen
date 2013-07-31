#include "StringTree.hpp"

StringTree::StringTree( std::string sInput ) : m_sInput( sInput ){
    m_RootNode = new StringTreeNode;
    m_RootNode->Parent = NULL;
    m_RootNode->PartStart = 0;
    m_RootNode->PartEnd = sInput.size() - 1;
    m_RootNode->lChild = NULL;
    m_RootNode->rChild = NULL;
    m_RootNode->Combine = "";
}

/* virtual */ StringTree::~StringTree(){
    DeleteChildren( m_RootNode );
}

/* virtual */ void StringTree::Atomise( StringTreeNode * target, StringTreeLevel stage /* = Parentheses */ ){
    if ( stage == Parentheses ){
	size_t uiOpeningParenthesis = m_sInput.substr( target->PartStart, target->PartEnd - target->PartStart ).find( "(" );
	
	if ( uiOpeningParenthesis != std::string::npos ){
	    
	}
	else {
	}
    }
}

/* virtual */ void StringTree::DeleteChildren( StringTreeNode * target ){
    if ( target->lChild != NULL ){
	DeleteChildren( target->lChild );
    }
    if ( target->rChild != NULL ){
	DeleteChildren( target->rChild );
    }
    delete target;
}