#include "QuadTree.h"

QuadTree::QuadTree()
{
}

//----------------------------------------------------------------------------------------------------

QuadTree::~QuadTree()
{
	Clear();
}

//----------------------------------------------------------------------------------------------------
void QuadTree::Initialize(int boundX, int boundY)
{
	mRoot.mBounds.w = (float)boundX;
	mRoot.mBounds.h = (float)boundY;
}

//----------------------------------------------------------------------------------------------------

void QuadTree::Insert(Collider* col)
{
	mRoot.Insert(col);
}

//----------------------------------------------------------------------------------------------------

void QuadTree::Clear()
{
	mRoot.Clear();
}

//----------------------------------------------------------------------------------------------------

void QuadTree::Update()
{
	mRoot.Update();
}

//----------------------------------------------------------------------------------------------------

QuadTree::Node::Node()
	: kMaxObjs(8)
	, kMinW(32)
	, kMinH(32)
	, mSplit(false)
{
	mBounds = Rect();
}

//----------------------------------------------------------------------------------------------------

QuadTree::Node::~Node()
{
	Clear();
}

//----------------------------------------------------------------------------------------------------

void QuadTree::Node::Insert(Collider* col)
{
	if (!mSplit)
	{
		mCols.push_back(col);
		if (mCols.size() > kMaxObjs)
			Split();
	}
	else
	{
		// Assign to the proper quadrants
		for (unsigned int i = 0; i < mChildren.size(); ++i)
		{
			if (mChildren[i]->InBounds(col))
				mChildren[i]->Insert(col);
		}
	}
}

//----------------------------------------------------------------------------------------------------

void QuadTree::Node::Clear()
{
	for(unsigned int i = 0; i < mChildren.size(); ++i)
	{
		delete mChildren[i];
		mChildren[i] = nullptr;
	}
	mChildren.clear();
	mCols.clear();
}

//----------------------------------------------------------------------------------------------------

void QuadTree::Node::Update()
{
	if (mSplit)
	{
		unsigned int s = mChildren.size();
		for (unsigned int i = 0; i < s; ++i)
		{
			mChildren[i]->Update();
		}
	}
	else
	{
		unsigned int s = mCols.size();
		for (unsigned int i = 0; i < s; ++i)
		{
			if (!mCols[i]->IsActive())
				continue;
			for (unsigned int j = i + 1; j < s; ++j)
			{
				if (!mCols[j]->IsActive())
					continue;
				if (mCols[i]->IsColliding(mCols[j]))
				{
					mCols[i]->Owner()->HandleCollision(mCols[j]->Owner());
					mCols[j]->Owner()->HandleCollision(mCols[i]->Owner());
				}
			}
		}			
	}
}

//----------------------------------------------------------------------------------------------------

void QuadTree::Node::Split()
{
	// Ignore split if already reached min bounds;
	if (mBounds.w * 0.5f < kMinW || mBounds.h * 0.5f < kMinH)
		return;

	mSplit = true;
	mChildren.resize(4);

	// Create children
	for (int i = 0; i < 4; ++i)
	{
		mChildren[i] = new Node();
		mChildren[i]->mBounds.x = mBounds.x + (i % 2) * mBounds.w;
		mChildren[i]->mBounds.y = mBounds.y + (i / 2) * mBounds.h;
		mChildren[i]->mBounds.w = mBounds.w * 0.5f;
		mChildren[i]->mBounds.h = mBounds.h * 0.5f;
	}

	// Pass objs to kids
	for (unsigned int i = 0; i < mCols.size(); ++i)
		Insert(mCols[i]);

	mCols.clear();
}

//----------------------------------------------------------------------------------------------------

bool QuadTree::Node::InBounds(Collider* col)
{
	// TODO Check obj's clip
	if (col->PositionTL().x > mBounds.Max().x)	return false;
	if (col->PositionTL().x < mBounds.x)	return false;
	if (col->PositionTL().y > mBounds.Max().y)	return false;
	if (col->PositionTL().y < mBounds.y)	return false;
	return true;
}