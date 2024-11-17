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
};