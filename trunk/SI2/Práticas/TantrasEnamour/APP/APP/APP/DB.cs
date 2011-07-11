using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Data.SqlClient;
using System.Data;

namespace APP
{
    class DB
    {
        readonly static string strConn = "server=(local),49664;Database=SI2;User ID=nac-admin;Password=admin2011;";
        static SqlConnection cn;
        static SqlCommand cmd;
        static SqlDataReader rdr;


        public static Boolean CreateCourses(String Name, int active, Double price)
        {
            Boolean result = false;
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

        public static Boolean CreateIngredients(String Name, int Qty_reserved, int Unit)
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
                    Console.WriteLine("Nome: {0} Cidade: {1}", rdr["Nome"], rdr["Cidade"]);
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

        /**
         * Método para inserir registo de Reunião
         * */
        public Boolean insertMeeting(int comment_id, String date, String details)
        {
            Boolean ret = false;
            System.Console.WriteLine("Insert Meeting");
            cn.Open();
            SqlTransaction tr = cn.BeginTransaction(IsolationLevel.ReadUncommitted);
            cmd = cn.CreateCommand();
            cmd.Transaction = tr;
            try
            {
                cmd.CommandText = String.Format("INSERT INTO MEETING (COMMENT_ID,DATE,DETAILS) values ({0},'{1}','{2})'", comment_id, date, details);
                cmd.ExecuteNonQuery();
                tr.Commit();
                ret = true;
            }
            catch (Exception e)
            {
                try
                {
                    tr.Rollback();
                }
                catch (SqlException ex)
                {
                    Console.WriteLine("Ocorreu a excepcao " + ex.GetType() + " no rollback da transaccao.");
                }
                Console.WriteLine("Ocorreu a excepcao " + e.GetType() + " ao inserir os registos." + e.Message);

            }
            finally
            {
                cn.Close();
            }

            System.Console.Write("\n\nFim. Prima Enter");
            System.Console.ReadLine();

            return ret;
        }

        class Comment
        {
            int _id; int _CUSTOMER_ID; int _COURSES_ID; int _GRADE; string _COMMENT;
            public Comment(int id, int CUSTOMER_ID, int COURSES_ID, int GRADE, string COMMENT)
            {
                _id = id;
                _COURSES_ID = COURSES_ID;
                _CUSTOMER_ID = CUSTOMER_ID;
                _COMMENT = COMMENT;
                _GRADE = GRADE;
            }

            public int ID
            {
                get { return _id; }
            }
            public int CustumerID
            {
                get { return _CUSTOMER_ID; }
            }
            public int COURSES_ID
            {
                get { return _COURSES_ID; }
            }
            public int Grade
            {
                get { return _GRADE; }
            }
            public String COMMENT
            {
                get { return _COMMENT; }
            }
        }

        /*
        Obtem os clientes registados que tem que ser contactados.
        */
        public IEnumerable<Comment> readComments()
        {
            cn = new SqlConnection(strConn);
            string strSQL = "select id,CUSTOMER_ID,COURSES_ID,GRADE,COMMENT from COMMENTS where status = 0 and grade < 4";

            cmd = new SqlCommand(strSQL, cn);

            cn.Open();
            SqlDataReader rdr = cmd.ExecuteReader();
            List<Comment> list = new List<Comment>();

            if (rdr.HasRows)
            {
                while (rdr.Read())
                {
                    Comment c = new Comment(Convert.ToInt32(rdr.GetValue(0).ToString()), Convert.ToInt32(rdr.GetValue(1).ToString()), Convert.ToInt32(rdr.GetValue(2).ToString()), Convert.ToInt32(rdr.GetValue(3).ToString()), rdr.GetValue(4).ToString());
                    list.Add(c);
                }
            }
            rdr.Close();
            cn.Close();
            return (list.Count == 0) ? null : list;
        }

        

    }
}
