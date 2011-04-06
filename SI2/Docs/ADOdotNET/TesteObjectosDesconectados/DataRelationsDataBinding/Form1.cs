using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace DataRelationsDataBinding
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();

            DataSet ds = new DataSet();
            regGrid.ReadOnly = true;
            regGrid.AllowUserToAddRows = false;
            vendGrid.ReadOnly = true;
            ds = new DataSet();
            ds.Tables.Add("vendasDesligado");
            ds.Tables["vendasDesligado"].Columns.Add("prod",
                System.Type.GetType("System.String"));
            ds.Tables["vendasDesligado"].Columns.Add("quant",
                System.Type.GetType("System.Int32"));
            ds.Tables["vendasDesligado"].Columns.Add("cstunit",
                System.Type.GetType("System.Single"));
            ds.Tables["vendasDesligado"].Columns.Add("reg",
                System.Type.GetType("System.String"));
            ds.Tables["vendasDesligado"].Columns["reg"].AllowDBNull = false;

            /* coluna calculável */
            DataColumn preco = new DataColumn("preco", typeof(System.Single));
            preco.Expression = "cstunit*quant";
            preco.ReadOnly = true;
            ds.Tables["vendasDesligado"].Columns.Add(preco);

            ds.Tables.Add("regioesDesligado");
            ds.Tables["regioesDesligado"].Columns.Add("reg",
                System.Type.GetType("System.String"));
            ds.Tables["regioesDesligado"].Columns.Add("descr",
                System.Type.GetType("System.String"));

            DataTable vendas = ds.Tables["vendasDesligado"];
            DataTable regioes = ds.Tables["regioesDesligado"];
            vendas.PrimaryKey = new DataColumn[] { vendas.Columns["prod"] };
            regioes.PrimaryKey = new DataColumn[] { regioes.Columns["reg"] };

            // definir a relação pai-filho
            ds.Relations.Add("rel1", regioes.Columns["reg"], vendas.Columns["reg"]);

            DataRow r = regioes.NewRow();
            r["reg"] = "reg1";
            r["descr"] = "descricao da regiao 1";
            regioes.Rows.Add(r);
            r = regioes.NewRow();
            r["reg"] = "reg2";
            r["descr"] = "descricao da regiao 2";
            regioes.Rows.Add(r);
            regioes.AcceptChanges();

            r = vendas.NewRow();
            r["prod"] = "novoProd1";
            r["quant"] = 3;
            r["cstunit"] = 2.7;
            r["reg"] = "reg1";
            vendas.Rows.Add(r);
            r = vendas.NewRow();
            r["prod"] = "novoProd2";
            r["quant"] = 10;
            r["cstunit"] = 10.2;
            r["reg"] = "reg1";
            vendas.Rows.Add(r);
            r = vendas.NewRow();
            r["prod"] = "novoProd3";
            r["quant"] = 20;
            r["cstunit"] = 0.7;
            r["reg"] = "reg2";
            vendas.Rows.Add(r);

            vendas.AcceptChanges();

            regGrid.DataSource = regioes;
            // quando DataSource é um DataTable,
            // DataMember pode ser a tabela filhos de uma relação 
            vendGrid.DataSource = regioes;
            vendGrid.DataMember = "rel1";
         }
    }
}