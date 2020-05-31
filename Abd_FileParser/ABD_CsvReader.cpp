#include "StdAfx.h"
#include "ABD_CsvReader.h"
#include <memory>    
#include <string>
#include <fstream>	
#include <sstream>	
#include "strsafe.h"

ABD_CsvReader::ABD_CsvReader()
{													 
}											 
  
ABD_CsvReader::~ABD_CsvReader(void)
{	   			    
	if(  m_vCsvLines.size() > 0 )
	{
		for(UINT i = 0; i <  m_vCsvLines.size(); i++)	  
		{
			if( m_vCsvLines[i] )   
				std::shared_ptr<CABD_TradesPositions> pAuto(m_vCsvLines[i]);	  

			m_vCsvLines[i] = NULL;
		}
		   
		m_vCsvLines.erase(m_vCsvLines.begin(), m_vCsvLines.end());
	}//if
}
		
// vritual
bool ABD_CsvReader::Parse(const std::string sFile, bool bReadHdr)
{  	    
	std::ifstream ifsFile(sFile);
	
	if(errno)
	{
		m_sLastError = strerror(errno);
		return false;
	}			 

	std::string line;
	if(bReadHdr)
	{
		std::getline(ifsFile, line);
		if( ParseHdr( line ) )
			return false;
	}

	while (std::getline(ifsFile, line))
	{	   	 	    
		m_vCsvLines.push_back(new CABD_TradesPositions(line)); 
	}
	 
	return true;
}

bool ABD_CsvReader::ParseHdr(const std::string& line)
{
	size_t size1 = line.size()+1;
	size_t	size2 = sizeof(m_recAdibeHdr)-4; //4 zero terminated char arrays 

	if(line.empty() || line[0] != 'H' || size1 < size2  || (line[1] != 'B' && line[1] != 'R' && line[1] != 'L' && line[1] != 'I' ) )		 
		return false;		   
		    
	m_recAdibeHdr.HeaderIndicator[0] = line[0];
	m_recAdibeHdr.ReportingFirmId[0] = line[1];
	StringCchCopy( m_recAdibeHdr.ReportingIdentification, sizeof(m_recAdibeHdr.ReportingIdentification), line.substr(2, 20).c_str());
	StringCchCopy( m_recAdibeHdr.NumberOfEmirRecordsOnly, sizeof(m_recAdibeHdr.NumberOfEmirRecordsOnly), line.substr(22, 8).c_str());
	    
	return true;
}
  
//

CABD_TradesPositions::CABD_TradesPositions(std::string& line) : 
ABD_TRDPOS(), CCsvLine(ABD_CSV_DELIM, ABD_CSV_DELIM_ESCAPED)
{ 					  
	m_bValid = DeserializeCsvLine(line);  
}	

bool CABD_TradesPositions::DeserializeCsvLine(std::string& line)
{
	ScvLineEscape(line);  
	std::stringstream ssLine(line);	
	  
	try
	{
		ReadCell( Abd_1             ,sizeof( Abd_1      )     , ssLine );
		ReadCell( Abd_2             ,sizeof( Abd_2      )     , ssLine );
		ReadCell( Abd_3             ,sizeof( Abd_3      )     , ssLine );
		ReadCell( CPTY_2              ,sizeof( CPTY_2       )     , ssLine );
		ReadCell( Abd_4             ,sizeof( Abd_4      )     , ssLine );
		ReadCell( CPTY_3              ,sizeof( CPTY_3       )     , ssLine ); 
		ReadCell( CPTY_4              ,sizeof( CPTY_4       )     , ssLine );
		ReadCell( CPTY_5              ,sizeof( CPTY_5       )     , ssLine );
		ReadCell( Abd_5             ,sizeof( Abd_5      )     , ssLine );
		ReadCell( CPTY_6              ,sizeof( CPTY_6       )     , ssLine );
		ReadCell( CPTY_7              ,sizeof( CPTY_7       )     , ssLine );
		ReadCell( Abd_6             ,sizeof( Abd_6      )     , ssLine );
		ReadCell( CPTY_8              ,sizeof( CPTY_8       )     , ssLine );
		ReadCell( Abd_7             ,sizeof( Abd_7      )     , ssLine );
		ReadCell( CPTY_9              ,sizeof( CPTY_9       )     , ssLine );
		ReadCell( Abd_8             ,sizeof( Abd_8      )     , ssLine );
		ReadCell( CPTY_10             ,sizeof( CPTY_10      )     , ssLine );
		ReadCell( Abd_9             ,sizeof( Abd_9      )     , ssLine );
		ReadCell( CPTY_11             ,sizeof( CPTY_11      )     , ssLine );
		ReadCell( CPTY_12             ,sizeof( CPTY_12      )     , ssLine );
		ReadCell( CPTY_13             ,sizeof( CPTY_13      )     , ssLine );
		ReadCell( CPTY_14             ,sizeof( CPTY_14      )     , ssLine );
		ReadCell( CPTY_15             ,sizeof( CPTY_15      )     , ssLine );
		ReadCell( CPTY_16             ,sizeof( CPTY_16      )     , ssLine );
		ReadCell( CPTY_17             ,sizeof( CPTY_17      )     , ssLine );
		ReadCell( CPTY_18             ,sizeof( CPTY_18      )     , ssLine );
		ReadCell( CPTY_19             ,sizeof( CPTY_19      )     , ssLine );
		ReadCell( CPTY_20             ,sizeof( CPTY_20      )     , ssLine );
		ReadCell( CPTY_21             ,sizeof( CPTY_21      )     , ssLine );
		ReadCell( CPTY_22             ,sizeof( CPTY_22      )     , ssLine );
		ReadCell( CPTY_23             ,sizeof( CPTY_23      )     , ssLine );
		ReadCell( CPTY_24             ,sizeof( CPTY_24      )     , ssLine );
		ReadCell( CPTY_25             ,sizeof( CPTY_25      )     , ssLine );
		ReadCell( CPTY_26             ,sizeof( CPTY_26      )     , ssLine );
		ReadCell( COMMON_1			  ,sizeof( COMMON_1		)     , ssLine );
		ReadCell( COMMON_2			  ,sizeof( COMMON_2		)     , ssLine );
		ReadCell( COMMON_3			  ,sizeof( COMMON_3		)     , ssLine );
		ReadCell( Abd_10            ,sizeof( Abd_10     )     , ssLine );
		ReadCell( COMMON_4			  ,sizeof( COMMON_4		)     , ssLine );
		ReadCell( Abd_11            ,sizeof( Abd_11     )     , ssLine );
		ReadCell( COMMON_5			  ,sizeof( COMMON_5		)     , ssLine );
		ReadCell( COMMON_6			  ,sizeof( COMMON_6		)     , ssLine );
		ReadCell( COMMON_7			  ,sizeof( COMMON_7		)     , ssLine );
		ReadCell( Abd_12            ,sizeof( Abd_12     )     , ssLine );
		ReadCell( COMMON_8			  ,sizeof( COMMON_8		)     , ssLine );
		ReadCell( COMMON_9			  ,sizeof( COMMON_9		)     , ssLine );
		ReadCell( Abd_13            ,sizeof( Abd_13     )     , ssLine );
		ReadCell( COMMON_10			  ,sizeof( COMMON_10	)	  , ssLine );
		ReadCell( COMMON_11			  ,sizeof( COMMON_11	)	  , ssLine );
		ReadCell( COMMON_12			  ,sizeof( COMMON_12	)	  , ssLine );
		ReadCell( COMMON_13			  ,sizeof( COMMON_13	)	  , ssLine );
		ReadCell( COMMON_14			  ,sizeof( COMMON_14	)	  , ssLine );
		ReadCell( COMMON_15			  ,sizeof( COMMON_15	)	  , ssLine );
		ReadCell( COMMON_16			  ,sizeof( COMMON_16	)	  , ssLine );
		ReadCell( COMMON_17			  ,sizeof( COMMON_17	)	  , ssLine );
		ReadCell( COMMON_18			  ,sizeof( COMMON_18	)	  , ssLine );
		ReadCell( Abd_14            ,sizeof( Abd_14     )     , ssLine );
		ReadCell( COMMON_19			  ,sizeof( COMMON_19	)	  , ssLine );
		ReadCell( COMMON_20			  ,sizeof( COMMON_20	)	  , ssLine );
		ReadCell( COMMON_21			  ,sizeof( COMMON_21	)	  , ssLine );
		ReadCell( COMMON_22			  ,sizeof( COMMON_22	)	  , ssLine );
		ReadCell( COMMON_23			  ,sizeof( COMMON_23	)	  , ssLine );
		ReadCell( COMMON_24			  ,sizeof( COMMON_24	)	  , ssLine );
		ReadCell( COMMON_25			  ,sizeof( COMMON_25	)	  , ssLine );
		ReadCell( Abd_15            ,sizeof( Abd_15     )     , ssLine );
		ReadCell( COMMON_26			  ,sizeof( COMMON_26	)	  , ssLine );
		ReadCell( COMMON_27			  ,sizeof( COMMON_27	)	  , ssLine );
		ReadCell( COMMON_28			  ,sizeof( COMMON_28	)	  , ssLine );
		ReadCell( COMMON_29			  ,sizeof( COMMON_29	)	  , ssLine );
		ReadCell( Abd_16            ,sizeof( Abd_16     )     , ssLine );
		ReadCell( COMMON_30			  ,sizeof( COMMON_30	)	  , ssLine );
		ReadCell( Abd_17            ,sizeof( Abd_17     )     , ssLine );
		ReadCell( COMMON_31			  ,sizeof( COMMON_31	)	  , ssLine );
		ReadCell( COMMON_32			  ,sizeof( COMMON_32	)	  , ssLine );
		ReadCell( COMMON_33			  ,sizeof( COMMON_33	)	  , ssLine );
		ReadCell( COMMON_34			  ,sizeof( COMMON_34	)	  , ssLine );
		ReadCell( COMMON_35			  ,sizeof( COMMON_35	)	  , ssLine );
		ReadCell( Abd_18            ,sizeof( Abd_18     )     , ssLine );
		ReadCell( COMMON_36			  ,sizeof( COMMON_36	)	  , ssLine );
		ReadCell( Abd_19            ,sizeof( Abd_19     )     , ssLine );
		ReadCell( COMMON_37			  ,sizeof( COMMON_37	)	  , ssLine );
		ReadCell( Abd_20            ,sizeof( Abd_20     )     , ssLine );
		ReadCell( COMMON_38			  ,sizeof( COMMON_38	)	  , ssLine );
		ReadCell( Abd_21            ,sizeof( Abd_21     )     , ssLine );
		ReadCell( Abd_22            ,sizeof( Abd_22     )     , ssLine );
		ReadCell( Abd_23            ,sizeof( Abd_23     )     , ssLine );
		ReadCell( COMMON_39			  ,sizeof( COMMON_39	)	  , ssLine );
		ReadCell( COMMON_40			  ,sizeof( COMMON_40	)	  , ssLine );
		ReadCell( COMMON_41			  ,sizeof( COMMON_41	)	  , ssLine );
		ReadCell( COMMON_42			  ,sizeof( COMMON_42	)	  , ssLine );
		ReadCell( COMMON_43			  ,sizeof( COMMON_43	)	  , ssLine );
		ReadCell( COMMON_44			  ,sizeof( COMMON_44	)	  , ssLine );
		ReadCell( COMMON_45			  ,sizeof( COMMON_45	)	  , ssLine );
		ReadCell( COMMON_46			  ,sizeof( COMMON_46	)	  , ssLine );
		ReadCell( COMMON_47			  ,sizeof( COMMON_47	)	  , ssLine );
		ReadCell( COMMON_48			  ,sizeof( COMMON_48	)	  , ssLine );
		ReadCell( COMMON_49			  ,sizeof( COMMON_49	)	  , ssLine );
		ReadCell( COMMON_50			  ,sizeof( COMMON_50	)	  , ssLine );
		ReadCell( COMMON_51			  ,sizeof( COMMON_51	)	  , ssLine );
		ReadCell( COMMON_52			  ,sizeof( COMMON_52	)	  , ssLine );
		ReadCell( COMMON_53			  ,sizeof( COMMON_53	)	  , ssLine );
		ReadCell( COMMON_54			  ,sizeof( COMMON_54	)	  , ssLine );
		ReadCell( COMMON_55			  ,sizeof( COMMON_55	)	  , ssLine );
		ReadCell( COMMON_56			  ,sizeof( COMMON_56	)	  , ssLine );
		ReadCell( COMMON_57			  ,sizeof( COMMON_57	)	  , ssLine );
		ReadCell( COMMON_58			  ,sizeof( COMMON_58	)	  , ssLine );
		ReadCell( COMMON_59			  ,sizeof( COMMON_59	)	  , ssLine );
	}
	catch (const std::runtime_error& error)
	{	   
		m_bValid = false;
		m_sError = error.what(); 
	}

	return m_bValid;
}

std::string CABD_TradesPositions::SerializeToCsvLine()
{
	std::string line;  
	  						 
	AddToCsvLine( line, Abd_1   );  
	AddToCsvLine( line, Abd_2   );  
	AddToCsvLine( line, Abd_3   );  
	AddToCsvLine( line, CPTY_2    );  
	AddToCsvLine( line, Abd_4   );  
	AddToCsvLine( line, CPTY_3    );  
	AddToCsvLine( line, CPTY_4    );  
	AddToCsvLine( line, CPTY_5    );  
	AddToCsvLine( line, Abd_5   );  
	AddToCsvLine( line, CPTY_6    );  
	AddToCsvLine( line, CPTY_7    );  
	AddToCsvLine( line, Abd_6   );  
	AddToCsvLine( line, CPTY_8    );  
	AddToCsvLine( line, Abd_7   );  
	AddToCsvLine( line, CPTY_9    );  
	AddToCsvLine( line, Abd_8   );  
	AddToCsvLine( line, CPTY_10   );  
	AddToCsvLine( line, Abd_9   );  
	AddToCsvLine( line, CPTY_11   );  
	AddToCsvLine( line, CPTY_12   );  
	AddToCsvLine( line, CPTY_13   );  
	AddToCsvLine( line, CPTY_14   );  
	AddToCsvLine( line, CPTY_15   );  
	AddToCsvLine( line, CPTY_16   );  
	AddToCsvLine( line, CPTY_17   );  
	AddToCsvLine( line, CPTY_18   );  
	AddToCsvLine( line, CPTY_19   );  
	AddToCsvLine( line, CPTY_20   );  
	AddToCsvLine( line, CPTY_21   );  
	AddToCsvLine( line, CPTY_22   );  
	AddToCsvLine( line, CPTY_23   );  
	AddToCsvLine( line, CPTY_24   );  
	AddToCsvLine( line, CPTY_25   );  
	AddToCsvLine( line, CPTY_26   );  
	AddToCsvLine( line, COMMON_1  );
	AddToCsvLine( line, COMMON_2  );
	AddToCsvLine( line, COMMON_3  );
	AddToCsvLine( line, Abd_10  );  
	AddToCsvLine( line, COMMON_4  );
	AddToCsvLine( line, Abd_11  );  
	AddToCsvLine( line, COMMON_5  );
	AddToCsvLine( line, COMMON_6  );
	AddToCsvLine( line, COMMON_7  );
	AddToCsvLine( line, Abd_12  );  
	AddToCsvLine( line, COMMON_8  );
	AddToCsvLine( line, COMMON_9  );
	AddToCsvLine( line, Abd_13  );  
	AddToCsvLine( line, COMMON_10 );	
	AddToCsvLine( line, COMMON_11 );	
	AddToCsvLine( line, COMMON_12 );	
	AddToCsvLine( line, COMMON_13 );	
	AddToCsvLine( line, COMMON_14 );	
	AddToCsvLine( line, COMMON_15 );	
	AddToCsvLine( line, COMMON_16 );	
	AddToCsvLine( line, COMMON_17 );	
	AddToCsvLine( line, COMMON_18 );	
	AddToCsvLine( line, Abd_14  );  
	AddToCsvLine( line, COMMON_19 );	
	AddToCsvLine( line, COMMON_20 );	
	AddToCsvLine( line, COMMON_21 );	
	AddToCsvLine( line, COMMON_22 );	
	AddToCsvLine( line, COMMON_23 );	
	AddToCsvLine( line, COMMON_24 );	
	AddToCsvLine( line, COMMON_25 );	
	AddToCsvLine( line, Abd_15  );  
	AddToCsvLine( line, COMMON_26 );	
	AddToCsvLine( line, COMMON_27 );	
	AddToCsvLine( line, COMMON_28 );	
	AddToCsvLine( line, COMMON_29 );	
	AddToCsvLine( line, Abd_16  );  
	AddToCsvLine( line, COMMON_30 );	
	AddToCsvLine( line, Abd_17  );  
	AddToCsvLine( line, COMMON_31 );	
	AddToCsvLine( line, COMMON_32 );	
	AddToCsvLine( line, COMMON_33 );	
	AddToCsvLine( line, COMMON_34 );	
	AddToCsvLine( line, COMMON_35 );	
	AddToCsvLine( line, Abd_18  );  
	AddToCsvLine( line, COMMON_36 );	
	AddToCsvLine( line, Abd_19  );  
	AddToCsvLine( line, COMMON_37 );	
	AddToCsvLine( line, Abd_20  );  
	AddToCsvLine( line, COMMON_38 );	
	AddToCsvLine( line, Abd_21  );  
	AddToCsvLine( line, Abd_22  );  
	AddToCsvLine( line, Abd_23  );  
	AddToCsvLine( line, COMMON_39 );	
	AddToCsvLine( line, COMMON_40 );	
	AddToCsvLine( line, COMMON_41 );	
	AddToCsvLine( line, COMMON_42 );	
	AddToCsvLine( line, COMMON_43 );	
	AddToCsvLine( line, COMMON_44 );	
	AddToCsvLine( line, COMMON_45 );	
	AddToCsvLine( line, COMMON_46 );	
	AddToCsvLine( line, COMMON_47 );	
	AddToCsvLine( line, COMMON_48 );	
	AddToCsvLine( line, COMMON_49 );	
	AddToCsvLine( line, COMMON_50 );	
	AddToCsvLine( line, COMMON_51 );	
	AddToCsvLine( line, COMMON_52 );	
	AddToCsvLine( line, COMMON_53 );	
	AddToCsvLine( line, COMMON_54 );	
	AddToCsvLine( line, COMMON_55 );	
	AddToCsvLine( line, COMMON_56 );	
	AddToCsvLine( line, COMMON_57 );	
	AddToCsvLine( line, COMMON_58 );	
	AddToCsvLine( line, COMMON_59 );
						   
	return line.substr(0, line.size()-1);
}
 
 