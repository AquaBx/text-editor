//
// Created by tomch on 17/10/2024.
//
#include <cassert>

#include "../src/TextEditor/TextEditor.h"

#include "tools.h"

void test_case()
{
    TextEditor editor;
    editor.setTextBuffer("This is a test");
    editor.setClipboard("clipboard");

    editor.keyPressed(true, false, false, SDLK_a);

    const unsigned long long start = editor.getSelectionStart();
    const unsigned long long end = editor.getSelectionEnd();

    editor.keyPressed(true, false, false, SDLK_c);

    Tools::assert_equals(editor.getClipboard(), editor.getTextBuffer(), "3 : Le presse-papier ne contient pas tout le texte. Actual: " + editor.getClipboard() + "; Expected: " + editor.getTextBuffer());
    Tools::assert_equals(editor.getSelectionStart(), start, "4 : Le début de la sélection a changé après la copie. Actual: " + std::to_string(start) + "; Expected: " + std::to_string(editor.getSelectionStart()));
    Tools::assert_equals(editor.getSelectionEnd(), end, "5 : La fin de la sélection a changé après la copie. Actual: " + std::to_string(end) + "; Expected: " + std::to_string(editor.getSelectionStart()));
}

int main()
{
    std::cout << "--------- test --------" << std::endl;
    std::cout << "Description : Sélectionne tout, puis copie" << std::endl;
    const int result = Tools::test(test_case);
    std::cout << "Error Code : " << result << std::endl;
    std::cout << "---- test finished ----" << std::endl;

    return result;
}

int WinMain(int argc, char** argv)
{
    return main();
}
