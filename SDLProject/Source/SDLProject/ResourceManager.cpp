//====================================================================================================
// Filename:	ResourceManager.cpp
// Created by:	Johnny Wu
//====================================================================================================
#include "ResourceManager.h"
#include <assert.h>
#include <iostream>
#include <stdio.h>

//====================================================================================================
// Class Definitions
//====================================================================================================

ResourceManager::ResourceManager()
	: mInitialized(false)
{
	// initialize for mpTextureMap
}

//----------------------------------------------------------------------------------------------------

void ResourceManager::Initialize()
{
	assert(!mInitialized);

	// TODO: Load all images in the texture folder
}

//----------------------------------------------------------------------------------------------------

void ResourceManager::Terminate()
{
	assert(mInitialized);

	// Deallocate textures and clear map
	auto mIter = mpTextureMap.begin();
	for (; mIter != mpTextureMap.end(); ++mIter)
	{
		delete mIter->second;
	}

	mpTextureMap.clear();

	// Set flag
	mInitialized = false;
}

//----------------------------------------------------------------------------------------------------

Texture* ResourceManager::GetTexture(std::string fileName)
{
	if (mpTextureMap[fileName] != nullptr)
		return mpTextureMap[fileName];
	else
	{
		Texture* newTexture = new Texture();
		newTexture->Load(fileName.c_str());
		mpTextureMap[fileName] = newTexture;
		return newTexture;
	}
}