#ifndef _BST_H
#define _BST_H

#include <utility>
#include <vector>

#include "fiUtil.h"

namespace FI { namespace DATA {

template<class K, class V>
class BinarySearchTree
{
public:

    struct Node 
    {
        Node():
            parent(nullptr),
            left(nullptr),
            right(nullptr)
        {}

        std::pair<K,V> data;

        Node    *parent,
                *left,
                *right;
    };

    BinarySearchTree() :
    	m_pTree(nullptr),
    	m_size(0),
		m_depth(0)
	{}

    ~BinarySearchTree()
	{
		clear();
	}

    inline std::pair<K,V>* find(const K& key)
	{
		if(m_pTree)
		{
			return rFind(key, m_pTree)->data;
		}
	}

    inline void insert(const std::pair<K,V>& elem)
	{
		rInsert(elem, &m_pTree);
	}

    inline void remove(const K& key)
	{
	}

    inline void clear()
	{
		if(m_pTree)
		{
			rClear(&m_pTree);
		}
	}

    inline std::pair<K,V>* min()
	{
	}

    inline std::pair<K,V>* max()
	{

	}

	inline void print()
	{
		if(m_pTree)
		{
			rPrint(m_pTree, 0);
		}
		else
		{
			FI::LOG("tree is empty");
		}
	}

	inline void inOrderPrint()
	{
		if(m_pTree)
		{
			rInOrder(m_pTree);
			std::cout << std::endl;
		}
	}

    inline size_t size()
	{
		return m_size;
	}

private:

	inline Node* rFind(const K& key, Node* node)
	{
		if(key == node->data.first)
		{
			return node;
		}
		else if(key < node->data.first)
		{
			return rFind(key, node->left);
		}
		else
		{
			return rFind(key, node->right);
		}
	}

    inline void rInsert(const std::pair<K,V>& elem, Node** _node)
	{
		Node *node = *_node;

		if(!node)
		{
			*_node = new Node;
			Node *n = *_node;
			n->parent = nullptr;
			n->left = nullptr;
			n->right = nullptr;
			n->data = elem;
			m_size++;
		}
		else
		{
			m_depth++;
			if(elem.first < node->data.first)
			{
				rInsert(elem, &node->left);
			}
			else if(elem.first > node->data.first)
			{
				rInsert(elem, &node->right);
			}
			else
			{
				// duplicate key - do nothing
			}
		}
	}

    inline void rClear(Node** _node)
	{
		Node *node = *_node;
		if(node)
		{
			rClear(&node->left);
			rClear(&node->right);
	
			delete node;
			if(node->left!=nullptr)
            	node->left=nullptr;
        	if(node->right!=nullptr)
            	node->right=nullptr;
			*_node = nullptr;
		}
	}

	// print the tree sideways (root at left)
	inline void rPrint(Node* node, size_t indent)
	{
		const int kCOUNT = 5;

		if (node == NULL)
		{
			return;
		}
	
		indent += kCOUNT;
	
		rPrint(node->right, indent);
	
		for (int i = kCOUNT; i < indent; i++)
		{
			std::cout << " ";
		}
		std::cout << node->data.first << std::endl;
	
		// Process left child
		rPrint(node->left, indent);
	}

	//print in order
	inline void rInOrder(Node* node)
	{
		if(node)
		{
			rInOrder(node->left);
			std::cout << node->data.first << " ";
			rInOrder(node->right);
		}
	}

    Node* m_pTree;
    size_t m_size;
	size_t m_depth;
};

} /*NS DATA*/
} /*NS FI*/ 

#endif /*_BST_H*/