using System;
using System.Windows.Forms;
using ChelasUIMaker.Engine;
namespace ChelasUIMakerApp
{
    internal class MyConfig : Config
    {
        protected override void LoadConfig()
        {
            var area1 = DefineArea<Panel>(p => { p.Width = 390; })
                        .WithContent<TextBox>(DefineArea<TextBox>(tb => { tb.Name = "visor"; tb.Dock = DockStyle.Fill; }))
                        .WithContent<Button>(DefineArea<Button>(b1 => { b1.Top = 50; b1.Text = "Botao 1"; }))
                        .WithContent<Button>(DefineArea<Button>(b2 => { b2.Top = 75; b2.Text = "Botao 2"; }));

            var area2 = DefineArea<Panel>(p => { p.Top = 100; p.Width = 390; })
                        .WithContent<Button>(DefineArea<Button>(b1 => { b1.Top = 50; b1.Text = "Botao 3"; }))
                        .WithContent<Button>(DefineArea<Button>(b2 => { b2.Top = 50; b2.Left = 300; b2.Name = "B4"; b2.Text = "Botao 4"; }));


            DefineArea<Form>(f =>
            {
                f.Text = "Form especificado de forma declarativa";
                f.Width = 430;
            })
                .WithController<MyController>()
                .WithContent(area1)
                .WithContent(area2);

        }
    }
}