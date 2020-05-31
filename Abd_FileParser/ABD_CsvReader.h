#pragma once
#include "ABD_TrdPos.h"  
#include "CsvLine.h"
#include <vector>    
 						    
#define ABD_CSV_DELIM ','	 
#define ABD_CSV_DELIM_ESCAPED "&#44;" // comma html escape ot 
	 	  
class CABD_TradesPositions: ABD_TRDPOS, CCsvLine 
{	
public:
	CABD_TradesPositions(std::string& ssLine);
	   
	bool DeserializeCsvLine(std::string& ssLine);

	std::string SerializeToCsvLine();
					 
	std::string GetError(){ return m_sError; };

	bool IsValid() {return m_bValid;}

private:   
	bool m_bValid;
	std::string m_sError;  
};
  
class ABD_CsvReader
{
public:
	ABD_CsvReader();
	virtual ~ABD_CsvReader(void);

	// override with custrom logic like processing the CABD_TradesPositions records
	// at the same time while reading the file
	virtual bool Parse(const std::string sFile, bool bReadHdr);
	std::string GetLastError(){ return m_sLastError; }		

private:
	bool ParseHdr(const std::string& line);

public:
	// the parsed csv data stroed in the memory
	ABD_TRDPOS_HDR m_recAdibeHdr;
	std::vector<CABD_TradesPositions*> m_vCsvLines; 

private:			 
	std::string m_sLastError;	 
};
	   
