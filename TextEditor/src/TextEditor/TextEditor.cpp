#include "TextEditor.h"


/*class TextEditor {
    private:


    public:
*/
TextEditor::TextEditor() {}

void TextEditor::draw(Renderer& renderer)
{
    renderer.drawText(textBuffer);
}

void TextEditor::setCommand(Command *cmd) {
    this->command = cmd;
}

void TextEditor::executeCommand() {

}

void TextEditor::keyPressed(bool ctrl, bool alt, bool shift, const SDL_KeyCode key) {
    if( key )
    {
        textBuffer += static_cast<char>(key);
    }
/*

    if (key == SDLK_BACKSPACE) {
        // effacer la sélection
        return;
    }

    if (key == SDLK_DELETE) {
        // effacer la sélection
        return;
    }

    switch (ctrl) {
        case true:
            switch (key) {
                case SDLK_c:
                    new CopyCommand(selectionStart, selectionEnd, this)

                    CopyCommand.execute();
                case SDLK_v:
                    PasteCommand.execute();
                case SDLK_x:
                    CutCommand.execute();
                case SDLK_a:
                    // sélectionner tout le texte
                default:
                    // pas une commande
            }
        case false:
            switch (alt) {
                case true:
                    switch (key) {
                        case (SDLK_UP):
                            // sélection texte
                        case (SDLK_DOWN):
                            // sélection texte
                        case (SDLK_LEFT):
                            // sélection texte
                        case (SDLK_RIGHT):
                            // sélection texte
                        default:
                            // pas une commande
                    }
                case false:
                    switch (key) {
                        case (SDLK_UP):
                        case (SDLK_DOWN):
                        case (SDLK_LEFT):
                        case (SDLK_RIGHT):
                            // pas une commande
                        default:
                        // entrer texte
                        default :
                            // pas une commande
                    }
            }
    }
    */
}

void TextEditor::undoCommand() {

}

TextEditor::~TextEditor() {}
