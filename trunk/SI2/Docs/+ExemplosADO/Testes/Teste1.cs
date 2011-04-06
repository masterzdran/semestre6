using System;
using System.Data;
using System.Data.OleDb;

namespace teste1
{
	/// <summary>
	/// Summary description for Class1.
	/// </summary>
	class Class1
	{
		/// <summary>
		/// The main entry point for the application.
		/// </summary>
		[STAThread]
		static void Main(string[] args)
		{
			//
			// TODO: Add code to start application here
			//


			// string de ligação à base de dados
			/* string strConn = "Provider=SQLOLEDB;Data Source=ssicsrv2\\alunos;"+
				"Initial Catalog=bd_si_ap;User ID='si_ap';Password='123';"+
				"Connect Timeout=30;"; */
		
			string strConn = "Provider=SQLOLEDB;Data Source=(local);"+
				"Initial Catalog=db_si_ap; Integrated Security=SSPI;"+
				"Connect Timeout=30;"; 

			
			OleDbConnection cn = new OleDbConnection(strConn); 
			try
			{
				cn.Open();
			}
			catch(InvalidOperationException iex)
			{   /* ligação já aberta */ 
			Console.WriteLine("Ligação já aberta\n");
			return;
			}
			catch(OleDbException oleex)
			{   /* erro na ligação */ 
			
			Console.WriteLine("Erro na ligação\n");
			return;
			}


			// ZONA PARA FAZER ACESSO AOS DADOS

			DataTable tbl; 
			tbl = cn.GetOleDbSchemaTable(OleDbSchemaGuid.Tables,null);
			foreach(DataRow row in tbl.Rows) 
			{
				foreach (DataColumn col in tbl.Columns)
					Console.Write("\t\t\t"+row[col].ToString());
				Console.WriteLine("\n******");
			}
			Console.ReadLine();
			Console.WriteLine("-------------");


   Object[] objRestrictions = new object[] {null, null, "alunos", null};
   tbl = cn.GetOleDbSchemaTable(OleDbSchemaGuid.Columns,objRestrictions);
			foreach(DataRow row in tbl.Rows) 
			{
				foreach (DataColumn col in tbl.Columns)
					Console.Write("\t"+row[col].ToString());
				Console.WriteLine("\n******");
			}
			Console.ReadLine();

			// Teste de evento InfoMessage
			cn.InfoMessage += new OleDbInfoMessageEventHandler(cn_InfoMessage);
			OleDbCommand cmd = cn.CreateCommand();
			cmd.CommandText="PRINT 'Information from SQL Server'";
			cmd.ExecuteNonQuery();
			cmd.CommandText="RAISERROR('Information Error',10,1)";
			cmd.ExecuteNonQuery();
			cmd.CommandText="exec sp1";
			cmd.ExecuteNonQuery();

			Console.WriteLine("---------------------------------");
			// Teste de evento StateChange
			cn.StateChange +=
				new StateChangeEventHandler(cn_StateChange);
			cn.Close();
			cn.Open();
			Console.ReadLine();

			cn.Dispose();

			//Teste de "connection pooling"
			/* strConn = @"Provider=SQLOLEDB;Data Source=ssicsrv2\\alunos;"+
				"Initial Catalog=siADONET;User ID='user_ado';Password='';"+
				"Connect Timeout=30;";*/			                    		
			cn = new OleDbConnection(strConn); 
			System.Console.WriteLine("Com pooling");
			System.Console.WriteLine(System.DateTime.UtcNow);
			for(int i = 0; i < 5000; ++i) 
			{
				cn.Close();
				cn.Open();
			}
			System.Console.WriteLine(System.DateTime.UtcNow);
			cn.Close();
			
			// retirar a indicação de pooling
			cn.ConnectionString = strConn+"OLE DB Services=-4;"; // Sem connection pooling
			cn.Open();
			//Sem connection pooling
			System.Console.WriteLine("\n\nSem pooling");
			System.Console.WriteLine(System.DateTime.UtcNow);
			for(int i = 0; i < 5000; ++i) 
			{
				cn.Close();
				cn.Open();
			}
			System.Console.WriteLine(System.DateTime.UtcNow);
			System.Console.ReadLine();
			cn.Close();
		}


		static void cn_InfoMessage(object sender, OleDbInfoMessageEventArgs e) 
		{ 
			Console.WriteLine("Evento InfoMessage: "+e.Message+"("+e.ErrorCode+"). Source: "+e.Source);
			foreach (OleDbError err in e.Errors)
			{
				Console.WriteLine("A fonte {0} recebeu um SQLState {1} com erro numero {2}: {3}",
					err.Source, err.SQLState, err.NativeError, err.Message);
			}
			Console.WriteLine(">>>>>>>");
		}

		static void cn_StateChange(object sender, StateChangeEventArgs e) 
		{  
			Console.WriteLine("Evento StateChange. Mudou de "+
				e.OriginalState.ToString() + 
				" para "+
				e.CurrentState.ToString());
		}

	}
}
