/*	WARNING: COPYRIGHT (C) 2016 XSENS TECHNOLOGIES OR SUBSIDIARIES WORLDWIDE. ALL RIGHTS RESERVED.
	THIS FILE AND THE SOURCE CODE IT CONTAINS (AND/OR THE BINARY CODE FILES FOUND IN THE SAME
	FOLDER THAT CONTAINS THIS FILE) AND ALL RELATED SOFTWARE (COLLECTIVELY, "CODE") ARE SUBJECT
	TO A RESTRICTED LICENSE AGREEMENT ("AGREEMENT") BETWEEN XSENS AS LICENSOR AND THE AUTHORIZED
	LICENSEE UNDER THE AGREEMENT. THE CODE MUST BE USED SOLELY WITH XSENS PRODUCTS INCORPORATED
	INTO LICENSEE PRODUCTS IN ACCORDANCE WITH THE AGREEMENT. ANY USE, MODIFICATION, COPYING OR
	DISTRIBUTION OF THE CODE IS STRICTLY PROHIBITED UNLESS EXPRESSLY AUTHORIZED BY THE AGREEMENT.
	IF YOU ARE NOT AN AUTHORIZED USER OF THE CODE IN ACCORDANCE WITH THE AGREEMENT, YOU MUST STOP
	USING OR VIEWING THE CODE NOW, REMOVE ANY COPIES OF THE CODE FROM YOUR COMPUTER AND NOTIFY
	XSENS IMMEDIATELY BY EMAIL TO INFO@XSENS.COM. ANY COPIES OR DERIVATIVES OF THE CODE (IN WHOLE
	OR IN PART) IN SOURCE CODE FORM THAT ARE PERMITTED BY THE AGREEMENT MUST RETAIN THE ABOVE
	COPYRIGHT NOTICE AND THIS PARAGRAPH IN ITS ENTIRETY, AS REQUIRED BY THE AGREEMENT.
*/

#ifdef __cplusplus
#ifndef XSEXCEPTION_H
#define XSEXCEPTION_H

#include <exception>
#include "xsresultvalue.h"
#include "xsstring.h"

/*! \brief Exception class for Xsens public libraries. Inherits from std::exception
*/
class XsException : public std::exception {
public:
	//! \brief Copy constructor
	XsException(XsException const& e)
		: m_code(e.m_code)
		, m_description(e.m_description)
	{
	}

	/*! \brief Initializing constructor
		\details This constructor uses the value in \a err and the supplied \a description to create a full
		text for when the user requests what() or text()
		\param err The error code that the exception should report
		\param description A description of the error. The constructor prefixes this with a textual
							description of the error code unless prefix is false.
		\param prefix Whether to prefix the description with a textual description of the error code or not (default is yes)
	*/
	XsException(XsResultValue err, XsString const& description, bool prefix = true)
		: m_code(err)
		, m_description(description)
	{
		if (prefix && (m_code != XRV_OK))
		{
			char codeString[16];
			sprintf(codeString, "%d: ", (int) m_code);
			XsString rv(codeString);
			rv << XsResultValue_toString(m_code);
			if (!m_description.empty())
			{
				rv << ". ";
				rv.append(m_description);
			}
			m_description = rv;
		}
	}

	/*! \brief Initializing constructor
		\param description A description of the error.
	*/
	explicit XsException(XsString const& description)
		: m_code(XRV_ERROR)
		, m_description(description)
	{
	}

	//! \brief Destructor
	virtual ~XsException() throw()
	{
	}

	//! \brief Assignment operator, copies \a e to this
	XsException& operator = (XsException const& e)
	{
		m_code = e.m_code;
		m_description = e.m_description;
		return *this;
	}

	//! \brief Returns the error value supplied during construction
	inline XsResultValue code() const throw()
	{
		return m_code;
	}

	//! \brief Returns a description of the error that occurred as a char const*
	inline char const* what() const throw()
	{
		return m_description.c_str();
	}

	//! \brief Returns a description of the error that occurred as a XsString
	inline XsString const& text() const throw()
	{
		return m_description;
	}

private:
	XsResultValue m_code;	//!< The supplied error code
	XsString m_description;	//!< The supplied description, prefixed with a description of the error code
};

#endif // file guard
#endif // __cplusplus guard
