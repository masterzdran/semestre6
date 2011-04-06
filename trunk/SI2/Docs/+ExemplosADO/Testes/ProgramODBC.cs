using System;
using System.Data.Odbc;
class Demo{
  public static void Main(string[] args){
    try{
      OdbcCommand comm = new OdbcCommand();
      // for MySQL
      /* comm.Connection = new OdbcConnection(
        "DSN=SIDEETC;user=root;password=;"); */
        
      // for SQLServer
      comm.Connection = new OdbcConnection(
        "DSN=SIDEETC_MSSQL;user=root;password=;");
      
        
      String sql = @"SELECT NUMMEC, NOME,  EMAIL FROM aluno a WHERE NUMMEC >30000";
      comm.CommandText = sql;
      comm.Connection.Open();
      OdbcDataReader cursor = comm.ExecuteReader();
      while (cursor.Read())
        Console.WriteLine(cursor["NUMMEC"] + "\t"+
                          cursor["EMAIL"] + "\t"+
                          cursor["NOME"]);
      comm.Connection.Close();
    }catch (Exception e){
      Console.WriteLine(e.ToString());
    }
  }
}
