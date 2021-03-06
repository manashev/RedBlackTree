#include "BinaryTree.h" 

template<class TreeItemType>
void BinaryTree<TreeItemType>::deleteItem(TreeItemType &anitem)
{
	if (root->item == anitem)
		throw TreeException("TreeException: ���������� ������� ������ ������");
	TreeNode<TreeItemType> *tmpPtr = root, *nodePtr = NULL;
	while (tmpPtr != NULL && tmpPtr->item != anitem)
	{
		nodePtr = tmpPtr;
		if (anitem > tmpPtr->item)
			tmpPtr = tmpPtr->rightChildPtr;
		else
			tmpPtr = tmpPtr->leftChildPtr;
	}
	if (tmpPtr == NULL)
		throw TreeException("TreeException: ������� �� ������");
	else
	{
		if (nodePtr->rightChildPtr != NULL)
		{
			if (nodePtr->rightChildPtr->item == anitem)
				nodePtr->rightChildPtr = deleteItem_helper(nodePtr->rightChildPtr);
		}
		if (nodePtr->leftChildPtr != NULL)
		{
			if (nodePtr->leftChildPtr->item == anitem)
				nodePtr->leftChildPtr = deleteItem_helper(nodePtr->leftChildPtr);
		}
	}
}

template<class TreeItemType>
TreeNode<TreeItemType>* BinaryTree<TreeItemType>::deleteItem_helper(TreeNode<TreeItemType>*& nodePtr)
{
	if (nodePtr->leftChildPtr == NULL)
	{
		if (nodePtr->rightChildPtr == NULL)
		{
			delete nodePtr;
			return NULL;
		}
		else
		{
			TreeNode<TreeItemType> *nextNodePtr = nodePtr->rightChildPtr;
			delete nodePtr;
			return nextNodePtr;
		}
	}
	else // nodePtr->leftChildPtr != NULL
	{
		if (nodePtr->rightChildPtr == NULL)
		{
			TreeNode<TreeItemType> *nextNodePtr = nodePtr->leftChildPtr;
			delete nodePtr;
			return nextNodePtr;
		}
		else // nodePtr->leftChildPtr != NULL && nodePtr->rightChildPtr != NULL
		{
			TreeNode<TreeItemType> *nextNodePtr = nodePtr->rightChildPtr;
			if (nextNodePtr->leftChildPtr == NULL)
			{
				nodePtr->item = nextNodePtr->item;
				nodePtr->rightChildPtr = nextNodePtr->rightChildPtr;
				delete nextNodePtr;
				return nodePtr;
			}
			else
			{
				while (nextNodePtr->leftChildPtr != NULL)
					nextNodePtr = nextNodePtr->leftChildPtr;
				nodePtr->item = nextNodePtr->item;
				TreeNode<TreeItemType> *tmpPtr = nodePtr->rightChildPtr;
				while (tmpPtr->leftChildPtr != nextNodePtr)
					tmpPtr = tmpPtr->leftChildPtr;
				tmpPtr->leftChildPtr = deleteItem_helper(nextNodePtr);
				return nodePtr;
			}
		}
	}
}

template<class TreeItemType>
bool BinaryTree<TreeItemType>::isExist(TreeItemType &anitem) const
{
	return isExist_helper(root, anitem);
}

template<class TreeItemType>
bool BinaryTree<TreeItemType>::isExist_helper(TreeNode<TreeItemType> *nodePtr, TreeItemType &anitem) const
{
	if (nodePtr != NULL)
	{
		if (nodePtr->item == anitem)
			return 1;
		else if (anitem > nodePtr->item)
			return isExist_helper(nodePtr->rightChildPtr, anitem);
		else
			return isExist_helper(nodePtr->leftChildPtr, anitem);
	}
	else
		return 0;
}

template<class TreeItemType>
void BinaryTree<TreeItemType>::print() const
{
	print_helper(root, getDepth());
}

template<class TreeItemType>
std::ostream& operator<<(std::ostream& out, const BinaryTree<TreeItemType> &tree)
{
	tree.print_helper(tree.root, tree.getDepth());
	return out;
}

template<class TreeItemType>
void BinaryTree<TreeItemType>::print_helper(TreeNode<TreeItemType> *nodePtr, unsigned int level) const
{
	if (nodePtr)
	{
		print_helper(nodePtr->rightChildPtr, level - (unsigned int)1);
		std::cout << std::setw(level << (unsigned int)3) << std::setfill('-') << std::right << nodePtr->item << std::endl;
		print_helper(nodePtr->leftChildPtr, level - (unsigned int)1);
	}
}

template <class TreeItemType>
void BinaryTree<TreeItemType>::printLevels() const
{
	std::queue<TreeNode<TreeItemType>*> levelHubs;
	levelHubs.push(root);
	printLevels_helper((unsigned int)0, levelHubs);
}

template <class TreeItemType>
void BinaryTree<TreeItemType>::printLevels_helper(unsigned int level, std::queue<TreeNode<TreeItemType>*> &levelHubs) const
{
	std::cout << "LEVEL " << level << ':' << std::endl;
	std::queue<TreeNode<TreeItemType>*> nextLevelHubs;
	while (!levelHubs.empty())
	{
		std::cout << levelHubs.front()->item << std::endl;
		if (levelHubs.front()->leftChildPtr != NULL)
			nextLevelHubs.push(levelHubs.front()->leftChildPtr);
		if (levelHubs.front()->rightChildPtr != NULL)
			nextLevelHubs.push(levelHubs.front()->rightChildPtr);
		levelHubs.pop();
	}
	if (nextLevelHubs.empty())
		return;
	else
		printLevels_helper(level + (unsigned int)1, nextLevelHubs);
}

template <class TreeItemType>
unsigned int BinaryTree<TreeItemType>::getDepth() const
{
	if (root == NULL)
		throw TreeException("TreeException: ������ �� ���������");
	else
	{
		return getDepth_helper(root);
	}
}

template <class TreeItemType>
unsigned int BinaryTree<TreeItemType>::getDepth_helper(TreeNode<TreeItemType> *nodePtr) const
{
	if (nodePtr == NULL)
		return 0;
	else
	{
		return (unsigned int)1 + std::max(getDepth_helper(nodePtr->leftChildPtr), getDepth_helper(nodePtr->rightChildPtr));
	}
}

template <class TreeItemType>
unsigned int BinaryTree<TreeItemType>::getDepthOfMin() const
{
	if (root == NULL)
		throw TreeException("TreeException: ������ �� ���������");
	else
		return getDepthOfMin_helper(root);
}

template <class TreeItemType>
unsigned int BinaryTree<TreeItemType>::getDepthOfMin_helper(TreeNode<TreeItemType> *nodePtr) const
{
	if (nodePtr == NULL)
		return (unsigned int)0;
	else
		return (unsigned int)1 + getDepthOfMin_helper(nodePtr->leftChildPtr);
}

template <class TreeItemType>
unsigned int BinaryTree<TreeItemType>::getDepthOfMax() const
{
	if (root == NULL)
		throw TreeException("TreeException: ������ �� ���������");
	else
		return getDepthOfMax_helper(root);
}

template <class TreeItemType>
unsigned int BinaryTree<TreeItemType>::getDepthOfMax_helper(TreeNode<TreeItemType> *nodePtr) const
{
	if (root == NULL)
		return (unsigned int)0;
	else
		return (unsigned int)1 + getDepthOfMax_helper(nodePtr->rightChildPtr);
}

template <class TreeItemType>
void BinaryTree<TreeItemType>::attach(TreeItemType &newItem)
{
	attach_helper(newItem, root);
}

template <class TreeItemType>
void BinaryTree<TreeItemType>::attach_helper(const TreeItemType &newItem, TreeNode<TreeItemType> *&nodePtr)
{
	if (nodePtr == NULL)
	{
		nodePtr = new TreeNode<TreeItemType>(newItem, NULL, NULL);
		if (nodePtr == NULL)
			throw TreeException("TreeException: ���������� �������� ������");
	}
	else
	{
		if (newItem > nodePtr->item)
			attach_helper(newItem, nodePtr->rightChildPtr);
		else
			attach_helper(newItem, nodePtr->leftChildPtr);
	}
}

template <class TreeItemType>
BinaryTree<TreeItemType>::BinaryTree() : root(NULL) {}

template <class TreeItemType>
BinaryTree<TreeItemType>::BinaryTree(const TreeItemType& rootitem)
{
	root = new TreeNode<TreeItemType>(rootitem, NULL, NULL);
}

template <class TreeItemType>
BinaryTree<TreeItemType>::BinaryTree(const TreeItemType& rootitem, BinaryTree<TreeItemType>& leftTree, BinaryTree<TreeItemType>& rightTree)
{
	root = new TreeNode<TreeItemType>(rootitem, NULL, NULL);
	attachLeftSubtree(leftTree);
	attachRightSubtree(rightTree);
}

template <class TreeItemType>
BinaryTree<TreeItemType>::BinaryTree(const BinaryTree<TreeItemType>& tree)
{
	copyTree(tree.root, root);
}

template <class TreeItemType>
BinaryTree<TreeItemType>::~BinaryTree()
{
	destroyTree(root);
}

template <class TreeItemType>
BinaryTree<TreeItemType>::BinaryTree(TreeNode<TreeItemType> *nodePtr) : root(nodePtr) {}

template <class TreeItemType>
bool BinaryTree<TreeItemType>::isEmpty() const
{
	return (root == NULL);
}

template <class TreeItemType>
TreeItemType BinaryTree<TreeItemType>::getRootData() const
{
	if (isEmpty())
		throw TreeException("TreeException: ������ �����");
	return root->item;
} // ����� ������� getRootData

template <class TreeItemType>
void BinaryTree<TreeItemType>::setRootData(const TreeItemType& newitem)
{
	if (!isEmpty())
		root->item = newitem;
	else
	{
		root = new TreeNode<TreeItemType>(newitem, NULL, NULL);
		if (root == NULL)
			throw TreeException(
				"TreeException: ���������� �������� ������");
	}
}

template <class TreeItemType>
void BinaryTree<TreeItemType>::attachLeft(const TreeItemType& newitem)
{
	if (isEmpty())
		throw TreeException("TreeException: ������ �����");
	else if (root->leftChildPtr != NULL)
		throw TreeException("TreeException: ���������� ����� ��������� ����������");
	else
	{
		root->leftChildPtr = new TreeNode<TreeItemType>(newitem, NULL, NULL);
		if (root->leftChildPtr == NULL)
			throw TreeException("TreeException: ���������� �������� ������ ");
	}
}

template <class TreeItemType>
void BinaryTree<TreeItemType>::attachRight(const TreeItemType& newitem)
{
	if (isEmpty())
		throw TreeException("TreeException: ������ �����");
	else if (root->rightChildPtr != NULL)
		throw TreeException("TreeException: ���������� ���������� ������ ��������� ");
	else
	{
		root->rightChildPtr = new TreeNode<TreeItemType>(newitem, NULL, NULL);
		if (root->rightChildPtr == NULL)
			throw TreeException("TreeException: ���������� �������� ������");
	}
}

template <class TreeItemType>
void BinaryTree<TreeItemType>::attachLeftSubtree(BinaryTree& leftTree)
{
	if (isEmpty())
		throw TreeException("TreeException: ������ �����");
	else if (root->leftChildPtr != NULL)
		throw TreeException("TreeException: ���������� ���������� ����� ���������");
	else
	{
		root->leftChildPtr = leftTree.root;
		leftTree.root = NULL;
	}
}

template <class TreeItemType>
void BinaryTree<TreeItemType>::attachRightSubtree(BinaryTree& rightTree)
{
	if (isEmpty())
		throw TreeException("TreeException: ������ �����");
	else if (root->rightChildPtr != NULL)
		throw TreeException("TreeException: ���������� ���������� ������ ���������");
	else
	{
		root->rightChildPtr = rightTree.root;
		rightTree.root = NULL;

	}
}

template <class TreeItemType>
void BinaryTree<TreeItemType>::detachLeftSubtree(BinaryTree& leftTree)
{
	if (isEmpty())
		throw TreeException("TreeException: ������ �����");
	else if (root->leftChildPtr == NULL)
		throw TreeException("TreeException: ������ ��������� �� ����������");
	else
	{
		leftTree = BinaryTree<TreeItemType>(root->leftChildPtr);
		root->leftChildPtr = NULL;
	}
}

template <class TreeItemType>
void BinaryTree<TreeItemType>::detachRightSubtree(BinaryTree& rightTree)
{
	if (isEmpty())
		throw TreeException("TreeException: ������ �����");
	else if (root->rightChildPtr == NULL)
		throw TreeException("TreeException: ������� ��������� �� ����������");
	else
	{
		rightTree = BinaryTree<TreeItemType>(root->rightChildPtr);
		root->rightChildPtr = NULL;
	}
}

template <class TreeItemType>
BinaryTree<TreeItemType> BinaryTree<TreeItemType>::getLeftSubtree() const
{
	TreeNode<TreeItemType> *subTreePtr;
	if (isEmpty())
		return BinaryTree();
	else
	{
		copyTree(root->leftChildPtr, subTreePtr);
		return BinaryTree<TreeItemType>(subTreePtr);
	}
}

template <class TreeItemType>
BinaryTree<TreeItemType> BinaryTree<TreeItemType>::getRightSubtree() const
{
	TreeNode<TreeItemType> *subTreePtr;
	if (isEmpty())
		return BinaryTree();
	else
	{
		copyTree(root->rightChildPtr, subTreePtr);
		return BinaryTree<TreeItemType>(subTreePtr);
	}
}

template <class TreeItemType>
void BinaryTree<TreeItemType>::preorderTraverse(void(*visit)(TreeItemType &anitem))
{
	preorder(root, visit);
}

template <class TreeItemType>
void BinaryTree<TreeItemType>::inorderTraverse(void(*visit)(TreeItemType &anitem))
{
	inorder(root, visit);
}

template <class TreeItemType>
void BinaryTree<TreeItemType>::postorderTraverse(void(*visit)(TreeItemType &anitem))
{
	postorder(root, visit);
}

template <class TreeItemType>
BinaryTree<TreeItemType>& BinaryTree<TreeItemType>::operator=(const BinaryTree& rhs)
{
	if (this != &rhs)
	{
		destroyTree(root);
		copyTree(rhs.root, root);
	}
	return *this;
}

template <class TreeItemType>
void BinaryTree<TreeItemType>::copyTree(TreeNode<TreeItemType> *treePtr, TreeNode<TreeItemType> *& newTreePtr) const
{
	if (treePtr != NULL)
	{
		newTreePtr = new TreeNode<TreeItemType>(treePtr->item, NULL, NULL);
		if (newTreePtr == NULL)
			throw TreeException("TreeException: ���������� �������� ������");
		copyTree(treePtr->leftChildPtr, newTreePtr->leftChildPtr);
		copyTree(treePtr->rightChildPtr, newTreePtr->rightChildPtr);
	}
	else
		newTreePtr = NULL;
}

template <class TreeItemType>
void BinaryTree<TreeItemType>::destroyTree(TreeNode<TreeItemType> *& treePtr)
{
	if (treePtr != NULL)
	{
		destroyTree(treePtr->leftChildPtr);
		destroyTree(treePtr->rightChildPtr);
		delete treePtr;
		treePtr = NULL;
	}
}

template <class TreeItemType>
TreeNode<TreeItemType> *BinaryTree<TreeItemType>::rootPtr() const
{
	return root;
}

template <class TreeItemType>
void BinaryTree<TreeItemType>::setRootPtr(TreeNode<TreeItemType> *newRoot)
{
	root = newRoot;
}

template <class TreeItemType>
void BinaryTree<TreeItemType>::getChildPtrs(TreeNode<TreeItemType> *nodePtr, TreeNode<TreeItemType> *& leftPtr, TreeNode<TreeItemType> *& rightPtr) const
{
	leftPtr = nodePtr->leftChildPtr;
	rightPtr = nodePtr->rightChildPtr;
}

template <class TreeItemType>
void BinaryTree<TreeItemType>::setChildPtrs(TreeNode<TreeItemType> *nodePtr, TreeNode<TreeItemType> *leftPtr, TreeNode<TreeItemType> *rightPtr)
{
	nodePtr->leftChildPtr = leftPtr;
	nodePtr->rightChildPtr = rightPtr;
}

template <class TreeItemType>
void BinaryTree<TreeItemType>::preorder(TreeNode<TreeItemType> *treePtr, void(*visit)(TreeItemType &anitem))
{
	if (treePtr != NULL)
	{
		visit(treePtr->item);
		preorder(treePtr->leftChildPtr, visit);
		preorder(treePtr->rightChildPtr, visit);
	}
}

template <class TreeItemType>
void BinaryTree<TreeItemType>::inorder(TreeNode<TreeItemType> *treePtr, void(*visit)(TreeItemType &anitem))
{
	if (treePtr != NULL)
	{
		inorder(treePtr->leftChildPtr, visit);
		visit(treePtr->item);
		inorder(treePtr->rightChildPtr, visit);
	}
}

template <class TreeItemType>
void BinaryTree<TreeItemType>::postorder(TreeNode<TreeItemType> *treePtr, void(*visit)(TreeItemType &anitem))
{
	if (treePtr != NULL)
	{
		postorder(treePtr->leftChildPtr, visit);
		postorder(treePtr->rightChildPtr, visit);
		visit(treePtr->item);
	}
}