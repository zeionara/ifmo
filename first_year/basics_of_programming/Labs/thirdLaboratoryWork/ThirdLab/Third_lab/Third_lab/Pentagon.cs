using System;

sealed class Pentagon : Polygon
{
    public Pentagon(int id)
        : base(id, 5)
    { }

    public Pentagon(int id, int[] sides)
        : base(id, 5, sides)
    { }
}