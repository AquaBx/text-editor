//
// Created by tomch on 26/10/2024.
//

#include "Snapshot.h"

Snapshot::Snapshot(const std::string& textBuffer, const std::size_t position,
                   const std::size_t selectionStart, const std::size_t selectionEnd)
        : textBuffer(textBuffer),
          position(position),
          selectionStart(selectionStart),
          selectionEnd(selectionEnd)
{
}

