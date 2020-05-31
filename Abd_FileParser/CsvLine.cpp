#include "StdAfx.h"
#include "CsvLine.h"
#include <sstream>
#include <cstddef>	    	
#include <algorithm>
#include <cctype>	 
#include "strsafe.h"

std::string STrim(const std::string &s)
{
   auto itFront = std::find_if_not(s.begin(), s.end(), [](int c){return std::isspace(c);} );
   auto itBack = std::find_if_not(s.rbegin(), s.rend(), [](int c){return std::isspace(c);} ).base();
   return (itBack <= itFront ? std::string() : std::string(itFront, itBack));
}
	 
void SReplace(std::string& sText, const std::string& sSearch, const std::string& sReplace)
{
    size_t pos = 0;
    while((pos = sText.find(sSearch, pos)) != std::string::npos)
	{
         sText.replace(pos, sSearch.length(), sReplace);
         pos += sReplace.length();
    }				  
}

CCsvLine::CCsvLine(char cCellDelimeter, std::string sCellEscapedDelimeter) : 
m_nCellPos(0), m_cCellDelimeter(cCellDelimeter), m_sCellEscapedDelimeter(sCellEscapedDelimeter)
{	
	m_sCellDelimeter += m_cCellDelimeter; 
}

CCsvLine::~CCsvLine()
{
}

//virtual 
void CCsvLine::ReadCell(char* pszCell, size_t nCellSize, std::stringstream& ssLine)
{	  
	m_nCellPos++;
	std::string sCell;
	if( pszCell && std::getline(ssLine, sCell, m_cCellDelimeter) )
	{	 						 
		StringCchCopy(pszCell, nCellSize+1, CellGetEscapedText(sCell).c_str() );   
	}
	else
	{
		if(!ssLine.eof())
		{
			std::stringstream ssError;
			ssError	<< "Error in reading cell: " << m_nCellPos;  
			throw std::runtime_error(ssError.str());
		}
	}	  
}

//virtual 
void CCsvLine::AddToCsvLine(std::string& sLine, char* pszCell)
{
	if(sLine.length() != 0) sLine += m_cCellDelimeter;

	sLine.append(CellEscape(pszCell));   
}								   

//virtual 
std::string CCsvLine::CellEscape(const char* pszCell) 
{
	std::string buff(pszCell);
	SReplace(buff, "\"", "\"\"");
	STrim(buff);

	if( strchr(pszCell, ',') )	 		 
		return "\"" + buff + "\"";	 
					 
	return buff;
}

//virtual 
std::string CCsvLine::CellGetEscapedText(std::string& sCell) 
{			
	SReplace(sCell, "\"\"", "\"");
	if(sCell.find(GetEscDelim().c_str()) != std::string::npos && sCell[0] == '"' && sCell[sCell.length()-1] == '"')	    
	{										  
		std::string sFixed = sCell.substr(1, sCell.length() -2);
		SReplace(sFixed, GetEscDelim(), GetSDelim());
		return sFixed; 
	}

	return STrim(sCell);
}

//virtual
void CCsvLine::ScvLineEscape(std::string& line) 
{													   
	std::string::size_type start_position = 0;
	std::string::size_type end_position = 0;	  
 
	for(;;)
	{				    
		start_position = line.find('\"', start_position);

		if (start_position != std::string::npos)
		{
			++start_position;  		  
			end_position = line.find('\"', start_position);
			if (end_position != std::string::npos)
			{
				std::string sForEsc = line.substr(start_position, end_position - start_position);
				std::string sEscpd = sForEsc;	

				SReplace(sEscpd, GetSDelim(), GetEscDelim());
				SReplace(line, sForEsc, sEscpd);  

				start_position = end_position + GetEscDelim().length(); 	 
			}
			else break;
		}
		else break;	  
	}
}