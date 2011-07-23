using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace APP_trab1
{
    public static class ConsoleApplication
    {
        private static DB _database = new DB();
        public static void RunApplication()
        {
            bool exit = false;
            int command = 0;
            Console.WriteLine("-Comands:\n\t+Show All Comments - 0\n\t+Show All Negative Comments - 1"+
                "\n\t+Show Comments Without Meeting - 2"+
                "\n\t+New Meeting - 3\n\t+New Course - 4\n\t+Exit - 5");
            while (!exit)
            {
                Console.WriteLine("\nInsert Command Please:");
                try { command = int.Parse(Console.ReadLine()); }
                catch(Exception e) { Console.WriteLine("Sintaxe Error.");continue;}
                switch (command)
                {
                    case 0: {ShowComments(1); break; }
                    case 1: {ShowComments(2); break; }
                    case 2: {ShowComments(3); break; }
                    case 3: {Meeting(); break;}
                    case 4: {Course(); break;}
                    case 5: {exit = true; break;}
                    default:{Console.WriteLine("Invalid Command."); break;}
                }
            }
        }

        private static bool ShowComments(int i)
        {
            IEnumerable<DB.Comment> ie = null;
            switch (i)
            {
                case 1: { ie = _database.AllComments(); break; }
                case 2: { ie = _database.NegativeComments(); break; }
                case 3: { ie = _database.CommentsWithoutMeeting(); break; }
                default: {return false;}
            }
            if (ie != null)
            {
                Console.WriteLine("Comments:");
                foreach (var comment in ie)
                {
                    Console.WriteLine("\tSerial Number: " + comment.ID
                                + "\n\tCustomer:" + comment.CustumerID
                                + "\n\tCourse: " + comment.COURSES_ID
                                + "\n\tGrade: " + comment.Grade
                                + "\n\tComment: " + comment.COMMENT);
                    Console.WriteLine("-------------------------------------------");
                }
            }
            else Console.WriteLine("There isn't any comments available.");
            return ie != null;
        }

        private static void Meeting()
        {
            int commentid = 0;
            int day = 0, month = 0, year = 0;
            string values = "";
            try
            {
                Console.WriteLine("Comment Serial Number:");
                commentid = int.Parse(Console.ReadLine());
                Console.WriteLine("Day:");
                day = int.Parse(Console.ReadLine());
                Console.WriteLine("Month:");
                month = int.Parse(Console.ReadLine());
                Console.WriteLine("Year:");
                year = int.Parse(Console.ReadLine());
                Console.WriteLine("Details:");
                values = Console.ReadLine();
                _database.insertMeeting(commentid, day + "/" + month + "/" + year, values);
            }
            catch (Exception)
            {
                Console.WriteLine("Invalid Parameter was given... Please re-enter the data.");
            }
        }

        private static void Course()
        {
            string name, type;
            int active = 0, idcatalog = 0;
            double price = 0;
            try
            {
                Console.WriteLine("Name:");
                name = Console.ReadLine();
                Console.WriteLine("Active (Y/N):");
                string v = Console.ReadLine();
                active = ((v!=null && v.Equals("Y")) || (v!=null &&v.Equals("y")))
                            ? 1 : 0;
                Console.WriteLine("Price:");
                price = double.Parse(Console.ReadLine());
                Console.WriteLine("Type (entry/main course/dessert/soup):");
                type = Console.ReadLine();
                Console.WriteLine("Catalog ID:");
                idcatalog = int.Parse(Console.ReadLine());
                DB.CreateCourses(name, active, price, type, idcatalog);
            }
            catch(Exception)
            {
                Console.WriteLine("Invalid Parameter was given... Please re-enter the data.");
            }
        }
    }
}
