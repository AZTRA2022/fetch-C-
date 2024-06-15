#ifndef CURL_HELPER_H
#define CURL_HELPER_H

#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <vector>
#include <cstring>
/*
    string url = "https://65f8ca0ddf15145246100795.mockapi.io/api/v1/users";
    vector<string> headers = {
        "Content-Type: application/json",
        "Accept: application/json"
    };
    string api_key = "no need for fetch this api !! ==> MockApi ::  Enjoy Yourself !";
*/

std::string fetch(const std::string& url, const std::vector<std::string>& headers, const std::string& api_key) {
    std::string command = "curl";
    for (const auto& header : headers) {
        command += " -H \"" + header + "\"";
    }
    if (!api_key.empty()) {
        command += " -H \"Authorization: Bearer " + api_key + "\"";
    }
    command += " " + url;

    std::string result;
    FILE* pipe = popen(command.c_str(), "r");
    if (pipe) {
        char buffer[128];
        std::stringstream ss;
        while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
            ss << buffer;
        }
        int rc = pclose(pipe);
        if (rc != 0) {
            std::cerr << "Command execution failed with code: " << rc << std::endl;
        } else {
            result = ss.str();
        }
    } else {
        std::cerr << "Failed to execute command" << std::endl;
    }
    return result;
}

#endif 


/*---------------------------- chat-GPT has finally shown its real usefulness--------------------------*/