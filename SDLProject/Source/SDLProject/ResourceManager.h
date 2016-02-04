//====================================================================================================
// Filename:	ResourceManager.h
// Created by:	Johnny Wu
// Description:	Class for the managing all resources.
//====================================================================================================
#ifndef _RESOURCEMANAGER_H_
#define _RESOURCEMANAGER_H_

#include <map>
#include <string>

#include "Texture.h"

//====================================================================================================
// Class Declarations
//====================================================================================================

class ResourceManager
{
public:
	static ResourceManager& Instance()	{ static ResourceManager instance; return instance; }

	void Initialize();
	void Terminate();

	Texture* GetTexture(std::string textureName);

private:
	ResourceManager();	
	ResourceManager(ResourceManager const&);	// Don't implement
	void operator=(ResourceManager const&);		// Don't implement

	std::map<std::string, Texture*> mpTextureMap;	// Map of all texture resources
	bool mInitialized;								// Init flag
};

#endif // #ifndef _RESOURCEMANAGER_H_