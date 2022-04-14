#include <gtest/gtest.h>

#include <mcutils/xml/XmlDoc.h>

////////////////////////////////////////////////////////////////////////////////

class TestXmlDoc : public ::testing::Test
{
protected:
    TestXmlDoc() {}
    virtual ~TestXmlDoc() {}
    void SetUp() override {}
    void TearDown() override {}
};

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestXmlDoc, CanConstruct)
{
    mc::XmlDoc *doc = nullptr;
    EXPECT_NO_THROW( doc = new mc::XmlDoc() );
    delete doc;
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestXmlDoc, CanDestruct)
{
    mc::XmlDoc *doc = new mc::XmlDoc();
    EXPECT_NO_THROW( delete doc );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestXmlDoc, CanInstantiate)
{
    mc::XmlDoc doc;
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestXmlDoc, CanInstantiateAndOpenFile)
{
    mc::XmlDoc doc( "../tests/xml/data/test_xml_sample_data.xml" );

    EXPECT_TRUE( doc.isOpen() );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestXmlDoc, CanGetRootNode)
{
    mc::XmlDoc doc( "../tests/xml/data/test_xml_sample_data.xml" );

    EXPECT_TRUE( doc.isOpen() );

    mc::XmlNode rootNode = doc.getRootNode();

    EXPECT_TRUE( rootNode.isValid() );
    EXPECT_STREQ( rootNode.getName().c_str(), "test_root" );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestXmlDoc, CanOpenFile)
{
    mc::XmlDoc doc;

    EXPECT_NO_THROW( doc.openFile( "../tests/xml/data/test_xml_sample_data.xml" ) );
    EXPECT_TRUE( doc.isOpen() );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestXmlDoc, CanOpenFileEmpty)
{
    mc::XmlDoc doc;

    EXPECT_NO_THROW( doc.openFile( "../tests/xml/data/test_xml_sample_data_empty.xml" ) );
    EXPECT_FALSE( doc.isOpen() );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestXmlDoc, CanOpenFileNotExisting)
{
    mc::XmlDoc doc;

    EXPECT_NO_THROW( doc.openFile( "../tests/xml/data/test_xml_sample_data_not_existing.xml" ) );
    EXPECT_FALSE( doc.isOpen() );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestXmlDoc, CanCloseFile)
{
    mc::XmlDoc doc( "../tests/xml/data/test_xml_sample_data.xml" );

    EXPECT_TRUE( doc.isOpen() );
    EXPECT_NO_THROW( doc.closeFile() );
    EXPECT_FALSE( doc.isOpen() );
}
