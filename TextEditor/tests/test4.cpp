//
// Created by tomch on 17/10/2024.
//
#include <cassert>
#include <iostream>

#include "../src/TextEditor/TextEditor.h"

#include "tools.h"

void test_case()
{
    TextEditor editor;
    editor.setTextBuffer("This is a test");
    editor.setClipboard("clipboard");

    editor.keyPressed(true, false, false, 'a');

    unsigned long long start = editor.getSelectionStart();
    unsigned long long end = editor.getSelectionEnd();

    editor.keyPressed(true, false, false, 'c');

    Tools::assert_equals(editor.getSelectionStart(), start, "Curseur pas au bon endroit");
    Tools::assert_equals(editor.getSelectionEnd(), end, "Curseur pas au bon endroit");
    Tools::assert_equals(editor.getClipboard(), editor.getTextBuffer(), "Pas le bon clipboard");
}

int main()
{
    int result;
    std::cout << "--------- test --------" << std::endl;
    std::cout << "Description : Sélectionne tout, puis copie" << std::endl;
    result = Tools::test(test_case);
    std::cout << "Error Code : " << result << std::endl;
    std::cout << "---- test finished ----" << std::endl;

    return result;
}

int WinMain(int argc, char** argv)
{
    return main();
}
