#ifndef TREENODE_H_
#define TREENODE_H_


class TreeNode
{
public:
    TreeNode()
        : value(), count(0), left(nullptr), right(nullptr)
        { }
    TreeNode(const std::string& val, int cnt=1, 
             TreeNode* lhs=nullptr, TreeNode* rhs=nullptr)
        : value(val), count(cnt), left(lhs), right(rhs)
        { }
    TreeNode(const TreeNode& tn)
        : value(tn.value), count(tn.count)
        , left(TreeNode(*tn.left)), right(TreeNode(*tn.right))
        { }
    TreeNode& operator=(const TreeNode& tn)
    ~TreeNode()
private:
    std::string value;
    int         count;
    TreeNode*   left;
    TreeNode*   right;
};


#endif /*TREENODE_H_*/
