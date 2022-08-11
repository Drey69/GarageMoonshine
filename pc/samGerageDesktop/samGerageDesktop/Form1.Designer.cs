namespace samGerageDesktop
{
    partial class Form1
    {
        /// <summary>
        /// Обязательная переменная конструктора.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Освободить все используемые ресурсы.
        /// </summary>
        /// <param name="disposing">истинно, если управляемый ресурс должен быть удален; иначе ложно.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Код, автоматически созданный конструктором форм Windows

        /// <summary>
        /// Требуемый метод для поддержки конструктора — не изменяйте 
        /// содержимое этого метода с помощью редактора кода.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.Windows.Forms.DataVisualization.Charting.ChartArea chartArea1 = new System.Windows.Forms.DataVisualization.Charting.ChartArea();
            System.Windows.Forms.DataVisualization.Charting.Legend legend1 = new System.Windows.Forms.DataVisualization.Charting.Legend();
            System.Windows.Forms.DataVisualization.Charting.Series series1 = new System.Windows.Forms.DataVisualization.Charting.Series();
            System.Windows.Forms.DataVisualization.Charting.Series series2 = new System.Windows.Forms.DataVisualization.Charting.Series();
            this.tabControl1 = new System.Windows.Forms.TabControl();
            this.tabPage1 = new System.Windows.Forms.TabPage();
            this.button1 = new System.Windows.Forms.Button();
            this.chart1 = new System.Windows.Forms.DataVisualization.Charting.Chart();
            this.label3 = new System.Windows.Forms.Label();
            this.panel1 = new System.Windows.Forms.Panel();
            this.labelPower = new System.Windows.Forms.Label();
            this.labelMode = new System.Windows.Forms.Label();
            this.labelColS = new System.Windows.Forms.Label();
            this.labelColW = new System.Windows.Forms.Label();
            this.labelCubeS = new System.Windows.Forms.Label();
            this.labelCubeW = new System.Windows.Forms.Label();
            this.tabPage2 = new System.Windows.Forms.TabPage();
            this.buttonSave = new System.Windows.Forms.Button();
            this.button2 = new System.Windows.Forms.Button();
            this.buttonStartRec = new System.Windows.Forms.Button();
            this.textBox1 = new System.Windows.Forms.TextBox();
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.programBindingSource = new System.Windows.Forms.BindingSource(this.components);
            this.tabControl1.SuspendLayout();
            this.tabPage1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.chart1)).BeginInit();
            this.panel1.SuspendLayout();
            this.tabPage2.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.programBindingSource)).BeginInit();
            this.SuspendLayout();
            // 
            // tabControl1
            // 
            this.tabControl1.Controls.Add(this.tabPage1);
            this.tabControl1.Controls.Add(this.tabPage2);
            this.tabControl1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tabControl1.Location = new System.Drawing.Point(0, 0);
            this.tabControl1.Name = "tabControl1";
            this.tabControl1.SelectedIndex = 0;
            this.tabControl1.Size = new System.Drawing.Size(800, 450);
            this.tabControl1.TabIndex = 0;
            // 
            // tabPage1
            // 
            this.tabPage1.BackColor = System.Drawing.Color.LightSalmon;
            this.tabPage1.Controls.Add(this.button1);
            this.tabPage1.Controls.Add(this.chart1);
            this.tabPage1.Controls.Add(this.label3);
            this.tabPage1.Controls.Add(this.panel1);
            this.tabPage1.Location = new System.Drawing.Point(4, 22);
            this.tabPage1.Name = "tabPage1";
            this.tabPage1.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage1.Size = new System.Drawing.Size(792, 424);
            this.tabPage1.TabIndex = 0;
            this.tabPage1.Text = "tabPage1";
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(146, 274);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(75, 23);
            this.button1.TabIndex = 6;
            this.button1.Text = "connect";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // chart1
            // 
            this.chart1.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.chart1.BackColor = System.Drawing.Color.PeachPuff;
            this.chart1.BackGradientStyle = System.Windows.Forms.DataVisualization.Charting.GradientStyle.DiagonalRight;
            this.chart1.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.chart1.BackHatchStyle = System.Windows.Forms.DataVisualization.Charting.ChartHatchStyle.DarkHorizontal;
            this.chart1.BorderlineColor = System.Drawing.Color.Gold;
            this.chart1.BorderlineDashStyle = System.Windows.Forms.DataVisualization.Charting.ChartDashStyle.DashDotDot;
            chartArea1.AxisX.IntervalAutoMode = System.Windows.Forms.DataVisualization.Charting.IntervalAutoMode.VariableCount;
            chartArea1.AxisX.IntervalOffsetType = System.Windows.Forms.DataVisualization.Charting.DateTimeIntervalType.Minutes;
            chartArea1.AxisX.IntervalType = System.Windows.Forms.DataVisualization.Charting.DateTimeIntervalType.Minutes;
            chartArea1.AxisX.MaximumAutoSize = 25F;
            chartArea1.AxisY.Maximum = 105D;
            chartArea1.AxisY.Minimum = 60D;
            chartArea1.Name = "ChartArea1";
            this.chart1.ChartAreas.Add(chartArea1);
            legend1.Name = "Legend1";
            this.chart1.Legends.Add(legend1);
            this.chart1.Location = new System.Drawing.Point(272, 17);
            this.chart1.Name = "chart1";
            series1.BorderWidth = 3;
            series1.ChartArea = "ChartArea1";
            series1.ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Spline;
            series1.Color = System.Drawing.Color.Blue;
            series1.EmptyPointStyle.BorderWidth = 2;
            series1.Legend = "Legend1";
            series1.MarkerBorderWidth = 2;
            series1.Name = "cube";
            series1.XValueType = System.Windows.Forms.DataVisualization.Charting.ChartValueType.Time;
            series1.YValueType = System.Windows.Forms.DataVisualization.Charting.ChartValueType.Int32;
            series2.BorderWidth = 3;
            series2.ChartArea = "ChartArea1";
            series2.ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Spline;
            series2.Color = System.Drawing.Color.Lime;
            series2.Legend = "Legend1";
            series2.Name = "column";
            series2.ShadowColor = System.Drawing.Color.FromArgb(((int)(((byte)(224)))), ((int)(((byte)(224)))), ((int)(((byte)(224)))));
            series2.XValueType = System.Windows.Forms.DataVisualization.Charting.ChartValueType.Time;
            series2.YValueType = System.Windows.Forms.DataVisualization.Charting.ChartValueType.Int32;
            this.chart1.Series.Add(series1);
            this.chart1.Series.Add(series2);
            this.chart1.Size = new System.Drawing.Size(505, 390);
            this.chart1.TabIndex = 5;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Font = new System.Drawing.Font("Microsoft Sans Serif", 20.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.label3.Location = new System.Drawing.Point(23, 17);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(200, 31);
            this.label3.TabIndex = 4;
            this.label3.Text = "Device screen";
            // 
            // panel1
            // 
            this.panel1.BackColor = System.Drawing.Color.Navy;
            this.panel1.Controls.Add(this.labelPower);
            this.panel1.Controls.Add(this.labelMode);
            this.panel1.Controls.Add(this.labelColS);
            this.panel1.Controls.Add(this.labelColW);
            this.panel1.Controls.Add(this.labelCubeS);
            this.panel1.Controls.Add(this.labelCubeW);
            this.panel1.Location = new System.Drawing.Point(15, 60);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(222, 176);
            this.panel1.TabIndex = 3;
            // 
            // labelPower
            // 
            this.labelPower.AutoSize = true;
            this.labelPower.Font = new System.Drawing.Font("Microsoft Sans Serif", 20.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.labelPower.ForeColor = System.Drawing.Color.Aqua;
            this.labelPower.Location = new System.Drawing.Point(125, 113);
            this.labelPower.Name = "labelPower";
            this.labelPower.Size = new System.Drawing.Size(86, 31);
            this.labelPower.TabIndex = 5;
            this.labelPower.Text = "label6";
            // 
            // labelMode
            // 
            this.labelMode.AutoSize = true;
            this.labelMode.Font = new System.Drawing.Font("Microsoft Sans Serif", 15.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.labelMode.ForeColor = System.Drawing.Color.Aqua;
            this.labelMode.Location = new System.Drawing.Point(22, 118);
            this.labelMode.Name = "labelMode";
            this.labelMode.Size = new System.Drawing.Size(70, 25);
            this.labelMode.TabIndex = 4;
            this.labelMode.Text = "label5";
            // 
            // labelColS
            // 
            this.labelColS.AutoSize = true;
            this.labelColS.Font = new System.Drawing.Font("Microsoft Sans Serif", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.labelColS.ForeColor = System.Drawing.Color.Aqua;
            this.labelColS.Location = new System.Drawing.Point(127, 56);
            this.labelColS.Name = "labelColS";
            this.labelColS.Size = new System.Drawing.Size(60, 24);
            this.labelColS.TabIndex = 3;
            this.labelColS.Text = "label4";
            // 
            // labelColW
            // 
            this.labelColW.AutoSize = true;
            this.labelColW.Font = new System.Drawing.Font("Microsoft Sans Serif", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.labelColW.ForeColor = System.Drawing.Color.Aqua;
            this.labelColW.Location = new System.Drawing.Point(127, 24);
            this.labelColW.Name = "labelColW";
            this.labelColW.Size = new System.Drawing.Size(60, 24);
            this.labelColW.TabIndex = 2;
            this.labelColW.Text = "label3";
            // 
            // labelCubeS
            // 
            this.labelCubeS.AutoSize = true;
            this.labelCubeS.Font = new System.Drawing.Font("Microsoft Sans Serif", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.labelCubeS.ForeColor = System.Drawing.Color.Aqua;
            this.labelCubeS.Location = new System.Drawing.Point(29, 56);
            this.labelCubeS.Name = "labelCubeS";
            this.labelCubeS.Size = new System.Drawing.Size(60, 24);
            this.labelCubeS.TabIndex = 1;
            this.labelCubeS.Text = "label2";
            // 
            // labelCubeW
            // 
            this.labelCubeW.AutoSize = true;
            this.labelCubeW.Font = new System.Drawing.Font("Microsoft Sans Serif", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.labelCubeW.ForeColor = System.Drawing.Color.Aqua;
            this.labelCubeW.Location = new System.Drawing.Point(29, 24);
            this.labelCubeW.Name = "labelCubeW";
            this.labelCubeW.Size = new System.Drawing.Size(60, 24);
            this.labelCubeW.TabIndex = 0;
            this.labelCubeW.Text = "label1";
            this.labelCubeW.Click += new System.EventHandler(this.labelCubeW_Click);
            // 
            // tabPage2
            // 
            this.tabPage2.BackColor = System.Drawing.Color.Tan;
            this.tabPage2.Controls.Add(this.buttonSave);
            this.tabPage2.Controls.Add(this.button2);
            this.tabPage2.Controls.Add(this.buttonStartRec);
            this.tabPage2.Controls.Add(this.textBox1);
            this.tabPage2.Location = new System.Drawing.Point(4, 22);
            this.tabPage2.Name = "tabPage2";
            this.tabPage2.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage2.Size = new System.Drawing.Size(792, 424);
            this.tabPage2.TabIndex = 1;
            this.tabPage2.Text = "tabPage2";
            // 
            // buttonSave
            // 
            this.buttonSave.BackColor = System.Drawing.Color.LightSalmon;
            this.buttonSave.Location = new System.Drawing.Point(601, 123);
            this.buttonSave.Name = "buttonSave";
            this.buttonSave.Size = new System.Drawing.Size(183, 46);
            this.buttonSave.TabIndex = 3;
            this.buttonSave.Text = "SAVE DATA";
            this.buttonSave.UseVisualStyleBackColor = false;
            // 
            // button2
            // 
            this.button2.BackColor = System.Drawing.Color.LightSalmon;
            this.button2.Location = new System.Drawing.Point(601, 69);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(183, 48);
            this.button2.TabIndex = 2;
            this.button2.Text = "Do some important";
            this.button2.UseVisualStyleBackColor = false;
            // 
            // buttonStartRec
            // 
            this.buttonStartRec.BackColor = System.Drawing.Color.LightSalmon;
            this.buttonStartRec.Location = new System.Drawing.Point(601, 15);
            this.buttonStartRec.Name = "buttonStartRec";
            this.buttonStartRec.Size = new System.Drawing.Size(183, 48);
            this.buttonStartRec.TabIndex = 1;
            this.buttonStartRec.Text = "Start record";
            this.buttonStartRec.UseVisualStyleBackColor = false;
            // 
            // textBox1
            // 
            this.textBox1.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(128)))), ((int)(((byte)(64)))), ((int)(((byte)(0)))));
            this.textBox1.Dock = System.Windows.Forms.DockStyle.Left;
            this.textBox1.Font = new System.Drawing.Font("Yu Gothic Light", 10F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.textBox1.ForeColor = System.Drawing.Color.Lime;
            this.textBox1.Location = new System.Drawing.Point(3, 3);
            this.textBox1.Multiline = true;
            this.textBox1.Name = "textBox1";
            this.textBox1.Size = new System.Drawing.Size(472, 418);
            this.textBox1.TabIndex = 0;
            this.textBox1.Text = "<000.00,000.00,000.00,000.000>";
            // 
            // timer1
            // 
            this.timer1.Tick += new System.EventHandler(this.timer1_Tick);
            // 
            // programBindingSource
            // 
            this.programBindingSource.DataSource = typeof(samGerageDesktop.Program);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.DarkSalmon;
            this.ClientSize = new System.Drawing.Size(800, 450);
            this.Controls.Add(this.tabControl1);
            this.Name = "Form1";
            this.Text = "Form1";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.tabControl1.ResumeLayout(false);
            this.tabPage1.ResumeLayout(false);
            this.tabPage1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.chart1)).EndInit();
            this.panel1.ResumeLayout(false);
            this.panel1.PerformLayout();
            this.tabPage2.ResumeLayout(false);
            this.tabPage2.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.programBindingSource)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.TabControl tabControl1;
        private System.Windows.Forms.TabPage tabPage1;
        private System.Windows.Forms.DataVisualization.Charting.Chart chart1;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.Label labelPower;
      //  private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label labelMode;
       // private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label labelColS;
        private System.Windows.Forms.Label labelColW;
        private System.Windows.Forms.Label labelCubeS;
      //  private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label labelCubeW;
      
        private System.Windows.Forms.TabPage tabPage2;
        private System.Windows.Forms.Button buttonSave;
        private System.Windows.Forms.Button button2;
        private System.Windows.Forms.Button buttonStartRec;
        private System.Windows.Forms.TextBox textBox1;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Timer timer1;
        private System.Windows.Forms.BindingSource programBindingSource;
    }
}

