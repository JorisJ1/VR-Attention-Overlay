#include <stdio.h>
#include <chrono>
#include <openvr.h>
#include <string>
#include <thread>

// Start function.
int main(int argc, char** argv) {

	std::string imagePath = argv[1];
	const char* imagePathArr = imagePath.c_str();

	// Initialise VR.
	vr::EVRInitError error;
	vr::VR_Init(&error, vr::VRApplication_Overlay);

	if (error != 0) {
		printf("%d: error %s\n", __LINE__, VR_GetVRInitErrorAsSymbol(error));
		return 0;
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
	vr::VROverlay()->SetOverlayFromFile(handle, imagePathArr);
	//vr::VROverlay()->SetOverlayFromFile(handle, "attention.png");
	vr::VROverlay()->SetOverlayWidthInMeters(handle, 1);
	vr::VROverlay()->ShowOverlay(handle);
	vr::VROverlay()->SetOverlayTransformTrackedDeviceRelative(handle, vr::k_unTrackedDeviceIndex_Hmd, &transform);

	// Sleep, to keep the overlay on screen.
	using namespace std::chrono_literals;
	std::this_thread::sleep_for(2s);

	return 0;
}
