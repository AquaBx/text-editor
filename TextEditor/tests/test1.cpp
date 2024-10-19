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

    unsigned long long start = editor.getSelectionStart();
    unsigned long long end = editor.getSelectionEnd();

    Tools::assert_equals(start, end, "start et end ne sont pas égaux à l'init");

    editor.keyPressed(false, false, false, 'a');

    Tools::assert_equals(editor.getSelectionStart(), start + 1, "Position du curseur pas bon");
    Tools::assert_equals(editor.getSelectionEnd(), end + 1, "Position du curseur pas bon");

    Tools::assert_equals(editor.getTextBuffer(), std::string("aThis is a test"), "Textepas bon");
}

int main()
{
    int result;
    std::cout << "--------- test --------" << std::endl;
    std::cout << "Description : ajouter un caractère ajoute la lettre et décale de 1 notre curseur" << std::endl;
    result = Tools::test(test_case);
    std::cout << "Error Code : " << result << std::endl;
    std::cout << "---- test finished ----" << std::endl;

    return result;
}

int WinMain(int argc, char** argv)
{
    return main();
}
