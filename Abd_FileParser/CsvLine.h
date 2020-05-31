#pragma once

std::string STrim(const std::string &s);
void SReplace(std::string& sText, const std::string& sSearch, const std::string& sReplace);

//

class CCsvLine
{
protected:

	CCsvLine(char m_cCellDelimeter, std::string m_sCellEscapedDelimeter);  
	~CCsvLine();
		 
	virtual void AddToCsvLine(std::string& sLine, char* pszCell);

	virtual std::string CellEscape(const char* pszCell);

	virtual std::string CellGetEscapedText(std::string& sCell);
	
	virtual void ScvLineEscape(std::string& line);

	void ReadCell(char* pszCell, size_t nCellSize, std::stringstream& ssLine);
		  
	char GetDelim(){ return m_cCellDelimeter; }
	const std::string& GetSDelim(){ return m_sCellDelimeter; }
	const std::string& GetEscDelim(){ return m_sCellEscapedDelimeter;}

private:
	int m_nCellPos;
	char m_cCellDelimeter;
	std::string m_sCellDelimeter;
	std::string m_sCellEscapedDelimeter;
};