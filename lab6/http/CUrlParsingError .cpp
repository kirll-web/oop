#include "CUrlParsingError.h"

CUrlParsingError::CUrlParsingError(const std::string& error_message)
	: std::invalid_argument(error_message)
	, m_error_message(error_message)
{
}

std::string CUrlParsingError::GetMessage() const
{
	return m_error_message;
}