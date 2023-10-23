//
// Created by Ariel Saldana on 10/22/23.
//

#include "opcodes_hash.h"

namespace std {
    template<>
    struct hash<opcodes> {
        size_t operator()(const opcodes& op) const {
            return hash<int>()(static_cast<int>(op));
        }
    };
}
