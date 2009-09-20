// This code is in the public domain -- castano@gmail.com

#include "Tokenizer.h"
#include <nvcore/StrLib.h>

#include <stdio.h> // vsscanf
#include <stdarg.h>	// va_list
#include <stdlib.h>	// atof, atoi


#if NV_CC_MSVC
extern int nv_vsscanf(const char *inp, char const *fmt0, va_list ap);
#endif // NV_CC_MSVC


using namespace nv;

Token::Token() :
	m_str(""), m_len(0)
{
}

Token::Token(const Token & token) : 
	m_str(token.m_str), m_len(token.m_len)
{
}

Token::Token(const char * str, int len) : 
	m_str(str), m_len(len)
{
}

bool Token::operator==(const char * str) const
{
	return strncmp(m_str, str, m_len) == 0;
}
bool Token::operator!=(const char * str) const
{
	return strncmp(m_str, str, m_len) != 0;
}

bool Token::isNull()
{
	return m_len != 0;
}

float Token::toFloat() const
{
	return float(atof(m_str));
}

int Token::toInt() const
{
	return atoi(m_str);
}

uint Token::toUnsignedInt() const
{
	// @@ TBD
	return uint(atoi(m_str));
}

String Token::toString() const
{
	return String(m_str, m_len);
}

bool Token::parse(const char * format, int count, ...) const
{
	va_list arg;
	va_start(arg, count);

	int readCount = vsscanf(m_str, format, arg);

	va_end(arg);

	return readCount == count;
}


Tokenizer::Tokenizer(Stream * stream) : 
	m_reader(stream), m_lineNumber(0), m_columnNumber(0), m_delimiters("{}()="), m_spaces(" \t")
{
}

bool Tokenizer::nextLine(bool skipEmptyLines /*= true*/)
{
	do {
		if (!readLine()) {
			return false;
		}
	}
	while (!readToken() && skipEmptyLines);
	
	return true;
}

bool Tokenizer::nextToken(bool skipEndOfLine /*= false*/)
{
	if (!readToken()) {
		if (!skipEndOfLine) {
			return false;
		}
		else {
			return nextLine(true);
		}
	}
	return true;
}
	
bool Tokenizer::readToken()
{
	skipSpaces();
	
	const char * begin = m_line + m_columnNumber;
	
	if (*begin == '\0') {
		return false;
	}
	
	char c = readChar();
	if (isDelimiter(c)) {
		m_token = Token(begin, 1);
		return true;
	}
	
	// @@ Add support for quoted tokens "", ''
	
	int len = 0;
	while (!isDelimiter(c) && !isSpace(c) && c != '\0') {
		c = readChar();
		len++;
	}
	m_columnNumber--;
	
	m_token = Token(begin, len);
	
	return true;
}

char Tokenizer::readChar()
{
	return m_line[m_columnNumber++];
}

bool Tokenizer::readLine()
{
	m_lineNumber++;
	m_columnNumber = 0;
	m_line = m_reader.readLine();
	return m_line != NULL;
}

void Tokenizer::skipSpaces()
{
	while (isSpace(readChar())) {}
	m_columnNumber--;
}

bool Tokenizer::isSpace(char c)
{
	uint i = 0;
	while (m_spaces[i] != '\0') {
		if (c == m_spaces[i]) {
			return true;
		}
		i++;
	}
	return false;
}

bool Tokenizer::isDelimiter(char c)
{
	uint i = 0;
	while (m_delimiters[i] != '\0') {
		if (c == m_delimiters[i]) {
			return true;
		}
		i++;
	}
	return false;
}

