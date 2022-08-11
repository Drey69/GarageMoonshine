using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Net.Sockets;
using System.Windows.Forms;
//using System.Timers;
namespace samGerageDesktop
{
    public class connectionSam
    {
        private const string ipRemote = "192.168.4.1";
        private const int portRemote = 23;
        private TcpClient socket;
        private int TimeOutMs = 2000;

        private Timer timer;
        private string message;
        public connectionSam()
        {
            message = "";
            try
            {
                socket = new TcpClient();
                socket.SendTimeout = TimeOutMs;

            }
            catch
            {
                MessageBox.Show(" socket not created...");
            }
        }

        public bool connect()
        {
            try {
                socket.Connect(ipRemote, portRemote);
            }
            catch
            {
                MessageBox.Show(" no conection FUCK FUCK FUCK;");
            }
            return socket.Connected;
        }
        public string tick()
        {
            message = String.Empty;

            if (socket.Available >= 45)
            {
                NetworkStream stream = socket.GetStream();
                byte[] data = new Byte[45];

                Int32 bytes = stream.Read(data, 0, 45);
                shiftArr(ref data);
                message = System.Text.Encoding.ASCII.GetString(data, 0, 45);

                message = message.Remove(0, 1);
                message = message.Remove(message.Length - 1, 1);
                
            }

            return message;

        }
          
        private void shiftArr(ref Byte[] arr)
        {
            Byte temp = 0;
            while (arr[0] != '<')
            {
                temp = arr[0];
                int o = arr.Length - 1;
                for (int i = 0; i < o; i++)
                {

                    arr[i] = arr[i + 1];
                };
                arr[arr.Length - 1] = temp;
            };

        }
    }
}
