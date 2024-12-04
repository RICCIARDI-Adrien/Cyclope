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
		/** Construct a new page.
		 * @param stringBaseUrl Specify the page URL, starting from the server root and without any parameter.
		 */
		WebPageBase(std::string stringBaseUrl) : _stringBaseUrl{stringBaseUrl} {};

		/** Generate the HTML content that goes into the \<body\> tag.
		 * @param referenceStringContent On output, write the page content to this string.
		 * @return -1 if an error occurred,
		 * @return 0 on success.
		 */
		virtual int generateContent(std::string &referenceStringContent) = 0;

		/** Retrieve the page base URL (i.e. starting from the server root and without any parameter).
		 * @return The page base URL.
		 */
		inline std::string getBaseUrl() { return _stringBaseUrl; }

	private:
		/** The page base URL (i.e. starting from the server root and without any parameter). */
		std::string _stringBaseUrl;
};

#endif
