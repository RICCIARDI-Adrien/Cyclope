/** @file WebPageManualControl.hpp
 * Allow to remote control the robot.
 * @author Adrien RICCIARDI
 */
#ifndef HPP_WEB_PAGE_MANUAL_CONTROL_HPP
#define HPP_WEB_PAGE_MANUAL_CONTROL_HPP

#include <WebPageBase.hpp>

class WebPageManualControl : public WebPageBase
{
	public:
		// See base class documentation for description
		WebPageManualControl();

		// See base class documentation for description
		virtual int generateContent(std::string &referenceStringContent) override;
};

/** Give global access to the page statically allocated instance. */
extern WebPageManualControl webPageManualControl;

#endif
