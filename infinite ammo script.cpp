#include <iostream>
#include <Windows.h>
using namespace std;
#define WINDOW_NAME "Call of Duty\xAE" //تعريف نافذة اللعبة
#define COLT_M1911_CLIP_ADDRESS 0x018ED67C // تعريف العنوان المراد تعديله
#define POLL_RATE 100 
int main(int argc, char** argv)
{
    // اسم التطبيق
    SetConsoleTitleA("World at War CHEAT");
    cout << "START THE GAME FIRST" << endl;
    HWND handle_to_game_window = NULL;
    while (handle_to_game_window == NULL)
    {
        //اسم النافذة
        handle_to_game_window = FindWindowA(NULL, WINDOW_NAME);
        Sleep(POLL_RATE);
    }
    cout << "Handle To Game .." << endl;
    DWORD process_id;
    GetWindowThreadProcessId(handle_to_game_window, &process_id);
    if (process_id != NULL)
    {
        // في حال حصل اللعبة فاتحه
        cout << "Process ID Found" << endl;
    }
    else // في حال كانت اللعبة مقفله او يوجد خطاء في العثور على عنوان العملية
    {
        cout << "Process ID not Found" << endl;
        exit(1);
    }
    HANDLE process_handle;
    process_handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, process_id);
    if (process_handle != NULL)
    {
        cout << "Process Opened" << endl;
    }
    else
    {
        cout << "Process was not opened" << endl;
    }
    bool lock_clip = false;
    bool update_screen = true;
    while (true)
    {
        if (update_screen)
        {
            // الكلام اللي يطلع بالكونسول
            system("cls");
            cout << "World at War CHEAT" << endl;
            cout << "##################" << endl;
            cout << " [F1] - (" << (lock_clip ? "ON" : "OFF") << ") Lock Clip " << endl;
            update_screen = false;
        }
        // التحكم بالسكربت اثناء اللعب
        SHORT keypress;
        keypress = GetAsyncKeyState(VK_F1);
        if (keypress)
        {
            lock_clip = !lock_clip;
            update_screen = true;
        }
        if (lock_clip) // تعديل قيمة العنوان
        {
            int write_value = 50;
            WriteProcessMemory(process_handle, (LPVOID)COLT_M1911_CLIP_ADDRESS, &write_value, sizeof(write_value), NULL);
        }
    }
}

