/* CTK(Common Tool Kit, author: luyunhai 3664(117629)/huawei)
 * Copyright (c) 2010 Huawei Technologies Co., Ltd.
 * All rights reserved.
 */
#ifndef _Z_CTK_XML_NODE_H_
#define _Z_CTK_XML_NODE_H_

#include "ctk/xml/XMLAttr.h"

namespace ctk {
namespace xml {

    struct cdata_t { };

    class CTK_API XMLNode
    {
    public:
        typedef std::vector<String>        _AttrList;
        typedef std::map<String, XMLAttr>  _AttrMap;

        typedef std::vector<XMLNode*>      _NodeList;
        typedef std::map<String, XMLNode*> _NodeMap;

    public:
        XMLNode( rcistr _name=istr(), XMLNode* _parentNode=0 );
        XMLNode( rcistr _cdata, cdata_t );
        XMLNode( const XMLNode& _node );
        virtual ~XMLNode();

        XMLNode& operator=( const XMLNode& _node );
        XMLNode& operator+=( const XMLNode& _node );

        void assign( const XMLNode& _node );
        void append( const XMLNode& _node );

        // all fields is empty
        bool isEmpty() const;
        
        // equal to XMLNode::null()
        bool isNull() const;

        // no children
        bool isSimple() const;

        /**
        *get the name of the node
        */
        rcstr name() const ;

        /**
        *sets the name of the node. Generally done during parsing
        */
        void name( rcistr _name ) ;

        /**
        *returns the character data associated with this node.
        */
        rcstr cdata() const ;

        /**
        *sets the character data for this node.
        */
        void cdata( rcistr _cdata, bool _bEncode = false );

        /**
        *get the parent node of this node. May
        *return NULL if this is a root, or
        *top level node of the XML document
        *@return XMLNode the parent node. NULL if this
        *is a root node.
        */
        XMLNode* parent() const ;

        /**
        *sets the parent node. Generally called by the parser
        *during the parsing phase of the XML document
        */
        void parent( XMLNode* _parentNode ) ;

        //

        // insert attr if not exist
        XMLAttr& operator()( rcistr _name );
        XMLAttr& attr( rcistr _name );

        const XMLAttr& operator()( rcistr _name ) const;
        const XMLAttr& attr( rcistr _name ) const;

        const XMLAttr& attr( size_t _index ) const ;
        size_type numofAttrs() const;

        /**
        *adds a new attribute to the node. Generally called by
        *parser.
        */
        void addAttr( const XMLAttr& attr ) ;

        /**
        *adds a new attribute to the node. Generally called by
        *parser.
        */
        void addAttr( rcistr _name, rcistr _value ) ;

        /**
        *get the collection of attributes for this node
        *@return Enumerator<XMLAttr>* an enumerator of XMLAttr
        *objects
        */
        const _AttrList& getAttrNames() const ;

        const _AttrMap& getAttrMap() const ;

        void clearAttrs();

        //

        // insert child node if not exist
        XMLNode& operator[]( rcistr _name );
        XMLNode& child( rcistr _name );

        const XMLNode& operator[]( rcistr _name ) const ;
        const XMLNode& child( rcistr _name ) const ;

        const XMLNode& child( size_t _index ) const ;
        size_type numofChildren() const;
        
        //

        void addChildNode( XMLNode* _node ) ;

        void removeChildNode( XMLNode* _node ) ;

        XMLNode* addChildNode( rcistr _nodeName ) ;

        const _NodeList& getChildNodes() const ;

        const _NodeMap& getChildNodeMap() const ;

        void clearNodes();

        //

        int getDepth() const;

        String str(bool _formatted=false, uint _depth=0) const ;

        static const XMLNode& null();

    private:
        String    name_;
        String    cdata_;

        _AttrList attrNames_;
        _AttrMap  attrMap_;

        _NodeList childNodes_;
        _NodeMap  nodeMap_;

        ctk::Pointer<XMLNode>  parentNode_;

    };
    CTK_API std::ostream& operator<<(std::ostream& _os, const XMLNode& _v);

} // end of namespace xml
} // end of namespace ctk

#endif // _Z_CTK_XML_NODE_H_

