#include <gtest/gtest.h>

#include <mcutils/datatree/GroupNode.h>
#include <mcutils/datatree/ValueNode.h>

////////////////////////////////////////////////////////////////////////////////

class TestGroupNode : public ::testing::Test
{
protected:
    TestGroupNode() {}
    virtual ~TestGroupNode() {}
    void SetUp() override {}
    void TearDown() override {}
};

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestGroupNode, CanConstruct)
{
    mc::GroupNode *node = nullptr;
    EXPECT_NO_THROW( node = new mc::GroupNode() );
    delete node;
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestGroupNode, CanDestruct)
{
    mc::GroupNode *node = new mc::GroupNode();
    EXPECT_NO_THROW( delete node );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestGroupNode, CanInstantiate)
{
    mc::GroupNode node;
    EXPECT_STREQ( node.getName().c_str(), "" );

    mc::GroupNode node2( "xxx" );
    EXPECT_STREQ( node2.getName().c_str(), "xxx" );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestGroupNode, CanAddNode)
{
    mc::GroupNode root;

    EXPECT_EQ( mc::Result::Success, root.addNode( "group1", mc::NodeType::Group ) );
    EXPECT_EQ( mc::Result::Success, root.addNode( "group2", mc::NodeType::Group ) );
    EXPECT_EQ( mc::Result::Success, root.addNode( "group1.group1-1", mc::NodeType::Group ) );
    EXPECT_EQ( mc::Result::Success, root.addNode( "group1.group1-2", mc::NodeType::Group ) );
    EXPECT_EQ( mc::Result::Success, root.addNode( "group2.group2-1", mc::NodeType::Group ) );
    EXPECT_EQ( mc::Result::Success, root.addNode( "group1.data1", mc::NodeType::Bool ) );
    EXPECT_EQ( mc::Result::Success, root.addNode( "group1.data2", mc::NodeType::Int  ) );
    EXPECT_EQ( mc::Result::Success, root.addNode( "group2.data3", mc::NodeType::Real ) );

    EXPECT_EQ( mc::Result::Failure, root.addNode( "group1", mc::NodeType::Group ) );
    EXPECT_EQ( mc::Result::Failure, root.addNode( "group2", mc::NodeType::Group ) );
    EXPECT_EQ( mc::Result::Failure, root.addNode( "group1.group1-1", mc::NodeType::Group ) );
    EXPECT_EQ( mc::Result::Failure, root.addNode( "group1.group1-2", mc::NodeType::Group ) );
    EXPECT_EQ( mc::Result::Failure, root.addNode( "group2.group2-1", mc::NodeType::Group ) );
    EXPECT_EQ( mc::Result::Failure, root.addNode( "group1.data1", mc::NodeType::Bool ) );
    EXPECT_EQ( mc::Result::Failure, root.addNode( "group1.data2", mc::NodeType::Int  ) );
    EXPECT_EQ( mc::Result::Failure, root.addNode( "group2.data3", mc::NodeType::Real ) );

    EXPECT_EQ( mc::Result::Failure, root.addNode( "group2.data3.data4", mc::NodeType::Int ) );
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(TestGroupNode, CanGetNode)
{
    mc::GroupNode root;

    root.addNode( "group", mc::NodeType::Group );
    root.addNode( "group.data1", mc::NodeType::Bool );
    root.addNode( "group.data2", mc::NodeType::Int  );
    root.addNode( "group.data3", mc::NodeType::Real );

    mc::NodeWeakPtr nodeWeakPtr;
    mc::NodeSharedPtr nodeSharedPtr;
    mc::GroupNodeSharedPtr groupNodeSharedPtr;
    std::shared_ptr< mc::ValueNode<bool> >   valueNodeBoolSharedPtr;
    std::shared_ptr< mc::ValueNode<int> >    valueNodeIntSharedPtr;
    std::shared_ptr< mc::ValueNode<double> > valueNodeDoubleSharedPtr;

    nodeWeakPtr = root.getNode( "group" );
    EXPECT_FALSE( nodeWeakPtr.expired() );
    nodeSharedPtr = nodeWeakPtr.lock();
    groupNodeSharedPtr = std::dynamic_pointer_cast<mc::GroupNode,mc::Node>( nodeSharedPtr );
    EXPECT_NE( groupNodeSharedPtr.get(), nullptr );

    nodeWeakPtr = root.getNode( "group.data1" );
    EXPECT_FALSE( nodeWeakPtr.expired() );
    nodeSharedPtr = nodeWeakPtr.lock();
    valueNodeBoolSharedPtr = std::dynamic_pointer_cast<mc::ValueNode<bool>,mc::Node>( nodeSharedPtr );
    EXPECT_NE( valueNodeBoolSharedPtr.get(), nullptr );

    nodeWeakPtr = root.getNode( "group.data2" );
    EXPECT_FALSE( nodeWeakPtr.expired() );
    nodeSharedPtr = nodeWeakPtr.lock();
    valueNodeIntSharedPtr = std::dynamic_pointer_cast<mc::ValueNode<int>,mc::Node>( nodeSharedPtr );
    EXPECT_NE( valueNodeIntSharedPtr.get(), nullptr );

    nodeWeakPtr = root.getNode( "group.data3." );
    EXPECT_FALSE( nodeWeakPtr.expired() );
    nodeSharedPtr = nodeWeakPtr.lock();
    valueNodeDoubleSharedPtr = std::dynamic_pointer_cast<mc::ValueNode<double>,mc::Node>( nodeSharedPtr );
    EXPECT_NE( valueNodeDoubleSharedPtr.get(), nullptr );

    nodeWeakPtr = root.getNode( "group.data666" );
    EXPECT_TRUE( nodeWeakPtr.expired() );
}
