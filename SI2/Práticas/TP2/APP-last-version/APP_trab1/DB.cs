using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Data.SqlClient;
using System.Data;

namespace APP_trab1
{
    public class DB{
        private readonly static string strConn = @"Initial Catalog=SI2_TP1;Data Source=ELVISP-PC\SQLEXPRESS;Integrated Security=SSPI";
        private static SqlConnection cn;
        private static SqlCommand cmd;
        private static SqlDataReader rdr;
        static DB()
        {
            cn = new SqlConnection(strConn);
        }
        public static Boolean CreateCourses(String Name, int active, Double price, string type, int idcatalog)
        {
            Boolean result = false;
            Console.WriteLine("\nCreate Courses:\n");
            try
            {
                cn.Open();
                SqlCommand cmd = new SqlCommand("CreateCourses", cn);
                cmd.CommandType = CommandType.StoredProcedure;
                cmd.Parameters.Add(new SqlParameter("@Name", Name));
                cmd.Parameters.Add(new SqlParameter("@active", active));
                cmd.Parameters.Add(new SqlParameter("@price", price));
                cmd.Parameters.Add(new SqlParameter("@type", type));
                cmd.Parameters.Add(new SqlParameter("@idCatalog", idcatalog));
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

        /**
         * Método para inserir registo de Reunião
         * FUNCIONA!!*/
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
                cmd.CommandText = String.Format("set dateformat dmy; INSERT INTO MEETING (COMMENT_ID,DATE,DETAILS) values ({0},'{1}','{2}')", comment_id, date, details);
                cmd.ExecuteNonQuery();
                cmd.CommandText = String.Format("set dateformat dmy; update COMMENTS set STATUS = 1 where ID = {0}", comment_id);
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

            System.Console.Write("\n\nEnd. Press Enter.");
            System.Console.ReadLine();

            return ret;
        }

        public class Comment
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
        FUNCIONA!!*/

        public IEnumerable<Comment> AllComments()
        {
            return ReadComments("select id,CUSTOMER_ID,COURSES_ID,GRADE,COMMENT from COMMENTS");
        }

        public IEnumerable<Comment> NegativeComments()
        {
            return ReadComments("select id,CUSTOMER_ID,COURSES_ID,GRADE,COMMENT from COMMENTS where grade < 4");
        }

        public IEnumerable<Comment> CommentsWithoutMeeting()
        {
            return ReadComments("select id,CUSTOMER_ID,COURSES_ID,GRADE,COMMENT from COMMENTS where status = 0 and grade < 4");
        }


        private IEnumerable<Comment> ReadComments(string strSQL)
        {
            cn = new SqlConnection(strConn);
            cmd = new SqlCommand(strSQL, cn);
            cn.Open();
            SqlDataReader rdr = cmd.ExecuteReader();
            List<Comment> list = new List<Comment>();
            while (rdr!=null && rdr.HasRows & rdr.Read())
            {
                Comment c = new Comment(Convert.ToInt32(rdr.GetValue(0).ToString()),
                                        Convert.ToInt32(rdr.GetValue(1).ToString()),
                                        Convert.ToInt32(rdr.GetValue(2).ToString()),
                                        Convert.ToInt32(rdr.GetValue(3).ToString()),
                                        rdr.GetValue(4).ToString());
                list.Add(c);
            }
            if(rdr!=null)rdr.Close();
            cn.Close();
            return (list.Count == 0) ? null : list;
        }
    }
}
