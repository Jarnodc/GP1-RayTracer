#pragma once
//-----------------------------------------------------
// Include Files
//-----------------------------------------------------
#include "TriangleMesh.h"
#include <string>

using namespace std;
//-----------------------------------------------------
// Parser Class									
//-----------------------------------------------------
class Parser final
{
public:
	~Parser();			// Destructor

	// -------------------------
	// Copy/move constructors and assignment operators
	// ------------------------- 
	Parser(const Parser& other) {}
	Parser(Parser&& other) noexcept {}
	Parser& operator=(const Parser& other) {}
	Parser& operator=(Parser&& other) noexcept {}

	//-------------------------------------------------
	// Member functions						
	//-------------------------------------------------
	TriangleMesh* GetTriangleMesh(const string& filePath);

	//-------------------------------------------------
	// Static Member functions						
	//-------------------------------------------------
	static Parser* GetInstance();

private:
	//-------------------------------------------------
	// Private member functions								
	//-------------------------------------------------
	Parser() = default;	// Constructor


	//-------------------------------------------------
	// Datamembers								
	//-------------------------------------------------
	FVector3 ReadVertex(const string& line) const;
	IPoint3 ReadIdx(const string& line) const;

	//-------------------------------------------------
	// Static Datamembers								
	//-------------------------------------------------
	static Parser* m_pInstance;
};