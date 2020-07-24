#include "getSum.h"

getSum::getSum(wxTextCtrl* Box) {
    outBox = Box;
    
    /*/ Set the bInheritHandle flag so pipe handles are inherited. 
    sa.nLength = sizeof(SECURITY_ATTRIBUTES);
    sa.bInheritHandle = TRUE;
    sa.lpSecurityDescriptor = NULL;
    si.cb = sizeof(STARTUPINFO);
    si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
    si.wShowWindow = SW_HIDE;
    */
    
}
void getSum::test(std::unordered_map<wxString, wxString>& preFile, std::unordered_map<wxString, wxString>& preFile2) {
    //A function that confirms what files, if any, are different in a directory
    if (preFile.size() != preFile2.size()) {
        outBox->Clear();
        outBox->WriteText( "Directories contain a different amount of items..... Checking for similarities  ");
    }
    bool testBool;
    int testVar = 0;
    for (auto it = preFile.begin(); it != preFile.end(); it++) { //Test if each files MD5 sum is the same across each directory
        if (it->second != preFile2[it->first]) {
            testVar++;
        }
    }
    if (testVar == 0) { testBool = true; }
    else { testBool = false; }

    if (testBool == true) {  //Printing the results of the previouse for loop
        outBox->Clear();
        outBox->WriteText("CKsum is the same;\n");
    }
    else {
        outBox->Clear();
        outBox->WriteText("Sum is different in the following files;\n");
        for (auto it = preFile.begin(); it != preFile.end(); it++) { //Printing any functions that failed the previouse test
            if (it->second != preFile2[it->first]) {
                outBox->WriteText(it->first);
            }
        }

    }

}
wxString getSum::exCMD(wxString& command) {
    //A basic function to pipe a command to system and return the result
    char buffer[128];
    wxString result = "";
    FILE* pipe = _popen(command.c_str(), "r"); //Opening the pipe to FILE

        if (!pipe) {
            throw " popen failed! Pipe to CMD line failed to open\n Please restart application and try again\n";
        }
        while (!feof(pipe)) { //Read to end of proccess
            if (fgets(buffer, 128, pipe) != NULL)
            result += buffer; //Using a char array buffer to add to the result string
        }
    _pclose(pipe);
    return result;
}
/*wxString getSum::exCMD(std::string& command) { //using the WinAPI CreateProcess function
    LPSTR com = const_cast<char*>(command.c_str());
    char buf[128];
    wxString exResult = "";
    bool bStatus;
    LPDWORD btRead = 0;
    // Create a pipe for the child process's STDOUT.
    if (!CreatePipe(&STDout_rd, &STDout_wr, &sa, 0)) {
        throw "Pipe Error";
    }
    if (!SetHandleInformation(STDout_rd, HANDLE_FLAG_INHERIT, 0)) {
        throw "Pipe Error";
    }
     // Create one-way pipe for child process STDIN
    if (!CreatePipe(&STDin_rd, &STDin_wr, &sa, 0)) {
       throw "Pipe Error";
    }
    // Ensure write handle to pipe for STDIN is not inherited
    if (!SetHandleInformation(STDin_rd, HANDLE_FLAG_INHERIT, 0)) {
        throw "Pipe Error";
    }
    si.hStdError = STDout_wr;
    si.hStdOutput = STDout_wr;
    si.hStdInput = STDin_wr;
    
    BOOL result = ::CreateProcessA("C:\\Windows\\System32\\cmd.exe", com, NULL, NULL, true, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi);
    if (result == false) {throw "Call to CMD failed";
    }
       
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    do{ //Read to end of proccess
            bStatus = ReadFile(STDout_rd, buf, sizeof(buf), btRead, NULL);
            exResult += buf; //Using a char array buffer to add to the result string
    } while (bStatus || btRead != 0);

    return exResult;
}*/
void getSum::ckAndPrint(const fs::directory_entry& PATH, std::unordered_map<wxString, wxString>& M) {
    //A func to take a file path, get the md5sum and store both in the unordered map;
    wxString filePath = PATH.path().string();
    wxString first = " certutil -hashfile \"";
    wxString last = "\" md5";
    wxString fullComand = first + filePath + last;
    wxString resultCK = exCMD(fullComand); //Forming and sending the comand through a pipe

    int pos = resultCK.find(filePath);
    int len = filePath.size();
    resultCK.erase(pos, len);
    resultCK.erase(0, 13);
    resultCK.erase(33);  // Isolating the MD5 sum value

    pos = filePath.rfind("\\");
    filePath = filePath.substr(pos); //Isolating the file name
    M[filePath] = resultCK;  //Pushing the name and value into the map
}
void getSum::popMap(std::unordered_map<wxString, wxString>& mapRef, fs::path& mainPath) {
    //A function that pushes every path in a directory to ckAndPrint
    fs::recursive_directory_iterator dirIt(mainPath);
    outBox->WriteText("Waiting.");
    for (const fs::directory_entry& p : dirIt) {
        if (!p.is_directory()) {
            ckAndPrint(p, mapRef);
        }
        if (outBox->GetValue() == "Waiting.........") {
            outBox->Clear();
            outBox->WriteText("Waiting.");
        }
        else { outBox->WriteText("."); }
    }
}
void getSum::out(int menuItem, wxString& p1, wxString& p2) {
    mainPath = std::string(p1);
    mainPath2 = std::string(p2);
    outBox->Clear();
     try {
         if (menuItem == 0)
         {
             popMap(refPreFile, mainPath); //Populating a map with each file and its MD5 sum
             popMap(refPreFile2, mainPath2); //Populating a map with each file and its MD5 sum again
             test(refPreFile, refPreFile2); //Testing if both maps are the same and printing the results
         }
         else if (menuItem == 2) { 
             std::ifstream outCKIn(mainPath2);
             if (outCKIn.is_open()) {  //Importing the file data to a map
                 std::string name, num;
                 while (std::getline(outCKIn, name),std::getline(outCKIn, num)) {
                     num.insert(0, "\n");
                     preFile.insert({ name, num });
                 }
                 outCKIn.close();
             }
             else { throw "File path invalid..."; }

             mainPath = std::string(p1);
             popMap(refPreFile2, mainPath);  //Populating a map with the file names and MD5 data
             test(refPreFile, refPreFile2);  //Testing if the map data matches eachother and printing the results
         }
         else if (menuItem == 3) {
             popMap(refPreFile, mainPath);  //Creating a map with the file names and MD5 data
             std::ofstream outCK("outCK.txt");   //Creating a file to export data to
             for (auto it = preFile.begin(); it != preFile.end(); it++) {  //Exporting data
                 outCK << it->first << it->second << std::endl;
             }

             outBox->WriteText("File \"outCK.txt\" created at \n");
             outBox->WriteText(mainPath2.string());
             outCK.close();
         }
 
     }
     catch (std::string& x) { outBox->WriteText(x); }
   //Exception catches for bad paths and various errors
     catch (fs::filesystem_error& x) { outBox->WriteText(x.what()); outBox->WriteText("\nMost likely a bad path...\nExiting.....\n"); }
}
void getSum::out(int menuItem, wxString& p1) {
    outBox->Clear();
    try{
        mainPath = std::string(p1);
        if (menuItem==1) {
            popMap(refPreFile, mainPath);
            outBox->WriteText("Enter next path...");
        }
        else if (menuItem == 3) {
        popMap(refPreFile, mainPath);  //Creating a map with the file names and MD5 data
        std::ofstream outCK("outCK.txt");   //Creating a file to export data to
        for (auto it = preFile.begin(); it != preFile.end(); it++) {  //Exporting data
            outCK << it->first << it->second << std::endl;
        }

        outBox->WriteText("File \"outCK.txt\" created at program launch location.\n");
        outBox->WriteText(mainPath2.string());
        outCK.close();
        }
        
    }
    catch (std::string& x) { outBox->WriteText(x); }
    //Exception catches for bad paths and various errors
    catch (fs::filesystem_error& x) { outBox->WriteText(x.what()); outBox->WriteText("\nMost likely a bad path...\nExiting.....\n"); }


}
void getSum::out2(wxString& p2) {
    outBox->Clear();
    try{
        mainPath2 = std::string(p2);
        popMap(refPreFile2, mainPath2); //Populating a map with each file and its MD5 sum again
        test(refPreFile, refPreFile2); //Testing if both maps are the same and printing the results
    }
    catch (std::string& x) { outBox->WriteText(x); }
    //Exception catches for bad paths and various errors
    catch (fs::filesystem_error& x) { outBox->WriteText(x.what()); outBox->WriteText("\nMost likely a bad path...\nExiting.....\n"); }

}