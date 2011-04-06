using System;
using System.Collections.Generic;
using System.Text;

using System.Data;
using System.Data.Common;
using System.Data.SqlClient;


namespace CriarDataSets
{
    class Program
    {
        static void Main(string[] args)
        {
            //Create table in ado.net
            DataSet ds = new DataSet();
            ds.Tables.Add("vendasDesligado");
            ds.Tables["vendasDesligado"].Columns.Add("prod",
                                  System.Type.GetType("System.String")); //ou typeof
            ds.Tables["vendasDesligado"].Columns.Add("quant",
                                  typeof(System.Int32));
            ds.Tables["vendasDesligado"].Columns.Add("cstunit",
                                  typeof(System.Single));

            /* coluna calculável */
            DataColumn preco = new DataColumn("preco", typeof(System.Single));
            preco.Expression = "cstunit*quant";
            preco.ReadOnly = true;
            ds.Tables["vendasDesligado"].Columns.Add(preco);
            DataTable tbl = ds.Tables["vendasDesligado"];
            tbl.PrimaryKey = new DataColumn[] { tbl.Columns["prod"] };

            String SelectStr =
                   "SELECT produto, quantidade, custoUnitario FROM vendasADO";
            // string strConn = "Address=(local)\\instancia1;Database=SI_2;User ID=sa;Password=123;";
            string strConn = "Data Source=(local);Initial Catalog=SI2;Integrated Security=true;";
            SqlConnection cn = new SqlConnection(strConn);
            SqlDataAdapter da = new SqlDataAdapter(SelectStr, cn);
            DataTableMapping tm = da.TableMappings.Add("Table", "vendasDesligado");
            tm.ColumnMappings.Add("produto", "prod");
            tm.ColumnMappings.Add("quantidade", "quant");
            tm.ColumnMappings.Add("custoUnitario", "cstunit");
            ds.EnforceConstraints = false;
            //Add "ds" to SqlDataAdapter
            da.Fill(ds);
            ds.EnforceConstraints = true;
            System.Console.WriteLine("O que chegou da BD:\n");
            foreach (DataRow row in tbl.Rows)
            {
                foreach (DataColumn col in tbl.Columns)
                    Console.Write(col.ColumnName + " " +
                        row[col].ToString() + " ");
                Console.WriteLine("\n-------------------------------------------");
            }

            //add a new row in table
            DataRow r = tbl.NewRow();
            r["prod"] = "novoProd1";
            r["quant"] = 3;
            r["cstunit"] = 2.7;
            tbl.Rows.Add(r);
            r = tbl.NewRow();
            r["prod"] = "novoProd2";
            r["quant"] = 10;
            r["cstunit"] = 10.2;
            tbl.Rows.Add(r);
            tbl.AcceptChanges();

            //confirme that values are in data base
            System.Console.WriteLine("\n================\n");
            System.Console.WriteLine("O que chegou da BD e os novos:\n");
            foreach (DataRow row in tbl.Rows)
            {
                foreach (DataColumn col in tbl.Columns)
                    Console.Write(col.ColumnName + " " +
                        row[col].ToString() + " ");
                Console.WriteLine("\n-------------------------------------------");
            }
            /*
            // para provocar uma violação de restrições
            r = tbl.NewRow();
            r["prod"] = "novoProd2";
            r["quant"] = 10;
            r["cstunit"] = 10.2;
            tbl.Rows.Add(r);
            tbl.AcceptChanges();
            */
            Console.ReadLine();
        }
    }
}
