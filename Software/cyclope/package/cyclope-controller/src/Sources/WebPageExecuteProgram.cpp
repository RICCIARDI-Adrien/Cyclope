/** @file WebPageExecuteProgram.cpp
 * See WebPageExecuteProgram.hpp for description.
 * @author Adrien RICCIARDI
 */
#include <ArtificialIntelligenceProgramManager.hpp>
#include <Log.hpp>
#include <WebPageExecuteProgram.hpp>
#include <WebPageStartProgram.hpp>

WebPageExecuteProgram::WebPageExecuteProgram() : WebPageBase("/execute-program") {};

int WebPageExecuteProgram::generateContent(std::vector<UrlArgument *> &referenceVectorUrlArguments, std::string &referenceStringContent)
{
	referenceStringContent =
		"<script>\n"
		// Stop the running AI program when leaving the page
		"	onbeforeunload = (event) =>\n"
		"	{\n"
		"		command = CommunicationProtocol.COMMUNICATION_PROTOCOL_COMMAND_STOP_CURRENT_AI_PROGRAM;\n"
		"		communicationProtocolSendCommand(command);\n"
		"	}\n"
		"\n"
		"	function updateBatteryStatus()\n"
		"	{\n"
		"		communicationProtocolSendCommand(CommunicationProtocol.COMMUNICATION_PROTOCOL_COMMAND_GET_BATTERY_VOLTAGE).then((answer) =>\n"
		"		{\n"
		"			setUserInterfaceControlText(\"label-battery-status\", answer);\n"
		"		});\n"
		"	}\n"
		"	setInterval(updateBatteryStatus, 3000);\n" // Periodically poll the battery status
		"	updateBatteryStatus();\n" // Update the battery value as soon as possible
		"</script>\n"
		"<div class=\"text-center\">\n"
		"	<h1>Running an AI program</h1>\n"
		"</div>\n";

	// Retrieve the program to run (expect only one argument and assume that the first one is the good one)
	const WebPageBase::UrlArgument *pointerUrlArgument = referenceVectorUrlArguments[0];
	unsigned int programIndex;
	if (sscanf(pointerUrlArgument->stringValue, "%u", &programIndex) != 1)
	{
		LOG(LOG_ERR, "Failed to extract the program index (argument : \"%s\", value : \"%s\").", pointerUrlArgument->stringArgument, pointerUrlArgument->stringValue);
		referenceStringContent +=
			"<p class=\"text-center\">\n"
			"	Error : failed to extract the program index.\n"
			"</p>\n";
		return 0;
	}

	// Ask the main thread to run the program
	if (ArtificialIntelligenceProgramManager::startProgramExecution(programIndex) != 0)
	{
		LOG(LOG_ERR, "Failed to start program execution (program index : %u.", programIndex);
		referenceStringContent +=
			"<p class=\"text-center\">\n"
			"	Error : failed to start the program execution.\n"
			"</p>\n";
		return 0;
	}

	ArtificialIntelligenceProgramBase *pointerProgram = ArtificialIntelligenceProgramManager::getProgram(programIndex); // At this point, the program has already been found, so this
	referenceStringContent +=
		"<p class=\"text-center\">\n"
		"	Program name : " + std::string(pointerProgram->getDescriptiveName()) + "\n"
		"</p>\n"
		"<table class=\"table-center\">\n"
		"	<tr>\n"
		"		<th>Battery</th>\n"
		"	</tr>\n"
		"	<tr>\n"
		"		<td id=\"label-battery-status\">UNKNOWN</td>\n"
		"	</tr>\n"
		"</table>\n"
		"<br />\n"
		"<div class=\"div-button-center\">\n"
		"	<button onclick=\"location.href='" + webPageStartProgram.getBaseUrl() + "';\">Back</button>\n"
		"</div>\n";

	return 0;
}

// The statically allocated instance of the page
WebPageExecuteProgram webPageExecuteProgram{};
