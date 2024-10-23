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

    std::cout << "Selection start before Ctrl+A: " << editor.getSelectionStart() << std::endl;
    std::cout << "Selection end before Ctrl+A: " << editor.getSelectionEnd() << std::endl;

    editor.keyPressed(true, false, false, 'a');

    std::cout << "Selection start after Ctrl+A: " << editor.getSelectionStart() << std::endl;
    std::cout << "Selection end after Ctrl+A: " << editor.getSelectionEnd() << std::endl;

    unsigned long long start = editor.getSelectionStart();
    unsigned long long end = editor.getSelectionEnd();

    Tools::assert_equals(start, (unsigned long long) 0, "1 : La sélection ne commence pas au début du texte. Actual: " + std::to_string(start) + "; Expected: " + std::to_string(0));
    Tools::assert_equals(end, editor.getTextBuffer().length(), "2 : La sélection ne couvre pas tout le texte. Actual: " + std::to_string(end) + "; Expected: " + std::to_string(editor.getTextBuffer().length()));

    editor.keyPressed(true, false, false, 'c');

    Tools::assert_equals(editor.getClipboard(), editor.getTextBuffer(), "3 : Le presse-papier ne contient pas tout le texte. Actual: " + editor.getClipboard() + "; Expected: " + editor.getTextBuffer());
    Tools::assert_equals(editor.getSelectionStart(), start, "4 : Le début de la sélection a changé après la copie. Actual: " + std::to_string(start) + "; Expected: " + std::to_string(editor.getSelectionStart()));
    Tools::assert_equals(editor.getSelectionEnd(), end, "5 : La fin de la sélection a changé après la copie. Actual: " + std::to_string(end) + "; Expected: " + std::to_string(editor.getSelectionStart()));
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
