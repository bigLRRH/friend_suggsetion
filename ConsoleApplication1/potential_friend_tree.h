#ifndef _potential_friend_tree
#define _potential_friend_tree

#include "potential_friend.h"
#include "friend_suggestion_list.h"

enum COLOR
{
	RED,BLACK
};

struct potential_friend_tree_Node
{
	potential_friend element;
	potential_friend_tree_Node* leftChild,
		* rightChild,
		* parent;
	COLOR color;
	potential_friend_tree_Node(int the_id)
	{
		parent=leftChild = rightChild = nullptr;
		color = BLACK;
	}
	potential_friend_tree_Node(potential_friend_tree_Node* the_parent)
	{
		parent = the_parent;
		leftChild = rightChild = nullptr;
		color = BLACK;
	}
	potential_friend_tree_Node(int the_id, potential_friend_tree_Node*the_parent)
	{
		element = potential_friend(the_id);
		parent = the_parent;
		leftChild = new potential_friend_tree_Node(this);
		rightChild = new potential_friend_tree_Node(this);
		color = RED;
	}
	potential_friend_tree_Node(potential_friend the_element,potential_friend_tree_Node* the_leftChild,potential_friend_tree_Node*the_rightChild,potential_friend_tree_Node*the_parent,COLOR the_color)
	{
		element = the_element;
		leftChild = the_leftChild;
		rightChild = the_rightChild;
		parent = the_parent;
		color = the_color;
	}
};

class potential_friend_tree
{
public:
	potential_friend_tree();
	~potential_friend_tree();
	void free(potential_friend_tree_Node*);

	bool empty() const { return treeSize == 0; }
	int size() const { return treeSize; }

	potential_friend* find(int);
	potential_friend_tree_Node* indexOf(int);
	void insert(potential_friend_tree_Node**, int);
	void push(int);
	void erase(int);

	void convert_to_fsl(friend_suggestion_list* _fsl)
	{
		convert_to_fsl(_fsl, root);
	}
	void convert_to_fsl(friend_suggestion_list* _fsl, potential_friend_tree_Node* t)
	{
		if (!t || t->element.id == -1)return;
		convert_to_fsl(_fsl, t->leftChild);
		_fsl->insert(_fsl->size(), t->element);
		convert_to_fsl(_fsl, t->rightChild);
	}
protected:
	potential_friend_tree_Node* root;
	int treeSize;

	void leftRotate(potential_friend_tree_Node*r)
	{
		potential_friend_tree_Node* s = r->rightChild;
		potential_friend_tree_Node* t = s->leftChild;
		s->leftChild = r;
		r->rightChild = t;
		s->parent = r->parent;
		r->parent = s;
		t->parent = r;
	}
	void rightRotate(potential_friend_tree_Node*r)
	{
		potential_friend_tree_Node* s = r->leftChild;
		potential_friend_tree_Node* t = s->rightChild;
		s->rightChild = r;
		r->leftChild = t;
		s->parent = r->parent;
		r->parent = s;
		t->parent = r;
		
	}
};

potential_friend_tree::potential_friend_tree()
{
	root = nullptr;
	treeSize = 0;
}

potential_friend_tree::~potential_friend_tree()
{
	free(root);
}

void potential_friend_tree::free(potential_friend_tree_Node* t)
{
	if (t != nullptr)
	{
		free(t->leftChild);
		free(t->rightChild);
		delete t;
	}
}

potential_friend* potential_friend_tree::find(int the_id)
{
	potential_friend_tree_Node* p = indexOf(the_id);
	if (p)
		return &p->element;
	else
		return nullptr;
}

potential_friend_tree_Node* potential_friend_tree::indexOf(int the_id)
{
	potential_friend_tree_Node* p = root;
	while (p)
	{
		if (the_id < p->element.id)
			p = p->leftChild;
		else if (the_id > p->element.id)
			p = p->rightChild;
		else
			break;
	}
	return p;
}


void potential_friend_tree::push(int the_id)
{
	if (treeSize == 0)
	{
		root = new potential_friend_tree_Node(the_id);
		treeSize++;
		return;
	}
	potential_friend_tree_Node* p = indexOf(the_id);
	if (p)
	{
		p->element.weight++;
	}
	else
	{
		p = new potential_friend_tree_Node(the_id,p);
		while (p->parent && p->parent->color == RED)
		{//conflict with RB2
			potential_friend_tree_Node* pu, * gu,* uncle;
			gu = (pu = p->parent)->parent;
			if (pu = gu->leftChild)
				uncle = gu->rightChild;
			else
				uncle = gu->leftChild;

			gu->color = RED;
			if (uncle->color == BLACK)
			{//XYB
				potential_friend_tree_Node* tmp;
				if (pu == gu->leftChild)
				{
					if (p == pu->leftChild)
					{//LLB
						rightRotate(gu);
						pu->color = BLACK;
					}
					else//p == pu->rightChild
					{//LRB
						leftRotate(pu);
						rightRotate(gu);
						p->color = BLACK;
					}
				}
				else//pu == gu->rightChild
				{
					if (p == pu->leftChild)
					{//RLB
						rightRotate(pu);
						leftRotate(gu);
						p->color = BLACK;
					}
					else//p == pu->rightChild
					{//RRB
						leftRotate(gu);
						pu->color = BLACK;
					}
				}
				break;
			}
			else
			{//XYR
				pu->color = BLACK;
				uncle->color = BLACK;
				p = gu;
				continue;
			}
		}
		root->color = BLACK;
		treeSize++;
	}
}

void potential_friend_tree::erase(int the_id)
{
	potential_friend_tree_Node* u = indexOf(the_id),*pu=u;
	if (u && u->element.id == the_id)
	{
		if (u->leftChild && u->leftChild->element.id != -1 && u->rightChild && u->rightChild->element.id != -1)
		{//p有两个孩子
			potential_friend_tree_Node* s = u->leftChild;
			while (u->rightChild && u->rightChild->element.id != -1)
				s = s->rightChild;
			potential_friend_tree_Node* newNode = new potential_friend_tree_Node(s->element, u->leftChild, u->rightChild, u->parent, u->color);
			if (!u->parent)
				root = newNode;
			else
			{
				pu = u->parent;
				if (u = u->parent->leftChild)
					pu->leftChild = newNode;
				else
					pu->rightChild = newNode;
			}

			if (s->parent == u)
				pu = newNode;
			else
				pu = s->parent;
			delete u;
			u = s;
		}
		//p只有一个孩子
		potential_friend_tree_Node* c;
		if (u->leftChild && u->leftChild->element.id != -1)
			c = u->leftChild;
		else
			c = u->rightChild;
		if (u == root)
			root = c;
		else
			if (u == pu->leftChild)
				pu->leftChild = c;
			else
				pu->rightChild = c;
		if (c==root||c->color != u->color)
			c->color = BLACK;
		else
		{
			potential_friend_tree_Node* tmp;
			while (c != root && c->color == BLACK)
			{
				pu = c->parent;
				potential_friend_tree_Node* sibling;
				if (c == pu->leftChild)
				{//L
					sibling = pu->rightChild;
					if (sibling->color == BLACK)
					{//Lb
						if (sibling->leftChild->color == RED || sibling->rightChild->color == RED)
						{//Lb2 or Lb1
							potential_friend_tree_Node* nephew = sibling->leftChild;
							nephew->color = sibling->color;
							sibling->color = pu->color;
							if (sibling->rightChild->color == RED)
							{//Lb1R or Lb2
								leftRotate(pu);
							}
							else
							{//Lb1L
								rightRotate(sibling);
								leftRotate(pu);
							}
							pu->color = BLACK;
							break;
						}
						else
						{//Lb0
							sibling->color = RED;
							c = pu;
						}
					}
					else//uncle->color = RED
					{//Lr
						leftRotate(pu);
						pu->color = RED;
						sibling->color = BLACK;
					}
				}
				else//c == pu->rightChild
				{//R
					sibling = pu->leftChild;
					if (sibling->color == BLACK)
					{//Rb
						if (sibling->leftChild->color == RED || sibling->rightChild->color == RED)
						{//Rb2 or Rb1
							potential_friend_tree_Node* nephew = sibling->leftChild;
							nephew->color = sibling->color;
							sibling->color = pu->color;
							if (sibling->leftChild->color == RED)
							{//Rb1L or Rb2
								rightRotate(pu);
							}
							else
							{//Rb1R
								leftRotate(sibling);
								rightRotate(pu);
							}
							pu->color = BLACK;
							break;
						}
						else
						{//Rb0
							sibling->color = RED;
							c = pu;
						}
					}
					else//sibling->color = RED
					{//Rr
						rightRotate(pu);
						pu->color = RED;
						sibling->color = BLACK;
					}
				}
			}
		}
		root->color = BLACK;
		treeSize--;
		delete u;
	}
}
#endif // !_potential_friend_tree
