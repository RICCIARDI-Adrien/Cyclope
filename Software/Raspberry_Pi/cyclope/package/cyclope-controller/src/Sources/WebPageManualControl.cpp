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
		"	// Global variables\n"
		"	let isLightEnabled = false;\n"
		"	let isUpDirectionKeyPressed = false;\n"
		"	let isDownDirectionKeyPressed = false;\n"
		"	let isLeftDirectionKeyPressed = false;\n"
		"	let isRightDirectionKeyPressed = false;\n"
		"	let isLastPressedDirectionKeyOnVerticalAxis = false;\n"
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
		"	function setUserInterfaceControlText(htmlElementId, text)\n"
		"	{\n"
		"		userInterfaceControl = document.getElementById(htmlElementId);\n"
		"		userInterfaceControl.innerHTML = text;\n"
		"	}\n"
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
		"				isUpDirectionKeyPressed = isKeyPressed;\n"
		"				isLastPressedDirectionKeyOnVerticalAxis = true;\n"
		"				break;\n"
		"\n"
		"			case \"ArrowDown\":\n"
		"				isDownDirectionKeyPressed = isKeyPressed;\n"
		"				isLastPressedDirectionKeyOnVerticalAxis = true;\n"
		"				break;\n"
		"\n"
		"			case \"ArrowLeft\":\n"
		"				isLeftDirectionKeyPressed = isKeyPressed;\n"
		"				isLastPressedDirectionKeyOnVerticalAxis = false;\n"
		"				break;\n"
		"\n"
		"			case \"ArrowRight\":\n"
		"				isRightDirectionKeyPressed = isKeyPressed;\n"
		"				isLastPressedDirectionKeyOnVerticalAxis = false;\n"
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
		"				communicationProtocolSendCommand(command).then((answer) => { setUserInterfaceControlText(\"label-lights-status\", \"Lights : \" + answer); });\n"
		"				return; // The following code is only about motors management\n"
		"\n"
		"			// Ignore all other keys\n"
		"			default:\n"
		"				return;\n"
		"		}\n"
		"\n"
		"		// Handle the robot motion according to the pressed keys\n"
		"		// Stop the robot if all the direction keys are released\n"
		"		if (!isUpDirectionKeyPressed && !isDownDirectionKeyPressed && !isLeftDirectionKeyPressed && !isRightDirectionKeyPressed)\n"
		"		{\n"
		"			command = CommunicationProtocol.COMMUNICATION_PROTOCOL_COMMAND_SET_MOTION + RobotMotion.ROBOT_MOTION_STOP;\n"
		"			communicationProtocolSendCommand(command).then((answer) => { setUserInterfaceControlText(\"label-robot-motion-status\", \"Robot motion : \" + answer); });\n"
		"		}\n"
		"		else\n"
		"		{\n"
		"			// Handle both vertical and horizontal direction movements\n"
		"			if ((isUpDirectionKeyPressed || isDownDirectionKeyPressed) && (isLeftDirectionKeyPressed || isRightDirectionKeyPressed))\n"
		"			{\n"
		"				// Keep trace of the last direction the user took to favor it, and when this key will be released the previous direction will be favored\n"
		"				if (isLastPressedDirectionKeyOnVerticalAxis)\n"
		"				{\n"
		"					if (isUpDirectionKeyPressed)\n"
		"					{\n"
		"						command = CommunicationProtocol.COMMUNICATION_PROTOCOL_COMMAND_SET_MOTION + RobotMotion.ROBOT_MOTION_FORWARD;\n"
		"						communicationProtocolSendCommand(command).then((answer) => { setUserInterfaceControlText(\"label-robot-motion-status\", \"Robot motion : \" + answer); });\n"
		"					}\n"
		"					else\n"
		"					{\n"
		"						command = CommunicationProtocol.COMMUNICATION_PROTOCOL_COMMAND_SET_MOTION + RobotMotion.ROBOT_MOTION_BACKWARD;\n"
		"						communicationProtocolSendCommand(command).then((answer) => { setUserInterfaceControlText(\"label-robot-motion-status\", \"Robot motion : \" + answer); });\n"
		"					}\n"
		"				}\n"
		"				else\n"
		"				{\n"
		"					if (isLeftDirectionKeyPressed)\n"
		"					{\n"
		"						// Forward turn if going forward\n"
		"						if (isUpDirectionKeyPressed)\n"
		"						{\n"
		"							command = CommunicationProtocol.COMMUNICATION_PROTOCOL_COMMAND_SET_MOTION + RobotMotion.ROBOT_MOTION_FORWARD_LEFT;\n"
		"							communicationProtocolSendCommand(command).then((answer) => { setUserInterfaceControlText(\"label-robot-motion-status\", \"Robot motion : \" + answer); });\n"
		"						}\n"
		"						// Backward turn if going backward\n"
		"						else\n"
		"						{\n"
		"							command = CommunicationProtocol.COMMUNICATION_PROTOCOL_COMMAND_SET_MOTION + RobotMotion.ROBOT_MOTION_BACKWARD_LEFT;\n"
		"							communicationProtocolSendCommand(command).then((answer) => { setUserInterfaceControlText(\"label-robot-motion-status\", \"Robot motion : \" + answer); });\n"
		"						}\n"
		"					}\n"
		"					else\n"
		"					{\n"
		"						// Forward turn if going forward\n"
		"						if (isUpDirectionKeyPressed)\n"
		"						{\n"
		"							command = CommunicationProtocol.COMMUNICATION_PROTOCOL_COMMAND_SET_MOTION + RobotMotion.ROBOT_MOTION_FORWARD_RIGHT;\n"
		"							communicationProtocolSendCommand(command).then((answer) => { setUserInterfaceControlText(\"label-robot-motion-status\", \"Robot motion : \" + answer); });\n"
		"						}\n"
		"						// Backward turn if going backward\n"
		"						else\n"
		"						{\n"
		"							command = CommunicationProtocol.COMMUNICATION_PROTOCOL_COMMAND_SET_MOTION + RobotMotion.ROBOT_MOTION_BACKWARD_RIGHT;\n"
		"							communicationProtocolSendCommand(command).then((answer) => { setUserInterfaceControlText(\"label-robot-motion-status\", \"Robot motion : \" + answer); });\n"
		"						}\n"
		"					}\n"
		"				}\n"
		"			}\n"
		"			// Handle a single key press\n"
		"			else\n"
		"			{\n"
		"				if (isUpDirectionKeyPressed)\n"
		"				{\n"
		"					command = CommunicationProtocol.COMMUNICATION_PROTOCOL_COMMAND_SET_MOTION + RobotMotion.ROBOT_MOTION_FORWARD;\n"
		"					communicationProtocolSendCommand(command).then((answer) => { setUserInterfaceControlText(\"label-robot-motion-status\", \"Robot motion : \" + answer); });\n"
		"				}\n"
		"				else if (isDownDirectionKeyPressed)\n"
		"				{\n"
		"					command = CommunicationProtocol.COMMUNICATION_PROTOCOL_COMMAND_SET_MOTION + RobotMotion.ROBOT_MOTION_BACKWARD;\n"
		"					communicationProtocolSendCommand(command).then((answer) => { setUserInterfaceControlText(\"label-robot-motion-status\", \"Robot motion : \" + answer); });\n"
		"				}\n"
		"				else if (isLeftDirectionKeyPressed)\n"
		"				{\n"
		"					command = CommunicationProtocol.COMMUNICATION_PROTOCOL_COMMAND_SET_MOTION + RobotMotion.ROBOT_MOTION_FORWARD_LEFT;\n"
		"					communicationProtocolSendCommand(command).then((answer) => { setUserInterfaceControlText(\"label-robot-motion-status\", \"Robot motion : \" + answer); });\n"
		"				}\n"
		"				else if (isRightDirectionKeyPressed)\n"
		"				{\n"
		"					command = CommunicationProtocol.COMMUNICATION_PROTOCOL_COMMAND_SET_MOTION + RobotMotion.ROBOT_MOTION_FORWARD_RIGHT;\n"
		"					communicationProtocolSendCommand(command).then((answer) => { setUserInterfaceControlText(\"label-robot-motion-status\", \"Robot motion : \" + answer); });\n"
		"				}\n"
		"			}\n"
		"		}\n"
		"	}\n"
		"</script>\n"
		"\n"
		"<div class=\"text-center\">\n"
		"	<h1>Robot manual control</h1>\n"
		"</div>\n"
		"<p id=\"label-lights-status\">Lights : disabled</p>\n"
		"<p id=\"label-robot-motion-status\">Motion : stopped</p>\n"
		"<p class=\"text-center\">\n"
		"	<a href=\"" + webPageIndex.getBaseUrl() + "\">Back</a>\n" // TODO stop robot movement when clicked
		"</p>\n";

	return 0;
}

// The statically allocated instance of the page
WebPageManualControl webPageManualControl{};
