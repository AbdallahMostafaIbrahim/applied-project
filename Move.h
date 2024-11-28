#include <iostream>

enum MoveType
{
    Insert = 0,
    Remove = 1
};

struct Move
{
    MoveType type;
    int row;
    int column;
    int value;
    // Overload Cout operator
    friend std::ostream &operator<<(std::ostream &os, const Move &move)
    {
        os << "Move: ";
        if (move.type == MoveType::Insert)
        {
            os << "Insert ";
        }
        else
        {
            os << "Remove ";
        }
        os << move.value << " at (" << move.row << ", " << move.column << ")";
        return os;
    }
};