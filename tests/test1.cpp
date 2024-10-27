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

    Tools::assert_equals(start, end, "1 : start et end ne sont pas égaux à l'initialisation");

    editor.keyPressed(false, false, false, 'a');
    
    Tools::assert_equals(editor.getSelectionStart(), start + 1, "2 : Mauvaise position du curseur de début");
    Tools::assert_equals(editor.getSelectionEnd(), end + 1, "3 : Mauvaise position du curseur de fin");
    Tools::assert_equals(editor.getTextBuffer(), std::string("aThis is a test"), "4 : Mauvais texte : affiche '" + editor.getTextBuffer() + "'" );
}

int main()
{
    std::cout << "--------- test --------" << std::endl;
    std::cout << "Description : ajouter un caractère ajoute la lettre et décale de 1 notre curseur" << std::endl;
    const int result = Tools::test(test_case);
    std::cout << "Error Code : " << result << std::endl;
    std::cout << "---- test finished ----" << std::endl;

    return result;
}

int WinMain(int argc, char** argv)
{
    return main();
}
