namespace DataBinding
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
            this.components = new System.ComponentModel.Container();
            this.dataGridView1 = new System.Windows.Forms.DataGridView();
            this.bindingSource1 = new System.Windows.Forms.BindingSource(this.components);
            this.VerAlterações = new System.Windows.Forms.Button();
            this.VerOriginal = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.bindingSource1)).BeginInit();
            this.SuspendLayout();
            // 
            // dataGridView1
            // 
            this.dataGridView1.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridView1.Location = new System.Drawing.Point(40, 98);
            this.dataGridView1.Name = "dataGridView1";
            this.dataGridView1.RowTemplate.Height = 24;
            this.dataGridView1.Size = new System.Drawing.Size(525, 150);
            this.dataGridView1.TabIndex = 0;
            // 
            // VerAlterações
            // 
            this.VerAlterações.Location = new System.Drawing.Point(395, 12);
            this.VerAlterações.Name = "VerAlterações";
            this.VerAlterações.Size = new System.Drawing.Size(170, 34);
            this.VerAlterações.TabIndex = 1;
            this.VerAlterações.Text = "VerAlterações";
            this.VerAlterações.UseVisualStyleBackColor = true;
            this.VerAlterações.Click += new System.EventHandler(this.VerAlterações_Click);
            // 
            // VerOriginal
            // 
            this.VerOriginal.Location = new System.Drawing.Point(395, 58);
            this.VerOriginal.Name = "VerOriginal";
            this.VerOriginal.Size = new System.Drawing.Size(170, 34);
            this.VerOriginal.TabIndex = 2;
            this.VerOriginal.Text = "VerOriginal";
            this.VerOriginal.UseVisualStyleBackColor = true;
            this.VerOriginal.Click += new System.EventHandler(this.VerOriginal_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(600, 260);
            this.Controls.Add(this.VerOriginal);
            this.Controls.Add(this.VerAlterações);
            this.Controls.Add(this.dataGridView1);
            this.Name = "Form1";
            this.Text = "Form1";
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.bindingSource1)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.DataGridView dataGridView1;
        private System.Windows.Forms.BindingSource bindingSource1;
        private System.Windows.Forms.Button VerAlterações;
        private System.Windows.Forms.Button VerOriginal;
        
    }
}

