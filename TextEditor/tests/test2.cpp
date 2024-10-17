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

    editor.keyPressed(false,false,false,SDLK_DOWN);

    unsigned long long start = editor.getSelectionStart();
    unsigned long long end = editor.getSelectionEnd();

    Tools::assert_equals(start,end, "start et end ne sont pas égaux à l'init");
    Tools::assert_equals(start ,14, "start n'est pas à la fin de la string à l'init");

    editor.keyPressed(false,false,false,SDLK_RIGHT);

    Tools::assert_equals(editor.getSelectionStart(),start, "start a bougé malgré qu'il soit à la fin de la string");
    Tools::assert_equals(editor.getSelectionEnd(),end,"end a bougé malgré qu'il soit à la fin de la string");
}

int main()
{
    int result;

    std::cout << "--------- test --------" << std::endl;
    result = Tools::boubiboulga(test_case);
    std::cout << "Error Code : " << result << std::endl;
    std::cout << "---- test finished ----" << std::endl;

    return result;
}

int WinMain(int argc, char** argv)
{
    return main();
}