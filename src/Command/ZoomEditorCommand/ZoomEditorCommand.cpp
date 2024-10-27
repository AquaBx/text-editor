#include "ZoomEditorCommand.h"

ZoomEditorCommand::ZoomEditorCommand(TextEditor& textEditor, const float zoom)
    : Command(textEditor), zoom(zoom)
{
}

void ZoomEditorCommand::execute()
{
    if (const float newZoom = textEditor.getFontScale() + zoom; newZoom >= 0.5 && newZoom <= 1.5)
    {
        textEditor.setFontScale(newZoom);
    }
}
