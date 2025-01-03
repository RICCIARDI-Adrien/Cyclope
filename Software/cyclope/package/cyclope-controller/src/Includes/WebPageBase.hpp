/** @file WebPageBase.hpp
 * Base class for all web pages.
 * @author Adrien RICCIARDI
 */
#ifndef HPP_WEB_PAGE_BASE_HPP
#define HPP_WEB_PAGE_BASE_HPP

#include <string>
#include <utility>
#include <vector>

class WebPageBase
{
	public:
		/** Contain an argument and its value. */
		typedef struct
		{
			char stringArgument[32];
			char stringValue[32];
		} UrlArgument;

		/** Construct a new page.
		 * @param stringBaseUrl Specify the page URL, starting from the server root and without any parameter.
		 */
		WebPageBase(std::string stringBaseUrl) : _stringBaseUrl{stringBaseUrl} {};

		/** Generate the HTML content that goes into the \<body\> tag.
		 * @param referenceVectorUrlArguments Contain a list of the arguments provided with the URL.
		 * @param referenceStringContent On output, write the page content to this string.
		 * @return -1 if an error occurred,
		 * @return 0 on success.
		 */
		virtual int generateContent(std::vector<UrlArgument *> &referenceVectorUrlArguments, std::string &referenceStringContent) = 0;

		/** Retrieve the page base URL (i.e. starting from the server root and without any parameter).
		 * @return The page base URL.
		 */
		inline std::string getBaseUrl() { return _stringBaseUrl; }

	private:
		/** The page base URL (i.e. starting from the server root and without any parameter). */
		std::string _stringBaseUrl;
};

#endif
