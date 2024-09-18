using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Runtime.InteropServices;
using System.IO;

namespace dllUI
{
    public partial class c__Draw : Form
    {
        private int scale = 5;
        [DllImport(@"dfxParser.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode)]
        static extern IntPtr getConverter(StringBuilder mode, StringBuilder input);
        [DllImport(@"dfxParser.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode)]
        static extern void deleteConverter(IntPtr obj);
        [DllImport(@"dfxParser.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode)]
        internal static extern void drawFigure(IntPtr obj, IntPtr hdc, out int scale);
        public c__Draw()
        {
            InitializeComponent();
        }

        private void c__Draw_Load(object sender, EventArgs e)
        {
            
        }

        private void c__Draw_Paint(object sender, PaintEventArgs e)
        {
            //MessageBox.Show(Form1.mode);
            StringBuilder output = new StringBuilder(Form1.path, Form1.path.Length + 1);
            StringBuilder outputMode = new StringBuilder(Form1.mode, Form1.mode.Length + 1);
            IntPtr converter = getConverter(outputMode, output);
            IntPtr formHdc = e.Graphics.GetHdc();
            drawFigure(converter, formHdc, out scale);
            e.Graphics.ReleaseHdc(formHdc);
            deleteConverter(converter);
        }

        private void trackBar1_Scroll(object sender, EventArgs e)
        {
            scale = trackBar1.Value;
            this.Invalidate();
        }
    }
}
