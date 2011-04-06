namespace DataRelationsDataBinding
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.regGrid = new System.Windows.Forms.DataGridView();
            this.vendGrid = new System.Windows.Forms.DataGridView();
            ((System.ComponentModel.ISupportInitialize)(this.regGrid)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.vendGrid)).BeginInit();
            this.SuspendLayout();
            // 
            // regGrid
            // 
            this.regGrid.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.regGrid.Location = new System.Drawing.Point(62, 12);
            this.regGrid.Name = "regGrid";
            this.regGrid.RowTemplate.Height = 24;
            this.regGrid.Size = new System.Drawing.Size(422, 166);
            this.regGrid.TabIndex = 0;
            // 
            // vendGrid
            // 
            this.vendGrid.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.vendGrid.Location = new System.Drawing.Point(62, 184);
            this.vendGrid.Name = "vendGrid";
            this.vendGrid.RowTemplate.Height = 24;
            this.vendGrid.Size = new System.Drawing.Size(422, 150);
            this.vendGrid.TabIndex = 1;
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(620, 367);
            this.Controls.Add(this.vendGrid);
            this.Controls.Add(this.regGrid);
            this.Name = "Form1";
            this.Text = "Form1";
            ((System.ComponentModel.ISupportInitialize)(this.regGrid)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.vendGrid)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.DataGridView regGrid;
        private System.Windows.Forms.DataGridView vendGrid;
    }
}

