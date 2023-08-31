#include <iostream>
#include <regex>
#include <string>
#include <vector>
#include <fstream>

std::string processLine(const std::string &line) {
    // Regex patterns for matching
    std::regex xPattern(R"(\bx\s*:\s*(-?\d+)\b)");           // \b added for word boundary
    std::regex yPattern(R"(\by\s*:\s*(-?\d+)\b)");           // \b added for word boundary
    std::regex widthPattern(R"(width\s*:\s*(\d+))");
    std::regex heightPattern(R"(height\s*:\s*(\d+))");

    // Replacement patterns
    std::string xReplacement = "x: appWidth * $1 / 1920";    // Assuming 1920 as base width
    std::string yReplacement = "y: appHeight * $1 / 1080";   // Assuming 1080 as base height
    std::string widthReplacement = "width: appWidth * $1 / 1920";  // Assuming 1920 as base width
    std::string heightReplacement = "height: appHeight * $1 / 1080"; // Assuming 1080 as base height

    std::string result = line;

    if (std::regex_search(line, xPattern) || std::regex_search(line, yPattern) ||
        std::regex_search(line, widthPattern) || std::regex_search(line, heightPattern)) {
        
        // Replace the patterns
        result = std::regex_replace(result, xPattern, xReplacement);
        result = std::regex_replace(result, yPattern, yReplacement);
        result = std::regex_replace(result, widthPattern, widthReplacement);
        result = std::regex_replace(result, heightPattern, heightReplacement);
    }

    return result;
}


int main() {
    std::cout << "Enter your QML code (type 'END' on a new line to finish input):" << std::endl;

    std::vector<std::string> lines;
    std::string line;

    while (true) {
        std::getline(std::cin, line);
        if (line == "END") break;
        lines.push_back(processLine(line));
    }

    std::cout << "Processing complete. Saving to 'output.txt'...\n";

    // Save the processed QML code to a file
    std::ofstream outFile("output.txt");
    for (const auto& l : lines) {
        outFile << l << std::endl;
    }
    outFile.close();

    std::cout << "Saved to 'output.txt'.\n";

    return 0;
}
