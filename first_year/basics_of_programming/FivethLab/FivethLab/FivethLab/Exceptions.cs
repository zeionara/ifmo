using System;

public class ValueWasSkippedException : Exception
{
    public string description = "Skipped by user";
    public override string Message
    {
        get
        {
            return description;
        }
    }
}

public class OperationWasCancelledException : Exception
{
    public string description = "Cancelled by user";
    public override string Message
    {
        get
        {
            return description;
        }
    }
}

public class OperationWasCrashedException : Exception
{
    public string description = "Something happened";
    public override string Message
    {
        get
        {
            return description;
        }
    }
}

public class PolygonNotFoundedException : Exception
{
    public string description = "Polygon wasn't founded";
    public override string Message
    {
        get
        {
            return description;
        }
    }
}

public class IncompatibleTypesException : Exception
{
    public string description = "Objects have incompatible types";
    public override string Message
    {
        get
        {
            return description;
        }
    }
}

