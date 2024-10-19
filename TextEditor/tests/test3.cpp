//
// Created by tomch on 17/10/2024.
//
#include <cassert>
#include <iostream>

#include "../src/TextEditor/TextEditor.h"

#include "tools.h"

void test_case() {
    TextEditor editor;
    editor.setTextBuffer("This is a test");
    editor.setClipboard("clipboard");

    editor.keyPressed(false,false,false,SDLK_RIGHT);

    unsigned long long start = editor.getSelectionStart();
    unsigned long long end = editor.getSelectionEnd();

    editor.keyPressed(false,false,true,SDLK_RIGHT);
    editor.keyPressed(false,false,true,SDLK_LEFT);

    Tools::assert_equals(editor.getSelectionStart(),start, "Pas le bon comportement");
    Tools::assert_equals(editor.getSelectionEnd(),end,"Pas le bon comportement");
}
int main(){
    int result;
    std::cout << "--------- test1 --------" << std::endl;
    result = Tools::test(test_case);
    std::cout << "Error Code : " << result << std::endl;
    std::cout << "---- test1 finished ----" << std::endl;

    return result;
}

int WinMain(int argc, char** argv)
{
    return main();
}
