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

    Tools::assert_equals(editor.getSelectionStart(), (unsigned long long) 1, "1 : Le curseur n'est pas en position 1 après le déplacement.");
    Tools::assert_equals(editor.getSelectionEnd(), (unsigned long long) 1, "2 : La fin de la sélection n'est pas en position 1 après le déplacement.");

    editor.keyPressed(false, false, true, SDLK_RIGHT);

    Tools::assert_equals(editor.getSelectionStart(), (unsigned long long) 1, "3 : La sélection commence à la mauvaise position.");
    Tools::assert_equals(editor.getSelectionEnd(), (unsigned long long) 2, "4 : La fin de la sélection n'est pas correcte après sélection.");

    editor.keyPressed(false, false, true, SDLK_LEFT);

    Tools::assert_equals(editor.getSelectionStart(), (unsigned long long) 1, "5 : La sélection n'a pas correctement désélectionné le caractère. Actual: " + std::to_string(static_cast<unsigned long long>(editor.getSelectionStart())) + "; Expected: " + std::to_string(1));
    Tools::assert_equals(editor.getSelectionEnd(), (unsigned long long) 1, "6 : La fin de la sélection après désélection n'est pas correcte. Actual: " + std::to_string(static_cast<unsigned long long>(editor.getSelectionEnd())) + "; Expected: " + std::to_string(1));
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