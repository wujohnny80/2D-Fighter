#ifndef _QuadTree_H_
#define _QuadTree_H_

#include <iostream>
#include <vector>

#include "Collider.h"
#include "GameObject.h"
#include "Rect.h"

class QuadTree
{
public:
	QuadTree();
	~QuadTree();

	void Initialize(int boundX, int boundY);
	void Insert(Collider* col);
	void Clear();
	void Update();

private:	
	enum {TL, TR, BL, BR};
	class Node
	{
	public:
		Node();
		~Node();
		
		void Insert(Collider* col);
		void Clear();
		void Update();
		void Split();
		bool InBounds(Collider* col);
		
		const unsigned int kMaxObjs;
		const float kMinW;
		const float kMinH;
		bool mSplit;
		Rect mBounds;
		std::vector<Collider*> mCols;
		std::vector<Node*> mChildren;

	}; // End of Class Node

	Node mRoot;
}; // End of Class QuadTree

#endif //#ifndef _QuadTree_H_