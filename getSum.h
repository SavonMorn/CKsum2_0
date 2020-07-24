#pragma once
#include "wx/wx.h"
//#include <Windows.h>
#include <filesystem>
#include <fstream>
#include <unordered_map>
#include <stdio.h>

namespace fs = std::filesystem;

class getSum
{
    fs::path mainPath;
    fs::path mainPath2;
    std::unordered_map<wxString, wxString> preFile;
    std::reference_wrapper<std::unordered_map<wxString, wxString>> refPreFile = preFile;
    std::unordered_map<wxString, wxString> preFile2;
    std::reference_wrapper<std::unordered_map<wxString, wxString>> refPreFile2 = preFile2;
    int menuItem = 0;
    wxTextCtrl* outBox = nullptr;

  /*  STARTUPINFOA si = { 0 };
    PROCESS_INFORMATION pi = { 0 };
    HANDLE STDout_rd = NULL;
    HANDLE STDout_wr = NULL;
    HANDLE STDin_rd = NULL;
    HANDLE STDin_wr = NULL;
    SECURITY_ATTRIBUTES sa;*/
    
public:
    getSum(wxTextCtrl* Box);
    void out(int menuItem, wxString& p1, wxString& p2);
    void out(int menuItem, wxString& p1);
    void out2(wxString& p2);
    void popMap(std::unordered_map<wxString, wxString>& mapRef, fs::path& mainPath);
    void ckAndPrint(const fs::directory_entry& PATH, std::unordered_map<wxString, wxString>& M);
    wxString exCMD(wxString& command);
    void test(std::unordered_map<wxString, wxString>& preFile, std::unordered_map<wxString, wxString>& preFile2);

};

