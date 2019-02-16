#include "RkPlatform.h"

#include <random>

RkNativeWindowInfo rk_from_native_win(HINSTANCE instance, LPCSTR className, HWND window)
{
        RkNativeWindowInfo info;
        info.instance = instance;
        info.className = className;
        info.window = window;
        return info;
}

RkWindowId rk_id_from_win(HWND window)
{
        RkWindowId id;
        id.id = window;
        return id;
}

static inline char *wideToMulti(int codePage, const wchar_t *aw)
{
        const int required = WideCharToMultiByte(codePage, 0, aw, -1, NULL, 0, NULL, NULL);
        char *result = new char[required];
        WideCharToMultiByte(codePage, 0, aw, -1, result, required, NULL, NULL);
        return result;
}

extern "C" int main(int argc, char **argv);
extern "C" int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine, int nCmdShow)
{
        WNDCLASSEX wc;
        wc.cbSize        = sizeof(WNDCLASSEX);
        wc.style         = 0;
        wc.lpfnWndProc   = DefWindowProcA;
        wc.cbClsExtra    = 0;
        wc.cbWndExtra    = 0;
        wc.hInstance     = hInstance;
        wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
        wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
        wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
        wc.lpszMenuName  = NULL;

        std::random_device r;
        std::default_random_engine e1(r());
        std::uniform_int_distribution<int> uniform_dist(1, 1000000);
        int mean = uniform_dist(e1);
        wc.lpszClassName = ("Redkite_" + std::to_string(mean)).c_str();
        wc.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);

        if (!RegisterClassEx(&wc)) {
                RK_LOG_ERROR("can't register window class");
                return 1;
        }

        int argc;
        wchar_t **argvW = CommandLineToArgvW(GetCommandLineW(), &argc);
        if (!argvW)
                return -1;
        char **argv = new char *[argc + 1];
        for (int i = 0; i < argc; ++i)
                argv[i] = wideToMulti(CP_ACP, argvW[i]);
        argv[argc] = nullptr;
        LocalFree(argvW);
        const int exitCode = main(argc, argv);
        for (int i = 0; i < argc && argv[i]; ++i)
                delete [] argv[i];
        delete [] argv;
        return exitCode;
}
