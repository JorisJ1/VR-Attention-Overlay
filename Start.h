#include <stdio.h>
#include <openvr.h>
#include <chrono>
#include <thread>

using namespace vr;
using namespace std::this_thread;     // sleep_for, sleep_until
using namespace std::chrono_literals; // ns, us, ms, s, h, etc.
using std::chrono::system_clock;

void check_error(int line, EVRInitError error) { if (error != 0) printf("%d: error %s\n", line, VR_GetVRInitErrorAsSymbol(error)); }

int main(int argc, char** argv) {
	(void)argc; (void)argv;
	EVRInitError error;
	VR_Init(&error, VRApplication_Overlay);
	check_error(__LINE__, error);

	VROverlayHandle_t handle;
	VROverlay()->CreateOverlay("imgOverlayKey1", "imgOverlayName1", &handle);
	VROverlay()->SetOverlayFromFile(handle, "C:\\Users\\Joris\\source\\overige\\TestOpenVR-Overlay\\attention.png");
	VROverlay()->SetOverlayWidthInMeters(handle, 1);
	VROverlay()->ShowOverlay(handle);

	HmdMatrix34_t transform = {
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

	VROverlay()->SetOverlayTransformTrackedDeviceRelative(handle, k_unTrackedDeviceIndex_Hmd, &transform);

	//while (true) {}

	sleep_for(2s);

	return 0;
}

