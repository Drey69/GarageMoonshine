using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO.Ports;
using System.Windows.Forms;
using System.Globalization;


namespace samGerageDesktop
{
	public enum workMode
	{
		wm_off = 0,             //__OFF__
		wm_first,                   // 1 WORK
		wm_firstHeating,        // 1 HEAT
		wm_second,              // 2 WORK
		wm_secondHeating,   // 2 HEAT`
		wm_secondGetHeads,  // HEADS_
		wm_secondGetBody,   // _BODY_
		wm_secondsGetTail,  // _TAIL_
		wm_manual,              // MANUAL
		wm_wating,              // _WAIT_
		wm_over_ok              // _OVER_
	};
	public class State
	{
		private SerialPort port;
		public float cubeTemp { get; private set; }
		public float stableCubeTemp { get; private set; }    ///***
		public float stopGetHeadsTemp { get; private set; }      ///***
		public float columnTemp { get; private set; }
		public float stableColumnTemp { get; private set; }      ///***
		public float cubeTempConfigured { get; private set; }
		public float columnTempConfigured { get; private set; }
		public int power { get; private set; }
		public DateTime time { get; private set; }
		public DateTime timeCurrentMode { get; private set; }
		public workMode mode { get; private set; }

		
		public void setData(string dataStr)
        {
			string[] dataArr = new string[9];
			try
			{
				dataArr = dataStr.Split(',');
			}
			catch
			{
				MessageBox.Show("не разделилось", "ok");
			}

			//state.columnTemp;
			try
			{

				columnTemp = float.Parse(dataArr[0], CultureInfo.InvariantCulture.NumberFormat);			
				columnTempConfigured = float.Parse(dataArr[1], CultureInfo.InvariantCulture.NumberFormat);
				cubeTemp = float.Parse(dataArr[2], CultureInfo.InvariantCulture.NumberFormat);
				cubeTempConfigured = float.Parse(dataArr[3], CultureInfo.InvariantCulture.NumberFormat);
				mode = (workMode) int.Parse(dataArr[4]);
				power = int.Parse(dataArr[5]);
				// время тоже парсить надож
			}
			catch
            {
				MessageBox.Show("что то гдето не пропарсилося");
            }

		}

	
	};


}

