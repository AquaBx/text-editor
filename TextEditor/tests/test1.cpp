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

    unsigned long long start = editor.getSelectionStart();
    unsigned long long end = editor.getSelectionEnd();

    Tools::assert_equals(start,end, "start et end ne sont pas égaux à l'init");

    editor.keyPressed(false,false,false,SDLK_a);

    Tools::assert_equals(editor.getSelectionStart(),start+1, "");
    Tools::assert_equals(editor.getSelectionEnd(),end+1,"");

    Tools::assert_equals(editor.getTextBuffer(),"aThis is a test","");

}
int main()
{
    int result;
    std::cout << "--------- test1 --------" << std::endl;
    result = Tools::boubiboulga(test_case);
    std::cout << "Error Code : " << result << std::endl;
    std::cout << "---- test1 finished ----" << std::endl;

    return result;
}

int WinMain(int argc, char** argv)
{
    return main();
}
