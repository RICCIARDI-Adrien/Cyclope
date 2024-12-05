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
		"		KEY_STOP: 4,\n"
		"		KEY_LIGHT: 5\n"
		"	}\n"
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
		"			case \" \":\n"
		"				keyIndex = KeyIndex.KEY_STOP;\n"
		"				break;\n"
		"\n"
		"			case \"L\":\n"
		"			case \"l\":\n"
		"				keyIndex = KeyIndex.KEY_LIGHT;\n"
		"				break;\n"
		"\n"
		"			// Ignore all other keys\n"
		"			default:\n"
		"				return;\n"
		"		}\n"
		"\n"
		"		console.log(\"touche \" + keyIndex + \" press \" + isKeyPressed);\n"
		"\n"
		"		// Create the POST request\n"
		"		response = fetch(\"/api\", { method: \"POST\", body: \"setRobotMotion=2\" });\n"
		"		console.log(\"réponse \" + response.status);\n"
		"	}\n"
		"</script>\n"
		"\n"
		"<div class=\"text-center\">\n"
		"	<h1>Robot manual control</h1>\n"
		"</div>\n"
		"<p class=\"text-center\">\n"
		"	<a href=\"" + webPageIndex.getBaseUrl() + "\">Back</a>\n"
		"</p>\n";

	return 0;
}

// The statically allocated instance of the page
WebPageManualControl webPageManualControl{};
