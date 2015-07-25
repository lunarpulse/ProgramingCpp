#include "LocalizationManager.h"

namespace Localization
{
	Manager::Manager()
	{
		/*static const uint32_t INDEX_EN_US{ static_cast<uint32_t>(Languages::EN_US) };
		m_StringPacks[INDEX_EN_US][STRING_COLOR] = "COLOR"s;
		 
		static const uint32_t INDEX_EN_GB{ static_cast<uint32_t>(Languages::EN_GB) };
		m_StringPacks[INDEX_EN_GB][STRING_COLOR] = "COLOUR"s;
		*/
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