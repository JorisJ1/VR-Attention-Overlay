#include <stdio.h>
#include <chrono>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <openvr.h>
#include <string>
#include <sstream>
#include <thread>
#include <vector>
#include <windows.h>

// Return the directory containing the program executable.
std::wstring GetExeDirectory() {
	TCHAR buffer[MAX_PATH] = { 0 };
	GetModuleFileName(NULL, buffer, MAX_PATH);
	std::wstring::size_type pos = std::wstring(buffer).find_last_of(L"\\/");
	return std::wstring(buffer).substr(0, pos);
}

// Convert a wstring to a string.
std::string ConvertWstringToString(const std::wstring& wstr) {
	int len = WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, 0, 0, 0, 0);
	std::vector<char> buf(len);
	WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, &buf[0], len, 0, 0);
	return std::string(buf.begin(), buf.end());
}

// Check whether a file exists.
bool IsExistingFile(const std::string& name) {
	struct stat buffer;
	return (stat(name.c_str(), &buffer) == 0);
}

// Start function.
int main(int argc, char** argv) {

	// Check whether an filename has been provided and if the file exists.
	std::string argument;
	if (argc <= 1) {
		/*std::cout << "No argument had been passed. Please pass the filename of the desired image as an argument.\n";
		return 0;*/
		argument = "attention.png";
	} else {
		argument = argv[1];
	}

	std::string imagePath = ConvertWstringToString(GetExeDirectory()) + '\\' + argument;
	if (!std::filesystem::exists(imagePath)) {
		std::cout << "File not found: " << imagePath << '\n';
		return 0;
	} else {
		std::cout << "File present: " << imagePath << '\n';
	}

	// Initialise VR.
	vr::EVRInitError error;
	vr::VR_Init(&error, vr::VRApplication_Overlay);

	if (error != 0) {
		printf("%d: error %s\n", __LINE__, VR_GetVRInitErrorAsSymbol(error));
		return 0;
	} else {
		std::cout << "No VR errors: " << '\n';
	}

	// Specify the location of the image in VR. 
	vr::HmdMatrix34_t transform = {
		1.0f, // Unknown
		0.0f, // Unknown
		0.0f, // Unknown
		0.0f, // Unknown
		0.0f, // Unknown
		1.0f, // Unknown
		0.0f, // Unknown
		0.0f, // Higher means higher
		0.0f, // Skewed, right towards me
		0.0f, // Skewed, top towards me
		0.0f, // Unknown
		-3.0f // Lower is farther away.
	};

	// Initialise and show the VR overlay.
	vr::VROverlayHandle_t handle;
	vr::VROverlay()->CreateOverlay("imgOverlayKey1", "imgOverlayName1", &handle);
	vr::VROverlay()->SetOverlayFromFile(handle, imagePath.c_str());
	//vr::VROverlay()->SetOverlayFromFile(handle, "attention.png");
	vr::VROverlay()->SetOverlayWidthInMeters(handle, 1);
	vr::VROverlay()->ShowOverlay(handle);
	vr::VROverlay()->SetOverlayTransformTrackedDeviceRelative(handle, vr::k_unTrackedDeviceIndex_Hmd, &transform);

	std::cout << "Sleeping..." << '\n';

	// Sleep, to keep the overlay on screen.
	using namespace std::chrono_literals;
	std::this_thread::sleep_for(2s);

	return 0;
}