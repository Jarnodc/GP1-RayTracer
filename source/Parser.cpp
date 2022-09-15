//---------------------------
// Includes
//---------------------------
#include "Parser.h"
#include "MaterialManager.h"
#include <sstream>
#include <fstream>
#include <iostream>

//---------------------------
// Static datamembers
//---------------------------
Parser* Parser::m_pInstance = nullptr;

//---------------------------
// Constructor(s) & Destructor
//---------------------------

Parser::~Parser()
{

}

//---------------------------
// Member functions
//---------------------------

TriangleMesh* Parser::GetTriangleMesh(const string& filePath)
{
	std::ifstream fileStream{ filePath.c_str() };

	if (!fileStream)
	{
		cerr << "Parser::GetTriangleMesh(..), failed to load vertices from file " << filePath << endl;
		return nullptr;
	}

	vector<FVector3> verticesBuffer{};
	vector<IPoint3> idxBuffer{};


	string objLine;
	while (!fileStream.eof())
	{
		getline(fileStream, objLine);
		if (objLine.find("v  ", 0) == 0)
			verticesBuffer.push_back(ReadVertex(objLine));
		else if (objLine.find("f ", 0) == 0)
			idxBuffer.push_back(ReadIdx(objLine));
	}

	TriangleMesh* mesh = new TriangleMesh({}, MaterialManager::GetInstance()->GetMaterials()[7], verticesBuffer, idxBuffer, { 1,0,0,0, 0,1,0,0, 0,0,1,0, 0,2,0,1 });
	return mesh;
}

Parser* Parser::GetInstance()
{
	if (m_pInstance == nullptr)
		m_pInstance = new Parser();
	return m_pInstance;
}

FVector3 Parser::ReadVertex(const string& line) const
{
	const int arrSize{ 3 };
	float vector3fArr[arrSize]{};
	stringstream sstream{ line.substr(3) };
	string vector3fPart;
	for (int idx{}; idx < arrSize; ++idx) 
	{
		if(getline(sstream, vector3fPart, ' '))
			vector3fArr[idx] = stof(vector3fPart);
	}
	return { vector3fArr[0], vector3fArr[1], vector3fArr[2] };
}

IPoint3 Parser::ReadIdx(const string& line) const
{
	const int arrSize{ 3 };
	int idxPoint[arrSize]{};
	stringstream sstream{ line.substr(2) };
	string iPoint3Part;
	for (int idx{}; idx < arrSize; ++idx)
	{
		if (getline(sstream, iPoint3Part, ' '))
			idxPoint[idx] = stoi(iPoint3Part);
	}

	return { idxPoint[0] - 1, idxPoint[1] - 1, idxPoint[2] - 1};
}


