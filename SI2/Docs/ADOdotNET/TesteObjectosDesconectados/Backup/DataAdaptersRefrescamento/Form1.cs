using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;

using System.Drawing;
using System.Text;
using System.Windows.Forms;


using System.Data.SqlClient;
using System.Data.Common;


namespace DataAdaptersRefrescamento
{
    public partial class Form1 : Form
    {
        private SqlDataAdapter da;
        private DataTable tbl;

        public Form1()
        {
           InitializeComponent();

           string strConn = "Address=(local)\\instancia1;Database=SI_2;User ID=sa;Password=123;";

           SqlConnection cn = new SqlConnection(strConn);

           tbl = new DataTable();
           tbl.Columns.Add("cod",typeof(System.String));
           tbl.Columns.Add("nome",
               typeof(System.String));
           tbl.Columns.Add("ts",typeof(System.Byte[]));
    
           tbl.PrimaryKey = new DataColumn[] {tbl.Columns["cod"]};
            
           string SelectDisc =
               "SELECT cod,nome,ts FROM disciplinasAdo";

           da = new SqlDataAdapter(SelectDisc,cn);
           DataTableMapping tm = da.TableMappings.Add("Table","disciplinas");

           da.Fill(tbl);
           /*
            foreach (DataColumn c in tbl.Columns)
               MessageBox.Show(c.ColumnName + " " + c.DataType);
           */
           CriarUpdateCmd(da,cn);
           CriarInsertCmd(da,cn);

           dataGridView1.DataSource = tbl;  
        

        }
   
       
		private void CriarInsertCmd(SqlDataAdapter da,SqlConnection cn)
		{
			string insStr = "INSERT INTO disciplinasADO(cod, nome)VALUES(@p1,@p2);"+
	            "SELECT cod,nome,ts FROM disciplinasADO WHERE cod = @p3";

           SqlCommand insCmd = new SqlCommand(insStr,cn);
           SqlParameterCollection pc = insCmd.Parameters;
           pc.Add("@p1",SqlDbType.VarChar,10,"cod");
           pc.Add("@p2",SqlDbType.VarChar,10,"nome");
           pc.Add("@p3",SqlDbType.VarChar,10,"cod"); 
           insCmd.UpdatedRowSource = UpdateRowSource.FirstReturnedRecord; 
           da.InsertCommand = insCmd;

		}


		private void CriarUpdateCmd(SqlDataAdapter da,SqlConnection cn)
		{
			// A associação dos novos valores à linha é feita pelos nomes
			// das colunas (incluindo TableMappings e ColumnMappings)
			// e não tem nada a ver com os parâmetros
			// imaginamos que só se permite alteração da colona "nome”:
			// COMO o timestamp é único por Base de Dados, temos:
			string updtStr = "UPDATE disciplinasADO SET cod=@cod,nome=@nome WHERE ts = @ts;"+
	              "SELECT cod,nome,ts FROM disciplinasADO WHERE cod = @c";
            SqlCommand updCmd = new SqlCommand(updtStr,cn);
            SqlParameterCollection pc = updCmd.Parameters;
            SqlParameter par = pc.Add("@cod",SqlDbType.Char,10,"cod");
            par = pc.Add("@nome",SqlDbType.Char,50,"nome");
            par = pc.Add("@ts",SqlDbType.Timestamp,0,"ts");
            par.SourceVersion = DataRowVersion.Original;
            par = pc.Add("@c",SqlDbType.VarChar,10,"cod"); // valor corrente
            updCmd.UpdatedRowSource = UpdateRowSource.FirstReturnedRecord; 
            da.UpdateCommand = updCmd;
		}

        private void Actualizar_Click(object sender, EventArgs e)
        {
            try
            {
                da.ContinueUpdateOnError = true;
                da.Update(tbl);
            }
            catch (Exception e1)
            {
                MessageBox.Show(e1.ToString());
            }
            tbl.AcceptChanges();
        }

        private void dataGridView1_DataError(object sender, DataGridViewDataErrorEventArgs e)
        {
            // Foi necessario isto para deixar de dar um erro parvo
        }

    }
}