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

    editor.keyPressed(false, false, false, SDLK_RIGHT);
    unsigned long long start = editor.getSelectionStart();
    unsigned long long end = editor.getSelectionEnd();

    Tools::assert_equals(start, (unsigned long long) 1, "1 : Le curseur n'est pas en position 1 après le déplacement.");
    Tools::assert_equals(end, (unsigned long long) 1, "2 : La fin de la sélection n'est pas en position 1 après le déplacement.");

    editor.keyPressed(false, false, true, SDLK_RIGHT);
    Tools::assert_equals(editor.getSelectionStart(), start, "3 : La sélection commence à la mauvaise position.");
    Tools::assert_equals(editor.getSelectionEnd(), (unsigned long long) 2, "4 : La fin de la sélection n'est pas correcte après sélection.");

    editor.keyPressed(false, false, true, SDLK_LEFT);
    Tools::assert_equals(editor.getSelectionStart(), start, "5 : La sélection n'a pas correctement désélectionné le caractère.");
    Tools::assert_equals(editor.getSelectionEnd(), end, "6 : La fin de la sélection après désélection n'est pas correcte.");
}

int main()
{
    int result;
    std::cout << "--------- test --------" << std::endl;
    std::cout << "Description : Se déplace en position 1, sélectionne le caractère 2, et le déselectionne" << std::endl;
    result = Tools::test(test_case);
    std::cout << "Error Code : " << result << std::endl;
    std::cout << "---- test finished ----" << std::endl;

    return result;
}

int WinMain(int argc, char** argv)
{
    return main();
}
