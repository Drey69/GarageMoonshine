using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using samGerageDesktop;

namespace samGerageDesktop
{
    public partial class Form1 : Form
    {
        State state;
        connectionSam  device;
        public Form1()
        {
            device = new connectionSam();
            state = new State();
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
             
        }

        private void button1_Click(object sender, EventArgs e)
        {

            if (timer1.Enabled)
            {
                timer1.Enabled = false;
                button1.Text = "connect";
                return;
            }
            if (!device.connect()) return; //ежли нету конкету
            timer1.Enabled = true;
            timer1.Start();
            button1.Text = "DISconnect";


        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            string str = device.tick() + Environment.NewLine;
            if (str.Length < 40) return;
            textBox1.AppendText(str);
            state.setData(str);
            Program.bigData.Add(state);
            chart1.Series["column"].Points.Add(state.columnTemp);
            chart1.Series["cube"].Points.Add(state.cubeTemp);
            labelColW.Text = state.columnTemp.ToString();
            labelColS.Text = state.columnTempConfigured.ToString();
            labelCubeW.Text = state.cubeTemp.ToString();
            labelCubeS.Text = state.cubeTempConfigured.ToString();
            labelMode.Text = state.mode.ToString();
            labelPower.Text = state.power.ToString();
        }

        private void labelCubeW_Click(object sender, EventArgs e)
        {

        }
    }
}
