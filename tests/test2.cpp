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

    editor.keyPressed(false, false, false, SDLK_DOWN);

    unsigned long long start = editor.getSelectionStart();
    unsigned long long end = editor.getSelectionEnd();

    Tools::assert_equals(start, end, "1 : start et end ne sont pas égaux à l'initialisation");
    Tools::assert_equals(start, static_cast<unsigned long long>(14), "1 : start n'est pas à la fin de la string à l'initialisation");

    editor.keyPressed(false, false, false, SDLK_RIGHT);

    Tools::assert_equals(editor.getSelectionStart(), start, "3 : start a bougé malgré qu'il soit à la fin de la string");
    Tools::assert_equals(editor.getSelectionEnd(), end, "4 : end a bougé malgré qu'il soit à la fin de la string");
}

int main()
{
    int result;

    std::cout << "--------- test --------" << std::endl;
    std::cout << "Description : Va à la fin du buffer, et essaie de se déplacer à droite" << std::endl;
    result = Tools::test(test_case);
    std::cout << "Error Code : " << result << std::endl;
    std::cout << "---- test finished ----" << std::endl;

    return result;
}

int WinMain(int argc, char** argv)
{
    return main();
}
