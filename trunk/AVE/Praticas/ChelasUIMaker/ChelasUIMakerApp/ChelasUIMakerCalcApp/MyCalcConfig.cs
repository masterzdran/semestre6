   using System;
    using System.Windows.Forms;
    using System.Drawing;
 
namespace ChelasUIMakerCalcApp
{
    using ChelasUIMaker.Engine;
     internal class MyCalcConfig : Config
    {
        protected override void LoadConfig()
        {

            var area1 = DefineArea<Panel>(p => { p.Height=30; p.Width = 280; p.BackColor=Color.Gray; })
                .WithContent<TextBox>(DefineArea<TextBox>(tb => { tb.Top = 6; tb.Enabled=false; tb.Name="visor"; 
                     tb.BackColor=Color.LightYellow; tb.Text="0"; tb.TextAlign=HorizontalAlignment.Right;
                     tb.SetFont("Consolas,14"); }));

             var area2 = DefineArea<Panel>(p => { p.Name="operations"; p.Top=30; p.Width=280; p.Height=100; p.SetBackColor(0x30FFFF30); })
                .WithContent<Button>(DefineArea<Button>(b1 => { b1.Text="+"     ; b1.Top = 10;}))
                .WithContent<Button>(DefineArea<Button>(b2 => { b2.Text="+/-"   ; b2.Top = 10; b2.Left=100;}))
                .WithContent<Button>(DefineArea<Button>(b3 => { b3.Text="-"     ; b3.Top = 10; b3.Left=200;}))
                .WithContent<Button>(DefineArea<Button>(b4 => { b4.Text="*"     ; b4.Top = 50;}))
                .WithContent<Button>(DefineArea<Button>(b5 => { b5.Text="/"     ; b5.Top = 50; b5.Left=200;}))
                .WithContent<Button>(DefineArea<Button>(b6 => { b6.Text="="     ; b6.Top = 50;b6.Left=100;}));
                   

    var area3 = DefineArea<Panel>(p => { p.Top =90; p.Width = 280; p.Height=200; p.BackColor=Color.Gray; })
                .WithContent<Button>(DefineArea<Button>(b1 => { b1.Text = "1"; b1.ForeColor = Color.White; }))
                .WithContent<Button>(DefineArea<Button>(b2 => { b2.Text = "2"; b2.Left=100; b2.ForeColor = Color.White; }))
                .WithContent<Button>(DefineArea<Button>(b3 => { b3.Text = "3"; b3.Left=200; b3.ForeColor = Color.White; }))
                .WithContent<Button>(DefineArea<Button>(b4 => { b4.Text = "4"; b4.Top=50; b4.ForeColor = Color.White; }))
                .WithContent<Button>(DefineArea<Button>(b5 => { b5.Text = "5";  b5.Top=50; b5.Left=100; b5.ForeColor = Color.White; }))
                .WithContent<Button>(DefineArea<Button>(b6 => { b6.Text = "6"; b6.Top=50; b6.Left=200; b6.ForeColor = Color.White; }))
                .WithContent<Button>(DefineArea<Button>(b7 => { b7.Text = "7"; b7.Top=100; b7.ForeColor = Color.White; }))
                .WithContent<Button>(DefineArea<Button>(b8 => { b8.Text = "8"; b8.Top=100; b8.Left=100; b8.ForeColor = Color.White; }))
                .WithContent<Button>(DefineArea<Button>(b9 => { b9.Text = "9"; b9.Top=100; b9.Left=200; b9.ForeColor = Color.White; }))
                .WithContent<Button>(DefineArea<Button>(b0 => { b0.Text = "0"; b0.Top=150; b0.ForeColor = Color.White; }))
                .WithContent<Button>(DefineArea<Button>(bC => { bC.Text = "C"; bC.Top=150; bC.Left=100; bC.ForeColor = Color.White; }));

    DefineArea<Form>(f => { f.Text = "Calculadora"; f.Height = 350;f.Width=300; })
         .WithController<CalcController>()
         .WithContent(area1)
         .WithContent(area2)
         .WithContent(area3);
        }

    }
        }

        
