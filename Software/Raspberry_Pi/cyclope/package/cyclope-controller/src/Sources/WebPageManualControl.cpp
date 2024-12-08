/** @file WebPageManualControl.cpp
 * See WebPageManualControl.hpp for description.
 * @author Adrien RICCIARDI
 */
#include <WebPageIndex.hpp>
#include <WebPageManualControl.hpp>

WebPageManualControl::WebPageManualControl() : WebPageBase("/remote-control") {};

int WebPageManualControl::generateContent(std::string &referenceStringContent)
{
	referenceStringContent =
		"<script>\n"
		"	// A kind of enum to map a key code to an array index\n"
		"	const KeyIndex =\n"
		"	{\n"
		"		KEY_UP: 0,\n"
		"		KEY_DOWN: 1,\n"
		"		KEY_LEFT: 2,\n"
		"		KEY_RIGHT: 3,\n"
		"		KEY_LIGHT: 4\n"
		"	}\n"
		"\n"
		"	// Global variables\n"
		"	isLightEnabled = false;\n"
		"\n"
		"	// Catch all keyboard key press events\n"
		"	onkeydown = (event) =>\n"
		"	{\n"
		"		handleKeyEvent(true, event);\n"
		"	};\n"
		"\n"
		"	// Catch all keyboard key release events\n"
		"	onkeyup = (event) =>\n"
		"	{\n"
		"		handleKeyEvent(false, event);\n"
		"	};\n"
		"\n"
		"	function handleKeyEvent(isKeyPressed, keyEvent)\n"
		"	{\n"
		"		// Ignore keys repetition\n"
		"		if (isKeyPressed === true)\n"
		"		{\n"
		"			if (keyEvent.repeat) return;\n"
		"		}\n"
		"\n"
		"		// Map the pressed key to a key index\n"
		"		switch (keyEvent.key)\n"
		"		{\n"
		"			case \"ArrowUp\":\n"
		"				keyIndex = KeyIndex.KEY_UP;\n"
		"				break;\n"
		"\n"
		"			case \"ArrowDown\":\n"
		"				keyIndex = KeyIndex.KEY_DOWN;\n"
		"				break;\n"
		"\n"
		"			case \"ArrowLeft\":\n"
		"				keyIndex = KeyIndex.KEY_LEFT;\n"
		"				break;\n"
		"\n"
		"			case \"ArrowRight\":\n"
		"				keyIndex = KeyIndex.KEY_RIGHT;\n"
		"				break;\n"
		"\n"
		"			case \"L\":\n"
		"			case \"l\":\n"
		"				// This key is not considered as a button to hold\n"
		"				if (isKeyPressed === false) return;\n"
		"\n"
		"				// Toggle the light state\n"
		"				isLightEnabled = !isLightEnabled;\n"
		"				command = CommunicationProtocol.COMMUNICATION_PROTOCOL_COMMAND_SET_LIGHT_ENABLED;\n"
		"				if (isLightEnabled) command += '1';\n"
		"				else command += '0';\n"
		"				communicationProtocolSendCommand(command).then((text) =>\n"
		"				{\n"
		"					// Update the user interface\n"
		"					stringUserInterface = \"Lights : \" + text;\n"
		"					userInterfaceControl = document.getElementById(\"label-lights-status\");\n"
		"					userInterfaceControl.innerHTML = stringUserInterface;\n"
		"				});\n"
		"				break;\n"
		"\n"
		"			// Ignore all other keys\n"
		"			default:\n"
		"				return;\n"
		"		}\n"
		"	}\n"
		"</script>\n"
		"\n"
		"<div class=\"text-center\">\n"
		"	<h1>Robot manual control</h1>\n"
		"</div>\n"
		"<p id=\"label-lights-status\">Lights : disabled</p>\n"
		"<p class=\"text-center\">\n"
		"	<a href=\"" + webPageIndex.getBaseUrl() + "\">Back</a>\n"
		"</p>\n";

	return 0;
}

// The statically allocated instance of the page
WebPageManualControl webPageManualControl{};
