using System;
using System.Collections.Generic;
using System.Text;

using System.Data;
using System.Data.Common;
using System.Data.SqlClient;


namespace TesteObjConectados
{
    class Program
    {
        static void Main(string[] args)
        {    
            //SqlConnection cn = new SqlConnection("Data Source=(local)\\instancia1;Initial Catalog=SI_2;Integrated Security=true;");
            //SqlConnection cn = new SqlConnection("server=(local)\\instancia1;Initial Catalog=SI_2;User ID=sa;Password=123;");
            string strConn = "Address=(local)\\instancia1;Database=SI_2;User ID=sa;Password=123;";
            SqlConnection cn = new SqlConnection(strConn);
            /* Outras propriedades de connection string:
                    Connect Timeout 
                    Load Balance Timeout=
                    Max Pool Size 
                    Min Pool Size 
                    Pooling 
                    Enlist
                    ...
             */

            string strSQL = "SELECT Numero,Nome FROM Alunos";
            SqlCommand cmd = new SqlCommand(strSQL, cn);

            // Teste eventos
            System.Console.WriteLine("\n\nEvento InfoMessage");
            cn.InfoMessage += new SqlInfoMessageEventHandler(handler_InfoMessage);
            cn.Open();
            cmd.CommandText = "PRINT 'Salta';raiserror('Um erro 10',10,1)";
            cmd.ExecuteNonQuery();
            cn.Close();

            System.Console.WriteLine("\n\nEvento StateChange");
            cn.StateChange += new StateChangeEventHandler(handler_StateChange);
            cn.Open();
            cn.Close();

            cn = new SqlConnection(strConn);
            cmd = new SqlCommand(strSQL, cn);

/*            
            System.Console.WriteLine("\n\nTeste 5000 ligacoes com pooling");
            System.Console.WriteLine(System.DateTime.UtcNow);
            for (int i = 0; i < 5000; ++i)
            {
                cn.Open();
                cn.Close();
            }
            System.Console.WriteLine(System.DateTime.UtcNow);
            cn.Close();

            // retirar a indicação de pooling
            cn.ConnectionString = strConn + "pooling=false;"; // Sem connection pooling
            cn.Open();
            //Sem connection pooling
            System.Console.WriteLine("\n\nTeste 5000 ligacoes sem pooling");
            System.Console.WriteLine(System.DateTime.UtcNow);
            for (int i = 0; i < 5000; ++i)
            {
                cn.Close();
                cn.Open();
            }
            System.Console.WriteLine(System.DateTime.UtcNow);
            cn.Close();
*/
            // Leitura com ExecuteScalar
            System.Console.WriteLine("\n\nTeste ExecuteScalar");
            cn.Open();
            cmd =  new SqlCommand("Select Count(*) from alunos where numero = -1", cn);
            int n = (int)cmd.ExecuteScalar();
            System.Console.WriteLine("N = " + n);
            cn.Close();

            //Teste leitura Com DataReader
            System.Console.WriteLine("\n\nTeste DataReader");
            cmd = new SqlCommand(strSQL, cn);
            cn.Open();
            SqlDataReader rdr = cmd.ExecuteReader();
            bool res = rdr.HasRows;
            while (rdr.Read())
            {

                System.Console.WriteLine("Numero:" + rdr[0].ToString() + ",Nome: " +
                                          rdr[1].ToString());
            }
            rdr.Close();
            cn.Close();

            // Teste multiplos result sets
            System.Console.WriteLine("\n\nTeste multiplos result sets");
            strSQL = "SELECT * FROM Alunos; SELECT * FROM Alunos";
            cn.Open();
            cmd = new SqlCommand(strSQL, cn);
            rdr = cmd.ExecuteReader();
            do
            {
                while (rdr.Read())
                    Console.WriteLine("\t" + rdr.GetName(0) + " - " +
                                                  rdr.GetValue(0).ToString());
                Console.WriteLine("-------");
            } while (rdr.NextResult());
            rdr.Close();
            cn.Close();

            // Teste parâmetros
            System.Console.WriteLine("\n\nTeste de parâmetros");
            strSQL = "p";
            cn.Open(); 
        
            cmd = new SqlCommand(strSQL, cn);
            cmd.CommandType = CommandType.StoredProcedure;
            SqlParameter resp = cmd.Parameters.Add("@res", SqlDbType.Int);
            resp.Direction = ParameterDirection.ReturnValue;

            SqlParameter p1 = cmd.Parameters.Add("@p1", SqlDbType.Int);
            p1.Value = 2;  // ou: cmd.Parameters["p1"].Value = 2;

            SqlParameter p2 = cmd.Parameters.Add("@p2", SqlDbType.Int);
            p2.Direction = ParameterDirection.Output;
            rdr = cmd.ExecuteReader();
            while(rdr.Read())
                Console.WriteLine("\t"+rdr.GetName(0)+" - "+
		                rdr.GetValue(0).ToString());
            rdr.Close();
            // Só agora é que se pode ler os valores dos parâmetros
            Console.WriteLine("\tOutput = "+p2.Value.ToString());
            Console.WriteLine("\tRes = "+resp.Value.ToString());

            cn.Close();


            // Teste de transacções
            System.Console.WriteLine("\n\nTeste transacções");
            cn.Open();
            SqlTransaction tr = cn.BeginTransaction(IsolationLevel.ReadUncommitted);
            cmd = cn.CreateCommand();
            cmd.Transaction = tr;
            try
            {
                cmd.CommandText = "INSERT INTO Alunos values(500,'Ana')";
                cmd.ExecuteNonQuery();
                cmd.CommandText = "INSERT INTO Alunos values(600,'Ze Ze')";
                cmd.ExecuteNonQuery();
                tr.Commit();
            }
            catch (Exception e) 
            {
	            try
	            {
	                tr.Rollback();
	            }
	            catch (SqlException ex)
	            {
	                Console.WriteLine("Ocorreu a excepcao " + ex.GetType() +
			              " no rollback da transaccao.");
	            }
	            Console.WriteLine("Ocorreu a excepcao " + e.GetType() +
		              " ao inserir os registos.");
	            Console.WriteLine("Anuladas ambas as instrucoes.");
            }
            finally 
            {
	            cn.Close();
            }

            System.Console.Write("\n\nFim. Prima Enter");
            System.Console.ReadLine();

        }

        static void handler_InfoMessage(Object sender,
                                       SqlInfoMessageEventArgs e){
           //Console.WriteLine("Evento InfoMessage: " + e.Message +". Source: " + e.Source);
           //ou, para providers que possam enviar vários warnings:
             foreach (SqlError err in e.Errors) {
                    Console.WriteLine("A fonte {0} gerou erro com estado {1}"+
                                      ", numero {2}, classe {3} e mensagem {4}",
                                 err.Source,err.State,err.Number,err.Class,err.Message);
             }  
        }

        static void handler_StateChange(object sender, StateChangeEventArgs e)
        {
            Console.WriteLine("Evento StateChange. Mudou de " +
                                e.OriginalState.ToString() +
                                " para " +
                                e.CurrentState.ToString());
        }

 }
}	

