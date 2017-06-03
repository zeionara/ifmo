using System;


public class ValueWasSkipped : Exception
{
    public string description = "Skipped by user"; 
	public ValueWasSkipped()
	{
	}
    public override string ToString()
    {
        return description;
    }
}

public class OperationWasCancelled : Exception
{
    public string description = "Cancelled by user";
    public OperationWasCancelled()
    {
    }
    public override string ToString()
    {
        return description;
    }
}

public class OperationWasCrashed : Exception
{
    public string description = "Something happened";
    public OperationWasCrashed()
    {
    }
    public override string ToString()
    {
        return description;
    }
}

public class PolygonNotFounded : Exception
{
    public string description = "Polygon wasn't founded";
    public override string ToString()
    {
        return description;
    }
}

