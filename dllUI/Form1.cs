using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Windows.Forms;

namespace dllUI
{
    public partial class Form1 : Form
    {
        [DllImport(@"dfxParser.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode)]
        static extern IntPtr getConverter(StringBuilder mode, StringBuilder input);
        [DllImport(@"dfxParser.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode)]
        static extern void deleteConverter(IntPtr obj);
        [DllImport(@"dfxParser.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode)]
        internal static extern void MemoryLeaks(ref IntPtr s_array, ref int s_len);
        [DllImport(@"dfxParser.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode)]
        internal static extern IntPtr GetWindowHandle(IntPtr obj);
        [DllImport(@"dfxParser.dll", CallingConvention = CallingConvention.Cdecl, CharSet = CharSet.Unicode)]
        internal static extern void showWindow(IntPtr obj, int mode);

        public static List<List<double>> shapes = new List<List<double>>();
        public static string path = "";
        public static string mode = "";
        private List<string> modes = new List<string>();
        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            OpenFileDialog openFileDialog1 = new OpenFileDialog();
            DialogResult result = openFileDialog1.ShowDialog();
            if (result == DialogResult.OK)
            {
                string file = openFileDialog1.FileName;
                if(Path.GetFileName(openFileDialog1.FileName).Contains(".dfx"))
                {
                    path = file;
                    textBox1.Text = path;
                }
                else MessageBox.Show("Выбран неверный формат файла", "Ошибка");
            }
        }

        private void checkBox1_CheckedChanged(object sender, EventArgs e)
        {
            if(checkBox1.Checked)
            {
                modes.Add("all");
                checkBox2.Enabled = false; checkBox2.Checked = false;
                checkBox3.Enabled = false; checkBox3.Checked = false;
                checkBox4.Enabled = false; checkBox4.Checked = false;
                checkBox5.Enabled = false; checkBox5.Checked = false;
                checkBox6.Enabled = false; checkBox6.Checked = false;
            }
            else
            {
                modes.Clear();
                checkBox2.Enabled = true;
                checkBox3.Enabled = true;
                checkBox4.Enabled = true;
                checkBox5.Enabled = true;
                checkBox6.Enabled = true;
            }
        }

        private void checkBox2_CheckedChanged(object sender, EventArgs e)
        {
            if(checkBox2.Checked)
            {
                modes.Add("class Circle");
            }
            else
            {
                checkBox2.Tag = modes.IndexOf("class Circle");
                modes.Remove(modes[int.Parse(checkBox2.Tag.ToString())]);
            }
        }

        private void checkBox3_CheckedChanged(object sender, EventArgs e)
        {
            if (checkBox3.Checked)
            {
                modes.Add("class EllipseForm");
            }
            else
            {
                checkBox3.Tag = modes.IndexOf("class EllipseForm");
                modes.Remove(modes[int.Parse(checkBox3.Tag.ToString())]);
            }
        }

        private void checkBox4_CheckedChanged(object sender, EventArgs e)
        {
            if (checkBox4.Checked)
            {
                modes.Add("class Line");
            }
            else
            {
                checkBox4.Tag = modes.IndexOf("class Line");
                modes.Remove(modes[int.Parse(checkBox4.Tag.ToString())]);
            }
        }

        private void checkBox5_CheckedChanged(object sender, EventArgs e)
        {
            if (checkBox5.Checked)
            {
                modes.Add("class PolyLine");
            }
            else
            {
                checkBox5.Tag = modes.IndexOf("class PolyLine");
                modes.Remove(modes[int.Parse(checkBox5.Tag.ToString())]);
            }
        }

        private void checkBox6_CheckedChanged(object sender, EventArgs e)
        {
            if (checkBox6.Checked)
            {
                modes.Add("class Point");
            }
            else
            {
                checkBox6.Tag = modes.IndexOf("class Point");
                modes.Remove(modes[int.Parse(checkBox6.Tag.ToString())]);
            }
        }

        private void startPainting()
        {
            c__Draw form = new c__Draw();
            form.ShowDialog();
            //StringBuilder output = new StringBuilder(path, path.Length + 1);
            //StringBuilder outputMode = new StringBuilder(mode, mode.Length + 1);
            //IntPtr converter = getConverter(outputMode, output);
            //IntPtr hwnd = GetWindowHandle(converter);
            //showWindow(hwnd, 1);
            //deleteConverter(converter);
        }
        private void getData()
        {
            //StringBuilder output = new StringBuilder(path, path.Length + 1);
            //StringBuilder outputMode = new StringBuilder(mode, mode.Length + 1);
            //int countShapes;
            //IntPtr converter = getConverter(outputMode, output);
            //getSize(converter, out countShapes);

            //for (int i = 0; i < countShapes; i++)
            //{
            //    int countPoints = 0;
            //    IntPtr pointsPtr;
            //    getShape(converter, out pointsPtr, out countPoints, out i);
            //    double[] points = new double[countPoints];
            //    Marshal.Copy(pointsPtr, points, 0, countPoints);
            //    shapes.Add(points.ToList());
            //    Marshal.FreeCoTaskMem(pointsPtr);
            //}
            //deleteConverter(converter);

            startPainting();
        }
        private void button2_Click(object sender, EventArgs e)
        {
            mode = String.Join(",", modes);
            if (path == "" || mode == "")
                MessageBox.Show("Заполните данные", "Ошибка");
            else
            {
                shapes.Clear();
                getData();
            }
        }

        private void button3_Click(object sender, EventArgs e)
        {
            string s = "";
            IntPtr ip;
            ip = Marshal.StringToCoTaskMemUni(s);
            int len = s.Length;
            MemoryLeaks(ref ip, ref len);
            if (len > 0)
            {
                richTextBox1.Text = Marshal.PtrToStringUni(ip);
                Marshal.FreeCoTaskMem(ip);
            }
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            System.Windows.Forms.ToolTip t = new System.Windows.Forms.ToolTip();
            t.SetToolTip(button1, "Найдите файл формата .dfx");
            System.Windows.Forms.ToolTip t1 = new System.Windows.Forms.ToolTip();
            t1.SetToolTip(button2, "Отрисовать выбранный файл");
            System.Windows.Forms.ToolTip t2 = new System.Windows.Forms.ToolTip();
            t2.SetToolTip(button3, "Информация об утечках");
        }
    }
}
