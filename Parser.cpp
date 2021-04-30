#include "Parser.hpp"

#include <fstream>

#include "DiracMacros.hpp"


namespace Dirac
{


std::string convertToString(const std::string& tAddress)
{
	std::fstream lInputFile(tAddress);

	std::string lAssertMessage = "Could not open file at " + tAddress;
	DIRAC_ASSERT(lInputFile.is_open(), lAssertMessage)

	std::string fileContent;
	std::string lLine;
	while (getline(lInputFile, lLine))
	{
		fileContent.append(lLine);
		fileContent.append("\n");
	}
	lInputFile.close();

	fileContent.append("\0");

	return fileContent; 
}


Words splitLine(const std::string& tLine, const std::string& tDelimiter)
{

	Words lWords;

	std::size_t lStartPosition = 0;
	std::size_t lEndPosition = 0;

	while (lEndPosition != std::string::npos)
	{
		lEndPosition = tLine.find(tDelimiter, lStartPosition);
		lWords.push_back(tLine.substr(lStartPosition, lEndPosition - lStartPosition));
		lStartPosition = lEndPosition + 1;
	}
	return lWords; 
}


Words tokenize(const std::string& tLine)
{
	Words lWords;

	std::size_t lStartPosition 	= 0;
	std::size_t lEndPosition 	= 0;
	std::size_t lEndPosition1 	= 0;

	while (lEndPosition != std::string::npos)
	{
		lEndPosition = tLine.find(" ", lStartPosition);
		lEndPosition1 = tLine.find("\t", lStartPosition);
		
		// find the smallest
		lEndPosition = (lEndPosition > lEndPosition1? lEndPosition1: lEndPosition);
		
		std::string lWord = tLine.substr(lStartPosition, lEndPosition - lStartPosition);
		
		// multiple spaces or tabs
		if (lWord.size() != 0)
		{
			lWords.push_back(lWord);
		}
		lStartPosition = lEndPosition + 1;
	}
	return lWords; 

}



Words findUniforms(const std::string& tAddress)
{
	std::ifstream lInputFile(tAddress);

	std::string lAssertMessage = "Could not open file at " + tAddress;
	DIRAC_ASSERT(lInputFile.is_open(), lAssertMessage)
		
	Words lUniforms;
	std::string lLine;
	while (getline(lInputFile, lLine))
	{
		Words lLineWords = tokenize(lLine);
		
		if (lLineWords.size() != 0 and lLineWords[0] == "uniform")
		{
			lUniforms.push_back(lLineWords.back().substr(0, lLineWords.back().size() - 1));
		}
	}

	return lUniforms;

}


};
