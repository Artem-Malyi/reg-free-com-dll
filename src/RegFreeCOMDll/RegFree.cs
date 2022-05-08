using System;
using System.Runtime.InteropServices;
using System.Windows.Forms;

namespace RegFreeCOMDll
{
    [Guid("7E7DB6F5-7A52-47F9-8C12-093BDA5B3811")]
    public class RegFree : IRegFree
    {
        public void RegFreeCOMHello(string message)
        {
            MessageBox.Show(message, "RegFreeCOMDll");
        }
    }
}
