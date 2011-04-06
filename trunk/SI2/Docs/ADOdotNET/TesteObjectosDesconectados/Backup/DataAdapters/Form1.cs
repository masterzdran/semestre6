using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

using System.Data.SqlClient;
using System.Data.Common;


namespace DataAdapters
{
    public partial class Form1 : Form
    {
        private SqlDataAdapter da;
        private DataTable tbl;
        private DataSet ds;
        

        public Form1()
        {
            InitializeComponent();

            string strConn = "Address=(local)\\instancia1;Database=SI_2;User ID=sa;Password=123;";

            string SelectStr =
                    "SELECT numero, nome FROM Alunos";
            SqlConnection cn = new SqlConnection(strConn);
            da = new SqlDataAdapter(SelectStr, cn);
            ds = new DataSet();
            ds.Tables.Add("AlunosDesligado");
            ds.Tables["AlunosDesligado"].Columns.Add("num",
                        System.Type.GetType("System.Int32"));
            ds.Tables["AlunosDesligado"].Columns.Add("nome",
                        System.Type.GetType("System.String"));
            tbl = ds.Tables["AlunosDesligado"];
            tbl.PrimaryKey = new DataColumn[] { tbl.Columns["num"] };
            DataTableMapping tm = da.TableMappings.Add("Table", "AlunosDesligado");
            tm.ColumnMappings.Add("numero", "num");
            tm.ColumnMappings.Add("nome", "nome");
            ds.EnforceConstraints=false;
            da.Fill(ds);
            ds.EnforceConstraints=true;
            /*
             * // primeiro teste
             * 
            DataRow r = tbl.Rows.Find(new object[] {8000}); 
                                                         // ou: r = = tbl.Rows.Find(8000); ou r = tbl.Rows[0]
            r["num"] = 8001;
            tbl.Rows[1]["nome"] = "Novo Nome"; // = System.Convert.DBNull, ou
                                               // System.DBNull.Value; para NULL, ou
                                               // SqlString.Null
            tbl.Rows[1]["num"] = "9000";   
            
            foreach(DataRow row in tbl.Rows)
            {
	            foreach(DataColumn col in tbl.Columns)
		            MessageBox.Show(col.ColumnName+" "+
			            row[col,DataRowVersion.Original].ToString()+" "+row[col,DataRowVersion.Current].ToString()+" ");
            }
            */
            
            // 2º teste
           // CriarUpdateCmd(da, cn);
            

            //3º teste (SqlCommandBuilder)
            SqlCommandBuilder cb = new SqlCommandBuilder(da);
            MessageBox.Show(cb.GetUpdateCommand().CommandText);

            dataGridView1.DataSource = tbl; 
            
        }


        private void CriarInsertCmd(SqlDataAdapter da, SqlConnection cn)
        {
            string insStr = "INSERT INTO disciplinas(cod, nome) VALUES(?,?);" +
                            "SELECT cod,nome,ts FROM disciplinas WHERE cod = ?";
            SqlCommand insCmd = new SqlCommand(insStr, cn);
            SqlParameterCollection pc = insCmd.Parameters;
            pc.Add("cod", SqlDbType.VarChar, 10, "cod");
            pc.Add("nome", SqlDbType.VarChar, 10, "nome");
            pc.Add("cod", SqlDbType.VarChar, 10, "cod");
            insCmd.UpdatedRowSource = UpdateRowSource.FirstReturnedRecord;
            da.InsertCommand = insCmd;
        }



        private void CriarUpdateCmd(SqlDataAdapter da, SqlConnection cn)
        {
            // A associação dos novos valores à linha é feita pelos nomes
            // das colunas (incluindo TableMappings e ColumnMappings)
            // e não tem nada a ver com os parâmetros
            // imaginamos que só se permite alteração da colona "nome”:
            string updtStr =
            "UPDATE Alunos " +
            "SET numero = @numNovo, nome = @nomeNovo " +
            "WHERE numero = @numVelho AND nome = @nomeVelho; " +
            "SELECT numero, nome FROM  Alunos WHERE (numero =@numNovo)";
            // Experimentar com:
            //"SELECT 0000 as numero, nome FROM  Alunos WHERE (numero =@numNovo)";
            SqlCommand updCmd = new SqlCommand(updtStr,cn);
            SqlParameterCollection pc = updCmd.Parameters;
            pc.Add("@numNovo",SqlDbType.Int,0,"num");
            pc.Add("@nomeNovo",SqlDbType.Char,10,"nome");
            SqlParameter par = pc.Add("@numVelho",SqlDbType.Int,0,"num");
            par.SourceVersion = DataRowVersion.Original;
            par = pc.Add("@nomeVelho",SqlDbType.Char,10,"nome");
            par.SourceVersion = DataRowVersion.Original;
            da.UpdateCommand = updCmd;
        }

        private void Refrescar_Click(object sender, EventArgs e)
        {
            tbl.Clear();
            da.Fill(tbl);
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


        private void Form1_Load(object sender, EventArgs e)
        {
            // TODO: This line of code loads data into the 'sI_2DataSet.alunos' table. You can move, or remove it, as needed.

        }

    }
}