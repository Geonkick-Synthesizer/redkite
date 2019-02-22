#include "RkPlatform.h"
#include "RkEventQueue.h"
#include "RkEvent.h"

#include <random>

std::string rk_winApiClassName = "";
HINSTANCE rk_winApiInstance = nullptr;

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

static LRESULT CALLBACK RkWindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
        auto eventQueue = (RkEventQueue*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
        if (!eventQueue)
                return DefWindowProc(hWnd, msg, wParam, lParam);

        switch(msg)
        {
        case WM_DESTROY:
        {
                auto event = RkEvent::closeEvent();
                eventQueue->postEvent(rk_id_from_win(hWnd), event);
                return 0;
        }
        case WM_PAINT:
        {
                auto event = RkEvent::paintEvent();
                eventQueue->postEvent(rk_id_from_win(hWnd), event);
                return 0;
        }
        default:
                break;
        }

        return DefWindowProc(hWnd, msg, wParam, lParam);
}

#ifdef RK_FOR_SHARED
BOOL WINAPI DllMain(HINSTANCE hInstance,
                    DWORD fdwReason,
                    LPVOID lpvReserved)
{
        winApiInstance = hInstance;
        WNDCLASSEX wc;
        wc.cbSize        = sizeof(WNDCLASSEX);
        wc.style         = 0;
        wc.lpfnWndProc   = RkWindowProc;
        wc.cbClsExtra    = 0;
        wc.cbWndExtra    = 0;
        wc.hInstance     = hInstance;
        wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
        wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
        wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
        wc.lpszMenuName  = NULL;

        std::random_device r;
        std::default_random_engine e1(r());
        std::uniform_int_distribution<int> uniform_dist(1, 1000000);
        int mean = uniform_dist(e1);
        rk_winApiClassName = ("Redkite_" + std::to_string(mean)).c_str();
        wc.lpszClassName = rk_winApiClassName.c_str();
        wc.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);

        if (!RegisterClassEx(&wc)) {
                RK_LOG_ERROR("can't register window class");
                return FALSE;
        }
        return TRUE;
}
#else // RK_FOR_SHARED
static inline char *wideToMulti(int codePage, const wchar_t *aw)
{
        const int required = WideCharToMultiByte(codePage, 0, aw, -1, NULL, 0, NULL, NULL);
        char *result = new char[required];
        WideCharToMultiByte(codePage, 0, aw, -1, result, required, NULL, NULL);
        return result;
}

int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine,
                   int nCmdShow)
{
        rk_winApiInstance = hInstance;
        WNDCLASSEX wc;
        wc.cbSize        = sizeof(WNDCLASSEX);
        wc.style         = 0;
        wc.lpfnWndProc   = RkWindowProc;
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
        rk_winApiClassName = wc.lpszClassName;
        wc.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);

        if (!RegisterClassEx(&wc)) {
                RK_LOG_ERROR("can't register window class");
                return 1;
        }

        int argc;
        wchar_t **argvW = CommandLineToArgvW(GetCommandLineW(), &argc);
        if (!argvW)
                return 1;

        std::vector<char*> args(argc, nullptr);
        for (decltype(args.size()) i = 0; i < args.size(); i++)
                args[i] = wideToMulti(CP_ACP, argvW[i]);
        LocalFree(argvW);

        const int exitCode = main(args.size(), args.data());
        for (auto arg : args)
                delete [] arg;

        return exitCode;
}
#endif // RK_FOR_SHARED
