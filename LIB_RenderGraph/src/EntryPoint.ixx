#if _WIN32
#include <Windows.h>
#undef min
#undef max
#endif

export module RenderGraph:EntryPoint;

// CAUTION: This trick can only be used with static libraries, not shared libraries. Also
// extern "C" is not required.
export extern "C" int EntryPoint (int, char**);

#if _WIN32
int WINAPI WinMain (HINSTANCE, HINSTANCE, LPSTR, int) {
	return EntryPoint (__argc, __argv);
}
#else
int main (int argc, char** argv) {
	return EntryPoint (argc, argv);
}
#endif
