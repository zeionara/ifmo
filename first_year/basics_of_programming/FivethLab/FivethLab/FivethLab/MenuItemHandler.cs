using FourthLab;
using FourthLabBP;
using System;
using System.Collections.Generic;
using System.IO;

public static class MenuItemHandler
{
    public static void HandleSelectedGeneralMenuItem(int selectedMenuItem, ref ArrayPolygon arrayPolygon)
    {
        Polygon[] polygons;
        Polygon polygon;
        int position;
        int id;
        switch (selectedMenuItem)
        {
            case IdItemsOfGeneralMenu.APPEND:
                polygon = PolygonOperator.CreatePolygon();
                arrayPolygon.AppendElement(polygon);
                Console.WriteLine(MessagesForUser.SUCCESSFUL);
                FileSystemOperator<ArrayPolygon>.CollectionWasUpdated();
                break;
            case IdItemsOfGeneralMenu.ADD_NEW_TO_POSITION:
                polygon = PolygonOperator.CreatePolygon();
                position = PolygonOperator.ReadPosition(arrayPolygon.Length());
                arrayPolygon.AddElement(polygon, position);
                Console.WriteLine(MessagesForUser.SUCCESSFUL);
                FileSystemOperator<ArrayPolygon>.CollectionWasUpdated();
                break;
            case IdItemsOfGeneralMenu.POP_POLYGON:
                if (!IsPossibleWorkWithExistsPolygons(arrayPolygon)) { return; }
                arrayPolygon.PopElement();
                Console.WriteLine(MessagesForUser.SUCCESSFUL);
                FileSystemOperator<ArrayPolygon>.CollectionWasUpdated();
                break;
            case IdItemsOfGeneralMenu.REMOVE_POLYGON_FROM_POSITION:
                if (!IsPossibleWorkWithExistsPolygons(arrayPolygon)) { return; }
                position = PolygonOperator.ReadPosition(arrayPolygon.Length() - 1);
                arrayPolygon.RemoveElement(position);
                Console.WriteLine(MessagesForUser.SUCCESSFUL);
                FileSystemOperator<ArrayPolygon>.CollectionWasUpdated();
                break;
            case IdItemsOfGeneralMenu.REMOVE_POLYGON_WITH_ID:
                id = PolygonOperator.GetPolygonAttribute(MessagesForUser.ENTERING_ID_FOR_NEW_POLYGON, "id", 0, false);
                if (arrayPolygon.RemoveElementById(id))
                { Console.WriteLine(MessagesForUser.SUCCESSFUL); FileSystemOperator<ArrayPolygon>.CollectionWasUpdated(); }
                else { Console.WriteLine(MessagesForUser.NOT_POSSIBLE_BECAUSE_NOT_RESULTS_OF_SEARCHING_POLYGON); }
                break;
            case IdItemsOfGeneralMenu.FIND_POLYGON_BY_ID:
                id = PolygonOperator.GetPolygonAttribute(MessagesForUser.ENTERING_ID_FOR_NEW_POLYGON, "id", 0, false);
                polygon = arrayPolygon.FindPolygon(id);
                DisplayFoundedPolygon(polygon);
                break;
            case IdItemsOfGeneralMenu.PRINT_ALL_POLYGONS:
                if (!IsPossibleWorkWithExistsPolygons(arrayPolygon)) { return; }
                polygons = arrayPolygon.GetArrayOfPolygons();
                ShowAllPolygons(polygons);
                break;
            case IdItemsOfGeneralMenu.EXIT:
                Environment.Exit(0);
                break;
            case IdItemsOfGeneralMenu.PRINT_POLYGONS_WITH_TYPE:
                if (!IsPossibleWorkWithExistsPolygons(arrayPolygon)) { return; }
                FilterPolygonsAndPrint(arrayPolygon);
                break;
            case IdItemsOfGeneralMenu.WORK_WITH_FILES:
                MenuItemSelector.DisplayMenu(Menues.workWithFilesMenu);
                int selectedWorkWithFilesMenuItem = MenuItemSelector.SelectMenuItem(Menues.workWithFilesMenu);
                HandleSelectedWorkWithFilesMenuItem(selectedWorkWithFilesMenuItem, ref arrayPolygon);
                break;
            default:
                throw new OperationWasCrashedException();
        }
    }

    static void HandleSelectedWorkWithFilesMenuItem(int selectedItem, ref ArrayPolygon arrayPolygon)
    {
        switch (selectedItem)
        {
            case IdItemsOfWorkWithFilesMenu.SAVE_COLLECTION:
                FileSystemOperator<ArrayPolygon>.SaveCollection(arrayPolygon);
                break;
            case IdItemsOfWorkWithFilesMenu.LOAD_COLLECTION:
                arrayPolygon = FileSystemOperator<ArrayPolygon>.LoadCollection();
                break;
            case IdItemsOfWorkWithFilesMenu.IS_FILE_LOADED:
                if (FileSystemOperator<ArrayPolygon>.IsFileWasLoaded)
                {
                    Console.WriteLine("Yes, file was loaded");
                    break;
                }
                Console.WriteLine("No, file wasn't loaded");
                break;
            case IdItemsOfWorkWithFilesMenu.IS_CHANGES_SAVED:
                if (FileSystemOperator<ArrayPolygon>.IsChangesWasSaved)
                {
                    Console.WriteLine("Yes, changes was saved");
                    break;
                }
                Console.WriteLine("No, changes wasn't saved");
                break;
            case IdItemsOfWorkWithFilesMenu.IS_FILE_LOCKED:
                if (FileSystemOperator<ArrayPolygon>.IsFileWasLoaded)
                {
                    if (FileSystemOperator<ArrayPolygon>.IsFileLocked)
                    {
                        Console.WriteLine("Yes, loaded file locked for writing");
                        break;
                    }
                    Console.WriteLine("No, loaded file unlocked for writing");
                    break;
                }
                Console.WriteLine("No information about file");
                break;
            case IdItemsOfWorkWithFilesMenu.GO_BACK:
                break;
            default:
                throw new OperationWasCrashedException();
        }
    }
    
    static void FilterPolygonsAndPrint(ArrayPolygon polygons)
    {
        List<Polygon> filteredPolygons = new List<Polygon>();
        Console.WriteLine(MessagesForUser.SELECTING_TYPE_OF_POLYGONS);
        int polygonTypeMenuItem = PolygonOperator.SelectTypeOfPolygonFromMenu();
        switch (polygonTypeMenuItem)
        {
            case PolygonType.TRIANGLE:
                filteredPolygons = polygons.GetPolygonsWithType<Triangle>();
                break;
            case PolygonType.PARALLELOGRAM:
                filteredPolygons = polygons.GetPolygonsWithType<Parallelogram>();
                break;
            case PolygonType.PENTAGON:
                filteredPolygons = polygons.GetPolygonsWithType<Pentagon>();
                break;
            case PolygonType.HEXAGON:
                filteredPolygons = polygons.GetPolygonsWithType<Hexagon>();
                break;
            case PolygonType.HEPTAGON:
                filteredPolygons = polygons.GetPolygonsWithType<Heptagon>();
                break;
            default:
                throw new OperationWasCrashedException();
        }
        ShowAllPolygons(filteredPolygons);
        if (filteredPolygons.Count == 0)
        {
            Console.WriteLine(MessagesForUser.NO_ONE_POLYGON_FOUNDED);
        }
        return;
    }

    static bool IsPossibleWorkWithExistsPolygons(ArrayPolygon arrayPolygon)
    {
        if (arrayPolygon.Length() == 0)
        {
            Console.WriteLine(MessagesForUser.NOT_POSSIBLE_WITHOUT_POLYGONS);
            return false;
        }
        return true;
    }

    static void DisplayFoundedPolygon(Polygon polygon)
    {
        Console.WriteLine(MessagesForUser.ELEMENT_FOUNDED);
        Console.WriteLine(polygon);
    }

    static void ShowAllPolygons(Polygon[] polygons)
    {
        for (int i = 0; i < polygons.Length; i++)
        {
            Console.WriteLine(polygons[i]);
        }
    }

    static void ShowAllPolygons(List<Polygon> polygons)
    {
        for (int i = 0; i < polygons.Count; i++)
        {
            Console.WriteLine(polygons[i]);
        }
    }
}
