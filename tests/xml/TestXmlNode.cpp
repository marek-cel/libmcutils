#include <gtest/gtest.h>

#include <mcutils/xml/XmlNode.h>
#include <mcutils/xml/XmlDoc.h>

////////////////////////////////////////////////////////////////////////////////

class TestXmlNode : public ::testing::Test
{
protected:
    TestXmlNode() {}
    virtual ~TestXmlNode() {}
    void SetUp() override {}
    void TearDown() override {}
};

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestXmlNode, CanConstruct)
{
    mc::XmlNode *node = nullptr;
    EXPECT_NO_THROW( node = new mc::XmlNode() );
    delete node;
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestXmlNode, CanDestruct)
{
    mc::XmlNode *node = new mc::XmlNode();
    EXPECT_NO_THROW( delete node );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestXmlNode, CanInstantiate)
{
    mc::XmlNode node;
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestXmlNode, CanInstantiateAndCopy)
{
    std::string file = "../tests/xml/data/test_xml_sample_data.xml";

    xmlDocPtr  doc  = xmlParseFile( file.c_str() );
    xmlNodePtr root = xmlDocGetRootElement( doc );

    mc::XmlNode node0( root, file.c_str() );

    mc::XmlNode node( node0 );

    EXPECT_STREQ( node.getFile().c_str(), file.c_str() );

    xmlFreeDoc( doc );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestXmlNode, CanInstantiateAndMove)
{
    std::string file = "../tests/xml/data/test_xml_sample_data.xml";

    xmlDocPtr  doc  = xmlParseFile( file.c_str() );
    xmlNodePtr root = xmlDocGetRootElement( doc );

    mc::XmlNode node( std::move( mc::XmlNode( root, file.c_str() ) ) );

    EXPECT_STREQ( node.getFile().c_str(), file.c_str() );

    xmlFreeDoc( doc );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestXmlNode, CanInstantiateFromNodeAndFile)
{
    std::string file = "../tests/xml/data/test_xml_sample_data.xml";

    xmlDocPtr  doc  = xmlParseFile( file.c_str() );
    xmlNodePtr root = xmlDocGetRootElement( doc );

    mc::XmlNode node( root, file.c_str() );

    EXPECT_STREQ( node.getFile().c_str(), file.c_str() );

    xmlFreeDoc( doc );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestXmlNode, CanGetAttribute)
{
    std::string file = "../tests/xml/data/test_xml_sample_data.xml";

    mc::XmlDoc doc( file.c_str() );
    mc::XmlNode root = doc.getRootNode();

    EXPECT_STREQ( "A" , root.getAttribute( "attribute_a" ).c_str() );
    EXPECT_STREQ( "B" , root.getAttribute( "attribute_b" ).c_str() );
    EXPECT_STREQ( ""  , root.getAttribute( "attribute_x" ).c_str() );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestXmlNode, CanGetAttributes)
{
    std::string file = "../tests/xml/data/test_xml_sample_data.xml";

    mc::XmlDoc doc( file.c_str() );
    mc::XmlNode root = doc.getRootNode();

    mc::XmlNode::Attributes attributes = root.getAttributes();

    EXPECT_EQ( 2, attributes.size() );

    mc::XmlNode::Attributes::iterator it_a = attributes.find( "attribute_a" );
    mc::XmlNode::Attributes::iterator it_b = attributes.find( "attribute_b" );

    EXPECT_NE( attributes.end(), it_a );
    EXPECT_NE( attributes.end(), it_a );

    EXPECT_STREQ( "A" , it_a->second.c_str() );
    EXPECT_STREQ( "B" , it_b->second.c_str() );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestXmlNode, CanGetFirstChild)
{
    std::string file = "../tests/xml/data/test_xml_sample_data.xml";

    mc::XmlDoc doc( file.c_str() );
    mc::XmlNode root = doc.getRootNode();

    mc::XmlNode child = root.getFirstChild();

    EXPECT_TRUE( child.isValid() );
    EXPECT_TRUE( child.isText() );
    EXPECT_STREQ( "\nLorem ipsum\n", child.getText().c_str() );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestXmlNode, CanGetFirstChildElement)
{
    std::string file = "../tests/xml/data/test_xml_sample_data.xml";

    mc::XmlDoc doc( file.c_str() );
    mc::XmlNode root = doc.getRootNode();

    mc::XmlNode child = root.getFirstChildElement();

    EXPECT_TRUE( child.isValid() );
    EXPECT_TRUE( child.isElement() );
    EXPECT_STREQ( "sibling_1", child.getName().c_str() );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestXmlNode, CanGetFirstChildElementByName)
{
    std::string file = "../tests/xml/data/test_xml_sample_data.xml";

    mc::XmlDoc doc( file.c_str() );
    mc::XmlNode root = doc.getRootNode();

    mc::XmlNode child = root.getFirstChildElement( "sibling_2" );

    EXPECT_TRUE( child.isValid() );
    EXPECT_TRUE( child.isElement() );
    EXPECT_STREQ( "sibling_2", child.getName().c_str() );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestXmlNode, CanGetFirstChildElementNoChildren)
{
    std::string file = "../tests/xml/data/test_xml_sample_data_no_children.xml";

    mc::XmlDoc doc( file.c_str() );
    mc::XmlNode root = doc.getRootNode();

    mc::XmlNode child = root.getFirstChildElement();

    EXPECT_FALSE( child.isValid() );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestXmlNode, CanGetFile)
{
    std::string file = "../tests/xml/data/test_xml_sample_data.xml";

    mc::XmlDoc doc( file.c_str() );
    mc::XmlNode root = doc.getRootNode();

    EXPECT_STREQ( file.c_str(), root.getFile().c_str() );

    mc::XmlNode child = root.getFirstChildElement();

    EXPECT_STREQ( file.c_str(), child.getFile().c_str() );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestXmlNode, CanGetFileAndLine)
{
    std::string file = "../tests/xml/data/test_xml_sample_data.xml";

    mc::XmlDoc doc( file.c_str() );
    mc::XmlNode root = doc.getRootNode();

    EXPECT_STREQ( ( file + "(2)" ).c_str(), root.getFileAndLine().c_str() );

    mc::XmlNode child = root.getFirstChildElement();

    EXPECT_STREQ( ( file + "(4)" ).c_str(), child.getFileAndLine().c_str() );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestXmlNode, CanGetLine)
{
    std::string file = "../tests/xml/data/test_xml_sample_data.xml";

    mc::XmlDoc doc( file.c_str() );
    mc::XmlNode root = doc.getRootNode();

    EXPECT_EQ( 2, root.getLine() );

    mc::XmlNode child = root.getFirstChildElement();

    EXPECT_EQ( 4, child.getLine() );

    mc::XmlNode invalid;
    EXPECT_EQ( std::numeric_limits<int>::quiet_NaN(), invalid.getLine() );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestXmlNode, CanGetName)
{
    std::string file = "../tests/xml/data/test_xml_sample_data.xml";

    mc::XmlDoc doc( file.c_str() );
    mc::XmlNode root = doc.getRootNode();

    EXPECT_STREQ( "test_root", root.getName().c_str() );

    mc::XmlNode child = root.getFirstChildElement();

    EXPECT_STREQ( "sibling_1", child.getName().c_str() );

    mc::XmlNode invalid;
    EXPECT_STREQ( "", invalid.getName().c_str() );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestXmlNode, CanGetNextSibling)
{
    std::string file = "../tests/xml/data/test_xml_sample_data.xml";

    mc::XmlDoc doc( file.c_str() );
    mc::XmlNode root = doc.getRootNode();

    EXPECT_STREQ( "test_root", root.getName().c_str() );

    mc::XmlNode child1 = root.getFirstChildElement();
    mc::XmlNode child2 = child1.getNextSibling();

    EXPECT_TRUE( child2.isValid() );
    EXPECT_TRUE( child2.isText() );
    EXPECT_STREQ( "\ndolor sit amet\n", child2.getText().c_str() );

    mc::XmlNode child3 = child2.getNextSibling();
    EXPECT_TRUE( child3.isValid() );
    EXPECT_TRUE( child3.isElement() );

    mc::XmlNode child4 = child3.getNextSibling();
    EXPECT_TRUE( child4.isValid() );
    EXPECT_TRUE( child4.isText() );
    EXPECT_STREQ( "\n", child4.getText().c_str() );

    mc::XmlNode child5 = child4.getNextSibling();
    EXPECT_TRUE( child5.isValid() );
    EXPECT_TRUE( child5.isComment() );

    mc::XmlNode child6 = child5.getNextSibling();
    EXPECT_TRUE( child6.isValid() );
    EXPECT_TRUE( child6.isText() );
    EXPECT_STREQ( "\n", child6.getText().c_str() );

    mc::XmlNode child7 = child6.getNextSibling();
    EXPECT_FALSE( child7.isValid() );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestXmlNode, CanGetNextSiblingElement)
{
    std::string file = "../tests/xml/data/test_xml_sample_data.xml";

    mc::XmlDoc doc( file.c_str() );
    mc::XmlNode root = doc.getRootNode();

    EXPECT_STREQ( "test_root", root.getName().c_str() );

    mc::XmlNode child1 = root.getFirstChildElement();

    mc::XmlNode child2 = child1.getNextSiblingElement();
    EXPECT_TRUE( child2.isValid() );
    EXPECT_TRUE( child2.isElement() );
    EXPECT_STREQ( "sibling_2", child2.getName().c_str() );

    mc::XmlNode child3 = child2.getNextSiblingElement();
    EXPECT_FALSE( child3.isValid() );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestXmlNode, CanGetText)
{
    std::string file = "../tests/xml/data/test_xml_sample_data.xml";

    mc::XmlDoc doc( file.c_str() );
    mc::XmlNode root = doc.getRootNode();

    mc::XmlNode child = root.getFirstChild();
    EXPECT_TRUE( child.isValid() );
    EXPECT_TRUE( child.isText() );
    EXPECT_STREQ( "\nLorem ipsum\n", child.getText().c_str() );

    mc::XmlNode child1 = root.getFirstChildElement();
    EXPECT_STREQ( "", child1.getText().c_str() );

    mc::XmlNode child2 = child1.getNextSibling();
    EXPECT_TRUE( child2.isValid() );
    EXPECT_TRUE( child2.isText() );
    EXPECT_STREQ( "\ndolor sit amet\n", child2.getText().c_str() );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestXmlNode, CanCheckIfNodeHasAttribute)
{
    std::string file = "../tests/xml/data/test_xml_sample_data.xml";

    mc::XmlDoc doc( file.c_str() );
    mc::XmlNode root = doc.getRootNode();

    EXPECT_TRUE( root.hasAttribute( "attribute_a" ) );
    EXPECT_TRUE( root.hasAttribute( "attribute_b" ) );

    EXPECT_FALSE( root.hasAttribute( "attribute_x" ) );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestXmlNode, CanCheckIfNodeHasAnyAttributes)
{
    std::string file = "../tests/xml/data/test_xml_sample_data.xml";

    mc::XmlDoc doc( file.c_str() );
    mc::XmlNode root = doc.getRootNode();

    EXPECT_TRUE( root.hasAttributes() );

    mc::XmlNode child = root.getFirstChildElement();

    EXPECT_FALSE( child.hasAttributes() );

    mc::XmlNode inavlid;
    EXPECT_FALSE( inavlid.hasAttributes() );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestXmlNode, CanCheckIfNodeHasAnyChildren)
{
    std::string file = "../tests/xml/data/test_xml_sample_data.xml";

    mc::XmlDoc doc( file.c_str() );
    mc::XmlNode root = doc.getRootNode();

    EXPECT_TRUE( root.hasChildren() );

    mc::XmlNode child = root.getFirstChildElement();
    EXPECT_FALSE( child.hasChildren() );

    mc::XmlNode inavlid;
    EXPECT_FALSE( inavlid.hasChildren() );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestXmlNode, CanCheckIfNodeIsAttribute)
{
    mc::XmlNode inavlid;
    EXPECT_FALSE( inavlid.isAttribute() );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestXmlNode, CanCheckIfNodeIsComment)
{
    std::string file = "../tests/xml/data/test_xml_sample_data.xml";

    mc::XmlDoc doc( file.c_str() );
    mc::XmlNode root = doc.getRootNode();

    EXPECT_FALSE( root.isComment() );

    mc::XmlNode child1 = root.getFirstChildElement();
    EXPECT_FALSE( child1.isComment() );

    mc::XmlNode child2 = child1.getNextSibling();
    EXPECT_FALSE( child2.isComment() );

    mc::XmlNode child3 = child2.getNextSibling();
    EXPECT_FALSE( child3.isComment() );

    mc::XmlNode child4 = child3.getNextSibling();
    EXPECT_FALSE( child4.isComment() );

    mc::XmlNode child5 = child4.getNextSibling();
    EXPECT_TRUE( child5.isComment() );

    mc::XmlNode inavlid;
    EXPECT_FALSE( inavlid.isComment() );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestXmlNode, CanCheckIfNodeIsElement)
{
    std::string file = "../tests/xml/data/test_xml_sample_data.xml";

    mc::XmlDoc doc( file.c_str() );
    mc::XmlNode root = doc.getRootNode();

    EXPECT_TRUE( root.isElement() );

    mc::XmlNode child = root.getFirstChild();
    EXPECT_FALSE( child.isElement() );

    mc::XmlNode inavlid;
    EXPECT_FALSE( inavlid.isElement() );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestXmlNode, CanCheckIfNodeIsText)
{
    std::string file = "../tests/xml/data/test_xml_sample_data.xml";

    mc::XmlDoc doc( file.c_str() );
    mc::XmlNode root = doc.getRootNode();

    EXPECT_FALSE( root.isText() );

    mc::XmlNode child = root.getFirstChild();
    EXPECT_TRUE( child.isText() );

    mc::XmlNode inavlid;
    EXPECT_FALSE( inavlid.isText() );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestXmlNode, CanCheckIfNodeIsValid)
{
    std::string file = "../tests/xml/data/test_xml_sample_data.xml";

    mc::XmlDoc doc( file.c_str() );
    mc::XmlNode root = doc.getRootNode();

    EXPECT_TRUE( root.isValid() );

    mc::XmlNode child1 = root.getFirstChildElement();
    EXPECT_TRUE( child1.isValid() );

    mc::XmlNode child2 = child1.getNextSibling();
    EXPECT_TRUE( child2.isValid() );

    mc::XmlNode child3 = child2.getNextSibling();
    EXPECT_TRUE( child3.isValid() );

    mc::XmlNode child4 = child3.getNextSibling();
    EXPECT_TRUE( child4.isValid() );

    mc::XmlNode child5 = child4.getNextSibling();
    EXPECT_TRUE( child5.isValid() );

    mc::XmlNode child6 = child5.getNextSibling();
    EXPECT_TRUE( child6.isValid() );

    mc::XmlNode child7 = child6.getNextSibling();
    EXPECT_FALSE( child7.isValid() );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestXmlNode, CanAssign)
{
    mc::XmlNode node;

    std::string file = "../tests/xml/data/test_xml_sample_data.xml";

    xmlDocPtr  doc  = xmlParseFile( file.c_str() );
    xmlNodePtr root = xmlDocGetRootElement( doc );

    mc::XmlNode node0( root, file.c_str() );

    node = node0;

    EXPECT_STREQ( node.getFile().c_str(), file.c_str() );

    xmlFreeDoc( doc );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestXmlNode, CanAssignMove)
{
    mc::XmlNode node;

    std::string file = "../tests/xml/data/test_xml_sample_data.xml";

    xmlDocPtr  doc  = xmlParseFile( file.c_str() );
    xmlNodePtr root = xmlDocGetRootElement( doc );

    node = std::move( mc::XmlNode( root, file.c_str() ) );

    EXPECT_STREQ( node.getFile().c_str(), file.c_str() );

    xmlFreeDoc( doc );
}
