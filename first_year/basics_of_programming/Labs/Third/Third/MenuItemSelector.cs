using System;

public static class MenuItemSelector
{
    public static void DisplayMenu(Menues.MenuElement[] menu)
    {
        for (int i = 0; i < menu.Length; i++)
        {
            Console.WriteLine(menu[i].description);
        }
    }

    public static int SelectMenuItem(Menues.MenuElement[] menu)
    {
        int max = menu.Length;
        do
        {
            Console.WriteLine(MessagesForUser.SELECTING_MENU_ITEM);
            string readedString = Console.ReadLine();
            int selectedElement;
            if (readedString.Length > 0)
            {
                if ((int.TryParse(readedString, out selectedElement)) &&
                    (selectedElement > 0) &&
                    (selectedElement <= max))
                {
                    return selectedElement;
                }
                else
                {
                    Console.WriteLine(MessagesForUser.INVALID_SELECTION_MENU_ITEM);
                }
            }
            else
            {
                Console.WriteLine(MessagesForUser.EMPTY_INPUT_STRING);
            }
        } while (true);
    }
}
