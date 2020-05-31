#pragma once

struct ABD_TRDPOS_HDR
{	   
	ABD_TRDPOS_HDR(){ SecureZeroMemory(this, sizeof(*this)); }
	ABD_TRDPOS_HDR(char cHeaderIndicator, char cReportingFirmId, char* pszReportingIdentification, int nNumberOfEmirRecordsOnly)
	{
		SecureZeroMemory(this, sizeof(*this));
		HeaderIndicator[0] = cHeaderIndicator;
		ReportingFirmId[0] = cReportingFirmId;
		sprintf_s(ReportingIdentification, "%s", pszReportingIdentification);
		sprintf_s(NumberOfEmirRecordsOnly, "%08d", nNumberOfEmirRecordsOnly);	 
	}
	   
 	std::string ToString()
	{   
		std::string sHeader;
		
		sHeader += HeaderIndicator; 
		sHeader	+= ReportingFirmId;
		sHeader += ReportingIdentification;
		sHeader += NumberOfEmirRecordsOnly;

		return sHeader;
	}

	char HeaderIndicator[1 +1];  
	char ReportingFirmId[1 +1];  
	char ReportingIdentification[20 +1]; 
	char NumberOfEmirRecordsOnly[8 + 1];   

	//char Checksum				  [?]; no info
	//char ChecksumMatch		  [?]; no info
	//char GUID					  [?]; no info
	//char NumberOfRecordsMatch	  [?]; no info
};

struct ABD_TRDPOS
{	  
	ABD_TRDPOS(){ SecureZeroMemory(this, sizeof(*this)); }
				 
	char Abd_1[1 +1]; //1a		
	char Abd_2[3 +1]; //3n
	char Abd_3[3 +1]; //3a
	char CPTY_2[50 +1]; //50a
	char Abd_4[3 +1]; //3a
	char CPTY_3[50 +1]; //50a
	char CPTY_4[100 +1]; //100a
	char CPTY_5[500 +1]; //500a
	char Abd_5[2 +1]; //2a
	char CPTY_6[1 +1]; //1a
	char CPTY_7[1 +1]; //1a
	char Abd_6[3 +1]; //3a
	char CPTY_8[50 +1]; //50a
	char Abd_7[3 +1]; //3a
	char CPTY_9[50 +1]; //50a
	char Abd_8[3 +1]; //3a
	char CPTY_10[50 +1]; //50a
	char Abd_9[3 +1]; //3a
	char CPTY_11[50 +1]; //50a
	char CPTY_12[1 +1]; //1a
	char CPTY_13[1 +1]; //1a
	char CPTY_14[1 +1]; //1a
	char CPTY_15[1 +1]; //1a
	char CPTY_16[1 +1]; //1a
	char CPTY_17[26 +1]; //+/-18n.6n
	char CPTY_18[3 +1]; //3a
	char CPTY_19[10 +1]; //10a
	char CPTY_20[14 +1]; //14a
	char CPTY_21[1 +1]; //1a
	char CPTY_22[2 +1]; //2a
	char CPTY_23[1 +1]; //1a
	char CPTY_24[10 +1]; //10n
	char CPTY_25[26 +1]; //+/-18n.6n
	char CPTY_26[3 +1]; //3a
	char COMMON_1[1 +1]; //1a
	char COMMON_2[85 +1]; //85a
	char COMMON_3[6 +1]; //6a
	char Abd_10[4 +1]; //4a
	char COMMON_4[85 +1]; //85a
	char Abd_11[2 +1]; //2a
	char COMMON_5[3 +1]; //3a
	char COMMON_6[3 +1]; //3a
	char COMMON_7[3 +1]; //3a
	char Abd_12[3 +1]; //3a
	char COMMON_8[52 +1]; //52a
	char COMMON_9[40 +1]; //40a
	char Abd_13[52 +1]; //52a
	char COMMON_10[4 +1]; //4a
	char COMMON_11[1 +1]; //1a
	char COMMON_12[23 +1]; //+/-15n.6n
	char COMMON_13[3 +1]; //3a
	char COMMON_14[22 +1]; //+/-18n.2n
	char COMMON_15[10 +1]; //10n
	char COMMON_16[10 +1]; //10n
	char COMMON_17[22 +1]; //+/-18n.2n
	char COMMON_18[1 +1]; //1a
	char Abd_14[10 +1]; //10a
	char COMMON_19[25 +1]; //25a
	char COMMON_20[10 +1]; //10a
	char COMMON_21[10 +1]; //10a
	char COMMON_22[10 +1]; //10a
	char COMMON_23[10 +1]; //10a
	char COMMON_24[50 +1]; //50a
	char COMMON_25[4 +1]; //4n
	char Abd_15[10 +1]; //10a
	char COMMON_26[25 +1]; //25a
	char COMMON_27[1 +1]; //1a
	char COMMON_28[1 +1]; //1a
	char COMMON_29[1 +1]; //1a
	char Abd_16[10 +1]; //10a
	char COMMON_30[25 +1]; //25a
	char Abd_17[3 +1]; //3a
	char COMMON_31[20 +1]; //20a
	char COMMON_32[1 +1]; //1a
	char COMMON_33[12 +1]; //+/-2n.8n
	char COMMON_34[12 +1]; //+/-2n.8n
	char COMMON_35[20 +1]; //20a
	char Abd_18[20 +1]; //20a
	char COMMON_36[4 +1]; //(3n)+1a
	char Abd_19[4 +1]; //(3n)+1a
	char COMMON_37[4 +1]; //(3n)+1a
	char Abd_20[4 +1]; //(3n)+1a
	char COMMON_38[4 +1]; //(3n)+1a
	char Abd_21[4 +1]; //(3n)+1a
	char Abd_22[20 +1]; //20a
	char Abd_23[20 +1]; //20a
	char COMMON_39[40 +1]; //40a
	char COMMON_40[40 +1]; //40a
	char COMMON_41[3 +1]; //3a
	char COMMON_42[18 +1]; //+/-6n.10n
	char COMMON_43[18 +1]; //+/-6n.10n
	char COMMON_44[7 +1]; //3a/3a
	char COMMON_45[2 +1]; //2a
	char COMMON_46[2 +1]; //2a
	char COMMON_47[16 +1]; //16a
	char COMMON_48[50 +1]; //50a
	char COMMON_49[2 +1]; //2a
	char COMMON_50[19 +1]; //19a
	char COMMON_51[25 +1]; //25a
	char COMMON_52[11 +1]; //5n.5n
	char COMMON_53[5 +1]; //5a
	char COMMON_54[12 +1]; //+/-5n.5n
	char COMMON_55[1 +1]; //1a
	char COMMON_56[1 +1]; //1a
	char COMMON_57[12 +1]; //+/-5n.5n
	char COMMON_58[1 +1]; //1a
	char COMMON_59[50 +1]; //50a
};