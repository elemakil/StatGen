#include "StringTree.hpp"

StringTree::StringTree( std::string sInput ) : m_sInput( sInput ){
    m_RootNode = new StringTreeNode;
    m_RootNode->Parent = NULL;
    m_RootNode->PartStart = 0;
    m_RootNode->PartEnd = sInput.size() - 1;
}

/* virtual */ StringTree::~StringTree(){
    DeleteChildren( m_RootNode );
}

/* virtual */ void StringTree::Atomise( StringTreeNode * target, StringTreeLevel stage /* = Parentheses */ ){
    if ( stage == Parentheses ){
	size_t uiOpeningParenthesis = m_sInput.substr( target->PartStart, target->PartEnd ).find( "(" );
	
	if ( uiOpeningParenthesis != std::string::npos ){
	    
	}
	else {
	    Atomise( target, KetNotation );
	}
    }
}

/* virtual */ void StringTree::DeleteChildren( StringTreeNode * target ){
    if ( ! target->Children.empty() ){
	for ( size_t iChild=0; iChild<target->Children.size(); ++iChild ){
	    DeleteChildren( target->Children.at( iChild ) );
	}
    }
    delete target;
}
