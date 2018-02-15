#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>
#include <limits>


template <class Etype>
class TreeNode
{
public:
	Etype element;  // value in node
	TreeNode *left;  // left child
	TreeNode *right; // right child
	TreeNode *parent; // parent of node
    int depth; // increases by 1 if it has both children
	TreeNode(Etype e = 0, TreeNode *l = NULL, TreeNode *r = NULL, TreeNode *p = NULL, int d = NULL) :
		element(e), left(l), right(r), parent(p), depth(d){ }
};

template <class Etype>
class BinaryTree
{
protected:
	TreeNode<Etype> *root;  // root of tree
	Etype LOW;   // Smallest possible value stored in tree
	Etype HIGH;  // Largest possible value stored in tree
	bool insert(Etype & x, TreeNode<Etype> * & t, TreeNode<Etype>*  p);

    void printTree(TreeNode<Etype> * t, std::string indent, int currDepth = 0, int maxDepth = std::numeric_limits<int>::max());

	TreeNode<Etype> * findFirst(TreeNode<Etype> * t) const;
	TreeNode<Etype> * find(TreeNode<Etype> * curr, Etype value)const;
	int size(TreeNode<Etype> *t) const;
	TreeNode <Etype>* currentNode;
    void fall(TreeNode<Etype> *root); //deletes all the leaf nodes
    void printInOrder(TreeNode<Etype> *root); //prints tree inorder
    TreeNode<Etype>* successor(TreeNode<Etype> *root); //find the successor to currentNode
    Etype closestCommon(TreeNode<Etype>, TreeNode<Etype>); //finds first common ancestor
    void flip(TreeNode<Etype> * root);//switches the sides of the tree
    int widthHT(TreeNode<Etype>* ptr, int& height, int&width); // finds the width of the tree
    bool isBST(TreeNode<Etype>* ptr); //determines whether a binary tree is a BST or not
    void makeEmpty(TreeNode<Etype>* root); //deletes an entire tree
    bool buildFromPreorder(Etype & x, TreeNode<Etype> * & t, TreeNode<Etype>*  p);//builds tree from preorder traversal
    void perfectBalance(TreeNode<Etype>*& root, Etype *list, int beg, int fin, TreeNode<Etype>* parent = NULL);//builds a tree that is balanced
    void setDepth(TreeNode<Etype>* root);//assigns the depth for all the nodes in the tree
    void getMaxDepth(TreeNode<Etype>* root,TreeNode<Etype>* & max);//finds the max depth in the tree
public:
	/* Return the leftmost value in the tree.  Set a local currentNode to that node.*/
	Etype getFirst() {
		currentNode = findFirst(root);
		if (currentNode == NULL) return LOW;
		return currentNode->element;
	}

    bool isBST() {return isBST(root);};
    
    //prints message inputed and calls the printInOrder function to print the tree
	void printShort(std::string message)
    {
        std::cout << message << std::endl;
        printInOrder(root);
    }
    
    
	BinaryTree(Etype low = 0, Etype high = 0) : root(NULL) {
		LOW = low;
		HIGH = high;
	}

    void makeEmpty() {makeEmpty(root);};
	//calls private function successor and sets currentNode to the successor
    void successor()
    {
        currentNode = successor(currentNode);
    }
    
    //initializes width and height and calls the widthHT function. returns width
    int width()
    {
        int width = 0;
        int height = 0;
        widthHT(root, height, width);
        return width;
    };
    
    //finds the max depth and couts the root and depth
    void getMaxCompleteSubtree()
    {
        //std::cout << "In get Max subtree " <<std::endl;
        TreeNode<Etype>* max = root;
        setDepth(root);
        //std::cout << "out of in depth" << std::endl;
        getMaxDepth(root,max);
        //std::cout << "out of in max " << std::endl;
        std::cout << "Max tree root: " << max->element << std::endl << "Max Depth: " << max->depth << std::endl;
    };

    void perfectBalance(Etype *list, int beg, int fin)
    {
        perfectBalance(root, list, beg, fin);
    };
    
    //calls the protected function fall
    void fall() {fall(root);};
    void flip() {flip(root);};
	Etype closestCommon(Etype t1, Etype t2);
    
    void buildFromPreorder(Etype* list, int size)
    {
        for(int i = 0; i < size; i+=2)
        {
            buildfrompreorder(list[i]);
        }
    };

	//Print the tree preceeded by the "msg".
	// Print the tree to depth "depth"
	// Print the whole tree if no depth is specified
    void  printTree(std::string msg, int depth = std::numeric_limits<int>::max())
	{
		std::cout << std::endl << msg << std::endl;
		printTree(root, "", 0, depth);
	}

	//Insert item x into the tree using BST ordering
	virtual bool insert(Etype & x) { return insert(x, root, NULL); }
    
    virtual bool buildfrompreorder(Etype & x) {return buildFromPreorder(x,root,NULL);}
//    virtual bool buildfrompreorder(Etype& x)
//    {
//        bool temp = buildFromPreorder(x, root, NULL);
//        return temp;
//    }

	/*Return the value of the currentNode */
	Etype getCurrNodeValue( )
	{
		if (currentNode == NULL) return LOW;
		return currentNode->element;
	}

};

//----------------------------------------My-Code-------------------------------------

//prints while traversing the tree inorder
//O(n)
template <class Etype>
void BinaryTree<Etype>::printInOrder(TreeNode<Etype> *root)
{
    if (root == nullptr)
    {
        return;
    }
    printInOrder(root->left);
    std::cout << root->element << std::endl;
    printInOrder(root->right);
}

//traverses the tree preorder and deletes all the leaf nodes
//O(n)
template <class Etype>
void BinaryTree<Etype>::fall(TreeNode<Etype> *root)
{
    if (root == nullptr)
    {
        return;
    }
    if (root->left != nullptr)
    {
        if (root->left->left == nullptr && root->left->right == nullptr)
        {
            delete root->left;
            root->left = nullptr;
        }
        else
        {
            fall(root->left);
        }
    }
    if (root->right != nullptr)
    {
        if (root->right->left == nullptr && root->right->right == nullptr)
        {
            delete root->right;
            root->right = nullptr;
        }
        else
        {
            fall(root->right);
        }
    }
}

//finds next greatest number for currentNode
//O(n)
template <class Etype>
TreeNode<Etype>* BinaryTree<Etype>::successor(TreeNode<Etype>* ptr)
{
    if (ptr == nullptr)
    {
        return nullptr;
    }
    
    if (ptr->right != nullptr)
    {
        TreeNode<Etype>* temp = ptr->right;
        while(temp->left != nullptr)
        {
            temp = temp->left;
        }
        return temp;
    }
    else
    {
        TreeNode<Etype>* temp = ptr->parent;
        while(temp->element < ptr->element && temp != nullptr)
        {
            temp = temp->parent;
        }
        return temp;
    }
    
}


/*Uses the find function to find the node in the tree, then creates a vector from the node that shows its path
 back to the root. Then finds and returns the common number between the two vectors*/
//O(log(n))
template <class Etype>
Etype BinaryTree<Etype>::closestCommon(Etype t1, Etype t2)
{
    TreeNode<Etype> *ptr1 = find(root, t1);
    TreeNode<Etype> *ptr2 = find(root, t2);
    
    if((ptr1==nullptr) || (ptr2 == nullptr))
    {
        return NULL;
    }
    
    std::vector<TreeNode<Etype>*> info;
    std::vector<TreeNode<Etype>*> info2;
    
    info.push_back(ptr1);
    info2.push_back(ptr2);
    TreeNode<Etype>* search = ptr1->parent;
    while (search != nullptr)
    {
        info.push_back(search);
        search = search->parent;
    }
    
    TreeNode<Etype>* search2 = ptr2->parent;
    while (search2 != nullptr)
    {
        info2.push_back(search2);
        search2 = search2->parent;
    }
    
    
    for (int i = 0; i < info.size(); i++)
    {
        for (int j = 0; j < info2.size(); j++)
        {
            if(info[i]->element == info2[j]->element)
            {
                return info2[j]->element;
            }
        }
    }
    
    return NULL;
}

//moves all the pointers from the left to the right and vis versa
//O(n)
template <class Etype>
void BinaryTree<Etype>::flip(TreeNode<Etype>* ptr)
{
    if (ptr == nullptr)
    {
        return;
    }
    flip(ptr->left);
    flip(ptr->right);
    
    TreeNode<Etype>* temp = ptr->right;
    ptr->right = ptr->left;
    ptr->left = temp;
}

//Finds the longest path between the lowest leaf on the right and left side of the tree
//O(n)
template <class Etype>
int BinaryTree<Etype>::widthHT(TreeNode<Etype>* ptr, int& height, int& width)
{
    int widthLeft;
    int widthRight;
    int heightLeft;
    int heightRight;
    
    if (ptr == nullptr)
    {
        height = -1;
        width = 0;
        return height;
    }
    
    widthHT(ptr->left, heightLeft, widthLeft);
    widthHT(ptr->right, heightRight, widthRight);
    
    height = std::max(heightLeft,heightRight) + 1;
    width = std::max((heightLeft+heightRight + 2),std::max(widthRight, widthLeft));
    
    return width;
}

//creates a tree in preorder traversal
//O(n)
template <class Etype>
bool BinaryTree<Etype>::buildFromPreorder(Etype & data, TreeNode<Etype> * & t, TreeNode<Etype>*  parent)
{
    if (t == NULL)
    {
        t = new TreeNode<Etype>(data, NULL, NULL, parent);
        if (t == NULL)
        {
            return false;
        }
        else
        {
            return true;
        }
    }
    if (data < t->element)
    {
        return insert(data, t->right, t);
    }
    else
    {
        return insert(data, t->left, t);
    }
    
}

//determines if the tree is a binary tree or not
//O(n)
template <class Etype>
bool BinaryTree<Etype>::isBST(TreeNode<Etype>* ptr)
{
    if (ptr == nullptr)
    {
        return true;
    }
    
    if (isBST(ptr->left)&&(isBST(ptr->right)))
    {
        return true;
    }
    else
    {
        return false;
    }
    
    if (ptr->left != nullptr && (ptr->element < ptr->left->element))
    {
        return false;
    }
    
    if (ptr->right != nullptr && (ptr->element > ptr->right->element))
    {
        return false;
    }
    
    
}

//clears out the tree
//O(n)
template <class Etype>
void BinaryTree<Etype>::makeEmpty(TreeNode<Etype>* ptr)
{
    if (ptr == nullptr)
    {
        return;
    }
    
    if(ptr->left != nullptr)
    {
        makeEmpty(ptr->left);
    }
    if(ptr->right != nullptr)
    {
        makeEmpty(ptr->right);
    }
    
    delete ptr;
    ptr = nullptr;
   
}

//balances the tree, so the height is as even as possible
//O(n)
template <class Etype>
void BinaryTree<Etype>::perfectBalance(TreeNode<Etype>* & ptr, Etype *list, int beg, int fin, TreeNode<Etype>* parent)
{
    if(beg <= fin)
    {
        int temp = (fin + beg)/2;
        
        ptr = new TreeNode<Etype>(list[temp], NULL, NULL, parent);
        
        perfectBalance(ptr->left, list, beg, temp - 1, ptr);
        perfectBalance(ptr->right, list, temp + 1, fin, ptr);
    }
}

//sets all the nodes in the tree to the correct depth
//O(n)
template <class Etype>
void BinaryTree<Etype>::setDepth(TreeNode<Etype>* ptr)
{
    //std::cout << "In Set Depth" << std::endl;
    if((ptr == nullptr) || (ptr->left == nullptr) || (ptr->right == nullptr))
    {
        return;
    }
    
    setDepth(ptr->left);
    setDepth(ptr->right);
    
    ptr->depth = std::min(ptr->left->depth, ptr->right->depth) + 1;
    
}

//finds the biggest depth in the tree
//O(n)
template <class Etype>
void BinaryTree<Etype>::getMaxDepth(TreeNode<Etype>* ptr,TreeNode<Etype>* &max)
{
    if (ptr == nullptr)
    {
        return;
    }
    
    if(ptr->depth > max->depth)
    {
        max = ptr;
    }
    
    getMaxDepth(ptr->left,max);
    getMaxDepth(ptr->right, max);
    
}

//---------------------------------------------------------------------------------------

// return the number of nodes in the tree rooted at t
template <class Etype>
int BinaryTree<Etype>::size(TreeNode<Etype> *t) const
{
	if (t == NULL) return 0;
	return (1 + size(t->left) + size(t->right));
}


//Print the contents of tree t
// Indent the tree bby the string "indent"
// Print the tree to a depth of "depth" given "currdepth" is the depth of t
template <class Etype>
void BinaryTree<Etype>::printTree(TreeNode<Etype> *t, std::string indent, int currdepth, int depth)
{
	if (t == NULL || currdepth>depth) return;
	printTree(t->right, indent + "  ", currdepth + 1, depth);
	if (t->parent != NULL)
        std::cout << indent << t->element << "(" << t->parent->element << ")" << std::endl;
	else
        std::cout << indent << t->element << "( no parent)" << std::endl;
	printTree(t->left, indent + "  ", currdepth + 1, depth);
}

// insert inserts data into the tree rooted at t
// parent is the parent of t
// Returns true if insertion is successful 
// Code is O(log n) for a balanced tree as each level is accessed once
// This inserts as if we wanted to created a binary search tree.
template <class Etype>
bool BinaryTree<Etype>::insert(Etype & data, TreeNode<Etype> * & t, TreeNode<Etype> *  parent)
{
	if (t == NULL)
	{  // cout << "inserting " << data << endl;
		t = new TreeNode<Etype>(data, NULL, NULL, parent);
		if (t == NULL) return false;
		return true;
	}
	if (data < t->element) return insert(data, t->left, t);
	return insert(data, t->right, t);
}

// find seaches for data in the tree rooted at curr
// Returns the node if the find is successful, NULL otherwise
// Code is O(log n) for a balanced tree as each level is accessed once
template <class Etype>
TreeNode<Etype> * BinaryTree<Etype>::find(TreeNode<Etype> * curr, Etype value)const
{
    if (curr == nullptr)
    {
        return nullptr;
    }
    
    if (curr->element == value)
    {
        return curr;
    }
    TreeNode<Etype>* tempL = find(curr->left,value);
    if(tempL != nullptr)
    {
        return tempL;
    }
    else
    {
        return find(curr->right,value);
    }
    
}

// Find the leftmost node in a tree rooted at t.
template <class Etype>
TreeNode<Etype> * BinaryTree<Etype>::findFirst(TreeNode<Etype> * t) const
{
	if (t == nullptr) return t;
	TreeNode<Etype>* s = t;
	for (; s->left != NULL; s = s->left)
		;
	return s;
}


