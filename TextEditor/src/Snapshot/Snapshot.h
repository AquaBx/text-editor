//
// Created by tomch on 26/10/2024.
//

#pragma once
#include <string>

class Snapshot {
    friend class TextEditor;
    std::string textBuffer;
    std::size_t position{};
    std::size_t selectionStart{};
    std::size_t selectionEnd{};

    public:
        Snapshot(const std::string& textBuffer, std::size_t position, std::size_t selectionStart,
                 std::size_t selectionEnd);
        ~Snapshot() = default;
};
