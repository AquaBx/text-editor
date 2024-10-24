#include "ZoomEditorCommand.h"
#include <string>

ZoomEditorCommand::~ZoomEditorCommand() = default;

ZoomEditorCommand::ZoomEditorCommand(TextEditor& textEditor, float zoom)
    : textEditor(textEditor),
      zoom(zoom)
{
}

void ZoomEditorCommand::execute()
{
  float newZoom = textEditor.getFontScale()+zoom;
    if (newZoom >= 0.5 && newZoom <= 1.5) {
        textEditor.setFontScale(newZoom);
    }
}
