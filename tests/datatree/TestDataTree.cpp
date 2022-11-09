#include <gtest/gtest.h>

#include <mcutils/datatree/DataTree.h>

////////////////////////////////////////////////////////////////////////////////

class TestDataTree : public ::testing::Test
{
protected:
    TestDataTree() {}
    virtual ~TestDataTree() {}
    void SetUp() override {}
    void TearDown() override {}
};

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestDataTree, CanConstruct)
{
    mc::DataTree *dataTree = nullptr;
    EXPECT_NO_THROW( dataTree = new mc::DataTree() );
    delete dataTree;
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestDataTree, CanDestruct)
{
    mc::DataTree *dataTree = new mc::DataTree();
    EXPECT_NO_THROW( delete dataTree );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestDataTree, CanInstantiate)
{
    mc::DataTree dataTree;
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestDataTree, CanAddEntry)
{
    mc::DataTree dataTree;

    EXPECT_EQ( mc::Result::Success, dataTree.addEntry( "group0"   , mc::NodeType::Group ) );
    EXPECT_EQ( mc::Result::Success, dataTree.addEntry( "dataBool" , mc::NodeType::Bool  ) );
    EXPECT_EQ( mc::Result::Success, dataTree.addEntry( "dataInt"  , mc::NodeType::Int   ) );
    EXPECT_EQ( mc::Result::Success, dataTree.addEntry( "dataReal" , mc::NodeType::Real  ) );

    EXPECT_EQ( mc::Result::Failure, dataTree.addEntry( "group0"   , mc::NodeType::Group ) );
    EXPECT_EQ( mc::Result::Failure, dataTree.addEntry( "dataBool" , mc::NodeType::Bool  ) );
    EXPECT_EQ( mc::Result::Failure, dataTree.addEntry( "dataInt"  , mc::NodeType::Int   ) );
    EXPECT_EQ( mc::Result::Failure, dataTree.addEntry( "dataReal" , mc::NodeType::Real  ) );

    EXPECT_EQ( mc::Result::Success, dataTree.addEntry( "group0.dataBool" , mc::NodeType::Bool ) );
    EXPECT_EQ( mc::Result::Success, dataTree.addEntry( "group0.dataInt"  , mc::NodeType::Int  ) );
    EXPECT_EQ( mc::Result::Success, dataTree.addEntry( "group0.dataReal" , mc::NodeType::Real ) );

    EXPECT_EQ( mc::Result::Success, dataTree.addEntry( "group1.dataBool" , mc::NodeType::Bool ) );
    EXPECT_EQ( mc::Result::Success, dataTree.addEntry( "group1.dataInt"  , mc::NodeType::Int  ) );
    EXPECT_EQ( mc::Result::Success, dataTree.addEntry( "group1.dataReal" , mc::NodeType::Real ) );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestDataTree, CanGetRefBool)
{
    mc::DataTree dataTree;

    dataTree.addEntry( "group.dataBool" , mc::NodeType::Bool );
    dataTree.addEntry( "group.dataInt"  , mc::NodeType::Int  );
    dataTree.addEntry( "group.dataReal" , mc::NodeType::Real );

    std::string path;

    mc::DataRefBool dataRef;
    EXPECT_FALSE( dataRef.isValid() );

    dataRef = dataTree.getRefBool( "group.dataBool" );
    EXPECT_TRUE( dataRef.isValid() );

    path = "group.dataBool";
    dataRef = dataTree.getRefBool( path );
    EXPECT_TRUE( dataRef.isValid() );

    dataRef = dataTree.getRefBool( "group.dataInt" );
    EXPECT_FALSE( dataRef.isValid() );

    path = "group.dataInt";
    dataRef = dataTree.getRefBool( path );
    EXPECT_FALSE( dataRef.isValid() );

    dataRef = dataTree.getRefBool( "group.dataReal" );
    EXPECT_FALSE( dataRef.isValid() );

    path = "group.dataReal";
    dataRef = dataTree.getRefBool( path );
    EXPECT_FALSE( dataRef.isValid() );

    path = "group.dataReal";
    dataRef = dataTree.getRefBool( path );
    EXPECT_FALSE( dataRef.isValid() );

    dataRef = dataTree.getRefBool( "group.dataNotExisting" );
    EXPECT_FALSE( dataRef.isValid() );

    dataRef = dataTree.getRefBool( "group" );
    EXPECT_FALSE( dataRef.isValid() );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestDataTree, CanGetRefInt)
{
    mc::DataTree dataTree;

    dataTree.addEntry( "group.dataBool" , mc::NodeType::Bool );
    dataTree.addEntry( "group.dataInt"  , mc::NodeType::Int  );
    dataTree.addEntry( "group.dataReal" , mc::NodeType::Real );

    std::string path;

    mc::DataRefInt dataRef;
    EXPECT_FALSE( dataRef.isValid() );

    dataRef = dataTree.getRefInt( "group.dataBool" );
    EXPECT_FALSE( dataRef.isValid() );

    path = "group.dataBool";
    dataRef = dataTree.getRefInt( path );
    EXPECT_FALSE( dataRef.isValid() );

    dataRef = dataTree.getRefInt( "group.dataInt" );
    EXPECT_TRUE( dataRef.isValid() );

    path = "group.dataInt";
    dataRef = dataTree.getRefInt( path );
    EXPECT_TRUE( dataRef.isValid() );

    dataRef = dataTree.getRefInt( "group.dataReal" );
    EXPECT_FALSE( dataRef.isValid() );

    path = "group.dataReal";
    dataRef = dataTree.getRefInt( path );
    EXPECT_FALSE( dataRef.isValid() );

    dataRef = dataTree.getRefInt( "group.dataNotExisting" );
    EXPECT_FALSE( dataRef.isValid() );

    dataRef = dataTree.getRefInt( "group" );
    EXPECT_FALSE( dataRef.isValid() );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestDataTree, CanGetRefReal)
{
    mc::DataTree dataTree;

    dataTree.addEntry( "group.dataBool" , mc::NodeType::Bool );
    dataTree.addEntry( "group.dataInt"  , mc::NodeType::Int  );
    dataTree.addEntry( "group.dataReal" , mc::NodeType::Real );

    std::string path;

    mc::DataRefReal dataRef;
    EXPECT_FALSE( dataRef.isValid() );

    dataRef = dataTree.getRefReal( "group.dataBool" );
    EXPECT_FALSE( dataRef.isValid() );

    path = "group.dataBool";
    dataRef = dataTree.getRefReal( path );
    EXPECT_FALSE( dataRef.isValid() );

    dataRef = dataTree.getRefReal( "group.dataInt" );
    EXPECT_FALSE( dataRef.isValid() );

    path = "group.dataInt";
    dataRef = dataTree.getRefReal( path );
    EXPECT_FALSE( dataRef.isValid() );

    dataRef = dataTree.getRefReal( "group.dataReal" );
    EXPECT_TRUE( dataRef.isValid() );

    path = "group.dataReal";
    dataRef = dataTree.getRefReal( path );
    EXPECT_TRUE( dataRef.isValid() );

    dataRef = dataTree.getRefReal( "group.dataNotExisting" );
    EXPECT_FALSE( dataRef.isValid() );

    dataRef = dataTree.getRefReal( "group" );
    EXPECT_FALSE( dataRef.isValid() );
}


////////////////////////////////////////////////////////////////////////////////

TEST_F(TestDataTree, CanGetSubTree)
{
    mc::DataTree dataTree;

    dataTree.addEntry( "group1.group2.dataBool", mc::NodeType::Bool );

    mc::DataRefBool dataRef;
    EXPECT_FALSE( dataRef.isValid() );

    mc::DataTree dataTreeSub = dataTree.getSubTree( "group1" );

    dataRef = dataTreeSub.getRefBool( "group2.dataBool" );
    EXPECT_TRUE( dataRef.isValid() );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestDataTree, CanValidate)
{
    mc::GroupNodeSharedPtr groupNodeSharedPtr;
    mc::DataTree dataTree1( groupNodeSharedPtr );
    EXPECT_FALSE( dataTree1.isValid() );

    mc::DataTree dataTree2;
    EXPECT_TRUE( dataTree2.isValid() );
}
