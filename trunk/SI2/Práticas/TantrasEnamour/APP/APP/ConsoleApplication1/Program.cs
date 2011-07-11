using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Data.SqlClient;
using System.Data;

namespace ConsoleApplication1
{
    class Program
    {

        readonly static string strConn = "server=(local),49664;Database=SI2;User ID=nac-admin;Password=admin2011;";
        static SqlConnection cn;
        static SqlCommand cmd;
        static SqlDataReader rdr;

        
        public static Boolean CreateCourses(String Name , int active, Double price )
        {
            Boolean result= false;
            Console.WriteLine("\nCreate Courses:\n");
            try
            {
                SqlCommand cmd = new SqlCommand("CreateCourses", cn);
                cmd.CommandType = CommandType.StoredProcedure;
                cmd.Parameters.Add(new SqlParameter("@Name", Name));
                cmd.Parameters.Add(new SqlParameter("@active", active));
                cmd.Parameters.Add(new SqlParameter("@price", price));
                rdr = cmd.ExecuteReader();
                result = true;
                Console.WriteLine("\n Success\n");
            }
            finally
            {
                if (cn != null)
                {
                    cn.Close();
                }
                if (rdr != null)
                {
                    rdr.Close();
                }
            }
            return result;
        }

        public static Boolean CreateIngredients(String Name , int  Qty_reserved, int Unit )
        {
            Boolean result = false;
            Console.WriteLine("\nCreate CreateIngredients:\n");
            try
            {
                SqlCommand cmd = new SqlCommand("CreateIngredients", cn);
                cmd.CommandType = CommandType.StoredProcedure;
                cmd.Parameters.Add(new SqlParameter("@Name", Name));
                cmd.Parameters.Add(new SqlParameter("@Qty_reserved", Qty_reserved));
                cmd.Parameters.Add(new SqlParameter("@Unit", Unit));
                rdr = cmd.ExecuteReader();
                result = true;
                Console.WriteLine("\n Success\n");
            }
            finally
            {
                if (cn != null)
                {
                    cn.Close();
                }
                if (rdr != null)
                {
                    rdr.Close();
                }
            }
            return result;
        }


        public static Boolean ListClientsInPortoAndLisbon()
        {
            Boolean result = false;
            Console.WriteLine("\nCreate ListClientsInPortoAndLisbon:\n");
            try
            {
                SqlCommand cmd = new SqlCommand("ListClientsInPortoAndLisbon", cn);
                cmd.CommandType = CommandType.StoredProcedure;
                rdr = cmd.ExecuteReader();
                result = true;

                // iterate through results, printing each to console
                while (rdr.Read())
                {
                    Console.WriteLine("Nome: {0} Cidade: {1}",rdr["Nome"],rdr["Cidade"]);
                }
            }
            finally
            {
                if (cn != null)
                {
                    cn.Close();
                }
                if (rdr != null)
                {
                    rdr.Close();
                }
            }
            return result;
        }
        static void Main(string[] args)
        {
        }
    }
}
