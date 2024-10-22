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

    Tools::assert_equals(start, (unsigned long long) 0, "1 : La sélection ne commence pas au début du texte. Actual: " + std::to_string(start) + "; Expected: " + std::to_string(0));
    Tools::assert_equals(end, editor.getTextBuffer().length(), "2 : La sélection ne couvre pas tout le texte.");

    editor.keyPressed(true, false, false, 'c');

    Tools::assert_equals(editor.getClipboard(), editor.getTextBuffer(), "3 : Le presse-papier ne contient pas tout le texte.");
    Tools::assert_equals(editor.getSelectionStart(), start, "4 : Le début de la sélection a changé après la copie.");
    Tools::assert_equals(editor.getSelectionEnd(), end, "5 : La fin de la sélection a changé après la copie.");
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
