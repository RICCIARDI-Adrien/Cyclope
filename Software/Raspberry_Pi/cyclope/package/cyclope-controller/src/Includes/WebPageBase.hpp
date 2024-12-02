/** @file WebPageBase.hpp
 * Base class for all web pages.
 * @author Adrien RICCIARDI
 */
#ifndef HPP_WEB_PAGE_BASE_HPP
#define HPP_WEB_PAGE_BASE_HPP

#include <string>

class WebPageBase
{
	public:
		/** Generate the HTML content that goes into the \<body\> tag.
		 * @param referenceStringContent On output, write the page content to this string.
		 * @return -1 if an error occurred,
		 * @return 0 on success.
		 */
		virtual int generateContent(std::string &referenceStringContent) = 0;
};

#endif
