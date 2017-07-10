#ifndef BINARYTREE_H_
#define BINARYTREE_H_


class BinaryTree
{
public:
    BinaryTree()
        : root(new TreeNode)
        { }
    BinaryTree(const BinaryTree& bt)
        : root(new TreeNode(*bt.root))
        { }
    BinaryTree& operator=(const BinaryTree& rhs);
private:
    TreeNode* root;
};


#endif /*BINARYTREE_H_*/
