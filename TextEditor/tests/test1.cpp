//
// Created by tomch on 17/10/2024.
//
#include <cassert>
#include <iostream>

#include "../src/TextEditor/TextEditor.h"

int test_case_1() {
    TextEditor editor;
    editor.setTextBuffer("This is a test");
    editor.setClipboard("clipboard");

    unsigned long long start = editor.getSelectionStart();
    unsigned long long end = editor.getSelectionEnd();

    if (start != end) {
        return 1;
    }

    editor.keyPressed(false,false,false,SDLK_a);

    if (editor.getSelectionStart() != start+1) {
        return 1;
    }

    if (editor.getSelectionEnd() != end+1) {
        return 1;
    }

    if (editor.getTextBuffer() != "aThis is a test") {
        return 1;
    }

    return 0;
}

int main()
{

    std::cout << "--------- test1 --------" << std::endl;
    int result = test_case_1();
    std::cout << "Error Code : " << result << std::endl;
    std::cout << "---- test1 finished ----" << std::endl;

    return result;
}

int WinMain(int argc, char** argv)
{
    return main();
}
