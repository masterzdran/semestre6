using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

using System.Data.SqlClient;

namespace DataBinding
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();

            Original();


        }

        private void VerAlterações_Click(object sender, EventArgs e)
        {
            DataTable tbl = (DataTable)bindingSource1.DataSource;
            DataTable alterados = tbl.GetChanges();
            bindingSource1.DataSource = alterados;
            
        }

        private void VerOriginal_Click(object sender, EventArgs e)
        {
            Original();

        }

        private void Original()
        {
            String SelectStr =
                           "SELECT produto, quantidade, custoUnitario FROM vendasADO";
            string strConn = "Address=(local)\\instancia1;Database=SI_2;User ID=sa;Password=123;";
            SqlConnection cn = new SqlConnection(strConn);
            SqlDataAdapter da = new SqlDataAdapter(SelectStr, cn);
            DataTable tbl = new DataTable();
            da.Fill(tbl);
            bindingSource1.DataSource = tbl;
            dataGridView1.DataSource = bindingSource1;
        }
    }
  
}