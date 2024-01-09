

#include "Utilities.h"

namespace sdds {

	char Utilities::m_delimiter = ','; 

	void Utilities::setFieldWidth(size_t newWidth) {
		m_widthField = newWidth;
	}

	size_t Utilities::getFieldWidth() const {
		return m_widthField;
	}

	std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more) {
		std::string result{};
		size_t delimPos{};

		if (str[next_pos] == m_delimiter) {
			more = false;
			throw "ERROR: No token.";
		}

		result = str.substr(next_pos);
		delimPos = result.find(m_delimiter);
		result = str.substr(next_pos, delimPos);
		result.erase(0, result.find_first_not_of(" "));
		result.erase(result.find_last_not_of(" ") + 1);
		next_pos += delimPos + 1;

		if (delimPos == std::string::npos) 
			more = false;

		if (m_widthField < result.length()) 
			m_widthField = result.length();

		return result;
	}

	void Utilities::setDelimiter(char newDelimiter) {
		m_delimiter = newDelimiter;
	}

	char Utilities::getDelimiter() {
		return m_delimiter;
	}
}
