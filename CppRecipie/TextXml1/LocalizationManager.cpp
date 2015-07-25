#include "LocalizationManager.h"
#include "rapidxml.hpp"
//#include <iostream>

namespace Localization
{
	Manager::Manager()
	{
		/*static const uint32_t INDEX_EN_US{ static_cast<uint32_t>(Languages::EN_US) };
		m_StringPacks[INDEX_EN_US][STRING_COLOR] = "COLOR"s;
		 
		static const uint32_t INDEX_EN_GB{ static_cast<uint32_t>(Languages::EN_GB) };
		m_StringPacks[INDEX_EN_GB][STRING_COLOR] = "COLOUR"s;
		
		std::ifstream csvStringFile{ "strings.csv"s }; 
		
		assert(csvStringFile);
		if (csvStringFile)
		{
			while (!csvStringFile.eof())
			{
				std::string line;
				getline(csvStringFile, line);
				 
				if (line.size() > 0)
				{
					// Create a stringstream for the line
					std::stringstream lineStream{ line };
					 
					// Use the line stream to read in the string id
					std::string stringIdText;
					getline(lineStream, stringIdText, ',');
					 
					std::stringstream idStream{ stringIdText };
					uint32_t stringId;
					idStream >> stringId;
					
				// Loop over the line and read in each string
					uint32_t languageId = 0;
					std::string stringText;
					while (getline(lineStream, stringText, ','))
					{
						m_StringPacks[languageId++][stringId] = stringText;
					}
				}
			}
		}
		SetLanguage(Languages::EN_US);//default
		*/
		std::ifstream xmlStringFile{ "strings.xml"s };
		xmlStringFile.seekg(0, std::ios::end);
		uint32_t size{ static_cast<uint32_t>(xmlStringFile.tellg()) + 1 };
		char* buffer{ new char[size]{} };
		xmlStringFile.seekg(0, std::ios::beg);
		xmlStringFile.read(buffer, size);
		xmlStringFile.close();
		 //These two lines are responsible for initializing the XML data structure from the contents of the file.
		rapidxml::xml_document<> document;
		document.parse<0>(buffer);
		 
		rapidxml::xml_node<>* workbook{ document.first_node("Workbook") };
		if (workbook != nullptr)
		{
			rapidxml::xml_node<>* worksheet{ workbook->first_node("ss:Worksheet") };
			if (worksheet != nullptr)
			{
				rapidxml::xml_node<>* table{ worksheet->first_node("Table") };
				if (table != nullptr)
				{
					rapidxml::xml_node<>* row{ table->first_node("Row") };
					while (row != nullptr)
					{
						uint32_t stringId{ UINT32_MAX };
						 
						rapidxml::xml_node<>* cell{ row->first_node("Cell") };
						if (cell != nullptr)
						{
							rapidxml::xml_node<>* data{ cell->first_node("Data") };
							if (data != nullptr)
							{
								stringId = static_cast<uint32_t>(atoi(data->value()));
							}
						}
								 
						if (stringId != UINT32_MAX)
						{
							uint32_t languageIndex{ 0 };
							 
							cell = cell->next_sibling("Cell");
							while (cell != nullptr)
							{
								rapidxml::xml_node<>* data = cell->first_node("Data");
								if (data != nullptr)
								{
									m_StringPacks[languageIndex++][stringId] = data->value();
									//std::cout <<  stringId <<", "<< m_StringPacks[languageIndex-1][stringId] << std::endl;
								}
									cell = cell->next_sibling("Cell");
							}
						}
					 
						row = row->next_sibling("Row");
					}
				}
			}
		}
	}
	
	void Manager::SetLanguage(Languages language)
	{
		m_CurrentStringPack = &(m_StringPacks[static_cast<uint32_t>(language)]);
	}

	std::string Manager::GetString(StringID stringId) const
	{
		std::stringstream resultStream;
		resultStream << "!!!"s;
		resultStream << stringId;
		resultStream << "!!!"s;
		std::string result{ resultStream.str() };
		 
		auto iter = m_CurrentStringPack->find(stringId);
		if (iter != m_CurrentStringPack->end())
		{
		result = iter->second;
		}
		
		return result;
	}
}